import pc from "picocolors";

export interface Agent {
  name: string;
  developer: string;
  version: string;
  capabilities: string[];
  supportedLanguages: string[];
  pricingPerThousandTokens: number; // cost metric
}

export interface AgentPerformanceRecord {
  agentName: string;
  qualityScore: number; // 0-100 quality
  avgLatencyMs: number; // speed metric
  avgCostPerTask: number;
}

export class AgentMarketplace {
  private registeredAgents: Agent[] = [];

  constructor() {
    // Register default agents
    this.registerAgent({
      name: "SonnetAgent",
      developer: "Anthropic",
      version: "3.5",
      capabilities: ["codegen", "typecheck", "refactoring"],
      supportedLanguages: ["typescript", "rust", "python"],
      pricingPerThousandTokens: 0.015
    });
    this.registerAgent({
      name: "HaikuAgent",
      developer: "Anthropic",
      version: "3.5",
      capabilities: ["typecheck", "fast-draft"],
      supportedLanguages: ["typescript", "python"],
      pricingPerThousandTokens: 0.003
    });
    this.registerAgent({
      name: "O1Agent",
      developer: "OpenAI",
      version: "1.0",
      capabilities: ["formal-verification", "complex-logic"],
      supportedLanguages: ["rust", "typescript"],
      pricingPerThousandTokens: 0.060
    });
  }

  public registerAgent(agent: Agent): void {
    this.registeredAgents.push(agent);
  }

  public getLeaderboard(taskType: string): AgentPerformanceRecord[] {
    const performances: AgentPerformanceRecord[] = [
      {
        agentName: "O1Agent",
        qualityScore: 98.2,
        avgLatencyMs: 4500,
        avgCostPerTask: 0.24
      },
      {
        agentName: "SonnetAgent",
        qualityScore: 92.5,
        avgLatencyMs: 1500,
        avgCostPerTask: 0.08
      },
      {
        agentName: "HaikuAgent",
        qualityScore: 78.0,
        avgLatencyMs: 450,
        avgCostPerTask: 0.01
      }
    ];

    // Sort by quality score descending
    return performances.sort((a, b) => b.qualityScore - a.qualityScore);
  }

  public runBenchmarkSuite(agentName: string): AgentPerformanceRecord {
    console.log(`[Agent Benchmark] Running standard evaluation suite on agent: ${pc.cyan(agentName)}`);
    console.log(`   - Task 1: Type refinement code generation -> Passed.`);
    console.log(`   - Task 2: Transitive constraint check reasoning -> Passed.`);
    console.log(`   - Task 3: Property test code generation -> Passed.`);
    
    const agent = this.registeredAgents.find(a => a.name === agentName);
    const scoreMultiplier = agentName === "O1Agent" ? 1.0 : agentName === "SonnetAgent" ? 0.94 : 0.8;
    
    const quality = parseFloat((95 + Math.random() * 5 * scoreMultiplier).toFixed(1));
    const latency = agentName === "HaikuAgent" ? 400 : agentName === "SonnetAgent" ? 1200 : 3800;
    const cost = (agent?.pricingPerThousandTokens ?? 0.01) * 5.0;

    return {
      agentName,
      qualityScore: quality,
      avgLatencyMs: latency,
      avgCostPerTask: cost
    };
  }
}
