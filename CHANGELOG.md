# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.1.0] - 2026-05-25

### Added

- Project scaffolding: Cargo workspace with `omni-parser`, `omni-analyzer`, `omni-cli` crates
- CLI skeleton with `check`, `plan`, `build`, `init` subcommands
- AST type definitions for OmniLang Phase 0 syntax
- Single-Agent Pipeline (TypeScript Runtime & LLM Code Generation) in `runtime/`
- Tree-sitter Grammar & Editor Support in `tree-sitter-omnilang/` and `editors/vscode/`
- Declarative `metrics` block in service specifications (`counter`, `gauge`, `histogram`) with parser, AST, and syntax highlighting support
- Auto-instrumentation of service metrics in TypeScript code generator
- Dual license: Apache-2.0 OR MIT
