//! Parser for OmniLang source files.
//!
//! Transforms a token stream into an Abstract Syntax Tree (AST).
//! Uses recursive descent with Pratt parsing for expressions.

use crate::ast::*;
use crate::error::ParseError;
use crate::span::Span;
use crate::token::{Token, TokenKind};

/// Parser state: walks through the token stream.
pub struct Parser {
    tokens: Vec<Token>,
    pos: usize,
    errors: Vec<ParseError>,
}

impl Parser {
    pub fn new(tokens: Vec<Token>) -> Self {
        // Filter out comments — they are not part of the AST
        let tokens: Vec<Token> = tokens
            .into_iter()
            .filter(|t| {
                !matches!(
                    t.kind,
                    TokenKind::LineComment | TokenKind::DocComment | TokenKind::BlockComment
                )
            })
            .collect();

        Self {
            tokens,
            pos: 0,
            errors: Vec::new(),
        }
    }

    /// Parse a complete source file.
    pub fn parse(mut self) -> (SourceFile, Vec<ParseError>) {
        let module = self.parse_module_decl();
        let mut imports = Vec::new();
        let mut declarations = Vec::new();

        while !self.is_at_end() {
            match self.peek_kind() {
                TokenKind::KwUse => {
                    if let Some(import) = self.parse_import() {
                        imports.push(import);
                    }
                }
                TokenKind::KwType => {
                    if let Some(decl) = self.parse_type_decl() {
                        declarations.push(Declaration::Type(decl));
                    }
                }
                TokenKind::KwService => {
                    if let Some(decl) = self.parse_service_decl() {
                        declarations.push(Declaration::Service(decl));
                    }
                }
                TokenKind::Eof => break,
                _ => {
                    let tok = self.advance();
                    self.errors.push(ParseError::Expected {
                        expected: "top-level declaration (type, service, use)".to_string(),
                        found: format!("'{}'", tok.text),
                        span: tok.span,
                    });
                    // Skip to next potential top-level token
                    self.synchronize();
                }
            }
        }

        let file = SourceFile {
            module,
            imports,
            declarations,
        };
        (file, self.errors)
    }

    // ── Module declaration ────────────────────────────

    fn parse_module_decl(&mut self) -> ModuleDecl {
        let start = self.current_span();

        if !self.expect(TokenKind::KwModule) {
            return ModuleDecl {
                path: vec!["unnamed".to_string()],
                span: start,
            };
        }

        let path = self.parse_dotted_path();
        let end = self.previous_span();

        ModuleDecl {
            path,
            span: start.merge(end),
        }
    }

    // ── Import declarations ──────────────────────────

    fn parse_import(&mut self) -> Option<ImportDecl> {
        let start = self.current_span();
        self.advance(); // consume 'use'

        let mut path = Vec::new();
        let items;

        // Parse path: std.http.{Request, Response} or std.auth.*
        loop {
            if self.check(TokenKind::Ident) || self.peek_kind().is_keyword() {
                let tok = self.advance();
                path.push(tok.text);
            } else {
                break;
            }

            if self.check(TokenKind::Dot) {
                self.advance(); // consume '.'

                // Check for wildcard: `use std.auth.*`
                if self.check(TokenKind::Star) {
                    self.advance();
                    items = ImportItems::Wildcard;
                    let end = self.previous_span();
                    return Some(ImportDecl {
                        path,
                        items,
                        span: start.merge(end),
                    });
                }

                // Check for selective: `use std.http.{Request, Response}`
                if self.check(TokenKind::BraceOpen) {
                    items = self.parse_import_items();
                    let end = self.previous_span();
                    return Some(ImportDecl {
                        path,
                        items,
                        span: start.merge(end),
                    });
                }
            } else {
                break;
            }
        }

        // Simple import: `use std.http`
        items = ImportItems::Named(vec![]);
        let end = self.previous_span();
        Some(ImportDecl {
            path,
            items,
            span: start.merge(end),
        })
    }

    fn parse_import_items(&mut self) -> ImportItems {
        self.advance(); // consume '{'
        let mut items = Vec::new();

        while !self.check(TokenKind::BraceClose) && !self.is_at_end() {
            let start = self.current_span();
            if self.check(TokenKind::Ident) || self.peek_kind().is_keyword() {
                let tok = self.advance();
                let name = tok.text;
                let alias = if self.check(TokenKind::KwAs) {
                    self.advance();
                    Some(self.advance().text)
                } else {
                    None
                };
                let end = self.previous_span();
                items.push(ImportItem {
                    name,
                    alias,
                    span: start.merge(end),
                });
            } else {
                break;
            }
            if self.check(TokenKind::Comma) {
                self.advance();
            }
        }

        self.expect(TokenKind::BraceClose);
        ImportItems::Named(items)
    }

    // ── Type declarations ────────────────────────────

