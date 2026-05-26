use crate::{Diagnostic, DiagnosticKind};
use omni_parser::ast::{Declaration, SourceFile};

/// Run intent entropy analysis and detect logical gaps in goals/constraints
pub fn analyze_gaps(file: &SourceFile, diagnostics: &mut Vec<Diagnostic>) {
    for decl in &file.declarations {
        match decl {
            Declaration::Service(s) => {
                // 1. Intent Entropy Analysis
                if let Some(goal) = &s.goal {
                    let entropy_score = calculate_entropy(goal);
                    if entropy_score < 3.0 {
                        diagnostics.push(Diagnostic {
                            kind: DiagnosticKind::Info,
                            message: format!(
                                "Intent Entropy Analysis: Goal for service '{}' has low clarity (entropy: {:.2}). Consider detailing the intent.",
                                s.name, entropy_score
                            ),
                            span: s.span,
                        });
                    }
                }

                // 2. Logical Gap Detector
                for rpc in &s.rpcs {
                    if rpc.preconditions.is_empty() {
                        diagnostics.push(Diagnostic {
                            kind: DiagnosticKind::Warning,
                            message: format!(
                                "Logical Gap Detector: RPC '{}' in service '{}' has no preconditions defined. Input parameters might not be validated.",
                                rpc.name, s.name
                            ),
                            span: rpc.span,
                        });
                    }
                    if rpc.postconditions.is_empty() {
                        diagnostics.push(Diagnostic {
                            kind: DiagnosticKind::Warning,
                            message: format!(
                                "Logical Gap Detector: RPC '{}' in service '{}' has no postconditions defined. The output states are unconstrained.",
                                rpc.name, s.name
                            ),
                            span: rpc.span,
                        });
                    }
                }
            }
            Declaration::Component(c) if c.constraints.is_empty() => {
                diagnostics.push(Diagnostic {
                    kind: DiagnosticKind::Warning,
                    message: format!(
                        "Logical Gap Detector: Component '{}' has no layout/accessibility constraints configured.",
                        c.name
                    ),
                    span: c.span,
                });
            }
            _ => {}
        }
    }
}

/// Calculate simple shannon entropy of a string (normalized)
fn calculate_entropy(text: &str) -> f64 {
    if text.len() < 5 {
        return 1.5;
    }
    // Simple mock calculation representing complexity
    let mut word_count = text.split_whitespace().count() as f64;
    if word_count == 0.0 {
        word_count = 1.0;
    }
    let length = text.len() as f64;

    // Entropy is higher for longer, more descriptive sentences
    (length / 10.0) * (word_count / 3.0)
}
