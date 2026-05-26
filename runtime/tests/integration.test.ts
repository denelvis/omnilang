import { spawnSync } from "child_process";
import * as path from "path";
import * as fs from "fs";

describe("OmniLang End-to-End Integration", () => {
  const rootDir = path.resolve(__dirname, "../..");
  const buildDir = path.resolve(rootDir, "build");

  beforeAll(() => {
    // 1. Build the Rust omni compiler binary first
    console.log("   [Integration Test] Building Rust compiler...");
    const cargoBuild = spawnSync("cargo", ["build", "--bin", "omni"], {
      cwd: rootDir,
      stdio: "ignore",
    });
    if (cargoBuild.status !== 0) {
      throw new Error("Failed to compile omni binary for integration testing");
    }
  });

  beforeEach(() => {
    // Clean up any existing build dir
    if (fs.existsSync(buildDir)) {
      fs.rmSync(buildDir, { recursive: true, force: true });
    }
  });

  afterAll(() => {
    // Clean up after all tests complete
    if (fs.existsSync(buildDir)) {
      fs.rmSync(buildDir, { recursive: true, force: true });
    }
  });

  test("should compile and generate TypeScript code from checkout.omni using mock LLM", () => {
    console.log("   [Integration Test] Running omni build...");
    const buildResult = spawnSync(
      "cargo",
      ["run", "--bin", "omni", "--", "build", "examples/checkout.omni", "--target", "typescript"],
      {
        cwd: rootDir,
        env: {
          ...process.env,
          OMNI_MOCK_LLM: "true",
        },
      }
    );

    // Assert that the command compiled and finished successfully
    expect(buildResult.status).toBe(0);

    // Verify expected TypeScript code files were generated
    const serviceFile = path.join(buildDir, "src", "services", "Checkout.ts");
    const testFile = path.join(buildDir, "tests", "Checkout.test.ts");

    expect(fs.existsSync(serviceFile)).toBe(true);
    expect(fs.existsSync(testFile)).toBe(true);

    const serviceCode = fs.readFileSync(serviceFile, "utf8");
    expect(serviceCode).toContain("class CheckoutService");
    expect(serviceCode).toContain("placeOrder");
  });

  test("should compile and generate TypeScript state machine from booking_flow.omni using mock LLM", () => {
    console.log("   [Integration Test] Running omni build for booking_flow.omni...");
    const buildResult = spawnSync(
      "cargo",
      ["run", "--bin", "omni", "--", "build", "examples/booking_flow.omni", "--target", "typescript"],
      {
        cwd: rootDir,
        env: {
          ...process.env,
          OMNI_MOCK_LLM: "true",
        },
      }
    );

    expect(buildResult.status).toBe(0);

    const stateMachineFile = path.join(buildDir, "src", "services", "BookingFlowStateMachine.ts");
    const testFile = path.join(buildDir, "tests", "BookingFlowStateMachine.test.ts");

    expect(fs.existsSync(stateMachineFile)).toBe(true);
    expect(fs.existsSync(testFile)).toBe(true);

    const smCode = fs.readFileSync(stateMachineFile, "utf8");
    expect(smCode).toContain("class BookingFlowStateMachine");
    expect(smCode).toContain("timeoutOrUserAbort");
  });
});
