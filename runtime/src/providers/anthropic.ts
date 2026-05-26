import Anthropic from "@anthropic-ai/sdk";
import pc from "picocolors";
import { LLMProvider } from "./base";

export class AnthropicProvider implements LLMProvider {
  private client?: Anthropic;
  private isMock: boolean;

  constructor() {
    this.isMock = process.env.OMNI_MOCK_LLM === "true";
    if (!this.isMock) {
      const apiKey = process.env.ANTHROPIC_API_KEY || process.env.OMNI_API_KEY;
      if (!apiKey) {
        throw new Error(
          "Missing Anthropic API Key. Please set ANTHROPIC_API_KEY or OMNI_API_KEY in your environment, or run with OMNI_MOCK_LLM=true for mock mode."
        );
      }
      this.client = new Anthropic({ apiKey });
    }
  }

  public async generateCode(systemPrompt: string, userPrompt: string, model?: string): Promise<string> {
    if (this.isMock) {
      console.log(pc.blue("   [MOCK LLM] Simulating Claude 3.5 Sonnet response..."));
      return this.getMockResponse(systemPrompt, userPrompt);
    }

    if (!this.client) {
      throw new Error("Anthropic client is not initialized.");
    }

    const selectedModel = model || process.env.ANTHROPIC_MODEL || process.env.OMNI_MODEL || "claude-3-5-sonnet-20241022";
    const response = await this.client.messages.create({
      model: selectedModel,
      max_tokens: 4000,
      system: systemPrompt,
      messages: [{ role: "user", content: userPrompt }],
    });

    const content = response.content[0];
    if (content.type !== "text") {
      throw new Error("Unexpected non-text response from Claude API.");
    }

    return content.text;
  }

  public getMockResponse(systemPrompt: string, userPrompt: string): string {
    const promptLower = userPrompt.toLowerCase();

    // Detect target from the system prompt
    if (systemPrompt.toLowerCase().includes("rust")) {
      return this.getMockRustResponse(promptLower, userPrompt);
    }
    if (systemPrompt.toLowerCase().includes("python")) {
      return this.getMockPythonResponse(promptLower, userPrompt);
    }

    return this.getMockTypeScriptResponse(promptLower, userPrompt, systemPrompt);
  }

  private extractServiceName(prompt: string): string {
    // Match the quoted service name from the prompt (e.g., 'service: "AnalyticsService"')
    const quotedMatch = prompt.match(/service:\s*"([A-Z][a-zA-Z]+)"/);
    if (quotedMatch) return quotedMatch[1];
    // Fallback: find a CamelCase word ending in "Service"
    const svcMatch = prompt.match(/([A-Z][a-zA-Z]*Service)/);
    if (svcMatch) return svcMatch[1];
    return "DefaultService";
  }

  private toSnakeCase(name: string): string {
    return name.replace(/([A-Z])/g, "_$1").toLowerCase().replace(/^_/, "");
  }

