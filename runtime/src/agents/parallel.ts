/**
 * Parallel execution engine for multi-agent OmniLang builds.
 *
 * Provides dependency-aware parallelism, rate limiting, and
 * per-agent progress tracking.
 */

import pc from "picocolors";
import { AgentRegistry, AgentRegistration, TaskRequirement } from "./registry";

// ── Task types ───────────────────────────────────────────
export interface BuildTask {
  id: string;
  serviceName: string;
  taskType: "codegen" | "test" | "review" | "refactor" | "document";
  language: string;
  /** Dependencies: task IDs that must complete before this one */
  dependsOn: string[];
  /** The spec IR data for this task */
  specData: any;
  /** Optional: assigned agent ID */
  assignedAgent?: string;
}

export interface TaskResult {
  taskId: string;
  success: boolean;
  files: string[];
  duration: number;
  agentId: string;
  tokensUsed: number;
  retryCount: number;
  error?: string;
}

export interface ParallelConfig {
  /** Maximum concurrent tasks */
  maxConcurrency: number;
  /** Rate limit: max requests per minute per agent */
  rateLimitPerMinute: number;
  /** Maximum retries per task */
  maxRetries: number;
  /** Whether to escalate model on retry */
  escalateOnRetry: boolean;
  /** Budget tier */
  budgetTier: "cheap" | "balanced" | "premium";
}

// ── Progress tracking ────────────────────────────────────
export interface ProgressEvent {
  type: "start" | "complete" | "retry" | "fail" | "skip";
  taskId: string;
  serviceName: string;
  agentId?: string;
  timestamp: number;
  details?: string;
}

export type ProgressCallback = (event: ProgressEvent) => void;

// ── Parallel executor ────────────────────────────────────
export class ParallelExecutor {
  private registry: AgentRegistry;
  private config: ParallelConfig;
  private progressCallbacks: ProgressCallback[] = [];
  private rateLimitCounters: Map<string, number[]> = new Map();

  constructor(registry: AgentRegistry, config: ParallelConfig) {
    this.registry = registry;
    this.config = config;
  }

  /** Register a progress listener */
  onProgress(callback: ProgressCallback): void {
    this.progressCallbacks.push(callback);
  }

  /** Execute tasks with dependency-aware parallelism */
  async execute(
    tasks: BuildTask[],
    executor: (task: BuildTask, agent: AgentRegistration) => Promise<{ success: boolean; files: string[]; tokensUsed: number }>
  ): Promise<TaskResult[]> {
    const results: Map<string, TaskResult> = new Map();
    const pending = new Set(tasks.map((t) => t.id));
    const running = new Set<string>();
    const completed = new Set<string>();

    // Build dependency graph
    const taskMap = new Map(tasks.map((t) => [t.id, t]));

    const isReady = (task: BuildTask): boolean => {
      return task.dependsOn.every((dep) => completed.has(dep));
    };

    while (pending.size > 0 || running.size > 0) {
      // Find tasks ready to run
      const readyTasks = tasks.filter(
        (t) => pending.has(t.id) && !running.has(t.id) && isReady(t)
      );

      // Launch up to maxConcurrency tasks
      const slotsAvailable = this.config.maxConcurrency - running.size;
      const tasksToLaunch = readyTasks.slice(0, slotsAvailable);

      const promises = tasksToLaunch.map(async (task) => {
        pending.delete(task.id);
        running.add(task.id);

        const result = await this.executeWithRetry(task, executor);
        running.delete(task.id);
        completed.add(task.id);
        results.set(task.id, result);
      });

      if (promises.length > 0) {
        await Promise.all(promises);
      } else if (running.size > 0) {
        // Wait for some tasks to complete
        await new Promise((resolve) => setTimeout(resolve, 100));
      } else {
        // Deadlock: tasks remain but none are ready
        const deadlocked = Array.from(pending);
        console.error(
          pc.red(`Deadlock detected: tasks ${deadlocked.join(", ")} have unresolved dependencies`)
        );
        break;
      }
    }

    return Array.from(results.values());
  }

