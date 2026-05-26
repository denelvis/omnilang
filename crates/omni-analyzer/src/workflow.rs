use crate::{Diagnostic, DiagnosticKind};
use omni_parser::ast::{Declaration, SourceFile, WorkflowDecl};
use std::collections::{HashSet, VecDeque};

/// Check workflow transitions, detect dead states, and validate state definitions
pub fn check_workflows(file: &SourceFile, diagnostics: &mut Vec<Diagnostic>) {
    for decl in &file.declarations {
        if let Declaration::Workflow(w) = decl {
            validate_workflow_transitions(w, diagnostics);
            detect_dead_states(w, diagnostics);
        }
    }
}

fn validate_workflow_transitions(w: &WorkflowDecl, diagnostics: &mut Vec<Diagnostic>) {
    let states_set: HashSet<&str> = w.states.iter().map(|s| s.as_str()).collect();

    for trans in &w.transitions {
        // Validate from state
        if !states_set.contains(trans.from.as_str()) {
            diagnostics.push(Diagnostic {
                kind: DiagnosticKind::Error,
                message: format!(
                    "Workflow '{}': transition uses undefined source state '{}'",
                    w.name, trans.from
                ),
                span: trans.span,
            });
        }

        // Validate to state
        if !states_set.contains(trans.to.as_str()) {
            diagnostics.push(Diagnostic {
                kind: DiagnosticKind::Error,
                message: format!(
                    "Workflow '{}': transition uses undefined target state '{}'",
                    w.name, trans.to
                ),
                span: trans.span,
            });
        }

        // Validate timeout target state if configured
        if let Some(timeout) = trans
            .timeout
            .as_ref()
            .filter(|t| !states_set.contains(t.target_state.as_str()))
        {
            diagnostics.push(Diagnostic {
                kind: DiagnosticKind::Error,
                message: format!(
                    "Workflow '{}': timeout transition uses undefined target state '{}'",
                    w.name, timeout.target_state
                ),
                span: timeout.span,
            });
        }
    }
}

fn detect_dead_states(w: &WorkflowDecl, diagnostics: &mut Vec<Diagnostic>) {
    if w.states.is_empty() {
        return;
    }

    let start_state = &w.states[0];
    let mut visited = HashSet::new();
    let mut queue = VecDeque::new();

    visited.insert(start_state.as_str());
    queue.push_back(start_state.as_str());

    while let Some(current) = queue.pop_front() {
        for trans in &w.transitions {
            if trans.from == current && !visited.contains(trans.to.as_str()) {
                visited.insert(trans.to.as_str());
                queue.push_back(trans.to.as_str());
            }
            if let Some(timeout) = trans
                .timeout
                .as_ref()
                .filter(|t| trans.from == current && !visited.contains(t.target_state.as_str()))
            {
                visited.insert(timeout.target_state.as_str());
                queue.push_back(timeout.target_state.as_str());
            }
        }
    }

    for state in &w.states {
        if !visited.contains(state.as_str()) {
            diagnostics.push(Diagnostic {
                kind: DiagnosticKind::Warning,
                message: format!(
                    "Workflow '{}': state '{}' is unreachable (dead state)",
                    w.name, state
                ),
                span: w.span,
            });
        }
    }
}

/// Helper to generate Mermaid state machine representation
pub fn generate_mermaid_chart(w: &WorkflowDecl) -> String {
    let mut chart = String::new();
    chart.push_str("stateDiagram-v2\n");

    if !w.states.is_empty() {
        chart.push_str(&format!("  [*] --> {}\n", w.states[0]));
    }

    for trans in &w.transitions {
        let trigger = trans.trigger.as_deref().unwrap_or("transition");
        chart.push_str(&format!(
            "  {} --> {} : {}\n",
            trans.from, trans.to, trigger
        ));

        if let Some(timeout) = &trans.timeout {
            chart.push_str(&format!(
                "  {} --> {} : timeout\n",
                trans.from, timeout.target_state
            ));
        }
    }

    chart
}
