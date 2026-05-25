//! Abstract Syntax Tree definitions for OmniLang.
//!
//! These types represent the parsed structure of `.omni` source files.
//! The AST is produced by the parser and consumed by the analyzer.

use crate::Span;

/// A complete OmniLang source file.
#[derive(Debug, Clone, serde::Serialize)]
pub struct SourceFile {
    /// Module declaration (required, first statement).
    pub module: ModuleDecl,
    /// Import statements.
    pub imports: Vec<ImportDecl>,
    /// Top-level declarations.
    pub declarations: Vec<Declaration>,
}

/// Module declaration: `module acme.payments.checkout`
#[derive(Debug, Clone, serde::Serialize)]
pub struct ModuleDecl {
    /// Dotted module path, e.g. `["acme", "payments", "checkout"]`.
    pub path: Vec<String>,
    pub span: Span,
}

/// Import declaration: `use std.http.{Request, Response}`
#[derive(Debug, Clone, serde::Serialize)]
pub struct ImportDecl {
    /// The import path segments.
    pub path: Vec<String>,
    /// Specific items to import, or empty for wildcard `*`.
    pub items: ImportItems,
    pub span: Span,
}

#[derive(Debug, Clone, serde::Serialize)]
pub enum ImportItems {
    /// `use std.auth.*`
    Wildcard,
    /// `use std.http.{Request, Response}`
    Named(Vec<ImportItem>),
}

#[derive(Debug, Clone, serde::Serialize)]
pub struct ImportItem {
    pub name: String,
    /// Optional alias: `use std.money.Money as Currency`
    pub alias: Option<String>,
    pub span: Span,
}

/// A top-level declaration.
#[derive(Debug, Clone, serde::Serialize)]
pub enum Declaration {
    Type(TypeDecl),
    Service(ServiceDecl),
    // Phase 1+: Component, Pipeline, Workflow, Agent, Schema, Policy
}

// ---------------------------------------------------------------------------
// Type declarations
// ---------------------------------------------------------------------------

#[derive(Debug, Clone, serde::Serialize)]
pub struct TypeDecl {
    pub name: String,
    pub kind: TypeKind,
    pub span: Span,
}

#[derive(Debug, Clone, serde::Serialize)]
pub enum TypeKind {
    /// `type OrderStatus = enum { Draft, Pending, ... }`
    Enum(EnumType),
    /// `type Customer = struct { id: CustomerId, ... }`
    Struct(StructType),
    /// `type OrderId = String { format: regex("...") }`
    Refined(RefinedType),
    /// `type UserId = UUID` (simple alias)
    Alias(TypeRef),
}

#[derive(Debug, Clone, serde::Serialize)]
pub struct EnumType {
    pub variants: Vec<EnumVariant>,
    pub span: Span,
}

#[derive(Debug, Clone, serde::Serialize)]
pub struct EnumVariant {
    pub name: String,
    /// Optional associated data: `Shipped(tracking_id: String)`
    pub fields: Vec<Field>,
    pub span: Span,
}

#[derive(Debug, Clone, serde::Serialize)]
pub struct StructType {
    pub fields: Vec<Field>,
    pub span: Span,
}

#[derive(Debug, Clone, serde::Serialize)]
pub struct Field {
    pub name: String,
    pub ty: TypeRef,
    pub default: Option<Expression>,
    pub span: Span,
}

#[derive(Debug, Clone, serde::Serialize)]
pub struct RefinedType {
    pub base: TypeRef,
    pub constraints: Vec<TypeConstraint>,
    pub span: Span,
}

#[derive(Debug, Clone, serde::Serialize)]
pub struct TypeConstraint {
    pub name: String,
    pub value: Expression,
    pub span: Span,
}

/// A reference to a type, e.g. `String`, `List<Order>`, `Option<Int>`.
#[derive(Debug, Clone, serde::Serialize)]
pub struct TypeRef {
    pub name: String,
    pub type_args: Vec<TypeRef>,
    pub span: Span,
}

// ---------------------------------------------------------------------------
// Service declarations
// ---------------------------------------------------------------------------

#[derive(Debug, Clone, serde::Serialize)]
pub struct ServiceDecl {
    pub name: String,
    pub goal: Option<String>,
    pub constraints: Vec<Constraint>,
    pub depends_on: Vec<String>,
    pub rpcs: Vec<RpcDecl>,
    pub budget: Option<BudgetBlock>,
    pub metrics: Vec<MetricDecl>,
    pub span: Span,
}

