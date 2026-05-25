/**
 * Agent Registry — multi-agent support for OmniLang.
 *
 * Provides registration, capability matching, and routing of tasks
 * to the best available agent.
 */

// ── Agent capability types ───────────────────────────────
export interface AgentCapability {
  /** Language this agent can generate code for */
  languages: string[];
  /** Types of tasks this agent can handle */
  taskTypes: ("codegen" | "test" | "review" | "refactor" | "document")[];
  /** Quality tier: higher is better (1-10) */
  quality: number;
  /** Cost per 1K tokens (dollars) */
  costPer1kTokens: number;
  /** Average latency in ms */
  avgLatencyMs: number;
  /** Model identifier */
  model: string;
}

export interface AgentRegistration {
  id: string;
  name: string;
  provider: string;
  capabilities: AgentCapability;
  /** Whether agent is available for tasks */
  active: boolean;
}

export interface TaskRequirement {
  taskType: "codegen" | "test" | "review" | "refactor" | "document";
  language: string;
  /** Budget tier preference */
  budgetTier: "cheap" | "balanced" | "premium";
  /** Minimum quality threshold (1-10) */
  minQuality?: number;
}

// ── Agent Registry ───────────────────────────────────────
export class AgentRegistry {
  private agents: Map<string, AgentRegistration> = new Map();

  /** Register a new agent */
  register(agent: AgentRegistration): void {
    this.agents.set(agent.id, agent);
  }

  /** Unregister an agent */
  unregister(id: string): void {
    this.agents.delete(id);
  }

  /** Get all registered agents */
  list(): AgentRegistration[] {
    return Array.from(this.agents.values());
  }

  /** Get active agents */
  listActive(): AgentRegistration[] {
    return this.list().filter((a) => a.active);
  }

  /** Find the best agent for a task based on requirements */
  findBest(req: TaskRequirement): AgentRegistration | null {
    const candidates = this.listActive().filter((agent) => {
      const cap = agent.capabilities;

      // Must support the required language
      if (!cap.languages.includes(req.language)) return false;

      // Must support the task type
      if (!cap.taskTypes.includes(req.taskType)) return false;

      // Must meet minimum quality
      if (req.minQuality && cap.quality < req.minQuality) return false;

      return true;
    });

    if (candidates.length === 0) return null;

    // Sort by budget tier preference
    return candidates.sort((a, b) => {
      const aCap = a.capabilities;
      const bCap = b.capabilities;

      switch (req.budgetTier) {
        case "cheap":
          return aCap.costPer1kTokens - bCap.costPer1kTokens;
        case "premium":
          return bCap.quality - aCap.quality;
        case "balanced":
        default:
          // Score: quality / cost ratio
          const aScore = aCap.quality / (aCap.costPer1kTokens || 0.01);
          const bScore = bCap.quality / (bCap.costPer1kTokens || 0.01);
          return bScore - aScore;
      }
    })[0];
  }

  /** Find agent by ID */
  get(id: string): AgentRegistration | undefined {
    return this.agents.get(id);
  }
}

// ── Default agent configurations ─────────────────────────
export const DEFAULT_AGENTS: AgentRegistration[] = [
  {
    id: "claude-sonnet",
    name: "Claude 4 Sonnet",
    provider: "anthropic",
    capabilities: {
      languages: ["typescript", "rust", "python", "go"],
      taskTypes: ["codegen", "test", "review", "refactor", "document"],
      quality: 9,
      costPer1kTokens: 0.003,
      avgLatencyMs: 2000,
      model: "claude-sonnet-4-20250514",
    },
    active: true,
  },
  {
    id: "claude-haiku",
    name: "Claude 3.5 Haiku",
    provider: "anthropic",
    capabilities: {
      languages: ["typescript", "rust", "python", "go"],
      taskTypes: ["codegen", "test", "document"],
      quality: 6,
      costPer1kTokens: 0.001,
      avgLatencyMs: 800,
      model: "claude-3-5-haiku-20241022",
    },
    active: true,
  },
  {
    id: "claude-opus",
    name: "Claude 4 Opus",
    provider: "anthropic",
    capabilities: {
      languages: ["typescript", "rust", "python", "go"],
      taskTypes: ["codegen", "test", "review", "refactor", "document"],
      quality: 10,
      costPer1kTokens: 0.015,
      avgLatencyMs: 5000,
      model: "claude-opus-4-20250514",
    },
    active: true,
  },
];
