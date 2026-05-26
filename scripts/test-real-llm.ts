import { spawnSync } from "child_process";
import * as path from "path";
import * as fs from "fs";
import pc from "picocolors";

async function runIntegrationTest() {
  console.log(pc.bold("🚀 Running E2E Integration Test with Real LLM..."));

  // Ensure ANTHROPIC_API_KEY is present
  const apiKey = process.env.ANTHROPIC_API_KEY || process.env.OMNI_API_KEY;
  if (!apiKey) {
    console.error(pc.red("❌ Error: ANTHROPIC_API_KEY or OMNI_API_KEY must be set to run integration tests with a real LLM."));
    process.exit(1);
  }

  // 1. Run cargo build to compile the compiler bin
  console.log(pc.yellow("🔨 Building OmniLang compiler..."));
  const cargoBuild = spawnSync("cargo", ["build", "--bin", "omni"], { stdio: "inherit" });
  if (cargoBuild.status !== 0) {
    console.error(pc.red("❌ Error: Failed to build OmniLang compiler."));
    process.exit(1);
  }

  // 2. Run omni build for examples/checkout.omni with real LLM provider (anthropic)
  console.log(pc.yellow("📦 Executing omni build with real Claude 3.5 Sonnet..."));
  
  // Clear any existing build first
  const buildDir = path.resolve(process.cwd(), "build");
  if (fs.existsSync(buildDir)) {
    fs.rmSync(buildDir, { recursive: true, force: true });
  }

  // Clear existing traces first
  const tracesDir = path.resolve(process.cwd(), ".omni-cache", "traces");
  if (fs.existsSync(tracesDir)) {
    fs.rmSync(tracesDir, { recursive: true, force: true });
  }

  const buildProcess = spawnSync("cargo", ["run", "--bin", "omni", "--", "build", "examples/checkout.omni", "--target", "typescript"], {
    stdio: "inherit",
    env: {
      ...process.env,
      OMNI_LLM_PROVIDER: "anthropic",
      OMNI_MOCK_LLM: "false",
    }
  });

  if (buildProcess.status !== 0) {
    console.error(pc.red("❌ Error: omni build failed with real LLM."));
    process.exit(1);
  }

  console.log("\n" + pc.cyan("📊 Real LLM E2E Telemetry & Quality Report:"));
  if (fs.existsSync(tracesDir)) {
    const traceFiles = fs.readdirSync(tracesDir).filter(f => f.endsWith(".json") && f !== "retries.json");
    if (traceFiles.length === 0) {
      console.log(pc.yellow("   No trace files found in cache."));
    }
    for (const file of traceFiles) {
      try {
        const trace = JSON.parse(fs.readFileSync(path.join(tracesDir, file), "utf8"));
        console.log(pc.bold(`\n   Service: ${pc.cyan(trace.serviceName)}`));
        console.log(`     - Success: ${trace.success ? pc.green("Yes") : pc.red("No")}`);
        console.log(`     - Total Generation Attempts: ${pc.yellow(trace.attempts)}`);
        if (trace.errors && trace.errors.length > 0) {
          console.log(`     - Self-Correction Errors Encountered:`);
          for (let i = 0; i < trace.errors.length; i++) {
            console.log(pc.dim(`       [Retry ${i + 1}] ${trace.errors[i]}`));
          }
        } else {
          console.log(`     - Self-Correction Errors: ${pc.green("None (First-shot success)")}`);
        }
      } catch (err: any) {
        console.error(pc.red(`     - Error reading trace file ${file}: ${err.message}`));
      }
    }
  } else {
    console.log(pc.yellow("   Traces directory not found."));
  }

  console.log(pc.green("\n✅ E2E Integration Test with Real LLM passed successfully!"));
}

runIntegrationTest().catch(err => {
  console.error(err);
  process.exit(1);
});
