//! Type checking: validates that all type references resolve to defined types.

use omni_parser::ast::{Declaration, Field, SourceFile, TypeKind, TypeRef};

use crate::symbols::SymbolTable;
use crate::{Diagnostic, DiagnosticKind};

/// Check that all type references in the source file resolve to defined types.
pub fn check_types(file: &SourceFile, symbols: &SymbolTable, diagnostics: &mut Vec<Diagnostic>) {
    for decl in &file.declarations {
        match decl {
            Declaration::Type(t) => match &t.kind {
                TypeKind::Struct(s) => {
                    check_fields(&s.fields, symbols, diagnostics);
                }
                TypeKind::Refined(r) => {
                    check_type_ref(&r.base, symbols, diagnostics);
                }
                TypeKind::Alias(type_ref) => {
                    check_type_ref(type_ref, symbols, diagnostics);
                }
                TypeKind::Enum(e) => {
                    for variant in &e.variants {
                        check_fields(&variant.fields, symbols, diagnostics);
                    }
                }
            },
            Declaration::Service(s) => {
                for rpc in &s.rpcs {
                    check_fields(&rpc.inputs, symbols, diagnostics);
                    check_fields(&rpc.outputs, symbols, diagnostics);
                    for err_decl in &rpc.errors {
                        check_fields(&err_decl.fields, symbols, diagnostics);
                    }
                }
            }
        }
    }
}

fn check_fields(fields: &[Field], symbols: &SymbolTable, diagnostics: &mut Vec<Diagnostic>) {
    for field in fields {
        check_type_ref(&field.ty, symbols, diagnostics);
    }
}

fn check_type_ref(type_ref: &TypeRef, symbols: &SymbolTable, diagnostics: &mut Vec<Diagnostic>) {
    if !symbols.contains(&type_ref.name) {
        diagnostics.push(Diagnostic {
            kind: DiagnosticKind::Error,
            message: format!("undefined type: '{}'", type_ref.name),
            span: type_ref.span,
        });
    }

    // Check generic type arguments
    for arg in &type_ref.type_args {
        check_type_ref(arg, symbols, diagnostics);
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
}
