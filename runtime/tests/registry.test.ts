import { AgentRegistry, AgentRegistration, DEFAULT_AGENTS } from "../src/agents/registry";

describe("AgentRegistry", () => {
  let registry: AgentRegistry;

  const testAgent1: AgentRegistration = {
    id: "cheap-ts-agent",
    name: "Cheap TS Agent",
    provider: "test",
    capabilities: {
      languages: ["typescript"],
      taskTypes: ["codegen"],
      quality: 4,
      costPer1kTokens: 0.0005,
      avgLatencyMs: 500,
      model: "cheap-model-1",
    },
    active: true,
  };

  const testAgent2: AgentRegistration = {
    id: "premium-ts-agent",
    name: "Premium TS Agent",
    provider: "test",
    capabilities: {
      languages: ["typescript", "rust"],
      taskTypes: ["codegen", "refactor"],
      quality: 9,
      costPer1kTokens: 0.005,
      avgLatencyMs: 2500,
      model: "premium-model-1",
    },
    active: true,
  };

  const inactiveAgent: AgentRegistration = {
    id: "inactive-agent",
    name: "Inactive Agent",
    provider: "test",
    capabilities: {
      languages: ["typescript"],
      taskTypes: ["codegen"],
      quality: 8,
      costPer1kTokens: 0.002,
      avgLatencyMs: 1500,
      model: "inactive-model-1",
    },
    active: false,
  };

  beforeEach(() => {
    registry = new AgentRegistry();
  });

  test("should register, unregister and retrieve agents", () => {
    registry.register(testAgent1);
    expect(registry.get("cheap-ts-agent")).toEqual(testAgent1);
    expect(registry.list()).toHaveLength(1);

    registry.register(testAgent2);
    expect(registry.list()).toHaveLength(2);

    registry.unregister("cheap-ts-agent");
    expect(registry.get("cheap-ts-agent")).toBeUndefined();
    expect(registry.list()).toHaveLength(1);
    expect(registry.list()[0].id).toBe("premium-ts-agent");
  });

  test("should list active agents only in listActive", () => {
    registry.register(testAgent1);
    registry.register(inactiveAgent);

    expect(registry.list()).toHaveLength(2);
    expect(registry.listActive()).toHaveLength(1);
    expect(registry.listActive()[0].id).toBe("cheap-ts-agent");
  });

  test("should return null in findBest if no active agent supports requested language or task type", () => {
    registry.register(testAgent1); // only supports typescript and codegen

    // Language not supported
    let best = registry.findBest({
      taskType: "codegen",
      language: "rust",
      budgetTier: "cheap",
    });
    expect(best).toBeNull();

    // Task type not supported
    best = registry.findBest({
      taskType: "refactor",
      language: "typescript",
      budgetTier: "cheap",
    });
    expect(best).toBeNull();
  });

  test("should return null if agent does not meet minQuality requirement", () => {
    registry.register(testAgent1); // quality 4

    const best = registry.findBest({
      taskType: "codegen",
      language: "typescript",
      budgetTier: "cheap",
      minQuality: 6,
    });
    expect(best).toBeNull();
  });

  test("should sort by cost when budgetTier is cheap", () => {
    registry.register(testAgent1); // cost 0.0005, quality 4
    registry.register(testAgent2); // cost 0.005, quality 9

    const best = registry.findBest({
      taskType: "codegen",
      language: "typescript",
      budgetTier: "cheap",
    });
    expect(best?.id).toBe("cheap-ts-agent");
  });

  test("should sort by quality when budgetTier is premium", () => {
    registry.register(testAgent1); // cost 0.0005, quality 4
    registry.register(testAgent2); // cost 0.005, quality 9

    const best = registry.findBest({
      taskType: "codegen",
      language: "typescript",
      budgetTier: "premium",
    });
    expect(best?.id).toBe("premium-ts-agent");
  });

  test("should sort by quality/cost ratio when budgetTier is balanced", () => {
    // Agent A ratio: 5 / 0.01 = 500
    const agentA: AgentRegistration = {
      id: "agent-a",
      name: "Agent A",
      provider: "test",
      capabilities: {
        languages: ["typescript"],
        taskTypes: ["codegen"],
        quality: 5,
        costPer1kTokens: 0.01,
        avgLatencyMs: 1000,
        model: "model-a",
      },
      active: true,
    };

    // Agent B ratio: 8 / 0.04 = 200
    const agentB: AgentRegistration = {
      id: "agent-b",
      name: "Agent B",
      provider: "test",
      capabilities: {
        languages: ["typescript"],
        taskTypes: ["codegen"],
        quality: 8,
        costPer1kTokens: 0.04,
        avgLatencyMs: 1000,
        model: "model-b",
      },
      active: true,
    };

    registry.register(agentA);
    registry.register(agentB);

    const best = registry.findBest({
      taskType: "codegen",
      language: "typescript",
      budgetTier: "balanced",
    });
    expect(best?.id).toBe("agent-a"); // higher ratio
  });

  test("should load default agents successfully", () => {
    expect(DEFAULT_AGENTS.length).toBeGreaterThan(0);
    const registryWithDefaults = new AgentRegistry();
    for (const agent of DEFAULT_AGENTS) {
      registryWithDefaults.register(agent);
    }
    const best = registryWithDefaults.findBest({
      taskType: "codegen",
      language: "typescript",
      budgetTier: "balanced",
    });
    expect(best).not.toBeNull();
    expect(["claude-sonnet", "claude-haiku", "claude-opus"]).toContain(best?.id);
  });
});