  private getMockTypeScriptResponse(promptLower: string, rawPrompt: string, systemPrompt: string): string {
    // Case 0: SelfCorrectingService for validating the self-correction loop
    if (promptLower.includes("selfcorrectingservice")) {
      const isRetry = systemPrompt.includes("past generation retries") || systemPrompt.includes("LLM Prompt Adaptations");
      if (!isRetry) {
        // Return code with a TS type error on the first attempt
        return JSON.stringify({
          files: [
            {
              path: "src/services/SelfCorrectingService.ts",
              content: `export class SelfCorrectingService {
  public async process(): Promise<string> {
    const value: number = "this is a string, which triggers a TS compile error";
    return "ok";
  }
}
`
            },
            {
              path: "tests/SelfCorrectingService.test.ts",
              content: `import { SelfCorrectingService } from "../src/services/SelfCorrectingService";
describe("SelfCorrectingService", () => {
  it("should process", async () => {
    const service = new SelfCorrectingService();
    const res = await service.process();
    expect(res).toBe("ok");
  });
});
`
            }
          ]
        });
      } else {
        // Return corrected code on the retry attempt
        return JSON.stringify({
          files: [
            {
              path: "src/services/SelfCorrectingService.ts",
              content: `export class SelfCorrectingService {
  public async process(): Promise<string> {
    const value: number = 42;
    return "ok";
  }
}
`
            },
            {
              path: "tests/SelfCorrectingService.test.ts",
              content: `import { SelfCorrectingService } from "../src/services/SelfCorrectingService";
describe("SelfCorrectingService", () => {
  it("should process", async () => {
    const service = new SelfCorrectingService();
    const res = await service.process();
    expect(res).toBe("ok");
  });
});
`
            }
          ]
        });
      }
    }

    // Case 1: Checkout service
    if (promptLower.includes("checkoutservice") || promptLower.includes("\"checkout\"")) {
      return JSON.stringify({
        files: [
          {
            path: "src/services/Checkout.ts",
            content: `export interface ICheckoutService {
  placeOrder(customerId: string, items: any[]): Promise<string>;
}

export class CheckoutService implements ICheckoutService {
  public metrics = {
    payment_attempts_total: {
      counters: new Map<string, number>(),
      inc(labels: { payment_method: string; status: string }) {
        const key = JSON.stringify(labels);
        const val = this.counters.get(key) || 0;
        this.counters.set(key, val + 1);
      }
    }
  };

  public async placeOrder(customerId: string, items: any[]): Promise<string> {
    if (!customerId || customerId.trim() === "") {
      throw new Error("Customer ID is required");
    }
    if (!items || items.length === 0) {
      throw new Error("Cart is empty");
    }
    
    // Record metric attempt
    this.metrics.payment_attempts_total.inc({ payment_method: "credit_card", status: "success" });

    // Simulate order placement
    return "order-12345";
  }
}
`
          },
          {
            path: "tests/Checkout.test.ts",
            content: `import { CheckoutService } from "../src/services/Checkout";

describe("CheckoutService", () => {
  let service: CheckoutService;

  beforeEach(() => {
    service = new CheckoutService();
  });

  it("should place an order successfully", async () => {
    const orderId = await service.placeOrder("cust_999", [{ productId: "prod_1", quantity: 2 }]);
    expect(orderId).toBe("order-12345");
  });

  it("should throw error if customerId is missing", async () => {
    await expect(service.placeOrder("", [])).rejects.toThrow("Customer ID is required");
  });

  it("should record payment attempts total metric", async () => {
    await service.placeOrder("cust_999", [{ productId: "prod_1", quantity: 2 }]);
    const counters = service.metrics.payment_attempts_total.counters;
    const labelKey = JSON.stringify({ payment_method: "credit_card", status: "success" });
    expect(counters.get(labelKey)).toBe(1);
  });
});
`
          }
        ]
      });
    }

    // Case 1.5: UserService / stabilization test spec
    if (promptLower.includes("userservice") || promptLower.includes("registeruser")) {
      return JSON.stringify({
        files: [
          {
            path: "src/services/UserService.ts",
            content: `/**
 * UserService provides methods to register and manage user accounts
 */
export class UserService {
  private users = new Map<string, string>();

  /**
   * Register a new user with a given name
   */
  public async registerUser(name: string): Promise<string> {
    if (!name || name.trim() === "") {
      throw new Error("Name cannot be empty");
    }
    const id = "user-" + Math.random().toString(36).substring(2, 9);
    this.users.set(id, name);
    return id;
  }

  /**
   * Retrieve user name by their ID
   */
  public async getUserName(id: string): Promise<string> {
    const name = this.users.get(id);
    if (!name) {
      throw new Error("User not found");
    }
    return name;
  }

  /**
   * Update user profile details
   */
  public async updateUser(id: string, name: string): Promise<void> {
    if (!name || name.trim() === "") {
      throw new Error("Name cannot be empty");
    }
    if (!this.users.has(id)) {
      throw new Error("User not found");
    }
    this.users.set(id, name);
  }
}
`
          },
          {
            path: "tests/UserService.test.ts",
            content: `import { UserService } from "../src/services/UserService";

describe("UserService", () => {
  let service: UserService;

  beforeEach(() => {
    service = new UserService();
  });

  it("should register, retrieve, and update user successfully", async () => {
    const id = await service.registerUser("Alice");
    expect(id).toBeDefined();

    const name = await service.getUserName(id);
    expect(name).toBe("Alice");

    await service.updateUser(id, "Bob");
    const updatedName = await service.getUserName(id);
    expect(updatedName).toBe("Bob");
  });

  it("should fail to register user with empty name", async () => {
    await expect(service.registerUser("")).rejects.toThrow("Name cannot be empty");
  });

  it("should fail to update user with empty name", async () => {
    await expect(service.updateUser("user-123", "")).rejects.toThrow("Name cannot be empty");
  });
});
`
          }
        ]
      });
    }

    // Case 2: GreetingService / hello world spec
    if (promptLower.includes("greeting") || promptLower.includes("sayhello")) {
      return JSON.stringify({
        files: [
          {
            path: "src/services/GreetingService.ts",
            content: `export interface IGreetingService {
  sayHello(name: string): Promise<{ id: string; message: string; created_at: Date }>;
}

export class GreetingService implements IGreetingService {
  public async sayHello(name: string): Promise<{ id: string; message: string; created_at: Date }> {
    if (!name || name.trim() === "") {
      throw new Error("Name cannot be empty");
    }
    return {
      id: "greet-123",
      message: \`Hello, \${name}!\`,
      created_at: new Date()
    };
  }
}
`
          },
          {
            path: "tests/GreetingService.test.ts",
            content: `import { GreetingService } from "../src/services/GreetingService";

describe("GreetingService", () => {
  let service: GreetingService;

  beforeEach(() => {
    service = new GreetingService();
  });

  it("should return greeting message", async () => {
    const result = await service.sayHello("World");
    expect(result.message).toBe("Hello, World!");
    expect(result.id).toBe("greet-123");
  });

  it("should throw error on empty name", async () => {
    await expect(service.sayHello("")).rejects.toThrow("Name cannot be empty");
  });
});
`
          }
        ]
      });
    }

    // Default basic fallback mock — dynamic name
    const svcName = this.extractServiceName(rawPrompt);
    return JSON.stringify({
      files: [
        {
          path: `src/services/${svcName}.ts`,
          content: `export class ${svcName} {
  public async execute(input: any): Promise<any> {
    return { success: true };
  }
}
`
        },
        {
          path: `tests/${svcName}.test.ts`,
          content: `import { ${svcName} } from "../src/services/${svcName}";

describe("${svcName}", () => {
  it("should execute successfully", async () => {
    const service = new ${svcName}();
    const result = await service.execute({});
    expect(result.success).toBe(true);
  });
});
`
        }
      ]
    });
  }