  /** Execute a single task with retry logic and model escalation */
  private async executeWithRetry(
    task: BuildTask,
    executor: (task: BuildTask, agent: AgentRegistration) => Promise<{ success: boolean; files: string[]; tokensUsed: number }>
  ): Promise<TaskResult> {
    const startTime = Date.now();
    let retryCount = 0;
    let lastError: string | undefined;

    // Determine budget tier for this attempt
    const tiers: ("cheap" | "balanced" | "premium")[] = this.config.escalateOnRetry
      ? ["cheap", "balanced", "premium"]
      : [this.config.budgetTier];

    for (let attempt = 0; attempt <= this.config.maxRetries; attempt++) {
      const tierIndex = Math.min(attempt, tiers.length - 1);
      const currentTier = tiers[tierIndex];

      const req: TaskRequirement = {
        taskType: task.taskType,
        language: task.language,
        budgetTier: currentTier,
      };

      const agent = this.registry.findBest(req);
      if (!agent) {
        lastError = `No agent available for ${task.taskType} in ${task.language}`;
        continue;
      }

      // Rate limiting
      await this.waitForRateLimit(agent.id);

      this.emit({
        type: attempt === 0 ? "start" : "retry",
        taskId: task.id,
        serviceName: task.serviceName,
        agentId: agent.id,
        timestamp: Date.now(),
        details: attempt > 0 ? `retry #${attempt} (escalated to ${currentTier})` : undefined,
      });

      try {
        const result = await executor(task, agent);

        if (result.success) {
          this.emit({
            type: "complete",
            taskId: task.id,
            serviceName: task.serviceName,
            agentId: agent.id,
            timestamp: Date.now(),
          });

          return {
            taskId: task.id,
            success: true,
            files: result.files,
            duration: Date.now() - startTime,
            agentId: agent.id,
            tokensUsed: result.tokensUsed,
            retryCount,
          };
        }

        lastError = "Agent returned unsuccessful result";
        retryCount++;
      } catch (err: any) {
        lastError = err.message;
        retryCount++;
      }
    }

    this.emit({
      type: "fail",
      taskId: task.id,
      serviceName: task.serviceName,
      timestamp: Date.now(),
      details: lastError,
    });

    return {
      taskId: task.id,
      success: false,
      files: [],
      duration: Date.now() - startTime,
      agentId: "none",
      tokensUsed: 0,
      retryCount,
      error: lastError,
    };
  }

  /** Simple sliding-window rate limiter per agent */
  private async waitForRateLimit(agentId: string): Promise<void> {
    if (!this.rateLimitCounters.has(agentId)) {
      this.rateLimitCounters.set(agentId, []);
    }

    const timestamps = this.rateLimitCounters.get(agentId)!;
    const now = Date.now();
    const windowMs = 60_000;

    // Remove timestamps outside the window
    while (timestamps.length > 0 && timestamps[0] < now - windowMs) {
      timestamps.shift();
    }

    // Wait if at limit
    while (timestamps.length >= this.config.rateLimitPerMinute) {
      const waitMs = timestamps[0] + windowMs - now;
      await new Promise((resolve) => setTimeout(resolve, Math.max(waitMs, 100)));

      // Re-check
      const updatedNow = Date.now();
      while (timestamps.length > 0 && timestamps[0] < updatedNow - windowMs) {
        timestamps.shift();
      }
    }

    timestamps.push(Date.now());
  }

  /** Emit a progress event to all listeners */
  private emit(event: ProgressEvent): void {
    for (const cb of this.progressCallbacks) {
      try {
        cb(event);
      } catch {
        // Ignore listener errors
      }
    }
  }
}

// ── Helpers ──────────────────────────────────────────────

/** Build a dependency graph from IR spec services */
export function buildTasksFromIR(
  ir: any,
  language: string
): BuildTask[] {
  const services = ir.services || [];

  return services.map((svc: any, index: number) => ({
    id: `codegen-${svc.name}`,
    serviceName: svc.name,
    taskType: "codegen" as const,
    language,
    dependsOn: [], // All services can build in parallel unless specified
    specData: svc,
  }));
}