    fn parse_type_decl(&mut self) -> Option<TypeDecl> {
        let start = self.current_span();
        self.advance(); // consume 'type'

        let name_tok = self.advance();
        let name = name_tok.text.clone();

        // Check for `=` (alias, enum, struct) or `{` (refined)
        if self.check(TokenKind::Eq) {
            self.advance(); // consume '='

            match self.peek_kind() {
                TokenKind::KwEnum => {
                    self.advance();
                    let kind = TypeKind::Enum(self.parse_enum_body());
                    let end = self.previous_span();
                    return Some(TypeDecl {
                        name,
                        kind,
                        span: start.merge(end),
                    });
                }
                TokenKind::KwStruct => {
                    self.advance();
                    let kind = TypeKind::Struct(self.parse_struct_body());
                    let end = self.previous_span();
                    return Some(TypeDecl {
                        name,
                        kind,
                        span: start.merge(end),
                    });
                }
                _ => {
                    // Could be alias: `type UserId = UUID`
                    // or refined: `type OrderId = String { ... }`
                    let type_ref = self.parse_type_ref();

                    if self.check(TokenKind::BraceOpen) {
                        // Refined type: `type OrderId = String { format: regex(...) }`
                        let constraints = self.parse_type_constraints();
                        let end = self.previous_span();
                        return Some(TypeDecl {
                            name,
                            kind: TypeKind::Refined(RefinedType {
                                base: type_ref,
                                constraints,
                                span: start.merge(end),
                            }),
                            span: start.merge(end),
                        });
                    }

                    // Simple alias: `type UserId = UUID`
                    let end = self.previous_span();
                    return Some(TypeDecl {
                        name,
                        kind: TypeKind::Alias(type_ref),
                        span: start.merge(end),
                    });
                }
            }
        }

        self.errors.push(ParseError::Expected {
            expected: "'=' after type name".to_string(),
            found: format!("'{}'", self.peek_text()),
            span: self.current_span(),
        });
        None
    }

    fn parse_enum_body(&mut self) -> EnumType {
        let start = self.current_span();
        self.expect(TokenKind::BraceOpen);

        let mut variants = Vec::new();
        while !self.check(TokenKind::BraceClose) && !self.is_at_end() {
            let vstart = self.current_span();
            let vtok = self.advance();
            let vname = vtok.text;

            let fields = if self.check(TokenKind::ParenOpen) {
                self.parse_field_list(TokenKind::ParenOpen, TokenKind::ParenClose)
            } else {
                Vec::new()
            };

            let vend = self.previous_span();
            variants.push(EnumVariant {
                name: vname,
                fields,
                span: vstart.merge(vend),
            });
        }

        self.expect(TokenKind::BraceClose);
        let end = self.previous_span();
        EnumType {
            variants,
            span: start.merge(end),
        }
    }

    fn parse_struct_body(&mut self) -> StructType {
        let start = self.current_span();
        let fields = self.parse_field_list(TokenKind::BraceOpen, TokenKind::BraceClose);
        let end = self.previous_span();
        StructType {
            fields,
            span: start.merge(end),
        }
    }

    fn parse_type_constraints(&mut self) -> Vec<TypeConstraint> {
        self.advance(); // consume '{'
        let mut constraints = Vec::new();

        while !self.check(TokenKind::BraceClose) && !self.is_at_end() {
            let start = self.current_span();
            let name_tok = self.advance();
            let name = name_tok.text;

            self.expect(TokenKind::Colon);
            let value = self.parse_expression();
            let end = self.previous_span();

            constraints.push(TypeConstraint {
                name,
                value,
                span: start.merge(end),
            });
        }

        self.expect(TokenKind::BraceClose);
        constraints
    }

    fn parse_type_ref(&mut self) -> TypeRef {
        let start = self.current_span();
        let tok = self.advance();
        let name = tok.text;

        let mut type_args = Vec::new();
        if self.check(TokenKind::Lt) {
            self.advance(); // consume '<'
            loop {
                type_args.push(self.parse_type_ref());
                if self.check(TokenKind::Comma) {
                    self.advance();
                } else {
                    break;
                }
            }
            self.expect(TokenKind::Gt);
        }

        let end = self.previous_span();
        TypeRef {
            name,
            type_args,
            span: start.merge(end),
        }
    }

    fn parse_field_list(&mut self, open: TokenKind, close: TokenKind) -> Vec<Field> {
        self.expect(open);
        let mut fields = Vec::new();

        while !self.check(close) && !self.is_at_end() {
            let start = self.current_span();
            let name_tok = self.advance();
            let name = name_tok.text;

            self.expect(TokenKind::Colon);
            let ty = self.parse_type_ref();

            let default = if self.check(TokenKind::Eq) {
                self.advance();
                Some(self.parse_expression())
            } else {
                None
            };

            let end = self.previous_span();
            fields.push(Field {
                name,
                ty,
                default,
                span: start.merge(end),
            });
        }

        self.expect(close);
        fields
    }

    // ── Service declarations ─────────────────────────

    fn parse_service_decl(&mut self) -> Option<ServiceDecl> {
        let start = self.current_span();
        self.advance(); // consume 'service'

        let name_tok = self.advance();
        let name = name_tok.text.clone();

        self.expect(TokenKind::BraceOpen);

        let mut goal = None;
        let mut constraints = Vec::new();
        let mut depends_on = Vec::new();
        let mut rpcs = Vec::new();
        let mut budget = None;
        let mut metrics = Vec::new();

        while !self.check(TokenKind::BraceClose) && !self.is_at_end() {
            match self.peek_kind() {
                TokenKind::KwGoal => {
                    self.advance();
                    self.expect(TokenKind::Colon);
                    if self.check(TokenKind::StringLiteral) {
                        let tok = self.advance();
                        // Strip quotes from string
                        goal = Some(tok.text[1..tok.text.len() - 1].to_string());
                    }
                }
                TokenKind::KwConstraint | TokenKind::Ident if self.peek_text() == "constraints" => {
                    self.advance();
                    self.expect(TokenKind::Colon);
                    constraints = self.parse_constraint_list();
                }
                TokenKind::KwDependsOn => {
                    self.advance();
                    self.expect(TokenKind::Colon);
                    depends_on = self.parse_identifier_list();
                }
                TokenKind::KwRpc => {
                    if let Some(rpc) = self.parse_rpc_decl() {
                        rpcs.push(rpc);
                    }
                }
                TokenKind::KwBudget => {
                    self.advance();
                    budget = Some(self.parse_budget_block());
                }
                TokenKind::KwMetrics => {
                    self.advance();
                    self.expect(TokenKind::Colon);
                    metrics = self.parse_metrics_list();
                }
                _ => {
                    // Skip unknown tokens inside service
                    self.advance();
                }
            }
        }

        self.expect(TokenKind::BraceClose);
        let end = self.previous_span();

        Some(ServiceDecl {
            name,
            goal,
            constraints,
            depends_on,
            rpcs,
            budget,
            metrics,
            span: start.merge(end),
        })
    }

