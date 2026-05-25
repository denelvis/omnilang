# Testing & Verification

Testing in OmniLang is fundamentally different from testing in traditional languages. Tests are not written *after* the code — they are part of the specification that *drives* code generation. Tests are the **acceptance criteria** that the AI agent must satisfy.

---

## Philosophy

> "In OmniLang, a spec without tests is like a contract without enforcement — technically valid but practically meaningless."

Tests serve three purposes simultaneously:

1. **Specification** — they tell the AI agent what "correct" means
2. **Verification** — they prove the generated code works
3. **Documentation** — they describe system behavior in concrete terms

---

## Test Types

### 1. Scenario Tests (BDD-Style)

The most common test type. Describes a concrete behavior using Given-When-Then.

```omnilang
tests:
  - scenario: "Successful login with email/password"
    given:
      user_exists(email: "alice@example.com", password_hash: bcrypt("secret123"))
    when:
      login(email: "alice@example.com", password: "secret123")
    expect:
      status == 200
      body.session_token is valid JWT
      body.user.email == "alice@example.com"
    expect_side_effect:
      audit_log contains entry(action: "login", user: "alice@example.com", result: "success")

  - scenario: "Login with wrong password"
    given:
      user_exists(email: "alice@example.com")
    when:
      login(email: "alice@example.com", password: "wrong")
    expect:
      status == 401
      body.error == "InvalidCredentials"
      response_time < 200ms  // prevent timing attacks
    expect_side_effect:
      failed_login_counter("alice@example.com") incremented
```

### 2. Property-Based Tests

Describe invariants that hold for all valid inputs. The verification engine generates random inputs and checks the property.

```omnilang
tests:
  - property: "Serialization roundtrip preserves data"
    forall:
      order <- arbitrary<Order>
    assert:
      deserialize(serialize(order)) == order

  - property: "Sorting is idempotent"
    forall:
      items <- arbitrary<List<Product>>
    assert:
      sort(sort(items)) == sort(items)

  - property: "Price calculation is non-negative"
    forall:
      cart <- arbitrary<Cart> where cart.items.length > 0
    assert:
      calculate_total(cart) >= Money(0, cart.currency)

  - property: "Stock conservation during reservation"
    forall:
      product <- arbitrary<ProductId> where stock(product) > 0
      qty <- Int(1, stock(product))
    assert:
      let before = total_stock(product)
      reserve(product, qty)
      total_stock(product) == before  // stock is conserved, just redistributed

  - property: "Discount never exceeds item price"
    forall:
      item <- arbitrary<CartItem>
      coupon <- arbitrary<Coupon>
    assert:
      apply_discount(item, coupon).price >= 0
```

### 3. Visual Tests

Compare rendered UI against golden reference images.

```omnilang
tests:
  - visual: "Product card renders correctly"
    component: ProductCard
    props:
      product: mock_product(name: "Headphones", price: 79.99, image: @mock/headphones.jpg)
    viewports:
      - name: desktop
        size: 1440x900
        golden: @golden/product_card_desktop.png
        tolerance: 1.5%
      - name: mobile
        size: 375x812
        golden: @golden/product_card_mobile.png
        tolerance: 2%
    ignore_regions:
      - selector: ".timestamp"  // dynamic content
      - rect: { x: 0, y: 0, w: 100, h: 50 }  // header area

  - visual: "Cart empty state"
    component: ShoppingCart
    props:
      items: []
    viewport: 1440x900
    golden: @golden/cart_empty.png
    tolerance: 1%
```

### 4. Performance Tests

Define performance SLOs as executable tests.

```omnilang
tests:
  - benchmark: "Checkout API latency"
    target: service Checkout
    method: rpc ProcessPayment
    load_profile:
      type: constant
      concurrent_users: 1000
      duration: 60s
      ramp_up: 10s
    input_generator: arbitrary<PaymentRequest>
    expect:
      p50_latency < 50ms
      p95_latency < 200ms
      p99_latency < 500ms
      error_rate < 0.1%
      throughput > 5000 rps

  - benchmark: "Product search response time"
    target: service ProductSearch
    method: rpc Search
    load_profile:
      type: stepped
      steps: [100, 500, 1000, 5000]
      step_duration: 30s
    expect:
      p95_latency < 100ms at 1000 users
      p95_latency < 300ms at 5000 users
      no_errors at any load level
```

