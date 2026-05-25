//! # omni-parser
//!
//! Lexer and parser for the OmniLang specification language.
//!
//! This crate takes `.omni` source text and produces an Abstract Syntax Tree (AST)
//! that can be consumed by the analyzer for type checking and constraint resolution.

pub mod ast;
pub mod error;
pub mod lexer;
pub mod parser;
pub mod span;
pub mod token;

pub use ast::SourceFile;
pub use error::ParseError;
pub use lexer::Lexer;
pub use span::Span;
pub use token::{Token, TokenKind};