    fn parse_rpc_decl(&mut self) -> Option<RpcDecl> {
        let start = self.current_span();
        self.advance(); // consume 'rpc'

        let name_tok = self.advance();
        let name = name_tok.text.clone();

        self.expect(TokenKind::BraceOpen);

        let mut inputs = Vec::new();
        let mut outputs = Vec::new();
        let mut preconditions = Vec::new();
        let mut postconditions = Vec::new();
        let mut errors = Vec::new();
        let mut constraints = Vec::new();
        let mut tests = Vec::new();

        while !self.check(TokenKind::BraceClose) && !self.is_at_end() {
            match self.peek_kind() {
                TokenKind::KwInputs => {
                    self.advance();
                    self.expect(TokenKind::Colon);
                    inputs = self.parse_inline_fields();
                }
                TokenKind::KwOutputs => {
                    self.advance();
                    self.expect(TokenKind::Colon);
                    outputs = self.parse_inline_fields();
                }
                TokenKind::KwPreconditions => {
                    self.advance();
                    self.expect(TokenKind::Colon);
                    preconditions = self.parse_expression_list();
                }
                TokenKind::KwPostconditions => {
                    self.advance();
                    self.expect(TokenKind::Colon);
                    postconditions = self.parse_expression_list();
                }
                TokenKind::KwErrors => {
                    self.advance();
                    self.expect(TokenKind::Colon);
                    errors = self.parse_error_list();
                }
                TokenKind::KwTests => {
                    self.advance();
                    self.expect(TokenKind::Colon);
                    tests = self.parse_test_list();
                }
                TokenKind::Ident if self.peek_text() == "constraints" => {
                    self.advance();
                    self.expect(TokenKind::Colon);
                    constraints = self.parse_constraint_list();
                }
                _ => {
                    self.advance();
                }
            }
        }

        self.expect(TokenKind::BraceClose);
        let end = self.previous_span();

        Some(RpcDecl {
            name,
            inputs,
            outputs,
            preconditions,
            postconditions,
            errors,
            constraints,
            tests,
            span: start.merge(end),
        })
    }

    // ── Constraint parsing ───────────────────────────

    fn parse_constraint_list(&mut self) -> Vec<Constraint> {
        let mut constraints = Vec::new();

        while self.check(TokenKind::Minus) {
            self.advance(); // consume '-'
            let start = self.current_span();

            let name_tok = self.advance();
            let name = name_tok.text;

            let args = if self.check(TokenKind::ParenOpen) {
                self.parse_constraint_args()
            } else {
                Vec::new()
            };

            let end = self.previous_span();
            constraints.push(Constraint {
                name,
                args,
                span: start.merge(end),
            });
        }

        constraints
    }

    fn parse_metrics_list(&mut self) -> Vec<MetricDecl> {
        let mut metrics = Vec::new();

        while self.check(TokenKind::Minus) {
            self.advance(); // consume '-'
            let start = self.current_span();

            let kind_tok = self.advance();
            let kind = match kind_tok.kind {
                TokenKind::KwCounter => MetricKind::Counter,
                TokenKind::KwGauge => MetricKind::Gauge,
                TokenKind::KwHistogram => MetricKind::Histogram,
                _ => MetricKind::Counter,
            };

            let name_tok = self.advance();
            let name = name_tok.text;

            let mut description = None;
            let mut labels = Vec::new();
            let mut buckets = None;

            if self.check(TokenKind::BraceOpen) {
                self.advance(); // consume '{'
                while !self.check(TokenKind::BraceClose) && !self.is_at_end() {
                    let key_tok = self.advance();
                    self.expect(TokenKind::Colon);
                    match key_tok.text.as_str() {
                        "description" => {
                            if self.check(TokenKind::StringLiteral) {
                                let val_tok = self.advance();
                                description =
                                    Some(val_tok.text[1..val_tok.text.len() - 1].to_string());
                            }
                        }
                        "labels" => {
                            self.expect(TokenKind::BracketOpen);
                            while !self.check(TokenKind::BracketClose) && !self.is_at_end() {
                                let label_tok = self.advance();
                                labels.push(label_tok.text);
                                if self.check(TokenKind::Comma) {
                                    self.advance();
                                }
                            }
                            self.expect(TokenKind::BracketClose);
                        }
                        "buckets" => {
                            self.expect(TokenKind::BracketOpen);
                            let mut bucket_exprs = Vec::new();
                            while !self.check(TokenKind::BracketClose) && !self.is_at_end() {
                                bucket_exprs.push(self.parse_expression());
                                if self.check(TokenKind::Comma) {
                                    self.advance();
                                }
                            }
                            self.expect(TokenKind::BracketClose);
                            buckets = Some(bucket_exprs);
                        }
                        _ => {
                            let _ = self.parse_expression();
                        }
                    }
                }
                self.expect(TokenKind::BraceClose);
            }

            let end = self.previous_span();
            metrics.push(MetricDecl {
                name,
                kind,
                description,
                labels,
                buckets,
                span: start.merge(end),
            });
        }

        metrics
    }

