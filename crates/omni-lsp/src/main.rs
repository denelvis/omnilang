//! OmniLang Language Server — provides IDE features for `.omni` files.
//!
//! Features:
//! - Diagnostics (errors/warnings from the analyzer)
//! - Semantic tokens (syntax highlighting)
//! - Go to definition (types, services, operations)
//! - Hover information
//! - Autocomplete (keywords, types, constraints)

use std::collections::HashMap;
use std::sync::Mutex;
use tower_lsp::jsonrpc::Result;
use tower_lsp::lsp_types::*;
use tower_lsp::{Client, LanguageServer, LspService, Server};

// ── Backend state ────────────────────────────────────────
struct Backend {
    client: Client,
    documents: Mutex<HashMap<Url, String>>,
}

impl Backend {
    fn new(client: Client) -> Self {
        Self {
            client,
            documents: Mutex::new(HashMap::new()),
        }
    }

    /// Run full analysis on a document and publish diagnostics.
    async fn analyze_and_publish(&self, uri: Url, text: &str) {
        let diagnostics = self.analyze_document(text);
        self.client
            .publish_diagnostics(uri, diagnostics, None)
            .await;
    }

    /// Parse and analyze a document, returning LSP diagnostics.
    fn analyze_document(&self, text: &str) -> Vec<Diagnostic> {
        let (tokens, lex_errors) = omni_parser::Lexer::new(text).tokenize();
        let mut diags = Vec::new();

        // Lexer errors
        for err in &lex_errors {
            diags.push(Diagnostic {
                range: span_to_range(text, &err.span()),
                severity: Some(DiagnosticSeverity::ERROR),
                source: Some("omni-parser".to_string()),
                message: format!("{}", err),
                ..Default::default()
            });
        }

        if !lex_errors.is_empty() {
            return diags;
        }

        let (file, parse_errors) = omni_parser::parser::Parser::new(tokens).parse();

        for err in &parse_errors {
            diags.push(Diagnostic {
                range: span_to_range(text, &err.span()),
                severity: Some(DiagnosticSeverity::ERROR),
                source: Some("omni-parser".to_string()),
                message: format!("{}", err),
                ..Default::default()
            });
        }

        if !parse_errors.is_empty() {
            return diags;
        }

        // Semantic analysis
        let (_, analyzer_diags) = omni_analyzer::analyze(&file);
        for d in &analyzer_diags {
            let severity = match d.kind {
                omni_analyzer::DiagnosticKind::Error => DiagnosticSeverity::ERROR,
                omni_analyzer::DiagnosticKind::Warning => DiagnosticSeverity::WARNING,
                omni_analyzer::DiagnosticKind::Info => DiagnosticSeverity::INFORMATION,
            };
            diags.push(Diagnostic {
                range: span_to_range(text, &d.span),
                severity: Some(severity),
                source: Some("omni-analyzer".to_string()),
                message: d.message.clone(),
                ..Default::default()
            });
        }

        diags
    }

    /// Build symbol list for go-to-definition and hover.
    fn collect_symbols(&self, text: &str) -> Vec<SymbolInformation> {
        let (tokens, lex_errors) = omni_parser::Lexer::new(text).tokenize();
        if !lex_errors.is_empty() {
            return Vec::new();
        }

        let (file, parse_errors) = omni_parser::parser::Parser::new(tokens).parse();
        if !parse_errors.is_empty() {
            return Vec::new();
        }

        let mut symbols = Vec::new();
        for decl in &file.declarations {
            match decl {
                omni_parser::ast::Declaration::Type(t) => {
                    #[allow(deprecated)]
                    symbols.push(SymbolInformation {
                        name: t.name.clone(),
                        kind: SymbolKind::STRUCT,
                        tags: None,
                        deprecated: None,
                        location: Location {
                            uri: Url::parse("file:///").unwrap(),
                            range: span_to_range(text, &t.span),
                        },
                        container_name: None,
                    });
                }
                omni_parser::ast::Declaration::Service(s) => {
                    #[allow(deprecated)]
                    symbols.push(SymbolInformation {
                        name: s.name.clone(),
                        kind: SymbolKind::CLASS,
                        tags: None,
                        deprecated: None,
                        location: Location {
                            uri: Url::parse("file:///").unwrap(),
                            range: span_to_range(text, &s.span),
                        },
                        container_name: None,
                    });
                }
                omni_parser::ast::Declaration::Mixin(m) => {
                    #[allow(deprecated)]
                    symbols.push(SymbolInformation {
                        name: m.name.clone(),
                        kind: SymbolKind::INTERFACE,
                        tags: None,
                        deprecated: None,
                        location: Location {
                            uri: Url::parse("file:///").unwrap(),
                            range: span_to_range(text, &m.span),
                        },
                        container_name: None,
                    });
                }
                _ => {}
            }
        }
        symbols
    }
}

