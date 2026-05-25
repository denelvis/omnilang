//! Symbol table construction and name resolution.

use std::collections::HashMap;

use omni_parser::Span;
use omni_parser::ast::{Declaration, SourceFile, TypeKind};

use crate::{Diagnostic, DiagnosticKind};

/// A resolved symbol in the symbol table.
#[derive(Debug, Clone)]
pub struct Symbol {
    pub name: String,
    pub kind: SymbolKind,
    pub span: Span,
}

#[derive(Debug, Clone, PartialEq, Eq)]
pub enum SymbolKind {
    Type,
    Enum,
    Struct,
    Service,
}

/// The symbol table maps names to their definitions.
#[derive(Debug, Default)]
pub struct SymbolTable {
    symbols: HashMap<String, Symbol>,
}

impl SymbolTable {
    pub fn new() -> Self {
        Self::default()
    }

    pub fn insert(&mut self, name: String, symbol: Symbol) -> Option<Symbol> {
        self.symbols.insert(name, symbol)
    }

    pub fn get(&self, name: &str) -> Option<&Symbol> {
        self.symbols.get(name)
    }

    pub fn contains(&self, name: &str) -> bool {
        self.symbols.contains_key(name)
    }

    pub fn iter(&self) -> impl Iterator<Item = (&String, &Symbol)> {
        self.symbols.iter()
    }

    pub fn len(&self) -> usize {
        self.symbols.len()
    }

    pub fn is_empty(&self) -> bool {
        self.symbols.is_empty()
    }
}

/// Built-in types that are always available.
const BUILTIN_TYPES: &[&str] = &[
    "String",
    "Int",
    "Float",
    "Bool",
    "UUID",
    "Email",
    "URL",
    "DateTime",
    "Date",
    "Time",
    "Timestamp",
    "Duration",
    "Money",
    "Decimal",
    "Bytes",
    "Json",
    "Void",
    "Any",
    "List",
    "Set",
    "Map",
    "Option",
    "Result",
];

/// Build a symbol table from a parsed source file.
pub fn build_symbol_table(file: &SourceFile, diagnostics: &mut Vec<Diagnostic>) -> SymbolTable {
    let mut table = SymbolTable::new();

    // Register built-in types
    for &name in BUILTIN_TYPES {
        table.insert(
            name.to_string(),
            Symbol {
                name: name.to_string(),
                kind: SymbolKind::Type,
                span: Span::new(0, 0),
            },
        );
    }

    // Register all declarations
    for decl in &file.declarations {
        match decl {
            Declaration::Type(t) => {
                let kind = match &t.kind {
                    TypeKind::Enum(_) => SymbolKind::Enum,
                    TypeKind::Struct(_) => SymbolKind::Struct,
                    _ => SymbolKind::Type,
                };

                if let Some(prev) = table.get(&t.name)
                    && (prev.span.start != 0 || prev.span.end != 0)
                {
                    diagnostics.push(Diagnostic {
                        kind: DiagnosticKind::Error,
                        message: format!("duplicate type definition: '{}'", t.name),
                        span: t.span,
                    });
                }

                table.insert(
                    t.name.clone(),
                    Symbol {
                        name: t.name.clone(),
                        kind,
                        span: t.span,
                    },
                );
            }
            Declaration::Service(s) => {
                if let Some(prev) = table.get(&s.name)
                    && (prev.span.start != 0 || prev.span.end != 0)
                {
                    diagnostics.push(Diagnostic {
                        kind: DiagnosticKind::Error,
                        message: format!("duplicate service definition: '{}'", s.name),
                        span: s.span,
                    });
                }

                table.insert(
                    s.name.clone(),
                    Symbol {
                        name: s.name.clone(),
                        kind: SymbolKind::Service,
                        span: s.span,
                    },
                );
            }
        }
    }

    table
}

#[cfg(test)]
mod tests {
    use super::*;
    use omni_parser::Lexer;
    use omni_parser::parser::Parser;

    fn parse_and_build(input: &str) -> (SymbolTable, Vec<Diagnostic>) {
        let (tokens, _) = Lexer::new(input).tokenize();
        let (file, _) = Parser::new(tokens).parse();
        let mut diags = Vec::new();
        let table = build_symbol_table(&file, &mut diags);
        (table, diags)
    }

    #[test]
    fn builtin_types_are_registered() {
        let (table, _) = parse_and_build("module test");
        assert!(table.contains("String"));
        assert!(table.contains("Int"));
        assert!(table.contains("List"));
        assert!(table.contains("UUID"));
    }

    #[test]
    fn user_types_are_registered() {
        let (table, diags) =
            parse_and_build("module test\ntype OrderId = UUID\ntype Status = enum { Active }");
        assert!(diags.is_empty());
        assert!(table.contains("OrderId"));
        assert!(table.contains("Status"));
        assert_eq!(table.get("Status").unwrap().kind, SymbolKind::Enum);
    }

    #[test]
    fn services_are_registered() {
        let (table, diags) = parse_and_build("module test\nservice Checkout { goal: \"test\" }");
        assert!(diags.is_empty());
        assert!(table.contains("Checkout"));
        assert_eq!(table.get("Checkout").unwrap().kind, SymbolKind::Service);
    }

    #[test]
    fn duplicate_type_detected() {
        let (_, diags) = parse_and_build("module test\ntype OrderId = UUID\ntype OrderId = String");
        assert_eq!(diags.len(), 1);
        assert_eq!(diags[0].kind, DiagnosticKind::Error);
        assert!(diags[0].message.contains("duplicate"));
    }
}