#[derive(Debug, Clone, serde::Serialize)]
pub struct MetricDecl {
    pub name: String,
    pub kind: MetricKind,
    pub description: Option<String>,
    pub labels: Vec<String>,
    pub buckets: Option<Vec<Expression>>,
    pub span: Span,
}

#[derive(Debug, Clone, Copy, serde::Serialize, PartialEq, Eq)]
pub enum MetricKind {
    Counter,
    Gauge,
    Histogram,
}

#[derive(Debug, Clone, serde::Serialize)]
pub struct RpcDecl {
    pub name: String,
    pub inputs: Vec<Field>,
    pub outputs: Vec<Field>,
    pub preconditions: Vec<Expression>,
    pub postconditions: Vec<Expression>,
    pub errors: Vec<ErrorDecl>,
    pub constraints: Vec<Constraint>,
    pub tests: Vec<TestBlock>,
    pub span: Span,
}

#[derive(Debug, Clone, serde::Serialize)]
pub struct ErrorDecl {
    pub name: String,
    pub fields: Vec<Field>,
    pub span: Span,
}

#[derive(Debug, Clone, serde::Serialize)]
pub struct Constraint {
    pub name: String,
    pub args: Vec<ConstraintArg>,
    pub span: Span,
}

#[derive(Debug, Clone, serde::Serialize)]
pub struct ConstraintArg {
    pub name: Option<String>,
    pub value: Expression,
    pub span: Span,
}

// ---------------------------------------------------------------------------
// Test blocks
// ---------------------------------------------------------------------------

#[derive(Debug, Clone, serde::Serialize)]
pub struct TestBlock {
    pub kind: TestKind,
    pub span: Span,
}

#[derive(Debug, Clone, serde::Serialize)]
pub enum TestKind {
    Scenario {
        name: String,
        given: Vec<Expression>,
        when: Vec<Expression>,
        expect: Vec<Expression>,
        expect_error: Option<String>,
    },
    Property {
        name: String,
        quantifiers: Vec<Quantifier>,
        given: Vec<Expression>,
        when: Vec<Expression>,
        assert: Vec<Expression>,
    },
}

#[derive(Debug, Clone, serde::Serialize)]
pub struct Quantifier {
    pub name: String,
    pub generator: Expression,
    pub span: Span,
}

// ---------------------------------------------------------------------------
// Budget blocks
// ---------------------------------------------------------------------------

#[derive(Debug, Clone, serde::Serialize)]
pub struct BudgetBlock {
    pub entries: Vec<BudgetEntry>,
    pub span: Span,
}

#[derive(Debug, Clone, serde::Serialize)]
pub struct BudgetEntry {
    pub key: String,
    pub value: Expression,
    pub span: Span,
}

// ---------------------------------------------------------------------------
// Expressions (simplified for Phase 0)
// ---------------------------------------------------------------------------

/// Expressions used in constraints, pre/postconditions, and test assertions.
#[derive(Debug, Clone, serde::Serialize)]
pub enum Expression {
    /// A literal value: `42`, `"hello"`, `true`, `200ms`, `$0.10`
    Literal(Literal),
    /// An identifier: `order_id`, `PaymentStatus`
    Identifier(String, Span),
    /// Binary operation: `a == b`, `balance > 0`
    BinaryOp {
        left: Box<Expression>,
        op: BinaryOperator,
        right: Box<Expression>,
        span: Span,
    },
    /// Unary operation: `!deleted`
    UnaryOp {
        op: UnaryOperator,
        operand: Box<Expression>,
        span: Span,
    },
    /// Function call: `old(balance)`, `sum(items)`
    Call {
        function: String,
        args: Vec<Expression>,
        span: Span,
    },
    /// Field access: `order.status`
    FieldAccess {
        object: Box<Expression>,
        field: String,
        span: Span,
    },
    /// List literal: `[1, 2, 3]`
    List(Vec<Expression>, Span),
}

#[derive(Debug, Clone, serde::Serialize)]
pub enum Literal {
    Int(i64),
    Float(f64),
    String(String),
    Bool(bool),
    Duration(String),
    Money(String),
    Null,
}

#[derive(Debug, Clone, Copy, serde::Serialize)]
pub enum BinaryOperator {
    Eq,       // ==
    NotEq,    // !=
    Lt,       // <
    Gt,       // >
    LtEq,     // <=
    GtEq,     // >=
    And,      // &&
    Or,       // ||
    In,       // in
    NotIn,    // not in
    Range,    // ..
    RangeExc, // ..<
}

#[derive(Debug, Clone, Copy, serde::Serialize)]
pub enum UnaryOperator {
    Not, // !
    Neg, // -
}