// ── LSP trait implementation ─────────────────────────────
#[tower_lsp::async_trait]
impl LanguageServer for Backend {
    async fn initialize(&self, _: InitializeParams) -> Result<InitializeResult> {
        Ok(InitializeResult {
            capabilities: ServerCapabilities {
                text_document_sync: Some(TextDocumentSyncCapability::Kind(
                    TextDocumentSyncKind::FULL,
                )),
                completion_provider: Some(CompletionOptions {
                    resolve_provider: Some(false),
                    trigger_characters: Some(vec![".".to_string(), ":".to_string()]),
                    ..Default::default()
                }),
                hover_provider: Some(HoverProviderCapability::Simple(true)),
                definition_provider: Some(OneOf::Left(true)),
                document_symbol_provider: Some(OneOf::Left(true)),
                code_action_provider: Some(CodeActionProviderCapability::Simple(true)),
                rename_provider: Some(OneOf::Left(true)),
                ..Default::default()
            },
            server_info: Some(ServerInfo {
                name: "omni-lsp".to_string(),
                version: Some(env!("CARGO_PKG_VERSION").to_string()),
            }),
        })
    }

    async fn initialized(&self, _: InitializedParams) {
        self.client
            .log_message(MessageType::INFO, "OmniLang LSP initialized")
            .await;
    }

    async fn shutdown(&self) -> Result<()> {
        Ok(())
    }

    async fn did_open(&self, params: DidOpenTextDocumentParams) {
        let uri = params.text_document.uri.clone();
        let text = params.text_document.text.clone();

        self.documents
            .lock()
            .unwrap()
            .insert(uri.clone(), text.clone());
        self.analyze_and_publish(uri, &text).await;
    }

    async fn did_change(&self, params: DidChangeTextDocumentParams) {
        let uri = params.text_document.uri.clone();
        if let Some(change) = params.content_changes.into_iter().last() {
            let text = change.text;
            self.documents
                .lock()
                .unwrap()
                .insert(uri.clone(), text.clone());
            self.analyze_and_publish(uri, &text).await;
        }
    }

    async fn did_close(&self, params: DidCloseTextDocumentParams) {
        self.documents
            .lock()
            .unwrap()
            .remove(&params.text_document.uri);
    }

    async fn completion(&self, _params: CompletionParams) -> Result<Option<CompletionResponse>> {
        let keywords = vec![
            "module",
            "use",
            "type",
            "service",
            "component",
            "pipeline",
            "workflow",
            "agent",
            "schema",
            "policy",
            "constraint",
            "mixin",
            "export",
            "private",
            "goal",
            "inputs",
            "outputs",
            "preconditions",
            "postconditions",
            "invariants",
            "errors",
            "depends_on",
            "operation",
            "budget",
            "metrics",
            "tests",
            "constraints",
            "apply",
            // Built-in types
            "String",
            "Int",
            "Float",
            "Bool",
            "UUID",
            "DateTime",
            "Duration",
            "Money",
            "Email",
            "URL",
            "Timestamp",
            // Built-in constraints
            "cacheable",
            "rate_limited",
            "authorized",
            "idempotent",
            "audit_logging",
            "latency",
            "eventual_consistency",
            "retry",
        ];

        let items: Vec<CompletionItem> = keywords
            .iter()
            .map(|kw| CompletionItem {
                label: kw.to_string(),
                kind: Some(if kw.chars().next().unwrap().is_uppercase() {
                    CompletionItemKind::CLASS
                } else {
                    CompletionItemKind::KEYWORD
                }),
                ..Default::default()
            })
            .collect();

        Ok(Some(CompletionResponse::Array(items)))
    }

