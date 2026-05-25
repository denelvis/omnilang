# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.6.0] - 2026-05-25

### Added

- **Type Narrowing**: Control-flow-aware type analysis emits info diagnostics when optional fields are compared without null-check guards in preconditions.
- **Option Propagation**: Postcondition validation warns when accessing fields on optional-typed outputs without null-check guards.
- **Refined Generator Config**: Spec IR now includes `GeneratorConfig` for refined types, extracting range bounds, string length constraints, format patterns, and precision for constraint-aware arbitrary value generation.
- **Deterministic Type Mapping**: New `type_mapping` module with OmniLang → target type mapping tables for TypeScript, Rust, and Python (e.g. `UUID → Uuid`, `Money → Decimal`). Includes target-specific constraint compatibility validation.
- **Evidence System — Full Chain**:
  - `evidence/` directory: `omni verify` now copies JUnit XML and LCOV files to a dedicated evidence directory.
  - `evidence/chain.json`: Structured mapping linking constraints ("all tests pass", "code coverage") to their evidence artifacts.
  - CI-friendly JSON output: `omni verify --format json` emits machine-readable verification results.
- **Distribution & Packaging**:
  - Shell installer script (`scripts/install.sh`) for `curl | sh` installation.
  - Homebrew formula template (`scripts/homebrew/omni.rb`).
  - npm wrapper package (`scripts/npm/`) for `npx @omnilang/cli` support.
  - `cargo install omni-cli` support (existing Cargo.toml metadata).

### Changed

- `SpecIR` now includes `type_mappings` field with the target-specific type mapping table.
- `TypeDef` in Spec IR now includes an optional `generator` field with refined type constraints.
- `omni verify` command gains `--format` (human/json) and `--evidence-dir` flags.

## [0.5.0] - 2026-05-25

### Added

- **Contract System**: Service-level `invariants:` block with expression validation, `old()` postcondition-only enforcement (exactly 1 argument), and CamelCase symbol resolution against the symbol table.
- **Property-Based Testing**: Extended `forall:` quantifier parsing to support comma-separated entries with both `in` and `<-` syntaxes, and generic call expressions like `arbitrary<T>`.
- **Multi-Target Code Generation**: Support for `--target typescript`, `--target rust`, and `--target python` in the CLI build command and orchestrator runtime.
  - **TypeScript**: Jest tests, `fast-check` for property-based testing.
  - **Rust**: `Cargo.toml` scaffolding, `proptest` dev-dependency, service module auto-registration.
  - **Python**: `requirements.txt` with `pytest`/`hypothesis`/`mypy`/`pydantic`, `pyproject.toml` configuration.
- **Evidence System**: `omni verify` CLI subcommand that scans a build directory for JUnit XML test reports and LCOV coverage files, parses them, and prints a color-coded compliance report with `--report` for per-suite detail.
- **LLM Prompt Enhancements**: Target-specific system prompts instructing the LLM on contracts, invariants, custom error types, and property-based testing per language.
- **Mock LLM Extensions**: Mock responses for Rust (with `thiserror` error enums) and Python (with `dataclass`/`Exception` patterns) targets.
- **Tree-sitter**: `invariants_section` grammar rule, `invariants` keyword highlighting, and corpus test case for `Service with Invariants`.

## [0.4.0] - 2026-05-25

### Added

- Top-level custom constraint declarations in AST, parser, symbol table, and analyzer.
- Built-in validation rules for standard service constraints: `cacheable`, `rate_limited`, `authorized`, `latency`, and `eventual_consistency`.
- Service conflict detection (e.g. contradictory latency/SLO targets, conflicting authenticated/anonymous requirements).
- Transitive constraint propagation checks along the service dependency chain (via `depends_on`).
- Tree-sitter grammar rules, highlight queries, and tests for constraint declarations.
- Comprehensive unit tests in `parser.rs` and `type_check.rs`.

## [0.3.0] - 2026-05-25

### Added

- Extended type system parsing support for generic parameters (`<T: Bound1 + Bound2, E>`), union types (`A | B`), intersection types (`A & B`), and Option shorthand (`T?`).
- Typechecker validations for refined types constraints (`format`, `range`, `min_length`, `max_length`, `precision`, `example`).
- Refined types base type inference deducing the primitive base type from constraints (e.g. `format` -> `String`, `range` -> `Int` / `Float`, `precision` -> `Decimal`).
- Generic type argument count validation and type bounds presence checks in resolve phase.
- Extended type constructs support in tree-sitter grammar rules, syntax highlighting queries, and VS Code TextMate patterns.
- Unit testing suite for parser, typechecker, and tree-sitter.

## [0.2.0] - 2026-05-25

### Added

- Complete parser, AST types, name resolution, symbol registration, and type checking for six new blocks: `Component`, `Pipeline`, `Workflow`, `Agent`, `Schema`, and `Policy`.
- Complete Tree-sitter grammar rules, highlighting queries, and VS Code TextMate grammar updates for all new top-level blocks and their keywords.
- Support for visual spec options (e.g. command-line flags) and list-based policy conditions/clauses.
- GitHub issue templates (`bug_report.md`, `feature_request.md`, `rfs_proposal.md`), PR template, and a binary release workflow (`release.yml`).
- Verification example file `examples/phase-1-blocks.omni` containing all blocks.

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
