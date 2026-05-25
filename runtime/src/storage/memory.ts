/**
 * Agentic Memory — reasoning trace logger for LLM interactions.
 *
 * Captures the full chain of reasoning: prompts, responses, edits,
 * and verification results for transparency and debugging.
 */

import * as fs from "fs";
import * as path from "path";

export interface MemoryEntry {
  timestamp: number;
  type: "prompt" | "response" | "edit" | "verify" | "error" | "decision";
  agent: string;
  service: string;
  content: string;
  metadata?: Record<string, any>;
}

export interface ReasoningTrace {
  buildId: string;
  startTime: number;
  endTime?: number;
  entries: MemoryEntry[];
  summary?: string;
}

export class AgenticMemory {
  private traces: Map<string, ReasoningTrace> = new Map();
  private storageDir: string;

  constructor(baseDir: string = ".") {
    this.storageDir = path.join(baseDir, ".omni", "memory");
    fs.mkdirSync(this.storageDir, { recursive: true });
  }

  /** Start a new reasoning trace for a build */
  startTrace(buildId: string): ReasoningTrace {
    const trace: ReasoningTrace = {
      buildId,
      startTime: Date.now(),
      entries: [],
    };
    this.traces.set(buildId, trace);
    return trace;
  }

  /** Add an entry to a reasoning trace */
  addEntry(buildId: string, entry: Omit<MemoryEntry, "timestamp">): void {
    const trace = this.traces.get(buildId);
    if (!trace) return;

    trace.entries.push({
      ...entry,
      timestamp: Date.now(),
    });
  }

  /** Log a prompt sent to an agent */
  logPrompt(buildId: string, agent: string, service: string, prompt: string): void {
    this.addEntry(buildId, {
      type: "prompt",
      agent,
      service,
      content: prompt.substring(0, 500) + (prompt.length > 500 ? "..." : ""),
    });
  }

  /** Log a response received from an agent */
  logResponse(
    buildId: string,
    agent: string,
    service: string,
    response: string,
    tokensUsed: number
  ): void {
    this.addEntry(buildId, {
      type: "response",
      agent,
      service,
      content: response.substring(0, 500) + (response.length > 500 ? "..." : ""),
      metadata: { tokensUsed },
    });
  }

  /** Log a verification result */
  logVerification(
    buildId: string,
    service: string,
    passed: boolean,
    details: string
  ): void {
    this.addEntry(buildId, {
      type: "verify",
      agent: "verifier",
      service,
      content: details,
      metadata: { passed },
    });
  }

  /** Log a decision (e.g., model escalation, retry) */
  logDecision(buildId: string, agent: string, service: string, decision: string): void {
    this.addEntry(buildId, {
      type: "decision",
      agent,
      service,
      content: decision,
    });
  }

  /** Complete a trace and save to disk */
  completeTrace(buildId: string, summary?: string): void {
    const trace = this.traces.get(buildId);
    if (!trace) return;

    trace.endTime = Date.now();
    trace.summary = summary;

    // Save to disk
    const filePath = path.join(this.storageDir, `${buildId}.json`);
    fs.writeFileSync(filePath, JSON.stringify(trace, null, 2), "utf8");
  }

  /** Get a trace by ID */
  getTrace(buildId: string): ReasoningTrace | null {
    // Check in-memory first
    if (this.traces.has(buildId)) {
      return this.traces.get(buildId)!;
    }

    // Try loading from disk
    const filePath = path.join(this.storageDir, `${buildId}.json`);
    if (fs.existsSync(filePath)) {
      try {
        const raw = fs.readFileSync(filePath, "utf8");
        return JSON.parse(raw) as ReasoningTrace;
      } catch {
        return null;
      }
    }

    return null;
  }

  /** List all saved traces */
  listTraces(): string[] {
    if (!fs.existsSync(this.storageDir)) return [];

    return fs
      .readdirSync(this.storageDir)
      .filter((f) => f.endsWith(".json"))
      .map((f) => f.replace(".json", ""));
  }

  /** Generate a human-readable chain-of-thought report */
  generateReport(buildId: string): string {
    const trace = this.getTrace(buildId);
    if (!trace) return "No trace found.";

    const lines: string[] = [];
    const duration = (trace.endTime || Date.now()) - trace.startTime;

    lines.push(`# Build Reasoning Trace: ${buildId}`);
    lines.push(`Duration: ${(duration / 1000).toFixed(1)}s`);
    lines.push(`Entries: ${trace.entries.length}`);
    lines.push(``);

    for (const entry of trace.entries) {
      const ts = new Date(entry.timestamp).toISOString();
      const icon =
        entry.type === "prompt"
          ? "📤"
          : entry.type === "response"
            ? "📥"
            : entry.type === "verify"
              ? "✅"
              : entry.type === "error"
                ? "❌"
                : entry.type === "decision"
                  ? "🤔"
                  : "📝";

      lines.push(`${icon} [${ts}] ${entry.type.toUpperCase()} | ${entry.agent} → ${entry.service}`);
      lines.push(`   ${entry.content}`);
      if (entry.metadata) {
        lines.push(`   metadata: ${JSON.stringify(entry.metadata)}`);
      }
      lines.push(``);
    }

    if (trace.summary) {
      lines.push(`## Summary`);
      lines.push(trace.summary);
    }

    return lines.join("\n");
  }
}
