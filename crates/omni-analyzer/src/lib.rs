//! # omni-analyzer
//!
//! Semantic analyzer for OmniLang specifications.
//!
//! Takes an AST from `omni-parser` and performs:
//! - Name resolution (all types/services are defined)
//! - Type checking (inputs/outputs match between services)
//! - Constraint validation (detect conflicts)
//! - Dependency graph construction
//!
//! Produces a **Validated Spec IR** consumed by the orchestrator.

pub mod constraints;
pub mod deps;
pub mod ir;
pub mod symbols;
pub mod type_check;

use omni_parser::ParseError;
use omni_parser::ast::SourceFile;

pub use ir::SpecIR;
pub use symbols::SymbolTable;

/// Diagnostic message produced by the analyzer.
#[derive(Debug, Clone)]
pub struct Diagnostic {
    pub kind: DiagnosticKind,
    pub message: String,
    pub span: omni_parser::Span,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum DiagnosticKind {
    Error,
    Warning,
    Info,
}

impl std::fmt::Display for Diagnostic {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let prefix = match self.kind {
            DiagnosticKind::Error => "error",
            DiagnosticKind::Warning => "warning",
            DiagnosticKind::Info => "info",
        };
        write!(f, "{}: {}", prefix, self.message)
    }
}

/// Run the full analysis pipeline on a parsed source file.
/// Returns a validated SpecIR and any diagnostics.
pub fn analyze(file: &SourceFile) -> (Option<SpecIR>, Vec<Diagnostic>) {
    let mut diagnostics = Vec::new();

    // Phase 1: Build symbol table
    let symbol_table = symbols::build_symbol_table(file, &mut diagnostics);

    // Phase 2: Type checking
    type_check::check_types(file, &symbol_table, &mut diagnostics);

    // Phase 3: Constraint validation
    constraints::validate_constraints(file, &mut diagnostics);

    // Phase 4: Dependency graph
    let dep_graph = deps::build_dependency_graph(file, &mut diagnostics);

    // If there are errors, don't produce IR
    let has_errors = diagnostics.iter().any(|d| d.kind == DiagnosticKind::Error);

    if has_errors {
        return (None, diagnostics);
    }

    // Phase 5: Build Spec IR
    let ir = ir::build_spec_ir(file, &symbol_table, &dep_graph);

    (Some(ir), diagnostics)
}

/// Convenience: parse + analyze in one step
pub fn parse_and_analyze(source: &str) -> (Option<SpecIR>, Vec<Diagnostic>, Vec<ParseError>) {
    let (tokens, lex_errors) = omni_parser::Lexer::new(source).tokenize();

    if !lex_errors.is_empty() {
        return (None, Vec::new(), lex_errors);
    }

    let (file, parse_errors) = omni_parser::parser::Parser::new(tokens).parse();

    if !parse_errors.is_empty() {
        return (None, Vec::new(), parse_errors);
    }

    let (ir, diagnostics) = analyze(&file);
    (ir, diagnostics, Vec::new())
}
