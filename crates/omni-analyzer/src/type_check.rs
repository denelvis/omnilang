//! Type checking: validates that all type references resolve to defined types.

#![allow(
    clippy::collapsible_if,
    clippy::collapsible_match,
    clippy::too_many_arguments
)]

use std::collections::HashMap;

use omni_parser::Span;
use omni_parser::ast::{
    BinaryOperator, Constraint, Declaration, Expression, Field, Literal, RefinedType, SourceFile,
    TypeKind, TypeRef,
};

use crate::symbols::SymbolTable;
use crate::{Diagnostic, DiagnosticKind};

/// Check that all type references in the source file resolve to defined types.
pub fn check_types(file: &SourceFile, symbols: &SymbolTable, diagnostics: &mut Vec<Diagnostic>) {
    for decl in &file.declarations {
        match decl {
            Declaration::Type(t) => {
                // Verify bounds on type parameters
                for param in &t.type_params {
                    for bound in &param.bounds {
                        check_type_ref(bound, symbols, &[], diagnostics);
                    }
                }

                let local_generics: Vec<String> =
                    t.type_params.iter().map(|p| p.name.clone()).collect();
                match &t.kind {
                    TypeKind::Struct(s) => {
                        check_fields(&s.fields, symbols, &local_generics, diagnostics);
                    }
                    TypeKind::Refined(r) => {
                        if let Some(base) = &r.base {
                            check_type_ref(base, symbols, &local_generics, diagnostics);
                        }
                        check_refined_type(r, symbols, diagnostics);
                    }
                    TypeKind::Alias(type_ref) => {
                        check_type_ref(type_ref, symbols, &local_generics, diagnostics);
                    }
                    TypeKind::Enum(e) => {
                        for variant in &e.variants {
                            check_fields(&variant.fields, symbols, &local_generics, diagnostics);
                        }
                    }
                }
            }
            Declaration::Service(s) => {
                for rpc in &s.rpcs {
                    check_fields(&rpc.inputs, symbols, &[], diagnostics);
                    check_fields(&rpc.outputs, symbols, &[], diagnostics);
                    for err_decl in &rpc.errors {
                        check_fields(&err_decl.fields, symbols, &[], diagnostics);
                    }
                }
            }
            Declaration::Component(c) => {
                check_fields(&c.props, symbols, &[], diagnostics);
                check_fields(&c.state, symbols, &[], diagnostics);
                check_fields(&c.slots, symbols, &[], diagnostics);
                for event in &c.events {
                    check_fields(&event.params, symbols, &[], diagnostics);
                }
            }
            Declaration::Agent(a) => {
                for tool in &a.tools {
                    check_fields(&tool.inputs, symbols, &[], diagnostics);
                    check_fields(&tool.outputs, symbols, &[], diagnostics);
                }
            }
            Declaration::Schema(s) => {
                for entity in &s.entities {
                    for field in &entity.fields {
                        check_type_ref(&field.ty, symbols, &[], diagnostics);
                    }
                }
            }
            Declaration::Pipeline(_)
            | Declaration::Workflow(_)
            | Declaration::Policy(_)
            | Declaration::Constraint(_) => {}
        }
    }

    check_constraints(file, symbols, diagnostics);
    check_contracts(file, symbols, diagnostics);
    check_type_narrowing(file, diagnostics);
    check_option_propagation(file, symbols, diagnostics);
}

fn check_fields(
    fields: &[Field],
    symbols: &SymbolTable,
    local_generics: &[String],
    diagnostics: &mut Vec<Diagnostic>,
) {
    for field in fields {
        check_type_ref(&field.ty, symbols, local_generics, diagnostics);
    }
}

fn check_type_ref(
    type_ref: &TypeRef,
    symbols: &SymbolTable,
    local_generics: &[String],
    diagnostics: &mut Vec<Diagnostic>,
) {
    if type_ref.name == "Union" {
        for member in &type_ref.union_members {
            check_type_ref(member, symbols, local_generics, diagnostics);
        }
        return;
    }
    if type_ref.name == "Intersection" {
        for member in &type_ref.intersection_members {
            check_type_ref(member, symbols, local_generics, diagnostics);
        }
        return;
    }

    if local_generics.contains(&type_ref.name) {
        if !type_ref.type_args.is_empty() {
            diagnostics.push(Diagnostic {
                kind: DiagnosticKind::Error,
                message: format!(
                    "generic parameter '{}' cannot have type arguments",
                    type_ref.name
                ),
                span: type_ref.span,
            });
        }
        return;
    }

    if let Some(symbol) = symbols.get(&type_ref.name) {
        // Validate type argument count
        if symbol.type_params.len() != type_ref.type_args.len() {
            diagnostics.push(Diagnostic {
                kind: DiagnosticKind::Error,
                message: format!(
                    "type '{}' expects {} type arguments, found {}",
                    type_ref.name,
                    symbol.type_params.len(),
                    type_ref.type_args.len()
                ),
                span: type_ref.span,
            });
        }

        // Validate bounds and check type args recursively
        for (i, arg) in type_ref.type_args.iter().enumerate() {
            check_type_ref(arg, symbols, local_generics, diagnostics);

            if i < symbol.type_params.len() {
                let param = &symbol.type_params[i];
                for bound in &param.bounds {
                    if !symbols.contains(bound) {
                        diagnostics.push(Diagnostic {
                            kind: DiagnosticKind::Error,
                            message: format!("undefined type bound: '{}'", bound),
                            span: type_ref.span,
                        });
                    }
                }
            }
        }
    } else {
        diagnostics.push(Diagnostic {
            kind: DiagnosticKind::Error,
            message: format!("undefined type: '{}'", type_ref.name),
            span: type_ref.span,
        });
    }
}

