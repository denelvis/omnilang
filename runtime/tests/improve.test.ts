import * as fs from "fs";
import * as path from "path";
import { StrategyABTester, AgentOptimizer, TraceLog, RetryRecord } from "../src/improve";

describe("StrategyABTester", () => {
  const originalEnv = process.env;

  beforeEach(() => {
    jest.resetModules();
    process.env = { ...originalEnv };
  });

  afterAll(() => {
    process.env = originalEnv;
  });

  test("should route to default model when OMNI_MODEL is not set", () => {
    delete process.env.OMNI_MODEL;
    const result = StrategyABTester.route("UserService");
    expect(result.strategy).toBe("Standard Strategy");
    expect(result.model).toBe("claude-3-5-sonnet-20241022");
  });

  test("should route to model set in OMNI_MODEL environment variable", () => {
    process.env.OMNI_MODEL = "qwen2.5-coder:7b";
    const result = StrategyABTester.route("UserService");
    expect(result.strategy).toBe("Standard Strategy");
    expect(result.model).toBe("qwen2.5-coder:7b");
  });
});

describe("AgentOptimizer", () => {
  const testCacheDir = path.resolve(".test-omni-cache");

  const cleanup = () => {
    if (fs.existsSync(testCacheDir)) {
      fs.rmSync(testCacheDir, { recursive: true, force: true });
    }
  };

  beforeEach(() => {
    cleanup();
  });

  afterEach(() => {
    cleanup();
  });

  test("should initialize directories on creation", () => {
    const optimizer = new AgentOptimizer(testCacheDir);
    expect(fs.existsSync(testCacheDir)).toBe(true);
    expect(fs.existsSync(path.join(testCacheDir, "traces"))).toBe(true);
  });

  test("should write log traces correctly", () => {
    const optimizer = new AgentOptimizer(testCacheDir);
    const trace: TraceLog = {
      serviceName: "UserService",
      timestamp: new Date().toISOString(),
      target: "typescript",
      systemPrompt: "System Prompt",
      userPrompt: "User Prompt",
      response: "Response",
      success: true,
      attempts: 1,
      errors: [],
    };

    optimizer.logTrace(trace);

    const tracesDir = path.join(testCacheDir, "traces");
    const files = fs.readdirSync(tracesDir);
    const traceFile = files.find(f => f.startsWith("UserService_") && f.endsWith(".json"));
    expect(traceFile).toBeDefined();

    const traceData = JSON.parse(fs.readFileSync(path.join(tracesDir, traceFile!), "utf8"));
    expect(traceData.serviceName).toBe("UserService");
    expect(traceData.success).toBe(true);
  });

  test("should log retry records and use them in optimized instructions", () => {
    const optimizer = new AgentOptimizer(testCacheDir);
    const retry1: RetryRecord = {
      serviceName: "PaymentService",
      timestamp: new Date().toISOString(),
      attempt: 1,
      error: "Precondition failed: value must be positive",
      prompt: "Original Prompt",
    };
    const retry2: RetryRecord = {
      serviceName: "PaymentService",
      timestamp: new Date().toISOString(),
      attempt: 2,
      error: "Undefined variable: apiKey",
      prompt: "Original Prompt",
    };

    optimizer.logRetry(retry1);
    optimizer.logRetry(retry2);

    const instructions = optimizer.getOptimizedInstructions("PaymentService");
    expect(instructions).toContain("LLM Prompt Adaptations from past generation retries");
    expect(instructions).toContain("Precondition failed: value must be positive");
    expect(instructions).toContain("Undefined variable: apiKey");
    expect(instructions).toContain("Ensure all preconditions and constraints");
    expect(instructions).toContain("Make sure all types and interfaces referenced are imported");
  });

  test("should generate guidelines for various error messages", () => {
    const optimizer = new AgentOptimizer(testCacheDir);

    // Test preconditions and constraints
    let inst = optimizer.getOptimizedInstructions("Test", ["pre-condition failed"]);
    expect(inst).toContain("Ensure all preconditions and constraints");

    // Test postconditions
    inst = optimizer.getOptimizedInstructions("Test", ["post-condition failed"]);
    expect(inst).toContain("Ensure postconditions are satisfied");

    // Test syntax / compiler errors
    inst = optimizer.getOptimizedInstructions("Test", ["compiler error or syntax error"]);
    expect(inst).toContain("Verify target language syntax");

    // Test metric errors
    inst = optimizer.getOptimizedInstructions("Test", ["metric or counter error"]);
    expect(inst).toContain("Correctly initialize and increment all required metrics");
  });
});
