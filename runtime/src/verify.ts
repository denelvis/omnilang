import { spawnSync } from "child_process";
import pc from "picocolors";

export interface VerificationReport {
  success: boolean;
  typeCheckError?: string;
  testError?: string;
}

export class VerificationRunner {
  private outputDir: string;
  private target: string;

  constructor(outputDir: string, target: string = "typescript") {
    this.outputDir = outputDir;
    this.target = target;
  }

  public verify(): VerificationReport {
    switch (this.target) {
      case "rust":
        return this.verifyRust();
      case "python":
        return this.verifyPython();
      case "typescript":
      default:
        return this.verifyTypeScript();
    }
  }

  private verifyTypeScript(): VerificationReport {
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
        typeCheckError: errorText,
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
        testError: errorText,
      };
    }

    console.log(`     ${pc.green("✓")} All Jest tests passed`);

    return { success: true };
  }

  private verifyRust(): VerificationReport {
    console.log(pc.yellow("     Running cargo build..."));

    // 1. Run cargo build
    const buildRes = spawnSync("cargo", ["build"], {
      cwd: this.outputDir,
      stdio: "pipe",
      shell: true,
    });

    if (buildRes.status !== 0) {
      const errorText = buildRes.stdout.toString() + buildRes.stderr.toString();
      return {
        success: false,
        typeCheckError: errorText,
      };
    }

    console.log(`     ${pc.green("✓")} Rust cargo build passed`);

    // 2. Run cargo test
    console.log(pc.yellow("     Running cargo test..."));
    const testRes = spawnSync("cargo", ["test"], {
      cwd: this.outputDir,
      stdio: "pipe",
      shell: true,
    });

    if (testRes.status !== 0) {
      const errorText = testRes.stdout.toString() + testRes.stderr.toString();
      return {
        success: false,
        testError: errorText,
      };
    }

    console.log(`     ${pc.green("✓")} All Rust tests passed`);

    return { success: true };
  }

  private verifyPython(): VerificationReport {
    console.log(pc.yellow("     Running mypy type check..."));

    // 1. Run mypy
    const mypyRes = spawnSync("python3", ["-m", "mypy", "."], {
      cwd: this.outputDir,
      stdio: "pipe",
      shell: true,
    });

    if (mypyRes.status !== 0) {
      const errorText = mypyRes.stdout.toString() + mypyRes.stderr.toString();
      // mypy failures are non-fatal warnings for now
      console.log(
        `     ${pc.yellow("⚠")} mypy reported issues (non-blocking):`
      );
      console.log(pc.dim(errorText.trim()));
    } else {
      console.log(`     ${pc.green("✓")} mypy type check passed`);
    }

    // 2. Run pytest
    console.log(pc.yellow("     Running pytest..."));
    const pytestRes = spawnSync("python3", ["-m", "pytest", "-v"], {
      cwd: this.outputDir,
      stdio: "pipe",
      shell: true,
    });

    if (pytestRes.status !== 0) {
      const errorText =
        pytestRes.stdout.toString() + pytestRes.stderr.toString();
      return {
        success: false,
        testError: errorText,
      };
    }

    console.log(`     ${pc.green("✓")} All Python tests passed`);

    return { success: true };
  }
}
