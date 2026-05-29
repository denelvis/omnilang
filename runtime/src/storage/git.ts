/**
 * Git integration — auto-commit and auto-push for verified builds.
 *
 * After successful verification, automatically commit the generated code
 * with a structured commit message.
 */

import { execSync } from "child_process";
import * as path from "path";

export interface GitConfig {
  /** Auto-commit after successful verification */
  autoCommit: boolean;
  /** Auto-push after commit */
  autoPush: boolean;
  /** Branch to push to */
  branch: string;
  /** Commit message prefix */
  commitPrefix: string;
}

export const DEFAULT_GIT_CONFIG: GitConfig = {
  autoCommit: true,
  autoPush: false,
  branch: "main",
  commitPrefix: "omni: ",
};

export class GitManager {
  private workDir: string;
  private config: GitConfig;

  constructor(workDir: string, config: GitConfig = DEFAULT_GIT_CONFIG) {
    this.workDir = workDir;
    this.config = config;
  }

  /** Check if git is available and directory is a repo */
  isGitRepo(): boolean {
    try {
      this.exec("git rev-parse --is-inside-work-tree");
      return true;
    } catch {
      return false;
    }
  }

  /** Check if there are uncommitted changes */
  hasChanges(): boolean {
    const output = this.exec("git status --porcelain");
    return output.trim().length > 0;
  }

  /** Stage all changes in the build directory */
  stageChanges(buildDir: string): void {
    this.exec(`git add ${buildDir}`);
  }

  /** Create a structured commit */
  commit(serviceName: string, stats: { operations: number; tests: number }): string {
    const message = `${this.config.commitPrefix}generate ${serviceName} (${stats.operations} operations, ${stats.tests} tests)`;
    this.exec(`git commit -m "${message}"`);
    return message;
  }

  /** Push to remote */
  push(): void {
    this.exec(`git push origin ${this.config.branch}`);
  }

  /** Full auto-commit flow */
  autoCommitAndPush(
    buildDir: string,
    serviceName: string,
    stats: { operations: number; tests: number }
  ): { committed: boolean; pushed: boolean; message: string } {
    if (!this.isGitRepo()) {
      return { committed: false, pushed: false, message: "Not a git repository" };
    }

    this.stageChanges(buildDir);

    if (!this.hasChanges()) {
      return { committed: false, pushed: false, message: "No changes to commit" };
    }

    if (!this.config.autoCommit) {
      return { committed: false, pushed: false, message: "Auto-commit disabled" };
    }

    const commitMsg = this.commit(serviceName, stats);

    let pushed = false;
    if (this.config.autoPush) {
      try {
        this.push();
        pushed = true;
      } catch {
        // Push failure is non-fatal
      }
    }

    return { committed: true, pushed, message: commitMsg };
  }

  /** Get the current HEAD hash */
  getHeadHash(): string {
    return this.exec("git rev-parse HEAD").trim();
  }

  /** Get a short diff summary */
  getDiffSummary(): string {
    return this.exec("git diff --stat HEAD~1").trim();
  }

  private exec(cmd: string): string {
    return execSync(cmd, { cwd: this.workDir, encoding: "utf8" });
  }
}
