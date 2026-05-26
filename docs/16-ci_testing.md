# CI E2E Testing & Mock Refinement

This document describes the principles of testing and verifying OmniLang code generation in continuous integration (CI) and during local development.

## 1. LLM Operational Modes (Mocks vs. Real LLMs)

The service generation process (`omni build`) depends on the language model. The runtime supports two main modes, which are toggled via environment variables:

### A. Mock Mode (for CI and Fast Local Tests)
In this mode, no real network requests are made to the LLM. Instead, a local deterministic generator mock is used.
* **How to enable:** Set `OMNI_MOCK_LLM=true` (this is the default behavior in most tests).
* **Benefits:**
  * Runs for free and instantly (less than a second).
  * Does not require API keys (`ANTHROPIC_API_KEY`) or locally running servers.
  * Ideal for testing compiler syntax, parsing, AST transformations, and CI pipelines in GitHub Actions.
* **Limitation:** The generated code is a mock skeleton, sufficient to pass basic compilation and simple test assertions, but it does not contain full business logic.

### B. E2E Mode with a Local Model (Ollama)
Local code generation without sending data to external cloud services. It is recommended to use the `qwen2.5-coder:7b` model or higher.
* **How to enable:**
  ```bash
  OMNI_MOCK_LLM=false OMNI_LLM_PROVIDER=ollama OLLAMA_MODEL="qwen2.5-coder:7b" cargo run --bin omni -- build <spec_path> --target typescript
  ```
* **Benefits:**
  * Free of charge (given local GPU/Apple Silicon).
  * Generates full, working code that conforms to contracts and pre/post-conditions.
  * Safe for private specifications.

### C. E2E Mode with a Cloud Model (Anthropic Claude 3.5 Sonnet)
Production-grade mode with the highest quality of logic, test, and JSDoc generation.
* **How to enable:**
  ```bash
  OMNI_MOCK_LLM=false OMNI_LLM_PROVIDER=anthropic ANTHROPIC_API_KEY="your-key-here" cargo run --bin omni -- build <spec_path> --target typescript
  ```
* **Benefits:**
  * Highest quality of complex business logic, invariants, and property-based test (`fast-check`) generation.
  * Full compliance with all TypeScript compiler rules (`strict: true`).

---

## 2. Running Tests in CI

In continuous integration pipelines (e.g., GitHub Actions), compiler and runtime tests are executed in mock mode to ensure speed and independence from external APIs:

```yaml
steps:
  - name: Run compiler tests (Rust)
    run: cargo test

  - name: Install Runtime Dependencies
    run: npm install --prefix runtime

  - name: Run Runtime Unit Tests (TypeScript)
    run: npm test --prefix runtime

  - name: Run Build E2E Test (Mock mode)
    env:
      OMNI_MOCK_LLM: "true"
    run: cargo run --bin omni -- build examples/simple_greet.omni --target typescript
```

---

## 3. Local E2E Logic Verification

To verify the actual capabilities of the code generator, run a local Ollama server:

1. Start Ollama and download the code model:
   ```bash
   ollama run qwen2.5-coder:7b
   ```
2. Build the specification generating real code:
   ```bash
   OMNI_MOCK_LLM=false OMNI_LLM_PROVIDER=ollama OLLAMA_MODEL="qwen2.5-coder:7b" cargo run --bin omni -- build examples/stabilization_test.schema.omni --target typescript
   ```
3. Verify that the generated TypeScript code in the `build` directory compiles and passes tests:
   ```bash
   npm test --prefix build
   ```
