import Anthropic from "@anthropic-ai/sdk";
import pc from "picocolors";

export interface LLMProvider {
  generateCode(systemPrompt: string, userPrompt: string): Promise<string>;
}

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

  public async generateCode(systemPrompt: string, userPrompt: string): Promise<string> {
    if (this.isMock) {
      console.log(pc.blue("   [MOCK LLM] Simulating Claude 3.5 Sonnet response..."));
      return this.getMockResponse(userPrompt);
    }

    if (!this.client) {
      throw new Error("Anthropic client is not initialized.");
    }

    const response = await this.client.messages.create({
      model: "claude-3-5-sonnet-20241022",
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

  private getMockResponse(userPrompt: string): string {
    const promptLower = userPrompt.toLowerCase();

    // Case 1: Checkout service
    if (promptLower.includes("checkout")) {
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

    // Default basic fallback mock
    return JSON.stringify({
      files: [
        {
          path: "src/services/Service.ts",
          content: `export class DefaultService {}`
        },
        {
          path: "tests/Service.test.ts",
          content: `describe("Service", () => { it("passes", () => {}) });`
        }
      ]
    });
  }
}