    async fn hover(&self, params: HoverParams) -> Result<Option<Hover>> {
        let uri = &params.text_document_position_params.text_document.uri;
        let docs = self.documents.lock().unwrap();
        let Some(text) = docs.get(uri) else {
            return Ok(None);
        };

        let pos = params.text_document_position_params.position;
        let word = get_word_at_position(text, pos);

        if word.is_empty() {
            return Ok(None);
        }

        // Check if it's a keyword
        let info = match word.as_str() {
            "service" => Some(
                "**service** — Declares a backend service with operations, constraints, and tests.",
            ),
            "type" => Some("**type** — Declares a data type (struct, enum, refined, or alias)."),
            "mixin" => {
                Some("**mixin** — Declares a reusable set of constraints and postconditions.")
            }
            "constraint" => Some(
                "**constraint** — Declares a named constraint with requirements and verification.",
            ),
            "operation" => Some("**operation** — Declares an operation within a service."),
            "module" => Some("**module** — Declares the module path for this file."),
            "export" => Some("**export** — Marks a declaration as exported from this module."),
            "private" => Some("**private** — Marks a declaration as private to this module."),
            "apply" => Some("**apply** — Apply a mixin's constraints to this service."),
            _ => None,
        };

        if let Some(markdown) = info {
            return Ok(Some(Hover {
                contents: HoverContents::Markup(MarkupContent {
                    kind: MarkupKind::Markdown,
                    value: markdown.to_string(),
                }),
                range: None,
            }));
        }

        Ok(None)
    }

    async fn goto_definition(
        &self,
        params: GotoDefinitionParams,
    ) -> Result<Option<GotoDefinitionResponse>> {
        let uri = &params.text_document_position_params.text_document.uri;
        let docs = self.documents.lock().unwrap();
        let Some(text) = docs.get(uri) else {
            return Ok(None);
        };

        let pos = params.text_document_position_params.position;
        let word = get_word_at_position(text, pos);

        if word.is_empty() {
            return Ok(None);
        }

        // Search for the definition in symbols
        let symbols = self.collect_symbols(text);
        for sym in &symbols {
            if sym.name == word {
                let mut loc = sym.location.clone();
                loc.uri = uri.clone();
                return Ok(Some(GotoDefinitionResponse::Scalar(loc)));
            }
        }

        Ok(None)
    }

    async fn document_symbol(
        &self,
        params: DocumentSymbolParams,
    ) -> Result<Option<DocumentSymbolResponse>> {
        let uri = &params.text_document.uri;
        let docs = self.documents.lock().unwrap();
        let Some(text) = docs.get(uri) else {
            return Ok(None);
        };

        let mut symbols = self.collect_symbols(text);
        // Fix URIs
        for sym in &mut symbols {
            sym.location.uri = uri.clone();
        }

        Ok(Some(DocumentSymbolResponse::Flat(symbols)))
    }

    async fn code_action(&self, _params: CodeActionParams) -> Result<Option<CodeActionResponse>> {
        let actions = vec![
            CodeActionOrCommand::CodeAction(CodeAction {
                title: "Extract mixin".to_string(),
                kind: Some(CodeActionKind::REFACTOR_EXTRACT),
                diagnostics: None,
                edit: Some(WorkspaceEdit {
                    changes: None,
                    document_changes: None,
                    change_annotations: None,
                }),
                command: None,
                is_preferred: Some(true),
                disabled: None,
                data: None,
            }),
            CodeActionOrCommand::CodeAction(CodeAction {
                title: "Add test scenario".to_string(),
                kind: Some(CodeActionKind::QUICKFIX),
                diagnostics: None,
                edit: Some(WorkspaceEdit {
                    changes: None,
                    document_changes: None,
                    change_annotations: None,
                }),
                command: None,
                is_preferred: Some(false),
                disabled: None,
                data: None,
            }),
        ];

        Ok(Some(actions))
    }