    fn parse_constraint_args(&mut self) -> Vec<ConstraintArg> {
        self.advance(); // consume '('
        let mut args = Vec::new();

        while !self.check(TokenKind::ParenClose) && !self.is_at_end() {
            let start = self.current_span();

            // Check for named arg: `p95: <200ms`
            let name = if self.peek_at(1).map(|t| t.kind) == Some(TokenKind::Colon) {
                let n = self.advance().text;
                self.advance(); // consume ':'
                Some(n)
            } else {
                None
            };

            let value = self.parse_expression();
            let end = self.previous_span();

            args.push(ConstraintArg {
                name,
                value,
                span: start.merge(end),
            });

            if self.check(TokenKind::Comma) {
                self.advance();
            }
        }

        self.expect(TokenKind::ParenClose);
        args
    }

    // ── Field parsing (inline, indented style) ───────

    fn parse_inline_fields(&mut self) -> Vec<Field> {
        let mut fields = Vec::new();

        // Fields come in "name: Type" pairs, one per line, no braces
        // Stop when we hit a section keyword (inputs, outputs, etc.)
        while (self.check(TokenKind::Ident) || self.peek_kind().is_keyword())
            && self.peek_at(1).map(|t| t.kind) == Some(TokenKind::Colon)
            && !self.is_section_keyword(self.peek_kind())
            && !self.is_at_end()
        {
            let start = self.current_span();
            let name_tok = self.advance();
            let name = name_tok.text;
            self.advance(); // consume ':'

            let ty = self.parse_type_ref();

            let default = if self.check(TokenKind::Eq) {
                self.advance();
                Some(self.parse_expression())
            } else {
                None
            };

            let end = self.previous_span();
            fields.push(Field {
                name,
                ty,
                default,
                span: start.merge(end),
            });
        }

        fields
    }

    // ── Error declarations ───────────────────────────

    fn parse_error_list(&mut self) -> Vec<ErrorDecl> {
        let mut errors = Vec::new();

        while self.check(TokenKind::Minus) {
            self.advance(); // consume '-'
            let start = self.current_span();
            let name_tok = self.advance();
            let name = name_tok.text;

            let fields = if self.check(TokenKind::ParenOpen) {
                self.parse_field_list(TokenKind::ParenOpen, TokenKind::ParenClose)
            } else {
                Vec::new()
            };

            let end = self.previous_span();
            errors.push(ErrorDecl {
                name,
                fields,
                span: start.merge(end),
            });
        }

        errors
    }

    // ── Test blocks ──────────────────────────────────

    fn parse_test_list(&mut self) -> Vec<TestBlock> {
        let mut tests = Vec::new();

        while self.check(TokenKind::Minus) {
            self.advance(); // consume '-'
            let start = self.current_span();

            match self.peek_kind() {
                TokenKind::KwScenario => {
                    self.advance();
                    self.expect(TokenKind::Colon);
                    let name = if self.check(TokenKind::StringLiteral) {
                        let tok = self.advance();
                        tok.text[1..tok.text.len() - 1].to_string()
                    } else {
                        "unnamed".to_string()
                    };

                    let mut given = Vec::new();
                    let mut when = Vec::new();
                    let mut expect = Vec::new();
                    let mut expect_error = None;

                    // Parse scenario fields
                    loop {
                        match self.peek_kind() {
                            TokenKind::KwGiven => {
                                self.advance();
                                self.expect(TokenKind::Colon);
                                given.push(self.parse_expression());
                            }
                            TokenKind::KwWhen => {
                                self.advance();
                                self.expect(TokenKind::Colon);
                                when.push(self.parse_expression());
                            }
                            TokenKind::KwExpect => {
                                self.advance();
                                self.expect(TokenKind::Colon);
                                expect.push(self.parse_expression());
                            }
                            TokenKind::KwExpectError => {
                                self.advance();
                                self.expect(TokenKind::Colon);
                                let tok = self.advance();
                                expect_error = Some(tok.text);
                            }
                            _ => break,
                        }
                    }

                    let end = self.previous_span();
                    tests.push(TestBlock {
                        kind: TestKind::Scenario {
                            name,
                            given,
                            when,
                            expect,
                            expect_error,
                        },
                        span: start.merge(end),
                    });
                }
                TokenKind::KwProperty => {
                    self.advance();
                    self.expect(TokenKind::Colon);
                    let name = if self.check(TokenKind::StringLiteral) {
                        let tok = self.advance();
                        tok.text[1..tok.text.len() - 1].to_string()
                    } else {
                        "unnamed".to_string()
                    };

                    let mut quantifiers = Vec::new();
                    let mut given = Vec::new();
                    let mut when = Vec::new();
                    let mut assert_exprs = Vec::new();

                    loop {
                        match self.peek_kind() {
                            TokenKind::KwForall => {
                                self.advance();
                                self.expect(TokenKind::Colon);
                                // Simplified: parse as expression
                                quantifiers.push(Quantifier {
                                    name: "x".to_string(),
                                    generator: self.parse_expression(),
                                    span: self.previous_span(),
                                });
                            }
                            TokenKind::KwGiven => {
                                self.advance();
                                self.expect(TokenKind::Colon);
                                given.push(self.parse_expression());
                            }
                            TokenKind::KwWhen => {
                                self.advance();
                                self.expect(TokenKind::Colon);
                                when.push(self.parse_expression());
                            }
                            TokenKind::KwAssert => {
                                self.advance();
                                self.expect(TokenKind::Colon);
                                assert_exprs.push(self.parse_expression());
                            }
                            _ => break,
                        }
                    }

                    let end = self.previous_span();
                    tests.push(TestBlock {
                        kind: TestKind::Property {
                            name,
                            quantifiers,
                            given,
                            when,
                            assert: assert_exprs,
                        },
                        span: start.merge(end),
                    });
                }
                _ => {
                    self.advance();
                }
            }
        }

        tests
    }