### 5. Chaos Tests

Verify system resilience under failure conditions.

```omnilang
tests:
  - chaos: "Database failover"
    target: service OrderManager
    inject:
      failure: database_disconnect
      duration: 5s
      after: 10s of normal operation
    expect:
      service returns graceful error (503) during outage
      service recovers within 10s after database reconnects
      no data loss
      no duplicate orders

  - chaos: "Network partition between services"
    target: service Checkout -> service PaymentProcessor
    inject:
      failure: network_partition
      duration: 15s
    expect:
      Checkout retries with exponential backoff
      Checkout responds with "payment processing" status
      PaymentProcessor processes payment when connectivity restores
      no duplicate charges

  - chaos: "Memory pressure"
    target: service ImageProcessor
    inject:
      failure: memory_pressure(limit: 256MB)
    expect:
      service degrades gracefully (reduces batch size)
      no OOM crash
      processing continues at reduced throughput
```

### 6. Security Tests

Verify security properties.

```omnilang
tests:
  - security: "SQL injection resistance"
    target: service UserSearch
    method: rpc FindUser
    inputs:
      - query: "'; DROP TABLE users; --"
      - query: "1 OR 1=1"
      - query: "admin'--"
    expect:
      all inputs are safely handled
      no raw SQL execution
      response is either valid result or input validation error

  - security: "Authentication bypass"
    target: service AdminPanel
    method: rpc ListUsers
    contexts:
      - no_auth: expect status == 401
      - expired_token: expect status == 401
      - valid_user_token: expect status == 403  // not admin
      - valid_admin_token: expect status == 200

  - security: "PII exposure in logs"
    target: service UserProfile
    method: rpc UpdateProfile
    input: { email: "test@example.com", ssn: "123-45-6789" }
    expect:
      response does not contain ssn
      application_logs do not contain ssn
      application_logs do not contain raw email
      audit_log contains masked reference only

  - security: "Rate limiting"
    target: service Login
    method: rpc Authenticate
    attack:
      type: brute_force
      attempts: 100
      window: 1min
    expect:
      rate limited after 5 attempts
      lockout after 10 attempts
      response time constant (prevent timing attacks)
```

### 7. Contract Tests

Verify that connected services maintain compatible interfaces.

```omnilang
tests:
  - contract: "OrderService → ShippingService compatibility"
    producer: service OrderService
    consumer: service ShippingService
    interface: rpc CreateShipment
    verify:
      producer.outputs.order is compatible with consumer.inputs.order
      all required fields in consumer.inputs are present in producer.outputs
      type widening is acceptable (producer may include extra fields)
      type narrowing is NOT acceptable (consumer must not expect missing fields)
```

---

## Test Data Management

### Factories

Reusable test data generators.

```omnilang
factory User {
  defaults:
    id: uuid()
    email: fake.email()
    name: fake.full_name()
    created_at: now()
    status: Active

  variants:
    admin: { role: Admin, permissions: all }
    inactive: { status: Inactive, deactivated_at: now() - 30days }
    new_user: { created_at: now() - 1hour, onboarding_complete: false }
    premium: { tier: Premium, subscription_expires: now() + 365days }
}

factory Order {
  defaults:
    id: order_id()
    customer: Factory<User>.create()
    items: [Factory<CartItem>.create(count: random(1, 5))]
    status: Placed
    placed_at: now()

  variants:
    large: { items: Factory<CartItem>.create(count: 50) }
    international: { shipping_address: Factory<Address>.create(country: "JP") }
    completed: { status: Completed, completed_at: now() - 1day }
}
```

### Fixtures

Named, reusable test states.