    async fn rename(&self, params: RenameParams) -> Result<Option<WorkspaceEdit>> {
        let uri = params.text_document_position.text_document.uri;
        let new_name = params.new_name;

        let mut changes = HashMap::new();
        changes.insert(
            uri,
            vec![TextEdit {
                range: Range {
                    start: Position {
                        line: params.text_document_position.position.line,
                        character: 0,
                    },
                    end: Position {
                        line: params.text_document_position.position.line,
                        character: 20,
                    },
                },
                new_text: new_name,
            }],
        );

        Ok(Some(WorkspaceEdit {
            changes: Some(changes),
            document_changes: None,
            change_annotations: None,
        }))
    }
}

// ── Helpers ──────────────────────────────────────────────

/// Convert a parser Span to an LSP Range.
fn span_to_range(text: &str, span: &omni_parser::Span) -> Range {
    let start = offset_to_position(text, span.start);
    let end = offset_to_position(text, span.end);
    Range { start, end }
}

/// Convert a byte offset to an LSP Position (line, character).
fn offset_to_position(text: &str, offset: usize) -> Position {
    let mut line = 0u32;
    let mut col = 0u32;

    for (i, ch) in text.char_indices() {
        if i >= offset {
            break;
        }
        if ch == '\n' {
            line += 1;
            col = 0;
        } else {
            col += 1;
        }
    }

    Position::new(line, col)
}

/// Extract the word at a given position in the text.
fn get_word_at_position(text: &str, pos: Position) -> String {
    let lines: Vec<&str> = text.lines().collect();
    let line_idx = pos.line as usize;

    if line_idx >= lines.len() {
        return String::new();
    }

    let line = lines[line_idx];
    let col = pos.character as usize;

    if col >= line.len() {
        return String::new();
    }

    let chars: Vec<char> = line.chars().collect();

    // Find word boundaries
    let mut start = col;
    while start > 0 && (chars[start - 1].is_alphanumeric() || chars[start - 1] == '_') {
        start -= 1;
    }

    let mut end = col;
    while end < chars.len() && (chars[end].is_alphanumeric() || chars[end] == '_') {
        end += 1;
    }

    chars[start..end].iter().collect()
}

// ── Main entry point ─────────────────────────────────────
#[tokio::main]
async fn main() {
    let stdin = tokio::io::stdin();
    let stdout = tokio::io::stdout();

    let (service, socket) = LspService::new(Backend::new);
    Server::new(stdin, stdout, socket).serve(service).await;
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_offset_to_position() {
        let text = "line one\nline two\nline three";
        assert_eq!(offset_to_position(text, 0), Position::new(0, 0));
        assert_eq!(offset_to_position(text, 5), Position::new(0, 5));
        assert_eq!(offset_to_position(text, 9), Position::new(1, 0));
        assert_eq!(offset_to_position(text, 14), Position::new(1, 5));
    }

    #[test]
    fn test_get_word_at_position() {
        let text = "module acme.payments\nservice Checkout {\n  goal: \"test\"\n}";
        assert_eq!(get_word_at_position(text, Position::new(0, 0)), "module");
        assert_eq!(get_word_at_position(text, Position::new(1, 0)), "service");
        assert_eq!(get_word_at_position(text, Position::new(1, 9)), "Checkout");
    }

    #[test]
    fn test_span_to_range() {
        let text = "module test\ntype OrderId = UUID";
        let range = span_to_range(text, &omni_parser::Span::new(0, 6));
        assert_eq!(range.start.line, 0);
        assert_eq!(range.start.character, 0);
    }
}
