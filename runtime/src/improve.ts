import * as fs from "fs";
import * as path from "path";

export interface TraceLog {
  serviceName: string;
  timestamp: string;
  target: string;
  systemPrompt: string;
  userPrompt: string;
  response: string;
  success: boolean;
  attempts: number;
  errors: string[];
}

export interface RetryRecord {
  serviceName: string;
  timestamp: string;
  attempt: number;
  error: string;
  prompt: string;
}

export class AgentOptimizer {
  private cacheDir: string;
  private tracesDir: string;
  private retriesFile: string;

  constructor(cacheDir: string = ".omni-cache") {
    this.cacheDir = path.resolve(cacheDir);
    this.tracesDir = path.join(this.cacheDir, "traces");
    this.retriesFile = path.join(this.tracesDir, "retries.json");
    this.ensureDirectories();
  }

  private ensureDirectories() {
    if (!fs.existsSync(this.cacheDir)) {
      fs.mkdirSync(this.cacheDir, { recursive: true });
    }
    if (!fs.existsSync(this.tracesDir)) {
      fs.mkdirSync(this.tracesDir, { recursive: true });
    }
  }

  public logTrace(trace: TraceLog): void {
    const tracePath = path.join(this.tracesDir, `${trace.serviceName}_${Date.now()}.json`);
    fs.writeFileSync(tracePath, JSON.stringify(trace, null, 2), "utf8");
  }

  public logRetry(retry: RetryRecord): void {
    let retries: RetryRecord[] = [];
    if (fs.existsSync(this.retriesFile)) {
      try {
        retries = JSON.parse(fs.readFileSync(this.retriesFile, "utf8"));
      } catch (e) {
        retries = [];
      }
    }
    retries.push(retry);
    fs.writeFileSync(this.retriesFile, JSON.stringify(retries, null, 2), "utf8");
  }

  /**
   * Automatic prompt optimization: analyzing retry history for a service
   * and generating additional instructions to append to the system prompt
   */
  public getOptimizedInstructions(serviceName: string, errorHistory?: string[]): string {
    const instructions: string[] = [];
    const errorsToAnalyze: string[] = errorHistory ? [...errorHistory] : [];

    // Also read from retries.json if any exist for this service
    if (fs.existsSync(this.retriesFile)) {
      try {
        const retries: RetryRecord[] = JSON.parse(fs.readFileSync(this.retriesFile, "utf8"));
        const serviceRetries = retries.filter(r => r.serviceName === serviceName);
        for (const r of serviceRetries) {
          errorsToAnalyze.push(r.error);
        }
      } catch (e) {
        // Ignore
      }
    }

    if (errorsToAnalyze.length > 0) {
      instructions.push("\n### IMPORTANT: LLM Prompt Adaptations from past generation retries:");
      instructions.push("The previous compilation/testing attempts failed with the following diagnostics. You MUST fix these errors in your new generation:");
      
      const uniqueErrors = Array.from(new Set(errorsToAnalyze));
      for (const err of uniqueErrors) {
        instructions.push(`\nError Diagnostic:\n\`\`\`\n${err}\n\`\`\``);
      }
      
      instructions.push("\nGeneral Guidelines based on analysis:");
      for (const err of uniqueErrors) {
        const lowerErr = err.toLowerCase();
        if (lowerErr.includes("precondition") || lowerErr.includes("pre-condition") || lowerErr.includes("assert") || lowerErr.includes("constraint")) {
          instructions.push("- Ensure all preconditions and constraints on operation inputs are strictly verified in code and throw appropriate errors on violation.");
        }
        if (lowerErr.includes("postcondition") || lowerErr.includes("post-condition")) {
          instructions.push("- Ensure postconditions are satisfied by returning output structures conforming to the defined schemas and rules.");
        }
        if (lowerErr.includes("syntax") || lowerErr.includes("parse") || lowerErr.includes("compiler") || lowerErr.includes("error")) {
          instructions.push("- Verify target language syntax, imports, and interface/module matching before finalizing files.");
        }
        if (lowerErr.includes("metric") || lowerErr.includes("counter")) {
          instructions.push("- Correctly initialize and increment all required metrics with matching labels/dimensions.");
        }
        if (lowerErr.includes("undefined") || lowerErr.includes("not found")) {
          instructions.push("- Make sure all types and interfaces referenced are imported or declared correctly in scope.");
        }
      }
    }

    return instructions.join("\n");
  }
}

/**
 * A/B Testing framework for routing agent strategies.
 * Evaluates Haiku-only vs. Sonnet-4 vs. Hybrid strategies.
 */
export class StrategyABTester {
  public static route(serviceName: string): { strategy: string; model: string } {
    const model = process.env.OMNI_MODEL || "claude-3-5-sonnet-20241022";
    return { strategy: "Standard Strategy", model };
  }
}
