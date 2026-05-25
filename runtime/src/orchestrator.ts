import * as fs from "fs";
import * as path from "path";
import { spawnSync } from "child_process";
import pc from "picocolors";
import { AnthropicProvider } from "./providers/anthropic";
import { CodeGenAgent } from "./agents/codegen";
import { VerificationRunner } from "./verify";

export interface OrchestratorOptions {
  irPath: string;
  outputDir: string;
  target: string;
}

export class Orchestrator {
  private irPath: string;
  private outputDir: string;
  private target: string;

  constructor(options: OrchestratorOptions) {
    this.irPath = options.irPath;
    this.outputDir = path.resolve(options.outputDir);
    this.target = options.target;
  }

  public async run(): Promise<void> {
    // 1. Load Spec IR JSON
    const irContent = fs.readFileSync(this.irPath, "utf8");
    const ir = JSON.parse(irContent);

    // 2. Initialize target directory structure
    console.log(pc.yellow(`   Initializing build directory at: ${this.outputDir}`));
    this.initializeBuildDirectory();

    // 3. Initialize LLM Provider and CodeGen Agent
    const provider = new AnthropicProvider();
    const agent = new CodeGenAgent(provider);

    // 4. Generate code for each service in build order (topological sort)
    console.log(pc.yellow(`   Executing code generation flow...`));
    const buildOrder: string[] = ir.build_order || [];

    if (buildOrder.length === 0 && ir.services) {
      // Fallback if build_order is empty but services are present
      for (const service of ir.services) {
        buildOrder.push(service.name);
      }
    }

    for (const serviceName of buildOrder) {
      await agent.generateService(serviceName, ir, this.outputDir);
    }

    // 5. Run Verification (tsc and jest tests)
    console.log(pc.yellow(`   Running verification tests...`));
    const verifier = new VerificationRunner(this.outputDir);
    const report = verifier.verify();

    if (report.success) {
      console.log(pc.green(`✅ Build and verification completed successfully!`));
      console.log(pc.green(`   All generated tests passed successfully.`));
    } else {
      console.error(pc.red(`❌ Verification failed!`));
      if (report.tscError) {
        console.error(pc.red(`   TypeScript Compilation Errors:`));
        console.error(pc.dim(report.tscError));
      }
      if (report.jestError) {
        console.error(pc.red(`   Jest Test Failure Output:`));
        console.error(pc.dim(report.jestError));
      }
      process.exit(1);
    }
  }

  private initializeBuildDirectory(): void {
    // 1. Create directory structure
    fs.mkdirSync(this.outputDir, { recursive: true });
    fs.mkdirSync(path.join(this.outputDir, "src", "services"), { recursive: true });
    fs.mkdirSync(path.join(this.outputDir, "tests"), { recursive: true });

    // 2. Write package.json
    const packageJsonPath = path.join(this.outputDir, "package.json");
    if (!fs.existsSync(packageJsonPath)) {
      const packageJson = {
        name: "omni-build",
        version: "0.1.0",
        private: true,
        scripts: {
          "test": "jest"
        },
        dependencies: {},
        devDependencies: {
          "typescript": "^5.6.3",
          "jest": "^29.7.0",
          "ts-jest": "^29.2.5",
          "@types/jest": "^29.5.14",
          "@types/node": "^20.17.6"
        }
      };
      fs.writeFileSync(packageJsonPath, JSON.stringify(packageJson, null, 2));
    }

    // 3. Write tsconfig.json
    const tsconfigJsonPath = path.join(this.outputDir, "tsconfig.json");
    if (!fs.existsSync(tsconfigJsonPath)) {
      const tsconfig = {
        compilerOptions: {
          target: "ES2022",
          module: "commonjs",
          moduleResolution: "node",
          outDir: "./dist",
          rootDir: ".",
          strict: true,
          esModuleInterop: true,
          skipLibCheck: true,
          forceConsistentCasingInFileNames: true
        },
        include: ["src/**/*", "tests/**/*"]
      };
      fs.writeFileSync(tsconfigJsonPath, JSON.stringify(tsconfig, null, 2));
    }

    // 4. Write jest.config.js
    const jestConfigPath = path.join(this.outputDir, "jest.config.js");
    if (!fs.existsSync(jestConfigPath)) {
      const jestConfig = `module.exports = {
  preset: 'ts-jest',
  testEnvironment: 'node',
  testMatch: ['**/tests/**/*.test.ts', '**/*.test.ts'],
};
`;
      fs.writeFileSync(jestConfigPath, jestConfig);
    }

    // 5. Run npm install if node_modules doesn't exist
    const nodeModulesPath = path.join(this.outputDir, "node_modules");
    if (!fs.existsSync(nodeModulesPath)) {
      console.log(pc.yellow(`   Installing packages in ${this.outputDir}...`));
      const res = spawnSync("npm", ["install"], {
        cwd: this.outputDir,
        stdio: "inherit",
        shell: true
      });
      if (res.status !== 0) {
        throw new Error(`npm install failed in ${this.outputDir} with exit code ${res.status}`);
      }
    }
  }
}