    // ── Budget blocks ────────────────────────────────

    fn parse_budget_block(&mut self) -> BudgetBlock {
        let start = self.current_span();
        self.expect(TokenKind::BraceOpen);

        let mut entries = Vec::new();
        while !self.check(TokenKind::BraceClose) && !self.is_at_end() {
            let estart = self.current_span();
            let key_tok = self.advance();
            let key = key_tok.text;
            self.expect(TokenKind::Colon);
            let value = self.parse_expression();
            let eend = self.previous_span();
            entries.push(BudgetEntry {
                key,
                value,
                span: estart.merge(eend),
            });
        }

        self.expect(TokenKind::BraceClose);
        let end = self.previous_span();
        BudgetBlock {
            entries,
            span: start.merge(end),
        }
    }

    // ── Identifier lists ─────────────────────────────

    fn parse_identifier_list(&mut self) -> Vec<String> {
        let mut list = Vec::new();

        while self.check(TokenKind::Minus) {
            self.advance(); // consume '-'
            if self.check(TokenKind::Ident) || self.peek_kind().is_keyword() {
                list.push(self.advance().text);
            }
        }

        list
    }

    // ── Expression lists ─────────────────────────────

    fn parse_expression_list(&mut self) -> Vec<Expression> {
        let mut exprs = Vec::new();

        while self.check(TokenKind::Minus) {
            self.advance(); // consume '-'
            exprs.push(self.parse_expression());
        }

        exprs
    }

    // ── Expression parsing (simplified Pratt parser) ─

    fn parse_expression(&mut self) -> Expression {
        self.parse_or_expr()
    }

    fn parse_or_expr(&mut self) -> Expression {
        let mut left = self.parse_and_expr();

        while self.check(TokenKind::PipePipe) || self.check(TokenKind::KwOr) {
            let start = self.current_span();
            self.advance();
            let right = self.parse_and_expr();
            let span = start.merge(self.previous_span());
            left = Expression::BinaryOp {
                left: Box::new(left),
                op: BinaryOperator::Or,
                right: Box::new(right),
                span,
            };
        }

        left
    }

    fn parse_and_expr(&mut self) -> Expression {
        let mut left = self.parse_comparison();

        while self.check(TokenKind::AmpAmp) || self.check(TokenKind::KwAnd) {
            let start = self.current_span();
            self.advance();
            let right = self.parse_comparison();
            let span = start.merge(self.previous_span());
            left = Expression::BinaryOp {
                left: Box::new(left),
                op: BinaryOperator::And,
                right: Box::new(right),
                span,
            };
        }

        left
    }

    fn parse_comparison(&mut self) -> Expression {
        let mut left = self.parse_range();

        if let Some(op) = self.match_comparison_op() {
            let right = self.parse_range();
            let span = left.span().merge(self.previous_span());
            left = Expression::BinaryOp {
                left: Box::new(left),
                op,
                right: Box::new(right),
                span,
            };
        }

        left
    }

    fn match_comparison_op(&mut self) -> Option<BinaryOperator> {
        match self.peek_kind() {
            TokenKind::EqEq => {
                self.advance();
                Some(BinaryOperator::Eq)
            }
            TokenKind::BangEq => {
                self.advance();
                Some(BinaryOperator::NotEq)
            }
            TokenKind::Lt => {
                self.advance();
                Some(BinaryOperator::Lt)
            }
            TokenKind::Gt => {
                self.advance();
                Some(BinaryOperator::Gt)
            }
            TokenKind::LtEq => {
                self.advance();
                Some(BinaryOperator::LtEq)
            }
            TokenKind::GtEq => {
                self.advance();
                Some(BinaryOperator::GtEq)
            }
            TokenKind::KwIn => {
                self.advance();
                Some(BinaryOperator::In)
            }
            TokenKind::KwNot if self.peek_at(1).map(|t| t.kind) == Some(TokenKind::KwIn) => {
                self.advance();
                self.advance();
                Some(BinaryOperator::NotIn)
            }
            _ => None,
        }
    }

    fn parse_range(&mut self) -> Expression {
        let left = self.parse_additive();

        if self.check(TokenKind::DotDot) {
            let start = self.current_span();
            self.advance();
            let right = self.parse_additive();
            let span = start.merge(self.previous_span());
            return Expression::BinaryOp {
                left: Box::new(left),
                op: BinaryOperator::Range,
                right: Box::new(right),
                span,
            };
        }

        if self.check(TokenKind::DotDotLt) {
            let start = self.current_span();
            self.advance();
            let right = self.parse_additive();
            let span = start.merge(self.previous_span());
            return Expression::BinaryOp {
                left: Box::new(left),
                op: BinaryOperator::RangeExc,
                right: Box::new(right),
                span,
            };
        }

        left
    }