fn check_refined_type(
    r: &RefinedType,
    _symbols: &SymbolTable,
    diagnostics: &mut Vec<Diagnostic>,
) -> Option<String> {
    let base_name = r.base.as_ref().map(|b| b.name.clone());
    let mut inferred_from_constraints = None;

    for constraint in &r.constraints {
        match constraint.name.as_str() {
            "format" => {
                let valid = match &constraint.value {
                    Expression::Call { function, args, .. } => {
                        function == "regex"
                            && args.len() == 1
                            && matches!(&args[0], Expression::Literal(Literal::String(_)))
                    }
                    Expression::Literal(Literal::String(_)) => true,
                    _ => false,
                };
                if !valid {
                    diagnostics.push(Diagnostic {
                        kind: DiagnosticKind::Error,
                        message: "format constraint expects regex(\"pattern\") or a string literal"
                            .to_string(),
                        span: constraint.span,
                    });
                }
                inferred_from_constraints = Some("String".to_string());
            }
            "range" => {
                let valid = match &constraint.value {
                    Expression::List(elements, _) => {
                        elements.len() == 2
                            && elements.iter().all(|e| {
                                matches!(
                                    e,
                                    Expression::Literal(Literal::Int(_))
                                        | Expression::Literal(Literal::Float(_))
                                )
                            })
                    }
                    _ => false,
                };
                if !valid {
                    diagnostics.push(Diagnostic {
                        kind: DiagnosticKind::Error,
                        message: "range constraint expects a list of two numbers, e.g. [min, max]"
                            .to_string(),
                        span: constraint.span,
                    });
                }
                // Infer type: if range is invalid or has float, default to Float, else Int
                if inferred_from_constraints.is_none() {
                    let mut is_int = true;
                    if let Expression::List(elements, _) = &constraint.value {
                        if elements.len() == 2
                            && elements
                                .iter()
                                .any(|e| matches!(e, Expression::Literal(Literal::Float(_))))
                        {
                            is_int = false;
                        }
                    } else {
                        is_int = false; // default to float if malformed list
                    }
                    inferred_from_constraints = Some(if is_int {
                        "Int".to_string()
                    } else {
                        "Float".to_string()
                    });
                }
            }
            "min_length" | "max_length" => {
                let valid = matches!(&constraint.value, Expression::Literal(Literal::Int(_)));
                if !valid {
                    diagnostics.push(Diagnostic {
                        kind: DiagnosticKind::Error,
                        message: format!(
                            "{} constraint expects an integer literal",
                            constraint.name
                        ),
                        span: constraint.span,
                    });
                }
                if inferred_from_constraints.is_none() {
                    inferred_from_constraints = Some("String".to_string());
                }
            }
            "precision" => {
                let valid = matches!(&constraint.value, Expression::Literal(Literal::Int(_)));
                if !valid {
                    diagnostics.push(Diagnostic {
                        kind: DiagnosticKind::Error,
                        message: "precision constraint expects an integer literal".to_string(),
                        span: constraint.span,
                    });
                }
                inferred_from_constraints = Some("Decimal".to_string());
            }
            "example" => {}
            _ => {
                diagnostics.push(Diagnostic {
                    kind: DiagnosticKind::Error,
                    message: format!("unknown type constraint: '{}'", constraint.name),
                    span: constraint.span,
                });
            }
        }
    }

    let resolved_base = match (base_name, inferred_from_constraints) {
        (Some(b), _) => Some(b),
        (None, Some(inf)) => Some(inf),
        (None, None) => {
            diagnostics.push(Diagnostic {
                kind: DiagnosticKind::Error,
                message:
                    "cannot infer base type; please specify it explicitly (e.g. String { ... })"
                        .to_string(),
                span: r.span,
            });
            None
        }
    };

    if let Some(ref base) = resolved_base {
        for constraint in &r.constraints {
            if constraint.name == "example" {
                let compatible = match base.as_str() {
                    "String" => {
                        matches!(&constraint.value, Expression::Literal(Literal::String(_)))
                    }
                    "Int" => matches!(&constraint.value, Expression::Literal(Literal::Int(_))),
                    "Float" => matches!(
                        &constraint.value,
                        Expression::Literal(Literal::Float(_) | Literal::Int(_))
                    ),
                    "Decimal" => matches!(
                        &constraint.value,
                        Expression::Literal(Literal::Float(_) | Literal::Int(_))
                    ),
                    "Bool" => matches!(&constraint.value, Expression::Literal(Literal::Bool(_))),
                    _ => true,
                };
                if !compatible {
                    diagnostics.push(Diagnostic {
                        kind: DiagnosticKind::Error,
                        message: format!("example value is not compatible with base type {}", base),
                        span: constraint.span,
                    });
                }
            }
        }
    }

    resolved_base
}

