# Glossary

Key terms and definitions used throughout the OmniLang documentation.

---

| Term | Definition |
|------|-----------|
| **Agent** | An AI system (typically an LLM) that reads OmniLang specifications and generates implementation artifacts. Agents are stateless and communicate via the Agent Protocol. |
| **Agent Protocol** | The structured message format and lifecycle rules governing communication between the OmniLang orchestrator and AI agents. |
| **Acting Environment** | The CPU-based execution environment where generated code is compiled, tested, and verified inside MicroVMs. Isolated from the Thinking Environment. |
| **Analyzer** | The deterministic (non-AI) component that parses, type-checks, and validates OmniLang source files. Analogous to a traditional compiler frontend. |
| **Artifact** | Any output produced by the build process: source code, tests, infrastructure manifests, documentation, reports. |
| **Budget** | Resource constraints for the build process, including token limits, cost caps, time limits, and model preferences. |
| **Chaos Test** | A test that verifies system resilience by injecting failures (network partitions, service crashes, resource exhaustion). |
| **Compilation** | In OmniLang, the process of transforming a specification into verified, working artifacts via AI agents. Includes generation and verification. |
| **Confidence Level** | A trust rating (Proven, High, Medium, Low, Speculative) attached to generated artifacts, indicating the strength of verification evidence. |
| **Constraint** | A machine-verifiable requirement that the generated implementation must satisfy (e.g., `idempotent`, `latency(p95: <200ms)`, `PCI_compliant`). |
| **Constrained Decoding** | An inference technique where the LLM is forced to generate output strictly conforming to a formal grammar (e.g., an OMWF schema), eliminating syntax errors in the output by construction. Also called grammar-constrained generation. |
| **Contract** | A formal interface definition including inputs, outputs, preconditions, postconditions, invariants, and error types. Inspired by Design by Contract (DbC). |
| **Dual-Phase Compilation** | The architecture where probabilistic AI generation is sandwiched between deterministic analysis and verification phases. |
| **Egress Filtering** | Network security mechanism in the sandbox that blocks all outbound traffic except explicitly whitelisted domains. |
| **Entropy Score** | A metric (0-10) computed by the IDE that estimates how ambiguous a `goal` field is. Higher entropy = more possible interpretations = more risk of incorrect generation. |
| **Evidence** | Verifiable proof that a constraint or test was satisfied. Includes test results, coverage reports, benchmark data, security scans, and visual diffs. |
| **Evidence Chain** | A complete, auditable record linking each constraint to the evidence that proves it was verified. |
| **Factory** | A reusable test data generator that produces domain objects with sensible defaults and named variants. |
| **Fixture** | A named, reusable test state comprising multiple factories composed into a coherent scenario. |
| **Goal** | A natural-language description of what a service, component, or system should accomplish. Provides semantic context within the structured scaffolding of an intent block. |
| **Golden File** | A reference image (screenshot) used for visual testing. Generated output is compared against the golden file with a configurable tolerance. |
| **Guardrails Engine** | The runtime component that monitors AI agent output streams and blocks responses violating spec invariants. Used in the Production Runtime Layer. |
| **Instrumental Deadlock** | A situation where an agent encounters a task requiring an MCP tool that doesn't exist. Resolved via JIT Tool creation, registry fallback, or human escalation. |
| **Intent Block** | The primary specification unit in OmniLang. Declares what a system component should do (goal), its constraints, contracts, tests, and evidence. Block types include `service`, `component`, `pipeline`, `workflow`, `agent`, `schema`. |
| **Invariant** | A condition that must hold at all times throughout the system's lifecycle (e.g., "account balance is never negative"). |
| **JIT Tool** | A Just-In-Time Tool — an MCP adapter that an agent writes and loads at runtime when a needed tool doesn't exist. |
| **MCP (Model Context Protocol)** | An open standard protocol for agent-to-tooling communication. Follows a Host/Client/Server architecture where each MCP server gives agents a specific capability. |
| **MicroVM** | A lightweight virtual machine (e.g., Firecracker, Kata Containers) with its own Linux kernel, used for sandbox isolation. Boots in 80-100ms, provides hardware-level isolation unlike Docker containers. |
| **Mixin** | A reusable bundle of constraints, postconditions, and tests that can be applied to multiple intent blocks. Similar to traits or interfaces. |
| **Module** | A namespaced unit of OmniLang specification, typically corresponding to one `.omni` file. Modules can import from and export to other modules. |
| **Multimodal Type** | A type representing non-textual data: images, screenshots, traces, logs, diagrams, audio, or video. These are first-class types in OmniLang. |
| **Orchestrator** | The component that plans, schedules, and manages the execution of AI agent tasks during compilation. Handles task planning, agent routing, budget management, and retry logic. |
| **OMWF (OmniLang Minimized Wire Format)** | A compact, line-oriented text format optimized for LLM tokenizers, used as the wire format for all inter-agent communication. Reduces token overhead by 40-50% compared to JSON by eliminating quotes, braces, and redundant delimiters. Humans always see the equivalent JSON; OMWF is transparent to developers. |
| **Policy** | An organization-wide or project-wide rule set that applies constraints across all services in scope. Policies enforce governance and compliance. |
| **Policy Hot-Reload** | The ability to update OmniLang runtime constraints without redeploying the underlying service. Used in the Production Runtime Layer. |
| **Postcondition** | A condition that must be true after an operation completes. Defines the expected state change. |
| **Precondition** | A condition that must be true before an operation can execute. Defines valid input states. |
| **Property-Based Test** | A test that verifies an invariant holds for all valid inputs by generating random test cases. Uses shrinking to find minimal failing cases. |
| **Reasoning Trace** | A structured log of every decision an AI agent made during generation — which architecture, which library, which patterns, and why. Viewable in the IDE. |
| **Refined Type** | A base type enhanced with domain-specific validation rules (e.g., `Email = String { format: RFC_5322 }`). Also called a semantic type. |
| **Retry Controller** | The component that manages the generate-verify-retry loop, including failure analysis, prompt enhancement, and escalation to humans. |
| **Scenario Test** | A concrete, BDD-style test case using Given-When-Then structure to describe a specific system behavior. |
| **Self-Refinement Loop** | The closed-loop mechanism where verification failures are fed back to the AI agent as structured error context, enabling iterative improvement without human intervention. |
| **Semantic Gap** | The distance between human intent and machine execution. OmniLang addresses the *second* semantic gap: between human intent and AI-generated output. |
| **Spec** | Short for specification. The OmniLang source code that describes what a system should do and how to verify it. |
| **Spec Engineer** | A new engineering role focused on writing specifications so precise that any AI agent can generate correct implementations from them on the first attempt. |
| **Spec IR** | Specification Intermediate Representation. The validated, structured form of the spec produced by the analyzer and consumed by the orchestrator. |
| **Target Language** | The implementation language into which the spec is compiled (e.g., TypeScript, Rust, Python, Go). Chosen for auditability, debuggability, and ecosystem leverage. |
| **Thinking Environment** | The GPU-based execution environment where LLMs reason about specifications, plan implementations, and generate code. Separated from the Acting Environment. |
| **Trust Policy** | Rules governing what confidence levels are required for different environments (e.g., production requires High, staging accepts Medium). |
| **Trust Type** | See Confidence Level. A type wrapper (`Confident<T>`) that attaches a trust rating and evidence to any value. |
| **Validated Spec IR** | The output of the analyzer phase — a fully type-checked, constraint-validated, dependency-resolved representation of the spec. |
| **Verification Engine** | The component that runs tests, checks constraints, collects evidence, and produces verification reports. Runs deterministically in the sandbox. |
| **Verification Package** | A community-authored package of reusable constraints, invariants, and test scenarios (e.g., `@security/pci-dss-v4`). The OmniLang equivalent of a code library. |
| **Visual Test** | A test that compares a rendered UI component against a golden reference image, with configurable tolerance for pixel differences. |
| **Zero-Trust Network** | The sandbox network security model where all egress traffic is blocked by default, with access permitted only to explicitly whitelisted domains. |

