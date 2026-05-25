# Type System

OmniLang features a rich type system that goes far beyond traditional data types. It includes **data types**, **confidence types**, **multimodal types**, **budget types**, and **semantic types** — all designed to minimize ambiguity between human intent and AI-generated output.

---

## Design Principles

1. **Types encode meaning, not just shape** — `Email` is not just `String`, it carries validation rules and semantic intent
2. **Types flow across boundaries** — a contract's output type must be compatible with its consumer's input type
3. **Types express uncertainty** — `Confident<T>` wraps any type with a trust level
4. **Types include non-data concepts** — cost budgets, latency SLOs, and visual expectations are typed

---

## Primitive Types

```omnilang
// Scalar types
Bool
Int                    // arbitrary precision
Int32, Int64           // fixed width
Float32, Float64
String
Char

// Temporal types
DateTime               // ISO 8601
Duration               // e.g., 5s, 200ms, 24h
Timestamp              // Unix epoch milliseconds
Date
Time

// Identity types
UUID
ULID
CUID

// Monetary
Money(amount: Float64, currency: CurrencyCode)

// Network
URL
Email
IPAddress(v4 | v6)
Port
```

---

## Collection Types

```omnilang
List<T>                // ordered collection
Set<T>                 // unique unordered collection
Map<K, V>              // key-value mapping
Queue<T>               // FIFO queue
Stack<T>               // LIFO stack
Tree<T>                // hierarchical structure

// Bounded collections
List<T>(min: 1, max: 100)
String(min_length: 1, max_length: 255)
```

---

## Algebraic Types

```omnilang
// Sum types (tagged unions)
type PaymentStatus = enum {
  Pending
  Processing
  Completed(transaction_id: TransactionId)
  Failed(error: PaymentError)
  Refunded(refund_id: RefundId, amount: Money)
}

// Product types (records/structs)
type Address = struct {
  street: String(max_length: 200)
  city: String
  state: Option<String>
  postal_code: PostalCode
  country: CountryCode(ISO_3166_1)
}

// Option type (nullable)
Option<T> = Some(T) | None

// Result type (fallible operations)
Result<T, E> = Ok(T) | Err(E)
```

---

## Semantic Types (Refined Types)

Semantic types add domain-specific validation rules to base types. They are not just aliases — they carry **verification constraints** that the agent must ensure in the generated code.

```omnilang
// Define refined types with validation rules
type Email = String {
  format: RFC_5322
  max_length: 254
  normalize: lowercase
}

type Password = String {
  min_length: 12
  must_contain: [uppercase, lowercase, digit, special]
  not_in: common_passwords_list
  storage: bcrypt(rounds: 12)  // semantic: how to persist
}

type PostalCode = String {
  format: regex("^[0-9]{5}(-[0-9]{4})?$")  // US ZIP
}

type Latitude = Float64 {
  range: [-90.0, 90.0]
}

type Longitude = Float64 {
  range: [-180.0, 180.0]
}

type GeoPoint = struct {
  lat: Latitude
  lng: Longitude
}

type Age = Int {
  range: [0, 150]
}

type Percentage = Float64 {
  range: [0.0, 100.0]
  precision: 2
}
```

---

## Confidence Types

Confidence types wrap any value with a trust level, enabling the system to track and propagate uncertainty.

```omnilang
// Generic confidence wrapper
type Confident<T> = struct {
  value: T
  confidence: ConfidenceLevel
  evidence: List<EvidenceRef>
  generated_by: AgentId
  generated_at: Timestamp
}

// Confidence levels
type ConfidenceLevel = enum {
  Proven         // Formally verified
  High           // Thoroughly tested
  Medium         // Functionally tested
  Low            // Minimally tested
  Speculative    // Unverified
}

// Usage in contracts
contract AnalyzeSentiment {
  inputs:
    text: String

  outputs:
    sentiment: Confident<SentimentScore>
    // The output explicitly carries its confidence level

  postconditions:
    - sentiment.confidence >= Medium
    // Agent must achieve at least Medium confidence
}
```

### Confidence Arithmetic

```omnilang
// Confidence degrades through composition
Confident<A> + Confident<B> → Confident<C>
  where C.confidence = min(A.confidence, B.confidence)

// Confidence can be upgraded via additional evidence
upgrade(Confident<T>, evidence: Evidence) → Confident<T>
  where new.confidence = compute_confidence(old.evidence + evidence)
```

---

## Multimodal Types

OmniLang treats non-textual data as first-class types, enabling specs that reference images, audio, video, and structured traces.

