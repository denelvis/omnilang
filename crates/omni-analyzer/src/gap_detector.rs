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

/// Calculate Shannon entropy of a string
fn calculate_entropy(text: &str) -> f64 {
    if text.is_empty() {
        return 0.0;
    }
    let mut counts = std::collections::HashMap::new();
    for c in text.chars() {
        *counts.entry(c).or_insert(0) += 1;
    }
    let total = text.chars().count() as f64;
    let mut entropy = 0.0;
    for &count in counts.values() {
        let p = count as f64 / total;
        entropy -= p * p.log2();
    }
    entropy
}