pub fn check_constraints(
    file: &SourceFile,
    symbols: &SymbolTable,
    diagnostics: &mut Vec<Diagnostic>,
) {
    use std::collections::{HashMap, HashSet};

    // 1. Verify existence & validate args
    for decl in &file.declarations {
        match decl {
            Declaration::Service(s) => {
                check_service_conflicts(&s.name, &s.constraints, diagnostics);
                for c in &s.constraints {
                    check_constraint_existence(c, symbols, diagnostics);
                    validate_constraint_args(c, diagnostics);
                }
                for rpc in &s.rpcs {
                    check_service_conflicts(
                        &format!("{}.{}", s.name, rpc.name),
                        &rpc.constraints,
                        diagnostics,
                    );
                    for c in &rpc.constraints {
                        check_constraint_existence(c, symbols, diagnostics);
                        validate_constraint_args(c, diagnostics);
                    }
                }
            }
            Declaration::Component(c) => {
                for constraint in &c.constraints {
                    check_constraint_existence(constraint, symbols, diagnostics);
                    validate_constraint_args(constraint, diagnostics);
                }
            }
            Declaration::Pipeline(p) => {
                for constraint in &p.constraints {
                    check_constraint_existence(constraint, symbols, diagnostics);
                    validate_constraint_args(constraint, diagnostics);
                }
            }
            Declaration::Workflow(w) => {
                for constraint in &w.constraints {
                    check_constraint_existence(constraint, symbols, diagnostics);
                    validate_constraint_args(constraint, diagnostics);
                }
            }
            _ => {}
        }
    }

    // 2. Propagate constraints down the depends_on dependency chain
    let mut service_deps: HashMap<String, Vec<String>> = HashMap::new();
    let mut service_constraints: HashMap<String, Vec<String>> = HashMap::new();
    let mut service_spans: HashMap<String, Span> = HashMap::new();

    for decl in &file.declarations {
        if let Declaration::Service(s) = decl {
            service_deps.insert(s.name.clone(), s.depends_on.clone());
            let c_names: Vec<String> = s.constraints.iter().map(|c| c.name.clone()).collect();
            service_constraints.insert(s.name.clone(), c_names);
            service_spans.insert(s.name.clone(), s.span);
        }
    }

    let propagating_constraints = ["PCI_compliant", "GDPR", "authenticated", "audit_logging"];

    for (s_name, c_names) in &service_constraints {
        for c in c_names {
            if propagating_constraints.contains(&c.as_str()) {
                let mut visited = HashSet::new();
                let span = service_spans
                    .get(s_name)
                    .cloned()
                    .unwrap_or(Span::new(0, 0));
                check_transitive_propagation(
                    s_name,
                    s_name,
                    c,
                    &service_deps,
                    &service_constraints,
                    &mut visited,
                    diagnostics,
                    span,
                );
            }
        }
    }
}

fn check_constraint_existence(
    c: &Constraint,
    symbols: &SymbolTable,
    diagnostics: &mut Vec<Diagnostic>,
) {
    let builtins = vec![
        "idempotent",
        "cacheable",
        "rate_limited",
        "authenticated",
        "authorized",
        "latency",
        "audit_logging",
        "eventual_consistency",
        "anonymous",
    ];

    if !builtins.contains(&c.name.as_str()) && !symbols.contains(&c.name) {
        diagnostics.push(Diagnostic {
            kind: DiagnosticKind::Error,
            message: format!("undefined constraint: '{}'", c.name),
            span: c.span,
        });
    }
}

