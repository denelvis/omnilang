import { ParallelExecutor, BuildTask, ParallelConfig, ProgressEvent, buildTasksFromIR } from "../src/agents/parallel";
import { AgentRegistry, AgentRegistration } from "../src/agents/registry";
import * as path from "path";
import * as fs from "fs";
import { CodeGenAgent } from "../src/agents/codegen";

jest.mock("fs", () => {
  const original = jest.requireActual("fs");
  return {
    ...original,
    existsSync: jest.fn().mockReturnValue(true),
    mkdirSync: jest.fn(),
    writeFileSync: jest.fn(),
    readFileSync: jest.fn(),
    appendFileSync: jest.fn(),
  };
});

jest.mock("../src/prompts/codegen", () => ({
  getSystemPrompt: jest.fn().mockReturnValue("system prompt"),
  getUserPrompt: jest.fn().mockImplementation((serviceName) => `serviceName: ${serviceName}`),
}));

describe("ParallelExecutor", () => {
  let registry: AgentRegistry;
  let config: ParallelConfig;

  const testAgent: AgentRegistration = {
    id: "test-agent",
    name: "Test Agent",
    provider: "test",
    capabilities: {
      languages: ["typescript"],
      taskTypes: ["codegen"],
      quality: 5,
      costPer1kTokens: 0.001,
      avgLatencyMs: 100,
      model: "test-model",
    },
    active: true,
  };

  beforeEach(() => {
    registry = new AgentRegistry();
    registry.register(testAgent);

    config = {
      maxConcurrency: 2,
      rateLimitPerMinute: 60,
      maxRetries: 1,
      escalateOnRetry: false,
      budgetTier: "cheap",
    };
  });

  test("should execute independent tasks concurrently", async () => {
    const executor = new ParallelExecutor(registry, config);

    const tasks: BuildTask[] = [
      { id: "task-1", serviceName: "Service1", taskType: "codegen", language: "typescript", dependsOn: [], specData: {} },
      { id: "task-2", serviceName: "Service2", taskType: "codegen", language: "typescript", dependsOn: [], specData: {} },
    ];

    const executionOrder: string[] = [];
    const mockTaskExecutor = jest.fn().mockImplementation(async (task) => {
      executionOrder.push(task.id);
      return { success: true, files: [`${task.id}.ts`], tokensUsed: 100 };
    });

    const results = await executor.execute(tasks, mockTaskExecutor);

    expect(results).toHaveLength(2);
    expect(results.find((r) => r.taskId === "task-1")?.success).toBe(true);
    expect(results.find((r) => r.taskId === "task-2")?.success).toBe(true);
    expect(mockTaskExecutor).toHaveBeenCalledTimes(2);
  });

  test("should respect task dependency ordering", async () => {
    const executor = new ParallelExecutor(registry, config);

    const tasks: BuildTask[] = [
      { id: "task-child", serviceName: "ChildService", taskType: "codegen", language: "typescript", dependsOn: ["task-parent"], specData: {} },
      { id: "task-parent", serviceName: "ParentService", taskType: "codegen", language: "typescript", dependsOn: [], specData: {} },
    ];

    const executionOrder: string[] = [];
    const mockTaskExecutor = jest.fn().mockImplementation(async (task) => {
      executionOrder.push(task.id);
      return { success: true, files: [`${task.id}.ts`], tokensUsed: 100 };
    });

    const results = await executor.execute(tasks, mockTaskExecutor);

    expect(results).toHaveLength(2);
    // Parent must execute before child
    expect(executionOrder).toEqual(["task-parent", "task-child"]);
  });

  test("should emit progress events during execution", async () => {
    const executor = new ParallelExecutor(registry, config);
    const events: ProgressEvent[] = [];
    executor.onProgress((e) => events.push(e));

    const tasks: BuildTask[] = [
      { id: "task-1", serviceName: "Service1", taskType: "codegen", language: "typescript", dependsOn: [], specData: {} },
    ];

    const mockTaskExecutor = async (task: BuildTask) => ({ success: true, files: [], tokensUsed: 50 });

    await executor.execute(tasks, mockTaskExecutor);

    expect(events.map((e) => e.type)).toEqual(["start", "complete"]);
    expect(events[0].taskId).toBe("task-1");
    expect(events[1].taskId).toBe("task-1");
  });

  test("should retry on failure and escalate model tier if configured", async () => {
    // Add agents for escalation tiers
    const cheapAgent = {
      ...testAgent,
      id: "cheap-agent",
      capabilities: { ...testAgent.capabilities, quality: 2, costPer1kTokens: 0.0005 }
    };
    const balancedAgent = {
      ...testAgent,
      id: "balanced-agent",
      capabilities: { ...testAgent.capabilities, quality: 7, costPer1kTokens: 0.001 }
    };
    const premiumAgent = {
      ...testAgent,
      id: "premium-agent",
      capabilities: { ...testAgent.capabilities, quality: 9, costPer1kTokens: 0.005 }
    };
    
    registry.unregister("test-agent");
    registry.register(cheapAgent);
    registry.register(balancedAgent);
    registry.register(premiumAgent);

    config.maxRetries = 2;
    config.escalateOnRetry = true;
    config.budgetTier = "cheap";

    const executor = new ParallelExecutor(registry, config);
    const events: ProgressEvent[] = [];
    executor.onProgress((e) => events.push(e));

    const tasks: BuildTask[] = [
      { id: "task-fail", serviceName: "FailService", taskType: "codegen", language: "typescript", dependsOn: [], specData: {} },
    ];

    let attempts = 0;
    const mockTaskExecutor = jest.fn().mockImplementation(async () => {
      attempts++;
      if (attempts < 3) {
        throw new Error("Temporary network glitch");
      }
      return { success: true, files: ["success.ts"], tokensUsed: 200 };
    });

    const results = await executor.execute(tasks, mockTaskExecutor);

    expect(results[0].success).toBe(true);
    expect(results[0].retryCount).toBe(2);
    expect(mockTaskExecutor).toHaveBeenCalledTimes(3);

    // Event sequence: start -> retry -> retry -> complete
    expect(events.map((e) => e.type)).toEqual(["start", "retry", "retry", "complete"]);
    // Escalations: 
    // Attempt 0: cheap tier -> cheap-agent (cost 0.0005)
    // Attempt 1: balanced tier -> balanced-agent (ratio: 7/0.001=7000 vs cheap ratio 4000)
    // Attempt 2: premium tier -> premium-agent (quality: 9 vs balanced quality 7)
    expect(events[0].agentId).toBe("cheap-agent");
    expect(events[1].agentId).toBe("balanced-agent");
    expect(events[2].agentId).toBe("premium-agent");
  });

  test("should handle task failure when retries are exhausted", async () => {
    config.maxRetries = 1;
    const executor = new ParallelExecutor(registry, config);
    const events: ProgressEvent[] = [];
    executor.onProgress((e) => events.push(e));

    const tasks: BuildTask[] = [
      { id: "task-fail-hard", serviceName: "FailHardService", taskType: "codegen", language: "typescript", dependsOn: [], specData: {} },
    ];

    const mockTaskExecutor = jest.fn().mockImplementation(async () => {
      return { success: false, files: [], tokensUsed: 0 };
    });

    const results = await executor.execute(tasks, mockTaskExecutor);

    expect(results[0].success).toBe(false);
    expect(results[0].retryCount).toBe(2);
    expect(events.map((e) => e.type)).toEqual(["start", "retry", "fail"]);
  });

  test("should handle rate limiting sliding window delay", async () => {
    config.rateLimitPerMinute = 2; // Max 2 tasks per minute
    const executor = new ParallelExecutor(registry, config);

    const tasks: BuildTask[] = [
      { id: "t1", serviceName: "S1", taskType: "codegen", language: "typescript", dependsOn: [], specData: {} },
      { id: "t2", serviceName: "S2", taskType: "codegen", language: "typescript", dependsOn: [], specData: {} },
      { id: "t3", serviceName: "S3", taskType: "codegen", language: "typescript", dependsOn: [], specData: {} },
    ];

    const mockTaskExecutor = jest.fn().mockResolvedValue({ success: true, files: [], tokensUsed: 10 });

    // Mock Date.now to control time manually
    let fakeTime = 100000;
    const originalDateNow = Date.now;
    global.Date.now = jest.fn(() => fakeTime);

    // Mock global.setTimeout to execute immediately and advance fakeTime
    const spySetTimeout = jest.spyOn(global, "setTimeout").mockImplementation((cb: any, ms: any) => {
      fakeTime += ms; // Fast-forward fake time by the wait duration
      cb();
      return {} as any;
    });

    const results = await executor.execute(tasks, mockTaskExecutor);
    expect(results).toHaveLength(3);
    expect(mockTaskExecutor).toHaveBeenCalledTimes(3);

    // Restore Date.now and setTimeout
    global.Date.now = originalDateNow;
    spySetTimeout.mockRestore();
  });

  test("E2E: should execute dependency-aware code generation using a real SpecIR structure", async () => {
    // 1. Construct a realistic SpecIR
    const mockIr: any = {
      module_path: ["acme", "shop"],
      source_file: {
        module: { path: ["acme", "shop"], span: { start: 0, end: 0 } },
        imports: [],
        exports: [],
        declarations: [
          {
            Service: {
              name: "AuthService",
              depends_on: [],
            },
          },
          {
            Service: {
              name: "UserService",
              depends_on: ["AuthService"],
            },
          },
          {
            Service: {
              name: "OrderService",
              depends_on: ["UserService"],
            },
          },
        ],
      },
      services: [
        { name: "AuthService" },
        { name: "UserService" },
        { name: "OrderService" },
      ],
      build_order: ["AuthService", "UserService", "OrderService"],
      types: [],
      type_mappings: [],
      stats: {
        type_count: 0,
        service_count: 3,
        rpc_count: 0,
        test_count: 0,
        constraint_count: 0,
        metric_count: 0,
        component_count: 0,
        pipeline_count: 0,
        workflow_count: 0,
        agent_count: 0,
        schema_count: 0,
        policy_count: 0,
      },
    };

    // 2. Build tasks
    const tasks = buildTasksFromIR(mockIr, "typescript");
    expect(tasks).toHaveLength(3);

    // 3. Setup parallel executor
    const executor = new ParallelExecutor(registry, config);

    // 4. Mock the LLM provider and CodeGenAgent
    const mockProvider = {
      generateCode: jest.fn().mockImplementation(async (sys: string, user: string) => {
        if (user.includes("AuthService")) {
          return JSON.stringify({
            files: [{ path: "src/services/AuthService.ts", content: "auth" }]
          });
        }
        if (user.includes("UserService")) {
          return JSON.stringify({
            files: [{ path: "src/services/UserService.ts", content: "user" }]
          });
        }
        if (user.includes("OrderService")) {
          return JSON.stringify({
            files: [{ path: "src/services/OrderService.ts", content: "order" }]
          });
        }
        return JSON.stringify({ files: [] });
      }),
    };
    const codeGenAgent = new CodeGenAgent(mockProvider);

    // 5. Track execution order
    const executionOrder: string[] = [];
    const writtenFiles: string[] = [];

    const taskExecutor = async (task: BuildTask, agent: AgentRegistration) => {
      executionOrder.push(task.serviceName);
      // Simulate CodeGenAgent behavior
      const result = await codeGenAgent.generateService(
        task.serviceName,
        mockIr,
        "mock-output",
        "typescript"
      );
      if (result.success) {
        writtenFiles.push(...result.files);
      }
      return { success: result.success, files: result.files, tokensUsed: 100 };
    };

    // 6. Execute
    const results = await executor.execute(tasks, taskExecutor);

    // 7. Assertions
    expect(results).toHaveLength(3);
    expect(results.every(r => r.success)).toBe(true);
    // Order must respect: AuthService -> UserService -> OrderService
    expect(executionOrder).toEqual(["AuthService", "UserService", "OrderService"]);
    expect(writtenFiles).toContain(path.join("mock-output", "src/services/AuthService.ts"));
    expect(writtenFiles).toContain(path.join("mock-output", "src/services/UserService.ts"));
    expect(writtenFiles).toContain(path.join("mock-output", "src/services/OrderService.ts"));
  });
});

describe("buildTasksFromIR", () => {
  test("should construct build tasks and dependencies from IR", () => {
    const mockIr = {
      services: [
        { name: "UserService" },
        { name: "OrderService" },
      ],
      source_file: {
        declarations: [
          {
            Service: {
              name: "UserService",
              depends_on: [],
            },
          },
          {
            Service: {
              name: "OrderService",
              depends_on: ["UserService"],
            },
          },
        ],
      },
    };

    const tasks = buildTasksFromIR(mockIr, "typescript");

    expect(tasks).toHaveLength(2);
    
    const userTask = tasks.find((t) => t.serviceName === "UserService");
    const orderTask = tasks.find((t) => t.serviceName === "OrderService");

    expect(userTask).toBeDefined();
    expect(userTask?.id).toBe("codegen-UserService");
    expect(userTask?.dependsOn).toEqual([]);

    expect(orderTask).toBeDefined();
    expect(orderTask?.id).toBe("codegen-OrderService");
    expect(orderTask?.dependsOn).toEqual(["codegen-UserService"]);
  });
});
