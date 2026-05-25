<h1 align="center">⚡ OmniLang</h1>

<p align="center">
  <strong>The specification language for AI-native development.</strong><br>
  Write specs, not code. Let AI agents generate verified implementations.
</p>

<p align="center">
  <a href="https://github.com/denelvis/omnilang/actions"><img src="https://img.shields.io/github/actions/workflow/status/denelvis/omnilang/ci.yml?branch=main&label=CI&style=flat-square" alt="CI"></a>
  <a href="LICENSE-APACHE"><img src="https://img.shields.io/badge/license-Apache--2.0%20OR%20MIT-blue?style=flat-square" alt="License"></a>
  <img src="https://img.shields.io/badge/status-alpha-orange?style=flat-square" alt="Status">
</p>

---

## What is OmniLang?

OmniLang is a **declarative specification language** that bridges the gap between human intent and AI-generated code. You describe *what* your system should do — the AI agents figure out *how*.

```omnilang
module acme.checkout

service Checkout {
  goal: "Process customer orders with payment validation"

  constraints:
    - idempotent
    - latency(p95: <200ms)
    - PCI_compliant

  rpc PlaceOrder {
    inputs:
      customer_id: CustomerId
      items: List<OrderItem>
      payment: PaymentMethod

    outputs:
      order_id: OrderId
      status: OrderStatus
      receipt: Receipt

    postconditions:
      - inventory_reserved(items)
      - payment_charged(payment, total(items))

    tests:
      - scenario: "Successful order"
        given: valid_customer(), in_stock_items(3)
        expect: status == OrderStatus.Confirmed

      - scenario: "Insufficient stock"
        given: valid_customer(), out_of_stock_item()
        expect_error: InsufficientStock
  }
}
```

Then:

```bash
$ omni build
[1/5] Analyzing specs... ✓ (3 services, 12 types)
[2/5] Planning execution... ✓ (8 tasks, estimated cost: $0.15)
[3/5] Generating artifacts... ✓
[4/5] Verifying... ✓ (24 tests passed, all constraints met)
[5/5] Emitting artifacts... ✓

Build succeeded. Confidence: High. Cost: $0.12. Duration: 1m 42s.
```

**Output:** production-ready TypeScript (or Rust, Python, Go) with tests, types, and infrastructure manifests. The AI is only needed during the build — the output is pure, deterministic code.

## Key Ideas

| Concept | Description |
|---------|-------------|
| **Intent over implementation** | Describe *what*, not *how*. The spec is the source of truth. |
| **Verification is compilation** | AI generates code → tests run → constraints check → output is proven correct. |
| **Agent-agnostic** | Works with any LLM: OpenAI, Anthropic, Google, open-source models. |
| **Confidence types** | Every artifact has a trust level: Proven, High, Medium, Low, Speculative. |
| **Budget-aware** | Token limits, cost caps, model tiering — built into the language. |

## Installation

> ⚠️ OmniLang is in early development. The CLI currently supports `omni check` (spec validation).

```bash
# From source (requires Rust 1.85+)
cargo install omni-cli

# Pre-built binaries coming soon:
# curl -fsSL https://install.omnilang.dev | sh
# brew install omnilang/tap/omni
# npm install -g @omnilang/cli
```

## Quick Start

```bash
# Initialize a new project
omni init my-api

# Validate your specs
omni check

# See what would be generated (dry run)
omni plan

# Generate verified code
omni build
```

## Documentation

Full specification docs are in [`docs/`](./docs/):

| Document | Description |
|----------|-------------|
| [Vision & Philosophy](./docs/00-vision.md) | Why OmniLang exists |
| [Architecture](./docs/01-architecture.md) | Layered architecture, Thinking/Acting split |
| [Core Concepts](./docs/02-core-concepts.md) | Intent blocks, constraints, contracts, evidence |
| [Type System](./docs/03-type-system.md) | Refined types, generics, confidence types |
| [Syntax Reference](./docs/04-syntax-reference.md) | Complete grammar and syntax |
| [Compilation Model](./docs/05-compilation-model.md) | 5-phase build pipeline |
| [Testing & Verification](./docs/06-testing-verification.md) | Scenario, property, visual, chaos tests |
| [Module System](./docs/07-module-system.md) | Imports, exports, packages |
| [Agent Protocol](./docs/08-agent-protocol.md) | How AI agents interact with specs |
| [Tooling & IDE](./docs/09-tooling-ide.md) | LSP, VS Code, entropy analysis |
| [Examples](./docs/10-examples.md) | Real-world spec examples |
| [Roadmap](./docs/11-roadmap.md) | Development phases |
| [Glossary](./docs/12-glossary.md) | Key terms and abbreviations |

## Project Structure

```
crates/
├── omni-parser/     # Lexer + Parser → AST
├── omni-analyzer/   # Type checker, constraint resolver → Spec IR
└── omni-cli/        # CLI binary (`omni` command)
```

## Contributing

See [CONTRIBUTING.md](./CONTRIBUTING.md) for build instructions and contribution guidelines.

## License

Licensed under either of:

- Apache License, Version 2.0 ([LICENSE-APACHE](LICENSE-APACHE))
- MIT License ([LICENSE-MIT](LICENSE-MIT))

at your option.