```omnilang
// Visual types
type Screenshot = Image {
  format: PNG | JPEG | WebP
  metadata: struct {
    viewport: Viewport
    device_pixel_ratio: Float64
    captured_at: Timestamp
  }
}

type VisualGolden = struct {
  reference: Screenshot
  tolerance: Percentage        // pixel diff tolerance
  ignore_regions: List<Rect>   // areas to skip (e.g., timestamps)
}

type Viewport = struct {
  width: Int(range: [320, 3840])
  height: Int(range: [240, 2160])
}

// Trace types
type Trace = struct {
  spans: List<Span>
  format: OpenTelemetry | Jaeger | Zipkin
}

type Span = struct {
  operation: String
  duration: Duration
  status: SpanStatus
  attributes: Map<String, Any>
  children: List<Span>
}

// Log types
type LogStream = struct {
  entries: List<LogEntry>
  format: JSON | Plaintext | Structured
}

type LogEntry = struct {
  timestamp: Timestamp
  level: LogLevel
  message: String
  context: Map<String, Any>
}

// Schema types
type DatabaseSchema = struct {
  tables: List<TableDef>
  format: SQL_DDL | Prisma | TypeORM
}

type APISchema = struct {
  endpoints: List<EndpointDef>
  format: OpenAPI_3 | GraphQL_SDL | Protobuf
}

// Document types
type Diagram = Image {
  source: Mermaid | PlantUML | D2
  rendered: Screenshot
}

type Document = struct {
  content: Markdown | RST | AsciiDoc
  embedded_media: List<Image | Diagram>
}
```

---

## Budget Types

Budget types make resource constraints explicit and trackable.

```omnilang
type TokenBudget = struct {
  max_input_tokens: Int
  max_output_tokens: Int
  max_total_tokens: Int
  model_preference: ModelPreference
}

type CostBudget = struct {
  max_total: Money
  per_component: Option<Money>
  per_retry: Option<Money>
  alert_threshold: Percentage  // alert when N% consumed
}

type ModelPreference = enum {
  CheapFast         // e.g., GPT-4o-mini, Claude Haiku
  Balanced          // e.g., GPT-4o, Claude Sonnet
  SmartExpensive    // e.g., o3, Claude Opus
  Custom(model_id: String)
}

type TimeBudget = struct {
  max_generation_time: Duration
  max_verification_time: Duration
  timeout_action: TimeoutAction
}

type TimeoutAction = enum {
  ReturnBestEffort(confidence: Speculative)
  Fail(message: String)
  EscalateToHuman
}

// Usage
budget {
  cost: CostBudget {
    max_total: $0.50
    per_component: $0.10
    alert_threshold: 80%
  }

  tokens: TokenBudget {
    max_total_tokens: 100_000
    model_preference: Balanced
  }

  time: TimeBudget {
    max_generation_time: 5min
    timeout_action: EscalateToHuman
  }
}
```

---

## Type Composition

Types compose through standard algebraic operations:

```omnilang
// Union types
type PaymentMethod = CreditCard | BankTransfer | CryptoWallet | PayPal

// Intersection types (must satisfy all)
type SecureEndpoint = Endpoint & Authenticated & RateLimited & Logged

// Generic types
type Paginated<T> = struct {
  items: List<T>
  total: Int
  page: Int
  per_page: Int(range: [1, 100])
  has_next: Bool
}

// Mapped types (transform all fields)
type Nullable<T: struct> = {
  [field in T]: Option<T[field]>
}

// Partial types (all fields optional)
type UpdateRequest<T: struct> = Partial<T> & { id: T.id }
```

---

## Type Compatibility and Subtyping

OmniLang uses **structural subtyping** — types are compatible if their shapes match, regardless of name.

```omnilang
type Dog = struct { name: String, age: Int }
type Pet = struct { name: String }

// Dog is a subtype of Pet (has all required fields)
// So a function expecting Pet can accept Dog
```

### Contract Type Checking

The analyzer verifies type compatibility across service boundaries:

```omnilang
service OrderService {
  outputs:
    order: Order  // includes field: items: List<OrderItem>
}

service ShippingService {
  inputs:
    items: List<ShippableItem>  // ShippableItem ⊂ OrderItem must hold
}

// The analyzer checks: OrderItem is structurally compatible with ShippableItem
// If not → compile-time error: "OrderItem missing field 'weight' required by ShippableItem"
```

---

## Standard Library Types

OmniLang includes a standard library of commonly used domain types:

| Module | Types |
|--------|-------|
| `std.auth` | `UserId`, `SessionToken`, `Permission`, `Role`, `AuthContext` |
| `std.http` | `HttpMethod`, `StatusCode`, `Header`, `Request`, `Response` |
| `std.money` | `Money`, `CurrencyCode`, `ExchangeRate` |
| `std.geo` | `GeoPoint`, `BoundingBox`, `Distance` |
| `std.time` | `TimeZone`, `DateRange`, `Cron`, `Recurrence` |
| `std.media` | `Image`, `Video`, `Audio`, `MimeType` |
| `std.infra` | `ContainerSpec`, `ResourceLimit`, `HealthCheck` |
| `std.observe` | `Metric`, `Trace`, `LogLevel`, `Alert` |
