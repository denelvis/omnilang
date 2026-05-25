//! Spec IR — the validated intermediate representation output by the analyzer.

use omni_parser::ast::{Declaration, SourceFile, TypeKind};

use crate::deps::DependencyGraph;
use crate::symbols::SymbolTable;

/// Validated Specification IR — the output of the analysis phase.
/// This is consumed by the orchestrator/codegen pipeline.
#[derive(Debug, Clone, serde::Serialize)]
pub struct SpecIR {
    /// Module path: `["acme", "payments", "checkout"]`
    pub module_path: Vec<String>,
    /// The parsed source file AST containing all declarations
    pub source_file: SourceFile,
    /// All type definitions
    pub types: Vec<TypeDef>,
    /// All service definitions
    pub services: Vec<ServiceDef>,
    /// Build order (topologically sorted)
    pub build_order: Vec<String>,
    /// Summary statistics
    pub stats: SpecStats,
}

#[derive(Debug, Clone, serde::Serialize)]
pub struct TypeDef {
    pub name: String,
    pub kind: String, // "enum", "struct", "refined", "alias"
    pub field_count: usize,
}

#[derive(Debug, Clone, serde::Serialize)]
pub struct ServiceDef {
    pub name: String,
    pub goal: Option<String>,
    pub rpc_count: usize,
    pub rpc_names: Vec<String>,
    pub constraint_count: usize,
    pub constraint_names: Vec<String>,
    pub dependency_count: usize,
    pub test_count: usize,
    pub metric_count: usize,
    pub metric_names: Vec<String>,
}

#[derive(Debug, Clone, serde::Serialize)]
pub struct SpecStats {
    pub type_count: usize,
    pub service_count: usize,
    pub rpc_count: usize,
    pub test_count: usize,
    pub constraint_count: usize,
    pub metric_count: usize,
}

/// Build the validated Spec IR from analyzed data.
pub fn build_spec_ir(
    file: &SourceFile,
    _symbols: &SymbolTable,
    dep_graph: &DependencyGraph,
) -> SpecIR {
    let mut types = Vec::new();
    let mut services = Vec::new();
    let mut total_rpcs = 0;
    let mut total_tests = 0;
    let mut total_constraints = 0;
    let mut total_metrics = 0;

    for decl in &file.declarations {
        match decl {
            Declaration::Type(t) => {
                let (kind, field_count) = match &t.kind {
                    TypeKind::Enum(e) => ("enum".to_string(), e.variants.len()),
                    TypeKind::Struct(s) => ("struct".to_string(), s.fields.len()),
                    TypeKind::Refined(_) => ("refined".to_string(), 0),
                    TypeKind::Alias(_) => ("alias".to_string(), 0),
                };
                types.push(TypeDef {
                    name: t.name.clone(),
                    kind,
                    field_count,
                });
            }
            Declaration::Service(s) => {
                let rpc_names: Vec<String> = s.rpcs.iter().map(|r| r.name.clone()).collect();
                let constraint_names: Vec<String> =
                    s.constraints.iter().map(|c| c.name.clone()).collect();
                let metric_names: Vec<String> = s.metrics.iter().map(|m| m.name.clone()).collect();
                let test_count: usize = s.rpcs.iter().map(|r| r.tests.len()).sum();

                total_rpcs += s.rpcs.len();
                total_tests += test_count;
                total_constraints += s.constraints.len();
                total_metrics += s.metrics.len();

                services.push(ServiceDef {
                    name: s.name.clone(),
                    goal: s.goal.clone(),
                    rpc_count: s.rpcs.len(),
                    rpc_names,
                    constraint_count: s.constraints.len(),
                    constraint_names,
                    dependency_count: s.depends_on.len(),
                    test_count,
                    metric_count: s.metrics.len(),
                    metric_names,
                });
            }
        }
    }

    let stats = SpecStats {
        type_count: types.len(),
        service_count: services.len(),
        rpc_count: total_rpcs,
        test_count: total_tests,
        constraint_count: total_constraints,
        metric_count: total_metrics,
    };

    SpecIR {
        module_path: file.module.path.clone(),
        source_file: file.clone(),
        types,
        services,
        build_order: dep_graph.order.clone(),
        stats,
    }
}