---

## Abbreviations

| Abbreviation | Expansion |
|-------------|-----------|
| AST | Abstract Syntax Tree |
| BDD | Behavior-Driven Development |
| CI/CD | Continuous Integration / Continuous Deployment |
| CLS | Cumulative Layout Shift |
| CRUD | Create, Read, Update, Delete |
| DAST | Dynamic Application Security Testing |
| DbC | Design by Contract |
| DSL | Domain-Specific Language |
| EBNF | Extended Backus-Naur Form |
| ETL | Extract, Transform, Load |
| GDPR | General Data Protection Regulation |
| GGUF | GPT-Generated Unified Format (quantized model format) |
| HIPAA | Health Insurance Portability and Accountability Act |
| IR | Intermediate Representation |
| JIT | Just-In-Time (dynamic tool creation at runtime) |
| JWT | JSON Web Token |
| LLM | Large Language Model |
| LSP | Language Server Protocol |
| MCP | Model Context Protocol |
| mTLS | Mutual Transport Layer Security |
| OMWF | OmniLang Minimized Wire Format |
| OWASP | Open Web Application Security Project |
| PCI DSS | Payment Card Industry Data Security Standard |
| PII | Personally Identifiable Information |
| RBAC | Role-Based Access Control |
| ABAC | Attribute-Based Access Control |
| RFS | Request for Spec (community proposal process, analogous to RFC) |
| SARIF | Static Analysis Results Interchange Format |
| SAST | Static Application Security Testing |
| SDD | Spec-Driven Development |
| SLM | Small Language Model (7B-13B parameters, for local inference) |
| SLO | Service Level Objective |
| SMT | Satisfiability Modulo Theories |
| TLS | Transport Layer Security |
| WCAG | Web Content Accessibility Guidelines |