fn validate_constraint_args(c: &Constraint, diagnostics: &mut Vec<Diagnostic>) {
    match c.name.as_str() {
        "idempotent" | "authenticated" | "audit_logging" => {
            if !c.args.is_empty() {
                diagnostics.push(Diagnostic {
                    kind: DiagnosticKind::Error,
                    message: format!("constraint '{}' does not expect any arguments", c.name),
                    span: c.span,
                });
            }
        }
        "cacheable" => {
            if c.args.len() != 1 {
                diagnostics.push(Diagnostic {
                    kind: DiagnosticKind::Error,
                    message: "constraint 'cacheable' expects exactly 1 argument (ttl: Duration)"
                        .to_string(),
                    span: c.span,
                });
                return;
            }
            let arg = &c.args[0];
            if let Some(ref name) = arg.name {
                if name != "ttl" {
                    diagnostics.push(Diagnostic {
                        kind: DiagnosticKind::Error,
                        message: format!(
                            "unknown argument '{}' for constraint 'cacheable', expected 'ttl'",
                            name
                        ),
                        span: arg.span,
                    });
                }
            }
            if !matches!(&arg.value, Expression::Literal(Literal::Duration(_))) {
                diagnostics.push(Diagnostic {
                    kind: DiagnosticKind::Error,
                    message: "argument 'ttl' for 'cacheable' must be a Duration (e.g. 5min, 200ms)"
                        .to_string(),
                    span: arg.span,
                });
            }
        }
        "rate_limited" => {
            if c.args.len() != 2 {
                diagnostics.push(Diagnostic {
                    kind: DiagnosticKind::Error,
                    message: "constraint 'rate_limited' expects exactly 2 arguments (max: Int, window: Duration)".to_string(),
                    span: c.span,
                });
                return;
            }
            for (i, arg) in c.args.iter().enumerate() {
                let name = arg
                    .name
                    .as_deref()
                    .unwrap_or(if i == 0 { "max" } else { "window" });
                match name {
                    "max" => {
                        if !matches!(&arg.value, Expression::Literal(Literal::Int(_))) {
                            diagnostics.push(Diagnostic {
                                kind: DiagnosticKind::Error,
                                message: "argument 'max' for 'rate_limited' must be an integer"
                                    .to_string(),
                                span: arg.span,
                            });
                        }
                    }
                    "window" => {
                        if !matches!(&arg.value, Expression::Literal(Literal::Duration(_))) {
                            diagnostics.push(Diagnostic {
                                kind: DiagnosticKind::Error,
                                message: "argument 'window' for 'rate_limited' must be a Duration"
                                    .to_string(),
                                span: arg.span,
                            });
                        }
                    }
                    _ => {
                        diagnostics.push(Diagnostic {
                            kind: DiagnosticKind::Error,
                            message: format!("unknown argument '{}' for constraint 'rate_limited', expected 'max' or 'window'", name),
                            span: arg.span,
                        });
                    }
                }
            }
        }
        "authorized" => {
            if c.args.len() != 1 {
                diagnostics.push(Diagnostic {
                    kind: DiagnosticKind::Error,
                    message: "constraint 'authorized' expects exactly 1 argument (roles: [Role])"
                        .to_string(),
                    span: c.span,
                });
                return;
            }
            let arg = &c.args[0];
            if let Some(ref name) = arg.name {
                if name != "roles" {
                    diagnostics.push(Diagnostic {
                        kind: DiagnosticKind::Error,
                        message: format!(
                            "unknown argument '{}' for 'authorized', expected 'roles'",
                            name
                        ),
                        span: arg.span,
                    });
                }
            }
            if !matches!(&arg.value, Expression::List(_, _)) {
                diagnostics.push(Diagnostic {
                    kind: DiagnosticKind::Error,
                    message: "argument 'roles' for 'authorized' must be a list of roles, e.g. [Admin, User]".to_string(),
                    span: arg.span,
                });
            }
        }
        "latency" => {
            if c.args.is_empty() {
                diagnostics.push(Diagnostic {
                    kind: DiagnosticKind::Error,
                    message: "constraint 'latency' expects at least 1 percentile argument (e.g. p95: 50ms)".to_string(),
                    span: c.span,
                });
                return;
            }
            for arg in &c.args {
                match arg.name.as_deref() {
                    Some("p50") | Some("p95") | Some("p99") => {
                        if !matches!(&arg.value, Expression::Literal(Literal::Duration(_))) {
                            diagnostics.push(Diagnostic {
                                kind: DiagnosticKind::Error,
                                message: format!(
                                    "percentile '{}' value must be a Duration",
                                    arg.name.as_ref().unwrap()
                                ),
                                span: arg.span,
                            });
                        }
                    }
                    Some(other) => {
                        diagnostics.push(Diagnostic {
                            kind: DiagnosticKind::Error,
                            message: format!(
                                "unknown percentile '{}', expected p50, p95, or p99",
                                other
                            ),
                            span: arg.span,
                        });
                    }
                    None => {
                        diagnostics.push(Diagnostic {
                            kind: DiagnosticKind::Error,
                            message: "arguments to 'latency' must be named, e.g. p95: 50ms"
                                .to_string(),
                            span: arg.span,
                        });
                    }
                }
            }
        }
        "eventual_consistency" => {
            if c.args.len() != 1 {
                diagnostics.push(Diagnostic {
                    kind: DiagnosticKind::Error,
                    message: "constraint 'eventual_consistency' expects exactly 1 argument (max_lag: Duration)".to_string(),
                    span: c.span,
                });
                return;
            }
            let arg = &c.args[0];
            if let Some(ref name) = arg.name {
                if name != "max_lag" {
                    diagnostics.push(Diagnostic {
                        kind: DiagnosticKind::Error,
                        message: format!(
                            "unknown argument '{}' for 'eventual_consistency', expected 'max_lag'",
                            name
                        ),
                        span: arg.span,
                    });
                }
            }
            if !matches!(&arg.value, Expression::Literal(Literal::Duration(_))) {
                diagnostics.push(Diagnostic {
                    kind: DiagnosticKind::Error,
                    message: "argument 'max_lag' for 'eventual_consistency' must be a Duration"
                        .to_string(),
                    span: arg.span,
                });
            }
        }
        _ => {}
    }
}

fn check_service_conflicts(
    service_name: &str,
    constraints: &[Constraint],
    diagnostics: &mut Vec<Diagnostic>,
) {
    use std::collections::HashMap;
    let mut latency_percentiles: HashMap<String, String> = HashMap::new();
    let mut has_authenticated = false;
    let mut has_anonymous = false;

    for c in constraints {
        if c.name == "latency" {
            for arg in &c.args {
                if let Some(ref p_name) = arg.name {
                    if let Expression::Literal(Literal::Duration(d_val)) = &arg.value {
                        if let Some(prev_val) =
                            latency_percentiles.insert(p_name.clone(), d_val.clone())
                        {
                            if prev_val != *d_val {
                                diagnostics.push(Diagnostic {
                                    kind: DiagnosticKind::Error,
                                    message: format!(
                                        "conflicting latency requirements for '{}' in service '{}': {} vs {}",
                                        p_name, service_name, prev_val, d_val
                                    ),
                                    span: c.span,
                                });
                            }
                        }
                    }
                }
            }
        } else if c.name == "authenticated" {
            has_authenticated = true;
            if has_anonymous {
                diagnostics.push(Diagnostic {
                    kind: DiagnosticKind::Error,
                    message: format!(
                        "conflicting constraints on service '{}': 'authenticated' and 'anonymous'",
                        service_name
                    ),
                    span: c.span,
                });
            }
        } else if c.name == "anonymous" {
            has_anonymous = true;
            if has_authenticated {
                diagnostics.push(Diagnostic {
                    kind: DiagnosticKind::Error,
                    message: format!(
                        "conflicting constraints on service '{}': 'authenticated' and 'anonymous'",
                        service_name
                    ),
                    span: c.span,
                });
            }
        }
    }
}

