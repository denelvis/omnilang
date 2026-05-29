import { spawnSync } from "child_process";
import * as path from "path";
import * as fs from "fs";
import pc from "picocolors";

async function runDemo() {
  console.log(pc.bold(pc.cyan("⚡ Running OmniLang Self-Correction Visual Demo...")));

  const projectRoot = path.resolve(__dirname, "..");

  // Clear cache and traces first to ensure first attempt fails and runs self-correction
  const tracesDir = path.join(projectRoot, ".omni-cache", "traces");
  if (fs.existsSync(tracesDir)) {
    fs.rmSync(tracesDir, { recursive: true, force: true });
  }

  // Clear any existing build
  const buildDir = path.join(projectRoot, "build");
  if (fs.existsSync(buildDir)) {
    fs.rmSync(buildDir, { recursive: true, force: true });
  }

  console.log(pc.yellow("\n📦 Starting build process for BankTransferService specification..."));
  console.log(pc.yellow("   This spec declares strict invariants, but the generator's initial attempt has a type mismatch."));
  
  const buildProcess = spawnSync("cargo", ["run", "--bin", "omni", "--", "build", "examples/self_correction_demo.omni", "--target", "typescript"], {
    cwd: projectRoot,
    stdio: "inherit",
    env: {
      ...process.env,
      OMNI_MOCK_LLM: "true"
    }
  });

  if (buildProcess.status !== 0) {
    console.error(pc.red("\n❌ Error: omni build execution failed."));
    process.exit(1);
  }

  console.log("\n" + pc.bold(pc.green("✨ OmniLang Self-Correction Trace & Telemetry Summary:")));
  if (fs.existsSync(tracesDir)) {
    const traceFiles = fs.readdirSync(tracesDir).filter(f => f.endsWith(".json") && f !== "retries.json");
    for (const file of traceFiles) {
      try {
        const trace = JSON.parse(fs.readFileSync(path.join(tracesDir, file), "utf8"));
        console.log(`\n   Service: ${pc.cyan(trace.serviceName)}`);
        console.log(`   - E2E Validation Success: ${trace.success ? pc.green("Yes") : pc.red("No")}`);
        console.log(`   - Total Generation Attempts: ${pc.yellow(trace.attempts)}`);
        if (trace.errors && trace.errors.length > 0) {
          console.log(`   - Errors Captured and Self-Corrected:`);
          for (let i = 0; i < trace.errors.length; i++) {
            console.log(pc.dim(`     [Attempt ${i + 1} Failure] ${trace.errors[i].split("\n")[0]}`));
          }
        }
      } catch (err: any) {
        console.error(pc.red(`   - Error reading trace: ${err.message}`));
      }
    }
  }

  console.log(pc.green("\n✅ Self-correction visual demo completed successfully!"));
}

runDemo().catch(err => {
  console.error(err);
  process.exit(1);
});
