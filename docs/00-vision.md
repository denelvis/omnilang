# Vision & Philosophy

## The Problem: Two Semantic Gaps

Classical programming languages were invented to bridge the **first semantic gap** — between human thought and silicon execution. Languages like C, Java, and Python gave humans a way to express logic that machines could execute deterministically.

Today, a **second semantic gap** has emerged: the gap between human intent and the probabilistic, generative nature of Large Language Models. When a developer tells an AI agent "build me a checkout service," the agent must interpret fuzzy natural language, make hundreds of micro-decisions, and produce code — but there is no structured way to verify that the output actually matches the original intent.

Current approaches to bridging this gap are ad hoc:

| Approach | Limitation |
|----------|-----------|
| Chat prompts | Ambiguous, non-reproducible, no verification |
| YAML/JSON configs | Too rigid, poor expressiveness for goals and constraints |
| Markdown specs | Too loose, no machine-enforced semantics |
| LangChain expressions | Implementation-focused, not intent-focused |
| Swagger/OpenAPI | Describes API shape, not behavior or quality |

**OmniLang exists to close this second gap.**

---

## The Insight: Programming ≠ Coding Anymore

In the AI-native era, the fundamental act of programming is shifting:

```
Traditional:  Human → writes code → Machine executes
AI-Native:    Human → writes intent + constraints → Agent generates + verifies → Machine executes
```

This means the human's primary artifact is no longer **code** — it is a **verifiable specification**. The code becomes an intermediate artifact, just as assembly became an intermediate artifact when compilers were invented.

OmniLang is designed for this new reality.

---

## Core Philosophy

### 1. Intent Over Implementation

The developer describes **what** the system should do, not **how** it should do it. The "how" is the agent's job. The developer's job is to make the "what" precise enough that the agent cannot misinterpret it, and verifiable enough that deviations are caught.

### 2. Verification Is the New Compilation

In traditional languages, compilation transforms source code into executables and catches type errors. In OmniLang, "compilation" is the process where:

1. An AI agent reads the spec
2. Generates an implementation (in any target language)
3. Runs all specified tests and checks
4. Verifies constraints (performance, security, cost)
5. If verification fails → the agent iterates automatically
6. The output is a **proven, working system** (code + tests + infra manifests)

The spec is the source of truth. The generated code is a build artifact.

### 3. Uncertainty Is Fundamental

AI agents are probabilistic. They can be wrong. OmniLang acknowledges this by making **confidence levels, fallback strategies, and human-in-the-loop escalation** first-class language concepts — not afterthoughts.

### 4. The Spec Is the Single Source of Truth

Everything — architecture, behavior, quality attributes, test cases, visual expectations, cost budgets — lives in one coherent specification. No more scattered requirements in Jira, tests in pytest, architecture in Confluence, and deployment in Terraform. OmniLang unifies all of these.

---

## What OmniLang Is NOT

- **Not a replacement for Python/Go/Rust.** Those are target languages. OmniLang sits above them.
- **Not a prompt template system.** It has formal semantics, not just string interpolation.
- **Not UML 2.0.** It is executable and verifiable, not just a diagram.
- **Not a configuration format.** It expresses goals, behaviors, and quality constraints — not just settings.

---

## The Name

**OmniLang** (from Latin *omni-* "all, every") reflects the language's ambition to be:

- **Omni-modal** — handles text, images, traces, schemas, logs
- **Omni-layer** — spans from business intent to infrastructure
- **Omni-agent** — works with any AI agent, model, or toolchain

---

## Audience

| Role | How they use OmniLang |
|------|----------------------|
| **Product Engineer** | Writes intent blocks and acceptance criteria |
| **Platform Engineer** | Defines constraints, SLOs, and infrastructure policies |
| **AI Agent** | Reads specs, generates implementations, reports evidence |
| **QA Engineer** | Authors test scenarios and visual golden files |
| **Security Engineer** | Defines security constraints and audit requirements |
| **CI/CD Pipeline** | Consumes specs to orchestrate build-verify-deploy cycles |

---

## Guiding Metaphor

Think of OmniLang as a **blueprint language for buildings**, not the bricks and mortar themselves.

An architect draws blueprints that specify: "This room must be 30m², load-bearing, with natural light from the south." The architect doesn't lay bricks. The construction crew (AI agents) does that. But the blueprint is precise enough that the building inspector (verifier) can check if the result matches the intent.

OmniLang is the blueprint. The AI agent is the construction crew. The verification engine is the building inspector.