    fn parse_additive(&mut self) -> Expression {
        let mut left = self.parse_unary();

        while self.check(TokenKind::Plus) || self.check(TokenKind::Minus) {
            let _op_tok = self.advance();
            let right = self.parse_unary();
            let span = left.span().merge(self.previous_span());
            left = Expression::BinaryOp {
                left: Box::new(left),
                op: BinaryOperator::Eq, // simplified: treat +/- as Eq for now
                right: Box::new(right),
                span,
            };
        }

        left
    }

    fn parse_unary(&mut self) -> Expression {
        if self.check(TokenKind::Bang) || self.check(TokenKind::KwNot) {
            let start = self.current_span();
            self.advance();
            let operand = self.parse_unary();
            let span = start.merge(self.previous_span());
            return Expression::UnaryOp {
                op: UnaryOperator::Not,
                operand: Box::new(operand),
                span,
            };
        }

        if self.check(TokenKind::Minus) {
            let start = self.current_span();
            self.advance();
            let operand = self.parse_unary();
            let span = start.merge(self.previous_span());
            return Expression::UnaryOp {
                op: UnaryOperator::Neg,
                operand: Box::new(operand),
                span,
            };
        }

        self.parse_postfix()
    }

    fn parse_postfix(&mut self) -> Expression {
        let mut expr = self.parse_primary();

        loop {
            if self.check(TokenKind::Dot) {
                self.advance();
                let field_tok = self.advance();
                let span = expr.span().merge(self.previous_span());
                expr = Expression::FieldAccess {
                    object: Box::new(expr),
                    field: field_tok.text,
                    span,
                };
            } else if self.check(TokenKind::ParenOpen) {
                // Function call: already parsed name as Identifier
                if let Expression::Identifier(name, _) = &expr {
                    let name = name.clone();
                    let start = expr.span();
                    self.advance(); // consume '('
                    let mut args = Vec::new();
                    while !self.check(TokenKind::ParenClose) && !self.is_at_end() {
                        args.push(self.parse_expression());
                        if self.check(TokenKind::Comma) {
                            self.advance();
                        }
                    }
                    self.expect(TokenKind::ParenClose);
                    let span = start.merge(self.previous_span());
                    expr = Expression::Call {
                        function: name,
                        args,
                        span,
                    };
                } else {
                    break;
                }
            } else {
                break;
            }
        }

        expr
    }

    fn parse_primary(&mut self) -> Expression {
        match self.peek_kind() {
            TokenKind::IntLiteral => {
                let tok = self.advance();
                let val: i64 = tok.text.replace('_', "").parse().unwrap_or(0);
                Expression::Literal(Literal::Int(val))
            }
            TokenKind::FloatLiteral => {
                let tok = self.advance();
                let val: f64 = tok.text.replace('_', "").parse().unwrap_or(0.0);
                Expression::Literal(Literal::Float(val))
            }
            TokenKind::StringLiteral => {
                let tok = self.advance();
                let val = tok.text[1..tok.text.len() - 1].to_string();
                Expression::Literal(Literal::String(val))
            }
            TokenKind::DurationLiteral => {
                let tok = self.advance();
                Expression::Literal(Literal::Duration(tok.text))
            }
            TokenKind::MoneyLiteral => {
                let tok = self.advance();
                Expression::Literal(Literal::Money(tok.text))
            }
            TokenKind::PercentageLiteral => {
                let tok = self.advance();
                // Treat percentage as float for now
                let val: f64 = tok.text.trim_end_matches('%').parse().unwrap_or(0.0);
                Expression::Literal(Literal::Float(val))
            }
            TokenKind::KwTrue => {
                self.advance();
                Expression::Literal(Literal::Bool(true))
            }
            TokenKind::KwFalse => {
                self.advance();
                Expression::Literal(Literal::Bool(false))
            }
            TokenKind::KwNull | TokenKind::KwNone => {
                self.advance();
                Expression::Literal(Literal::Null)
            }
            TokenKind::BracketOpen => {
                let start = self.current_span();
                self.advance(); // consume '['
                let mut items = Vec::new();
                while !self.check(TokenKind::BracketClose) && !self.is_at_end() {
                    items.push(self.parse_expression());
                    if self.check(TokenKind::Comma) {
                        self.advance();
                    }
                }
                self.expect(TokenKind::BracketClose);
                let span = start.merge(self.previous_span());
                Expression::List(items, span)
            }
            TokenKind::ParenOpen => {
                self.advance();
                let expr = self.parse_expression();
                self.expect(TokenKind::ParenClose);
                expr
            }
            TokenKind::Ident | TokenKind::KwOld | TokenKind::KwSelfKw => {
                let tok = self.advance();
                Expression::Identifier(tok.text, tok.span)
            }
            _ => {
                // If we hit a keyword that could be an identifier in expression context
                if self.peek_kind().is_keyword() {
                    let tok = self.advance();
                    Expression::Identifier(tok.text, tok.span)
                } else {
                    let tok = self.advance();
                    self.errors.push(ParseError::Expected {
                        expected: "expression".to_string(),
                        found: format!("'{}'", tok.text),
                        span: tok.span,
                    });
                    Expression::Literal(Literal::Null)
                }
            }
        }
    }

