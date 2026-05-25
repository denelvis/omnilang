import * as fs from "fs";
import minimist from "minimist";
import * as dotenv from "dotenv";
import pc from "picocolors";
import { Orchestrator } from "./orchestrator";

dotenv.config();

function printUsage() {
  console.log(pc.bold("Usage:"));
  console.log("  node dist/index.js <path-to-spec-ir.json> [options]");
  console.log(pc.bold("Options:"));
  console.log("  --output <dir>  Directory to output generated code (default: build)");
  console.log("  --target <lang> Target language (default: typescript)");
}

async function main() {
  const argv = minimist(process.argv.slice(2));
  const irPath = argv._[0];

  if (!irPath) {
    console.error(pc.red("error: missing path to Spec IR JSON file."));
    printUsage();
    process.exit(1);
  }

  if (!fs.existsSync(irPath)) {
    console.error(pc.red(`error: file not found: ${irPath}`));
    process.exit(1);
  }

  const outputDir = argv.output || "build";
  const target = argv.target || "typescript";
  const fullStack = !!argv["full-stack"];

  console.log(pc.green(`🚀 Starting OmniLang Generator Runtime`));
  console.log(`   IR Path:   ${pc.cyan(irPath)}`);
  console.log(`   Output:    ${pc.cyan(outputDir)}`);
  console.log(`   Target:    ${pc.cyan(target)}`);
  if (fullStack) {
    console.log(`   Mode:      ${pc.cyan("full-stack")}`);
  }

  try {
    const orchestrator = new Orchestrator({ irPath, outputDir, target, fullStack });
    await orchestrator.run();
    process.exit(0);
  } catch (err: any) {
    console.error(pc.red(`error: runtime failed: ${err.message || err}`));
    process.exit(1);
  }
}

main();
