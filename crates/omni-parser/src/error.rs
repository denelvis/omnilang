use crate::Span;

/// Errors that can occur during lexing or parsing.
#[derive(Debug, Clone, thiserror::Error)]
pub enum ParseError {
    #[error("unexpected character '{ch}' at offset {}", span.start)]
    UnexpectedChar { ch: char, span: Span },

    #[error("unterminated string literal starting at offset {}", span.start)]
    UnterminatedString { span: Span },

    #[error("unterminated block comment starting at offset {}", span.start)]
    UnterminatedBlockComment { span: Span },

    #[error("expected {expected}, found {found}")]
    Expected {
        expected: String,
        found: String,
        span: Span,
    },

    #[error("{message}")]
    Custom { message: String, span: Span },
}

impl ParseError {
    pub fn span(&self) -> Span {
        match self {
            ParseError::UnexpectedChar { span, .. }
            | ParseError::UnterminatedString { span, .. }
            | ParseError::UnterminatedBlockComment { span, .. }
            | ParseError::Expected { span, .. }
            | ParseError::Custom { span, .. } => *span,
        }
    }
}
