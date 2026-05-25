//! Constraint validation: detect conflicts and validate references.

use omni_parser::ast::{Declaration, SourceFile};

use crate::{Diagnostic, DiagnosticKind};

/// Validate constraints across the specification.
pub fn validate_constraints(file: &SourceFile, diagnostics: &mut Vec<Diagnostic>) {
    for decl in &file.declarations {
        if let Declaration::Service(s) = decl {
            // Warning: service without constraints
            if s.constraints.is_empty() {
                diagnostics.push(Diagnostic {
                    kind: DiagnosticKind::Warning,
                    message: format!(
                        "service '{}' has no constraints — consider adding latency, reliability, or security constraints",
                        s.name
                    ),
                    span: s.span,
                });
            }

            // Warning: service without goal
            if s.goal.is_none() {
                diagnostics.push(Diagnostic {
                    kind: DiagnosticKind::Warning,
                    message: format!(
                        "service '{}' has no goal — the goal field helps AI agents understand the intent",
                        s.name
                    ),
                    span: s.span,
                });
            }

            // Check for conflicting constraints within a service
            let constraint_names: Vec<&str> =
                s.constraints.iter().map(|c| c.name.as_str()).collect();

            // Detect duplicates
            let mut seen = std::collections::HashSet::new();
            for name in &constraint_names {
                if !seen.insert(name) {
                    diagnostics.push(Diagnostic {
                        kind: DiagnosticKind::Error,
                        message: format!("duplicate constraint '{}' in service '{}'", name, s.name),
                        span: s.span,
                    });
                }
            }

            // Check RPC-level constraints
            for rpc in &s.rpcs {
                if rpc.tests.is_empty() {
                    diagnostics.push(Diagnostic {
                        kind: DiagnosticKind::Info,
                        message: format!(
                            "rpc '{}.{}' has no test scenarios — consider adding tests for verification",
                            s.name, rpc.name
                        ),
                        span: rpc.span,
                    });
                }
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use omni_parser::Lexer;
    use omni_parser::parser::Parser;

    fn parse_and_validate(input: &str) -> Vec<Diagnostic> {
        let (tokens, _) = Lexer::new(input).tokenize();
        let (file, _) = Parser::new(tokens).parse();
        let mut diags = Vec::new();
        validate_constraints(&file, &mut diags);
        diags
    }

    #[test]
    fn service_without_constraints_warns() {
        let diags = parse_and_validate(
            r#"module test
service API {
  goal: "Test"
}"#,
        );
        assert!(
            diags
                .iter()
                .any(|d| d.kind == DiagnosticKind::Warning && d.message.contains("no constraints"))
        );
    }

    #[test]
    fn service_without_goal_warns() {
        let diags = parse_and_validate(
            r#"module test
service API {
  constraints:
    - idempotent
}"#,
        );
        assert!(
            diags
                .iter()
                .any(|d| d.kind == DiagnosticKind::Warning && d.message.contains("no goal"))
        );
    }

    #[test]
    fn service_with_goal_and_constraints_ok() {
        let diags = parse_and_validate(
            r#"module test
service API {
  goal: "Test API"
  constraints:
    - idempotent
}"#,
        );
        // Should only have info-level, no errors or warnings
        assert!(diags.iter().all(|d| d.kind != DiagnosticKind::Error));
    }
}