  private getMockRustResponse(promptLower: string, rawPrompt: string): string {
    // Checkout service in Rust
    if (promptLower.includes("checkoutservice") || promptLower.includes("\"checkout\"")) {
      return JSON.stringify({
        files: [
          {
            path: "src/services/checkout.rs",
            content: `use thiserror::Error;

#[derive(Error, Debug)]
pub enum CheckoutError {
    #[error("Customer ID is required")]
    MissingCustomerId,
    #[error("Cart is empty")]
    EmptyCart,
}

pub struct CheckoutService;

impl CheckoutService {
    pub fn new() -> Self {
        Self
    }

    /// Place an order for a customer with the given items.
    pub fn place_order(&self, customer_id: &str, items: &[&str]) -> Result<String, CheckoutError> {
        // Precondition: customer_id must not be empty
        if customer_id.trim().is_empty() {
            return Err(CheckoutError::MissingCustomerId);
        }
        // Precondition: items must not be empty
        if items.is_empty() {
            return Err(CheckoutError::EmptyCart);
        }

        // Simulate order placement
        Ok("order-12345".to_string())
    }
}
`
          },
          {
            path: "tests/checkout_test.rs",
            content: `use omni_build::services::checkout::*;

#[test]
fn test_place_order_success() {
    let service = CheckoutService::new();
    let result = service.place_order("cust_999", &["prod_1"]);
    assert!(result.is_ok());
    assert_eq!(result.unwrap(), "order-12345");
}

#[test]
fn test_place_order_missing_customer_id() {
    let service = CheckoutService::new();
    let result = service.place_order("", &["prod_1"]);
    assert!(result.is_err());
}

#[test]
fn test_place_order_empty_cart() {
    let service = CheckoutService::new();
    let result = service.place_order("cust_999", &[]);
    assert!(result.is_err());
}
`
          }
        ]
      });
    }

    // Default fallback for Rust — dynamic name
    const svcName = this.extractServiceName(rawPrompt);
    const snakeName = this.toSnakeCase(svcName);
    return JSON.stringify({
      files: [
        {
          path: `src/services/${snakeName}.rs`,
          content: `pub struct ${svcName};\n\nimpl ${svcName} {\n    pub fn new() -> Self { Self }\n\n    pub fn execute(&self) -> Result<String, String> {\n        Ok("success".to_string())\n    }\n}\n`
        },
        {
          path: `tests/${snakeName}_test.rs`,
          content: `use omni_build::services::${snakeName}::*;\n\n#[test]\nfn test_${snakeName}_execute() {\n    let service = ${svcName}::new();\n    let result = service.execute();\n    assert!(result.is_ok());\n}\n`
        }
      ]
    });
  }

