# Contributing to OmniLang

Thank you for your interest in contributing to OmniLang! This document provides guidelines and instructions for contributing.

## Prerequisites

- [Rust](https://rustup.rs/) (1.85+)
- Git

## Getting Started

```bash
# Clone the repository
git clone https://github.com/denelvis/omnilang.git
cd omnilang

# Build all crates
cargo build --workspace

# Run tests
cargo test --workspace

# Run the CLI
cargo run -- --help
```

## Code Style

We enforce consistent code style via CI:

```bash
# Format code
cargo fmt --all

# Lint
cargo clippy -- -D warnings
```

All PRs must pass `cargo fmt --check` and `cargo clippy` before merge.

## Project Structure

```
crates/
├── omni-parser/     # Lexer + Parser → AST
├── omni-analyzer/   # Type checker + Constraint resolver → Spec IR
└── omni-cli/        # CLI binary (`omni` command)
```

## Making Changes

1. Fork the repository
2. Create a feature branch: `git checkout -b feat/my-feature`
3. Make your changes
4. Add tests for new functionality
5. Run `cargo test --workspace` to verify
6. Run `cargo fmt --all` and `cargo clippy`
7. Commit with [conventional commits](https://www.conventionalcommits.org/):
   - `feat: add enum type parsing`
   - `fix: handle unterminated strings in lexer`
   - `docs: update syntax reference`
   - `test: add snapshot tests for service blocks`
8. Open a Pull Request

## Pull Request Checklist

- [ ] Code compiles: `cargo build --workspace`
- [ ] Tests pass: `cargo test --workspace`
- [ ] No lint warnings: `cargo clippy -- -D warnings`
- [ ] Code formatted: `cargo fmt --all -- --check`
- [ ] New tests added for new functionality
- [ ] Documentation updated if needed

## Reporting Issues

Use [GitHub Issues](https://github.com/denelvis/omnilang/issues) with the appropriate template:

- **Bug Report** — something doesn't work as expected
- **Feature Request** — a new capability you'd like
- **RFS (Request for Spec)** — a proposal to change the OmniLang specification

## License

By contributing, you agree that your contributions will be licensed under Apache-2.0 OR MIT (dual license).