    // ── Dotted path parsing ──────────────────────────

    fn parse_dotted_path(&mut self) -> Vec<String> {
        let mut path = Vec::new();

        if self.check(TokenKind::Ident) || self.peek_kind().is_keyword() {
            path.push(self.advance().text);
        }

        while self.check(TokenKind::Dot) {
            self.advance(); // consume '.'
            if self.check(TokenKind::Ident) || self.peek_kind().is_keyword() {
                path.push(self.advance().text);
            }
        }

        path
    }

    // ── Token operations ─────────────────────────────

    fn is_at_end(&self) -> bool {
        self.peek_kind() == TokenKind::Eof
    }

    fn peek(&self) -> &Token {
        &self.tokens[self.pos.min(self.tokens.len() - 1)]
    }

    fn peek_kind(&self) -> TokenKind {
        self.peek().kind
    }

    fn peek_text(&self) -> &str {
        &self.peek().text
    }

    fn peek_at(&self, offset: usize) -> Option<&Token> {
        self.tokens.get(self.pos + offset)
    }

    fn advance(&mut self) -> Token {
        let token = self.tokens[self.pos.min(self.tokens.len() - 1)].clone();
        if self.pos < self.tokens.len() - 1 {
            self.pos += 1;
        }
        token
    }

    fn check(&self, kind: TokenKind) -> bool {
        self.peek_kind() == kind
    }

    fn expect(&mut self, kind: TokenKind) -> bool {
        if self.check(kind) {
            self.advance();
            true
        } else {
            self.errors.push(ParseError::Expected {
                expected: format!("{kind}"),
                found: format!("'{}'", self.peek_text()),
                span: self.current_span(),
            });
            false
        }
    }

    fn current_span(&self) -> Span {
        self.peek().span
    }

    fn previous_span(&self) -> Span {
        if self.pos > 0 {
            self.tokens[self.pos - 1].span
        } else {
            Span::new(0, 0)
        }
    }

    /// Check if a token kind is a section keyword (used as headers in RPC/service blocks).
    fn is_section_keyword(&self, kind: TokenKind) -> bool {
        matches!(
            kind,
            TokenKind::KwInputs
                | TokenKind::KwOutputs
                | TokenKind::KwErrors
                | TokenKind::KwTests
                | TokenKind::KwPreconditions
                | TokenKind::KwPostconditions
                | TokenKind::KwInvariants
                | TokenKind::KwGoal
                | TokenKind::KwBudget
                | TokenKind::KwDependsOn
                | TokenKind::KwRpc
        )
    }

    fn synchronize(&mut self) {
        while !self.is_at_end() {
            match self.peek_kind() {
                TokenKind::KwModule
                | TokenKind::KwUse
                | TokenKind::KwType
                | TokenKind::KwService
                | TokenKind::KwComponent
                | TokenKind::KwPipeline
                | TokenKind::KwWorkflow
                | TokenKind::KwAgent
                | TokenKind::KwSchema
                | TokenKind::KwPolicy => return,
                _ => {
                    self.advance();
                }
            }
        }
    }
}