  private getMockPythonResponse(promptLower: string, rawPrompt: string): string {
    // Checkout service in Python
    if (promptLower.includes("checkoutservice") || promptLower.includes("\"checkout\"")) {
      return JSON.stringify({
        files: [
          {
            path: "app/services/checkout.py",
            content: `from dataclasses import dataclass
from typing import List


class CheckoutError(Exception):
    """Base error for checkout operations."""
    pass


class MissingCustomerIdError(CheckoutError):
    """Raised when customer ID is missing."""
    pass


class EmptyCartError(CheckoutError):
    """Raised when cart is empty."""
    pass


@dataclass
class OrderResult:
    order_id: str


class CheckoutService:
    def place_order(self, customer_id: str, items: List[str]) -> OrderResult:
        """Place an order for a customer with the given items."""
        # Precondition: customer_id must not be empty
        if not customer_id or not customer_id.strip():
            raise MissingCustomerIdError("Customer ID is required")
        # Precondition: items must not be empty
        if not items:
            raise EmptyCartError("Cart is empty")

        # Simulate order placement
        return OrderResult(order_id="order-12345")
`
          },
          {
            path: "tests/test_checkout.py",
            content: `import pytest
from app.services.checkout import CheckoutService, MissingCustomerIdError, EmptyCartError


class TestCheckoutService:
    def setup_method(self):
        self.service = CheckoutService()

    def test_place_order_success(self):
        result = self.service.place_order("cust_999", ["prod_1"])
        assert result.order_id == "order-12345"

    def test_place_order_missing_customer_id(self):
        with pytest.raises(MissingCustomerIdError):
            self.service.place_order("", ["prod_1"])

    def test_place_order_empty_cart(self):
        with pytest.raises(EmptyCartError):
            self.service.place_order("cust_999", [])
`
          }
        ]
      });
    }

    // Default fallback for Python — dynamic name
    const svcName = this.extractServiceName(rawPrompt);
    const snakeName = this.toSnakeCase(svcName);
    return JSON.stringify({
      files: [
        {
          path: `app/services/${snakeName}.py`,
          content: `class ${svcName}:\n    def execute(self, **kwargs):\n        return {"success": True}\n`
        },
        {
          path: `tests/test_${snakeName}.py`,
          content: `from app.services.${snakeName} import ${svcName}\n\n\ndef test_${snakeName}_execute():\n    service = ${svcName}()\n    result = service.execute()\n    assert result["success"] is True\n`
        }
      ]
    });
  }
}