fn check_transitive_propagation(
    start_service: &str,
    current_service: &str,
    constraint: &str,
    service_deps: &HashMap<String, Vec<String>>,
    service_constraints: &HashMap<String, Vec<String>>,
    visited: &mut std::collections::HashSet<String>,
    diagnostics: &mut Vec<Diagnostic>,
    span: Span,
) {
    if !visited.insert(current_service.to_string()) {
        return;
    }

    if let Some(deps) = service_deps.get(current_service) {
        for dep in deps {
            if let Some(constraints) = service_constraints.get(dep) {
                if !constraints.contains(&constraint.to_string()) {
                    diagnostics.push(Diagnostic {
                        kind: DiagnosticKind::Error,
                        message: format!(
                            "constraint '{}' propagates from service '{}' to depended-on service '{}', but '{}' is missing it",
                            constraint, start_service, dep, dep
                        ),
                        span,
                    });
                }
            }
            check_transitive_propagation(
                start_service,
                dep,
                constraint,
                service_deps,
                service_constraints,
                visited,
                diagnostics,
                span,
            );
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::symbols::build_symbol_table;
    use omni_parser::Lexer;
    use omni_parser::parser::Parser;

    fn parse_and_check(input: &str) -> Vec<Diagnostic> {
        let (tokens, _) = Lexer::new(input).tokenize();
        let (file, _) = Parser::new(tokens).parse();
        let mut diags = Vec::new();
        let table = build_symbol_table(&file, &mut diags);
        check_types(&file, &table, &mut diags);
        diags
    }

    #[test]
    fn valid_type_references() {
        let diags = parse_and_check(
            "module test\ntype OrderId = UUID\ntype Customer = struct { id: OrderId email: String }",
        );
        assert!(diags.is_empty(), "unexpected diags: {diags:?}");
    }

    #[test]
    fn undefined_type_reference() {
        let diags = parse_and_check("module test\ntype Customer = struct { id: NonExistent }");
        assert_eq!(diags.len(), 1);
        assert!(diags[0].message.contains("undefined type"));
        assert!(diags[0].message.contains("NonExistent"));
    }

    #[test]
    fn builtin_types_valid() {
        let diags = parse_and_check(
            "module test\ntype Order = struct { name: String count: Int id: UUID }",
        );
        assert!(diags.is_empty());
    }

    #[test]
    fn service_rpc_type_check() {
        let diags = parse_and_check(
            r#"module test
type OrderId = UUID
service Orders {
  goal: "Manage orders"
  rpc GetOrder {
    inputs:
      id: OrderId
    outputs:
      name: String
  }
}"#,
        );
        assert!(diags.is_empty());
    }

    #[test]
    fn service_rpc_undefined_type() {
        let diags = parse_and_check(
            r#"module test
service Orders {
  goal: "Manage orders"
  rpc GetOrder {
    inputs:
      id: NonExistentType
    outputs:
      name: String
  }
}"#,
        );
        assert_eq!(diags.len(), 1);
        assert!(diags[0].message.contains("NonExistentType"));
    }

    #[test]
    fn component_and_schema_type_check() {
        let diags = parse_and_check(
            r#"module test
type ProductId = UUID

component ProductCard {
  props:
    id: ProductId
    label: String
}

schema Inventory {
  entity Product {
    id: ProductId
    stock: Int
  }
}"#,
        );
        assert!(diags.is_empty(), "unexpected diags: {diags:?}");
    }

    #[test]
    fn component_and_schema_undefined_type() {
        let diags = parse_and_check(
            r#"module test
component ProductCard {
  props:
    id: NonExistentId
}
"#,
        );
        assert_eq!(diags.len(), 1);
        assert!(diags[0].message.contains("NonExistentId"));
    }

    #[test]
    fn refined_type_inference_and_validation() {
        let diags = parse_and_check(
            r#"module test
type Ref1 = String {
  format: regex("^[0-9]+$")
  min_length: 5
}
type Ref2 = {
  range: [1, 10]
}
type Ref3 = {
  precision: 4
}
"#,
        );
        assert!(diags.is_empty(), "unexpected errors: {diags:?}");

        let diags = parse_and_check(
            r#"module test
type Ref1 = String {
  format: 42
}
"#,
        );
        assert_eq!(diags.len(), 1, "Ref1 diags: {:?}", diags);
        assert!(diags[0].message.contains("format constraint expects regex"));

        let diags = parse_and_check(
            r#"module test
type Ref2 = {
  range: "not-a-list"
}
"#,
        );
        assert_eq!(diags.len(), 1, "Ref2 diags: {:?}", diags);
        assert!(diags[0].message.contains("range constraint expects a list"));

        let diags = parse_and_check(
            r#"module test
type Ref3 = String {
  example: 42
}
"#,
        );
        assert_eq!(diags.len(), 1, "Ref3 diags: {:?}", diags);
        assert!(diags[0].message.contains("example value is not compatible"));
    }

    #[test]
    fn generic_type_validation() {
        let diags = parse_and_check(
            r#"module test
type Container<T> = struct {
  value: T
}
type Item = Container<Int>
"#,
        );
        assert!(diags.is_empty(), "unexpected errors: {diags:?}");

        let diags = parse_and_check(
            r#"module test
type Container<T> = struct {
  value: T
}
type Item = Container<Int, String>
"#,
        );
        assert_eq!(diags.len(), 1, "Container diags: {:?}", diags);
        assert!(
            diags[0]
                .message
                .contains("expects 1 type arguments, found 2")
        );

        let diags = parse_and_check(
            r#"module test
type Bound = struct { id: Int }
type Container<T: Bound> = struct {
  value: T
}
type Item = Container<Int>
"#,
        );
        assert!(diags.is_empty(), "unexpected errors: {diags:?}");

        let diags = parse_and_check(
            r#"module test
type Container<T: NonExistentBound> = struct {
  value: T
}
"#,
        );
        assert_eq!(diags.len(), 1, "NonExistentBound diags: {:?}", diags);
        assert!(
            diags[0]
                .message
                .contains("undefined type: 'NonExistentBound'")
        );
    }

    #[test]
    fn test_constraint_existence_and_args() {
        let diags = parse_and_check(
            r#"module test
service Payments {
  goal: "Process payments"
  constraints:
    - cacheable(ttl: 5min)
    - rate_limited(max: 100, window: 1s)
    - authorized(roles: [Admin, User])
    - latency(p95: 50ms, p99: 100ms)
    - eventual_consistency(max_lag: 5s)
    - audit_logging
}"#,
        );
        assert!(diags.is_empty(), "unexpected errors: {diags:?}");

        let diags = parse_and_check(
            r#"module test
service Payments {
  goal: "Process payments"
  constraints:
    - undefined_constraint_xyz
}"#,
        );
        assert_eq!(diags.len(), 1);
        assert!(
            diags[0]
                .message
                .contains("undefined constraint: 'undefined_constraint_xyz'")
        );

        let diags = parse_and_check(
            r#"module test
service Payments {
  goal: "Process payments"
  constraints:
    - cacheable(ttl: "5min")
}"#,
        );
        assert_eq!(diags.len(), 1);
        assert!(diags[0].message.contains("must be a Duration"));
    }

    #[test]
    fn test_constraint_conflicts() {
        let diags = parse_and_check(
            r#"module test
service Payments {
  goal: "Process payments"
  constraints:
    - latency(p95: 50ms, p95: 100ms)
}"#,
        );
        assert_eq!(diags.len(), 1);
        assert!(
            diags[0]
                .message
                .contains("conflicting latency requirements for 'p95'")
        );

        let diags = parse_and_check(
            r#"module test
service Payments {
  goal: "Process payments"
  constraints:
    - authenticated
    - anonymous
}"#,
        );
        assert_eq!(diags.len(), 1);
        assert!(diags[0].message.contains(
            "conflicting constraints on service 'Payments': 'authenticated' and 'anonymous'"
        ));
    }

    #[test]
    fn test_constraint_transitive_propagation() {
        let diags = parse_and_check(
            r#"module test
constraint PCI_compliant {}
service Checkout {
  goal: "Checkout"
  depends_on:
    - Payments
  constraints:
    - PCI_compliant
}
service Payments {
  goal: "Payments"
  constraints:
    - PCI_compliant
}"#,
        );
        assert!(diags.is_empty(), "unexpected errors: {diags:?}");

        let diags = parse_and_check(
            r#"module test
constraint PCI_compliant {}
service Checkout {
  goal: "Checkout"
  depends_on:
    - Payments
  constraints:
    - PCI_compliant
}
service Payments {
  goal: "Payments"
}
"#,
        );
        assert_eq!(diags.len(), 1);
        assert!(diags[0].message.contains("constraint 'PCI_compliant' propagates from service 'Checkout' to depended-on service 'Payments', but 'Payments' is missing it"));
    }

    #[test]
    fn test_contracts_validation() {
        // Valid contracts
        let diags = parse_and_check(
            r#"module test
service Bank {
  goal: "Test"
  invariants:
    - balance >= 0
  rpc Withdraw {
    inputs:
      amount: Int
    outputs:
      new_balance: Int
    preconditions:
      - amount > 0
      - balance >= amount
    postconditions:
      - new_balance == old(balance) - amount
  }
}"#,
        );
        assert!(diags.is_empty(), "unexpected errors: {diags:?}");

        // old() in precondition (disallowed)
        let diags = parse_and_check(
            r#"module test
service Bank {
  goal: "Test"
  rpc Withdraw {
    inputs:
      amount: Int
    preconditions:
      - old(amount) > 0
  }
}"#,
        );
        assert_eq!(diags.len(), 1);
        assert!(
            diags[0]
                .message
                .contains("old() is only allowed in postconditions")
        );
    }
}

pub fn check_contracts(
    file: &SourceFile,
    symbols: &SymbolTable,
    diagnostics: &mut Vec<Diagnostic>,
) {
    for decl in &file.declarations {
        if let Declaration::Service(s) = decl {
            for inv in &s.invariants {
                check_contract_expr(
                    inv,
                    ContractExprContext::Invariant,
                    &[],
                    &[],
                    symbols,
                    diagnostics,
                );
            }

            for rpc in &s.rpcs {
                let rpc_inputs: Vec<String> = rpc.inputs.iter().map(|i| i.name.clone()).collect();
                let rpc_outputs: Vec<String> = rpc.outputs.iter().map(|o| o.name.clone()).collect();

                for pre in &rpc.preconditions {
                    check_contract_expr(
                        pre,
                        ContractExprContext::Precondition,
                        &rpc_inputs,
                        &[],
                        symbols,
                        diagnostics,
                    );
                }

                for post in &rpc.postconditions {
                    check_contract_expr(
                        post,
                        ContractExprContext::Postcondition,
                        &rpc_inputs,
                        &rpc_outputs,
                        symbols,
                        diagnostics,
                    );
                }
            }
        }
    }
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
enum ContractExprContext {
    Precondition,
    Postcondition,
    Invariant,
}

#[allow(clippy::only_used_in_recursion)]
fn check_contract_expr(
    expr: &Expression,
    context: ContractExprContext,
    inputs: &[String],
    outputs: &[String],
    symbols: &SymbolTable,
    diagnostics: &mut Vec<Diagnostic>,
) {
    match expr {
        Expression::Literal(_) => {}
        Expression::Identifier(name, span) => {
            if name != "self" && name != "result" {
                if let Some(c) = name.chars().next() {
                    if c.is_uppercase() && !symbols.contains(name) {
                        diagnostics.push(Diagnostic {
                            kind: DiagnosticKind::Error,
                            message: format!("undefined symbol: '{}'", name),
                            span: *span,
                        });
                    }
                }
            }
        }
        Expression::Call {
            function,
            type_args,
            args,
            span,
        } => {
            if function == "old" {
                if context != ContractExprContext::Postcondition {
                    diagnostics.push(Diagnostic {
                        kind: DiagnosticKind::Error,
                        message: "old() is only allowed in postconditions".to_string(),
                        span: *span,
                    });
                }
                if args.len() != 1 {
                    diagnostics.push(Diagnostic {
                        kind: DiagnosticKind::Error,
                        message: "old() expects exactly 1 argument".to_string(),
                        span: *span,
                    });
                }
            }
            if let Some(t_args) = type_args {
                for t in t_args {
                    check_type_ref(t, symbols, &[], diagnostics);
                }
            }
            for arg in args {
                check_contract_expr(arg, context, inputs, outputs, symbols, diagnostics);
            }
        }
        Expression::BinaryOp { left, right, .. } => {
            check_contract_expr(left, context, inputs, outputs, symbols, diagnostics);
            check_contract_expr(right, context, inputs, outputs, symbols, diagnostics);
        }
        Expression::UnaryOp { operand, .. } => {
            check_contract_expr(operand, context, inputs, outputs, symbols, diagnostics);
        }
        Expression::FieldAccess { object, .. } => {
            check_contract_expr(object, context, inputs, outputs, symbols, diagnostics);
        }
        Expression::List(elements, _) => {
            for el in elements {
                check_contract_expr(el, context, inputs, outputs, symbols, diagnostics);
            }
        }
    }
}

/// Check for type narrowing opportunities in conditions.
/// Emits an info diagnostic when an optional field is compared directly without a null-check,
/// suggesting the user add a null-guard for proper type narrowing.
fn check_type_narrowing(file: &SourceFile, diagnostics: &mut Vec<Diagnostic>) {
    for decl in &file.declarations {
        if let Declaration::Service(s) = decl {
            for rpc in &s.rpcs {
                // Check preconditions for optional field comparisons without null-checks
                for pre in &rpc.preconditions {
                    check_narrowing_in_expr(pre, &rpc.inputs, diagnostics);
                }
            }
        }
    }
}

/// Walk an expression looking for comparisons on optional fields without a null guard.
fn check_narrowing_in_expr(expr: &Expression, fields: &[Field], diagnostics: &mut Vec<Diagnostic>) {
    match expr {
        Expression::BinaryOp {
            left, op, right, ..
        } => {
            // Check if either side is an optional field being compared directly
            if !matches!(op, BinaryOperator::Eq | BinaryOperator::NotEq) {
                // For non-equality operators (e.g. >, <, >=, <=) on optional fields,
                // suggest a null check
                if let Some((name, span)) = extract_optional_field_ref(left, fields) {
                    if !is_null_check(expr) {
                        diagnostics.push(Diagnostic {
                            kind: DiagnosticKind::Info,
                            message: format!(
                                "field '{}' has optional type; consider adding a null-check \
                                 guard for type narrowing (e.g. '{} != null')",
                                name, name
                            ),
                            span,
                        });
                    }
                }
                if let Some((name, span)) = extract_optional_field_ref(right, fields) {
                    if !is_null_check(expr) {
                        diagnostics.push(Diagnostic {
                            kind: DiagnosticKind::Info,
                            message: format!(
                                "field '{}' has optional type; consider adding a null-check \
                                 guard for type narrowing (e.g. '{} != null')",
                                name, name
                            ),
                            span,
                        });
                    }
                }
            }
            check_narrowing_in_expr(left, fields, diagnostics);
            check_narrowing_in_expr(right, fields, diagnostics);
        }
        Expression::UnaryOp { operand, .. } => {
            check_narrowing_in_expr(operand, fields, diagnostics);
        }
        Expression::Call { args, .. } => {
            for arg in args {
                check_narrowing_in_expr(arg, fields, diagnostics);
            }
        }
        Expression::FieldAccess { object, .. } => {
            check_narrowing_in_expr(object, fields, diagnostics);
        }
        Expression::List(elements, _) => {
            for el in elements {
                check_narrowing_in_expr(el, fields, diagnostics);
            }
        }
        _ => {}
    }
}

/// Extract (field_name, span) if the expression references an optional-typed field.
fn extract_optional_field_ref(expr: &Expression, fields: &[Field]) -> Option<(String, Span)> {
    if let Expression::Identifier(name, span) = expr {
        for field in fields {
            if field.name == *name && field.ty.name == "Option" {
                return Some((name.clone(), *span));
            }
        }
    }
    None
}

/// Check whether an expression is a null-check (x == null or x != null).
fn is_null_check(expr: &Expression) -> bool {
    if let Expression::BinaryOp {
        left, op, right, ..
    } = expr
    {
        if matches!(op, BinaryOperator::Eq | BinaryOperator::NotEq) {
            let lhs_is_null = matches!(right.as_ref(), Expression::Literal(Literal::Null));
            let rhs_is_null = matches!(left.as_ref(), Expression::Literal(Literal::Null));
            return lhs_is_null || rhs_is_null;
        }
    }
    false
}

/// Check for Option<T> propagation in postconditions.
/// If a postcondition references an output field whose type is optional,
/// emit an info diagnostic suggesting the user handle the None case.
fn check_option_propagation(
    file: &SourceFile,
    _symbols: &SymbolTable,
    diagnostics: &mut Vec<Diagnostic>,
) {
    for decl in &file.declarations {
        if let Declaration::Service(s) = decl {
            for rpc in &s.rpcs {
                let optional_outputs: Vec<String> = rpc
                    .outputs
                    .iter()
                    .filter(|f| f.ty.name == "Option")
                    .map(|f| f.name.clone())
                    .collect();

                if optional_outputs.is_empty() {
                    continue;
                }

                for post in &rpc.postconditions {
                    check_option_refs_in_expr(post, &optional_outputs, diagnostics);
                }
            }
        }
    }
}

/// Walk a postcondition expression and warn if it references an optional output
/// without going through a null-check gate first.
fn check_option_refs_in_expr(
    expr: &Expression,
    optional_names: &[String],
    diagnostics: &mut Vec<Diagnostic>,
) {
    match expr {
        Expression::FieldAccess {
            object,
            field: _,
            span,
        } => {
            // Check if the base object is an optional output being accessed without unwrap
            if let Expression::Identifier(name, _) = object.as_ref() {
                if optional_names.contains(name) {
                    diagnostics.push(Diagnostic {
                        kind: DiagnosticKind::Info,
                        message: format!(
                            "output '{}' has optional type; accessing field on it \
                             may fail if null — consider adding a null-check guard",
                            name
                        ),
                        span: *span,
                    });
                }
            }
            check_option_refs_in_expr(object, optional_names, diagnostics);
        }
        Expression::BinaryOp { left, right, .. } => {
            check_option_refs_in_expr(left, optional_names, diagnostics);
            check_option_refs_in_expr(right, optional_names, diagnostics);
        }
        Expression::UnaryOp { operand, .. } => {
            check_option_refs_in_expr(operand, optional_names, diagnostics);
        }
        Expression::Call { args, .. } => {
            for arg in args {
                check_option_refs_in_expr(arg, optional_names, diagnostics);
            }
        }
        Expression::List(elements, _) => {
            for el in elements {
                check_option_refs_in_expr(el, optional_names, diagnostics);
            }
        }
        _ => {}
    }
}

#[cfg(test)]
mod narrowing_tests {
    use super::*;
    use crate::symbols;

    fn analyze_and_collect(source: &str) -> Vec<Diagnostic> {
        let (tokens, _) = omni_parser::Lexer::new(source).tokenize();
        let (file, _) = omni_parser::parser::Parser::new(tokens).parse();
        let mut diags = Vec::new();
        let symbols = symbols::build_symbol_table(&file, &mut diags);
        check_types(&file, &symbols, &mut diags);
        diags
    }

    #[test]
    fn test_type_narrowing_warns_on_optional_comparison() {
        let source = r#"
module test

service PaymentService {
  rpc Pay {
    inputs:
      discount: Float?
    preconditions:
      - discount > 0
  }
}
"#;
        let diags = analyze_and_collect(source);
        let infos: Vec<_> = diags
            .iter()
            .filter(|d| d.kind == DiagnosticKind::Info && d.message.contains("null-check"))
            .collect();
        assert!(
            !infos.is_empty(),
            "expected info about null-check on optional field"
        );
    }

    #[test]
    fn test_type_narrowing_no_warn_for_non_optional() {
        let source = r#"
module test

service PaymentService {
  rpc Pay {
    inputs:
      amount: Float
    preconditions:
      - amount > 0
  }
}
"#;
        let diags = analyze_and_collect(source);
        let infos: Vec<_> = diags
            .iter()
            .filter(|d| d.kind == DiagnosticKind::Info && d.message.contains("null-check"))
            .collect();
        assert!(
            infos.is_empty(),
            "should not warn for non-optional field: {:?}",
            infos
        );
    }

    #[test]
    fn test_option_propagation_warns_on_field_access() {
        let source = r#"
module test

service PaymentService {
  rpc Pay {
    inputs:
      amount: Float
    outputs:
      receipt: Receipt?
    postconditions:
      - receipt.id != ""
  }
}
"#;
        let diags = analyze_and_collect(source);
        let infos: Vec<_> = diags
            .iter()
            .filter(|d| {
                d.kind == DiagnosticKind::Info
                    && d.message.contains("optional type")
                    && d.message.contains("receipt")
            })
            .collect();
        assert!(
            !infos.is_empty(),
            "expected info about optional output field access"
        );
    }

    #[test]
    fn test_option_propagation_no_warn_for_non_optional_output() {
        let source = r#"
module test

service PaymentService {
  rpc Pay {
    inputs:
      amount: Float
    outputs:
      receipt: Receipt
    postconditions:
      - receipt.id != ""
  }
}
"#;
        let diags = analyze_and_collect(source);
        let infos: Vec<_> = diags
            .iter()
            .filter(|d| {
                d.kind == DiagnosticKind::Info
                    && d.message.contains("optional type")
                    && d.message.contains("receipt")
            })
            .collect();
        assert!(
            infos.is_empty(),
            "should not warn for non-optional output: {:?}",
            infos
        );
    }
}