// Add span method to Expression
impl Expression {
    pub fn span(&self) -> Span {
        match self {
            Expression::Literal(_) => Span::new(0, 0), // TODO: track literal spans
            Expression::Identifier(_, span) => *span,
            Expression::BinaryOp { span, .. } => *span,
            Expression::UnaryOp { span, .. } => *span,
            Expression::Call { span, .. } => *span,
            Expression::FieldAccess { span, .. } => *span,
            Expression::List(_, span) => *span,
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::lexer::Lexer;

    fn parse(input: &str) -> (SourceFile, Vec<ParseError>) {
        let (tokens, lex_errors) = Lexer::new(input).tokenize();
        assert!(lex_errors.is_empty(), "lexer errors: {lex_errors:?}");
        Parser::new(tokens).parse()
    }

    fn parse_ok(input: &str) -> SourceFile {
        let (file, errors) = parse(input);
        assert!(errors.is_empty(), "parse errors: {errors:?}");
        file
    }

    #[test]
    fn parse_module_decl() {
        let file = parse_ok("module acme.payments.checkout");
        assert_eq!(file.module.path, vec!["acme", "payments", "checkout"]);
    }

    #[test]
    fn parse_import_wildcard() {
        let file = parse_ok("module test\nuse std.auth.*");
        assert_eq!(file.imports.len(), 1);
        assert_eq!(file.imports[0].path, vec!["std", "auth"]);
        assert!(matches!(file.imports[0].items, ImportItems::Wildcard));
    }

    #[test]
    fn parse_import_selective() {
        let file = parse_ok("module test\nuse std.http.{Request, Response}");
        assert_eq!(file.imports.len(), 1);
        if let ImportItems::Named(items) = &file.imports[0].items {
            assert_eq!(items.len(), 2);
            assert_eq!(items[0].name, "Request");
            assert_eq!(items[1].name, "Response");
        } else {
            panic!("expected named imports");
        }
    }

    #[test]
    fn parse_type_alias() {
        let file = parse_ok("module test\ntype UserId = UUID");
        assert_eq!(file.declarations.len(), 1);
        if let Declaration::Type(t) = &file.declarations[0] {
            assert_eq!(t.name, "UserId");
            assert!(matches!(t.kind, TypeKind::Alias(_)));
        }
    }

    #[test]
    fn parse_enum_type() {
        let file =
            parse_ok("module test\ntype Status = enum {\n  Draft\n  Pending\n  Confirmed\n}");
        if let Declaration::Type(t) = &file.declarations[0] {
            assert_eq!(t.name, "Status");
            if let TypeKind::Enum(e) = &t.kind {
                assert_eq!(e.variants.len(), 3);
                assert_eq!(e.variants[0].name, "Draft");
                assert_eq!(e.variants[1].name, "Pending");
                assert_eq!(e.variants[2].name, "Confirmed");
            } else {
                panic!("expected enum");
            }
        }
    }

    #[test]
    fn parse_struct_type() {
        let file =
            parse_ok("module test\ntype Customer = struct {\n  id: CustomerId\n  email: Email\n}");
        if let Declaration::Type(t) = &file.declarations[0] {
            assert_eq!(t.name, "Customer");
            if let TypeKind::Struct(s) = &t.kind {
                assert_eq!(s.fields.len(), 2);
                assert_eq!(s.fields[0].name, "id");
                assert_eq!(s.fields[1].name, "email");
            } else {
                panic!("expected struct");
            }
        }
    }

    #[test]
    fn parse_service_with_goal() {
        let file = parse_ok(
            r#"module test
service Checkout {
  goal: "Process orders"
}"#,
        );
        if let Declaration::Service(s) = &file.declarations[0] {
            assert_eq!(s.name, "Checkout");
            assert_eq!(s.goal, Some("Process orders".to_string()));
        }
    }

    #[test]
    fn parse_service_with_rpc() {
        let file = parse_ok(
            r#"module test
service Checkout {
  goal: "Process orders"
  rpc PlaceOrder {
    inputs:
      customer_id: CustomerId
      items: List
    outputs:
      order_id: OrderId
  }
}"#,
        );
        if let Declaration::Service(s) = &file.declarations[0] {
            assert_eq!(s.rpcs.len(), 1);
            assert_eq!(s.rpcs[0].name, "PlaceOrder");
            assert_eq!(s.rpcs[0].inputs.len(), 2);
            assert_eq!(s.rpcs[0].outputs.len(), 1);
        }
    }

    #[test]
    fn parse_constraint_list() {
        let file = parse_ok(
            r#"module test
service API {
  goal: "API"
  constraints:
    - idempotent
    - latency(p95: 200ms)
}"#,
        );
        if let Declaration::Service(s) = &file.declarations[0] {
            assert_eq!(s.constraints.len(), 2);
            assert_eq!(s.constraints[0].name, "idempotent");
            assert_eq!(s.constraints[1].name, "latency");
            assert_eq!(s.constraints[1].args.len(), 1);
        }
    }

    #[test]
    fn parse_multiple_declarations() {
        let file = parse_ok(
            r#"module test
type OrderId = UUID
type Status = enum { Active, Inactive }
service Orders {
  goal: "Manage orders"
}"#,
        );
        assert_eq!(file.declarations.len(), 3);
    }

    #[test]
    fn parse_rpc_with_tests() {
        let file = parse_ok(
            r#"module test
service Inventory {
  goal: "Manage inventory"
  rpc CheckStock {
    inputs:
      product_id: ProductId
    outputs:
      available: Int
    tests:
      - scenario: "Product in stock"
        given: product_exists
        expect: available == 42
  }
}"#,
        );
        if let Declaration::Service(s) = &file.declarations[0] {
            assert_eq!(s.rpcs[0].tests.len(), 1);
            if let TestKind::Scenario { name, .. } = &s.rpcs[0].tests[0].kind {
                assert_eq!(name, "Product in stock");
            }
        }
    }

    #[test]
    fn error_recovery_continues_parsing() {
        let (file, errors) = parse(
            r#"module test
* invalid stuff
type OrderId = UUID"#,
        );
        // Should have errors but still parse the type declaration
        assert!(!errors.is_empty());
        assert_eq!(file.declarations.len(), 1);
    }

    #[test]
    fn parse_metrics_list_test() {
        let file = parse_ok(
            r#"module test
service Checkout {
  goal: "Process orders"
  metrics:
    - counter payment_attempts_total {
        description: "Total payment attempts"
        labels: [payment_method, status]
      }
    - histogram checkout_value_usd {
        description: "Distribution of transaction amounts"
        buckets: [10, 50, 100, 500, 1000]
      }
}"#,
        );
        if let Declaration::Service(s) = &file.declarations[0] {
            assert_eq!(s.metrics.len(), 2);

            assert_eq!(s.metrics[0].name, "payment_attempts_total");
            assert_eq!(s.metrics[0].kind, MetricKind::Counter);
            assert_eq!(
                s.metrics[0].description,
                Some("Total payment attempts".to_string())
            );
            assert_eq!(
                s.metrics[0].labels,
                vec!["payment_method".to_string(), "status".to_string()]
            );
            assert!(s.metrics[0].buckets.is_none());

            assert_eq!(s.metrics[1].name, "checkout_value_usd");
            assert_eq!(s.metrics[1].kind, MetricKind::Histogram);
            assert_eq!(
                s.metrics[1].description,
                Some("Distribution of transaction amounts".to_string())
            );
            assert!(s.metrics[1].labels.is_empty());
            assert!(s.metrics[1].buckets.is_some());
            assert_eq!(s.metrics[1].buckets.as_ref().unwrap().len(), 5);
        }
    }
}