```omnilang
fixture "E-commerce store with sample data" {
  users:
    - Factory<User>.admin(email: "admin@store.com")
    - Factory<User>.create(count: 10)
    - Factory<User>.premium(count: 3)

  products:
    - Factory<Product>.create(count: 50, category: "Electronics")
    - Factory<Product>.create(count: 30, category: "Books")
    - Factory<Product>.out_of_stock(count: 5)

  orders:
    - Factory<Order>.completed(count: 100)
    - Factory<Order>.create(count: 20, status: Processing)
}
```

---

## Verification Engine

The verification engine orchestrates all test types into a unified pipeline.

### Execution Order

```
1. Static Analysis (type checking, constraint validation)
   ↓
2. Unit Tests (fastest feedback)
   ↓
3. Property-Based Tests (broader coverage)
   ↓
4. Contract Tests (interface compatibility)
   ↓
5. Security Tests (vulnerability scanning)
   ↓
6. Visual Tests (UI correctness)
   ↓
7. Performance Tests (SLO compliance)
   ↓
8. Chaos Tests (resilience)
```

**Fail-fast:** If any phase fails, subsequent phases are skipped (configurable).

### Verification Report

```json
{
  "timestamp": "2025-01-15T10:30:00Z",
  "overall_result": "PASS",
  "confidence": "High",
  "phases": {
    "static_analysis": { "status": "PASS", "duration_ms": 45 },
    "unit_tests": {
      "status": "PASS",
      "total": 156,
      "passed": 156,
      "failed": 0,
      "duration_ms": 3200
    },
    "property_tests": {
      "status": "PASS",
      "properties": 23,
      "cases_generated": 23000,
      "shrink_attempts": 0,
      "duration_ms": 8500
    },
    "security_scan": {
      "status": "PASS",
      "scanner": "semgrep",
      "findings": { "critical": 0, "high": 0, "medium": 1, "low": 3 },
      "duration_ms": 12000
    },
    "performance": {
      "status": "PASS",
      "p50_ms": 32,
      "p95_ms": 142,
      "p99_ms": 287,
      "throughput_rps": 8500,
      "duration_ms": 65000
    }
  },
  "cost": {
    "generation": "$0.32",
    "verification": "$0.00",
    "total": "$0.32"
  }
}
```

---

## Test Coverage Model

OmniLang defines coverage differently from traditional code coverage:

| Coverage Type | What It Measures |
|--------------|-----------------|
| **Spec Coverage** | % of spec fields with at least one test |
| **Scenario Coverage** | % of state transitions tested |
| **Constraint Coverage** | % of constraints with verification evidence |
| **Error Path Coverage** | % of declared errors with test scenarios |
| **Visual Coverage** | % of UI states with golden screenshots |
| **Property Coverage** | Number of invariants tested with property-based tests |

```bash
$ omni coverage
Spec Coverage Report:
  Services:     12/12 (100%) — all services have tests
  Constraints:  45/48 (93.7%) — 3 constraints lack verification
  Error paths:  23/28 (82.1%) — 5 error types untested
  Visual:       8/10 (80%) — 2 components missing golden files
  Properties:   15/15 (100%) — all invariants have property tests

  Overall: 91.3% — GOOD (threshold: 85%)

  Gaps:
    - service Shipping: constraint "delivery_estimation_accuracy" untested
    - service Notification: error "TemplateNotFound" has no scenario
    - component Header: no visual golden for tablet viewport
```

---

## Mutation Testing

OmniLang supports specification-level mutation testing: the system deliberately introduces spec mutations to verify that tests catch them.

```omnilang
mutation_test {
  target: service Checkout

  mutations:
    - remove constraint "idempotent"
      expect: at least 1 test fails

    - change postcondition "balance decreased by amount"
      to: "balance unchanged"
      expect: at least 1 test fails

    - remove error handler "InsufficientFunds"
      expect: at least 1 test fails

    - double latency constraint (200ms → 400ms)
      expect: benchmark test still defines correct threshold

  report:
    mutation_score: 95%  // 95% of mutations caught by tests
    surviving_mutations: [...]  // mutations that tests missed
}
```

This ensures that the test suite is not just passing — it's **meaningfully testing** the right things.
