import { spawnSync } from "child_process";
import pc from "picocolors";

export interface VerificationReport {
  success: boolean;
  tscError?: string;
  jestError?: string;
}

export class VerificationRunner {
  private outputDir: string;

  constructor(outputDir: string) {
    this.outputDir = outputDir;
  }

  public verify(): VerificationReport {
    console.log(pc.yellow("     Running TypeScript type check (tsc)..."));
    
    // 1. Run tsc --noEmit
    const tscRes = spawnSync("npx", ["tsc", "--noEmit"], {
      cwd: this.outputDir,
      stdio: "pipe",
      shell: true,
    });

    if (tscRes.status !== 0) {
      const errorText = tscRes.stdout.toString() + tscRes.stderr.toString();
      return {
        success: false,
        tscError: errorText,
      };
    }

    console.log(`     ${pc.green("✓")} TypeScript type check passed`);

    // 2. Run jest tests
    console.log(pc.yellow("     Running Jest tests..."));
    const jestRes = spawnSync("npx", ["jest", "--passWithNoTests"], {
      cwd: this.outputDir,
      stdio: "pipe",
      shell: true,
    });

    if (jestRes.status !== 0) {
      const errorText = jestRes.stdout.toString() + jestRes.stderr.toString();
      return {
        success: false,
        jestError: errorText,
      };
    }

    console.log(`     ${pc.green("✓")} All Jest tests passed`);

    return { success: true };
  }
}
