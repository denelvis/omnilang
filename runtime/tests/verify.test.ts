import { VerificationRunner } from "../src/verify";
import { spawnSync } from "child_process";
import * as fs from "fs";

jest.mock("child_process", () => ({
  spawnSync: jest.fn(),
}));

jest.mock("fs", () => {
  const original = jest.requireActual("fs");
  return {
    ...original,
    existsSync: jest.fn(),
    mkdirSync: jest.fn(),
    writeFileSync: jest.fn(),
  };
});

describe("VerificationRunner", () => {
  const mockSpawnSync = spawnSync as jest.Mock;
  const mockExistsSync = fs.existsSync as jest.Mock;

  beforeEach(() => {
    jest.resetAllMocks();
    mockExistsSync.mockReturnValue(true);
  });

  test("should verify TypeScript successfully", () => {
    const runner = new VerificationRunner("test-dir", "typescript");

    // Mock spawnSync to succeed on tsc and jest
    mockSpawnSync.mockReturnValue({ status: 0, stdout: Buffer.from("Success"), stderr: Buffer.from("") });

    const report = runner.verify();

    expect(report.success).toBe(true);
    expect(report.typeCheckError).toBeUndefined();
    expect(report.testError).toBeUndefined();
    // Expect 2 calls: tsc and jest
    expect(mockSpawnSync).toHaveBeenCalledTimes(2);
  });

  test("should fail TypeScript verification if tsc fails", () => {
    const runner = new VerificationRunner("test-dir", "typescript");

    mockSpawnSync.mockReturnValueOnce({
      status: 1,
      stdout: Buffer.from("Type error on line 1"),
      stderr: Buffer.from(""),
    });

    const report = runner.verify();

    expect(report.success).toBe(false);
    expect(report.typeCheckError).toContain("Type error on line 1");
    expect(report.testError).toBeUndefined();
    // Jest should not run since tsc failed
    expect(mockSpawnSync).toHaveBeenCalledTimes(1);
  });

  test("should fail TypeScript verification if jest fails", () => {
    const runner = new VerificationRunner("test-dir", "typescript");

    // tsc succeeds, jest fails
    mockSpawnSync
      .mockReturnValueOnce({ status: 0, stdout: Buffer.from("Success"), stderr: Buffer.from("") })
      .mockReturnValueOnce({ status: 1, stdout: Buffer.from("Test failed"), stderr: Buffer.from("") });

    const report = runner.verify();

    expect(report.success).toBe(false);
    expect(report.typeCheckError).toBeUndefined();
    expect(report.testError).toContain("Test failed");
    expect(mockSpawnSync).toHaveBeenCalledTimes(2);
  });

  test("should verify Rust successfully", () => {
    const runner = new VerificationRunner("test-dir", "rust");

    mockSpawnSync.mockReturnValue({ status: 0, stdout: Buffer.from("Success"), stderr: Buffer.from("") });

    const report = runner.verify();

    expect(report.success).toBe(true);
    expect(mockSpawnSync).toHaveBeenCalledTimes(2);
    // Assert cargo build and cargo test were called
    expect(mockSpawnSync.mock.calls[0][0]).toBe("cargo");
    expect(mockSpawnSync.mock.calls[0][1]).toEqual(["build"]);
    expect(mockSpawnSync.mock.calls[1][1]).toEqual(["test"]);
  });

  test("should fail Rust verification if cargo build fails", () => {
    const runner = new VerificationRunner("test-dir", "rust");

    mockSpawnSync.mockReturnValueOnce({ status: 1, stdout: Buffer.from("Cargo error"), stderr: Buffer.from("") });

    const report = runner.verify();

    expect(report.success).toBe(false);
    expect(report.typeCheckError).toContain("Cargo error");
    expect(mockSpawnSync).toHaveBeenCalledTimes(1);
  });

  test("should verify Python successfully", () => {
    const runner = new VerificationRunner("test-dir", "python");

    // mypy can return warning (ignored or succeeds), pytest must succeed
    mockSpawnSync.mockReturnValue({ status: 0, stdout: Buffer.from("Success"), stderr: Buffer.from("") });

    const report = runner.verify();

    expect(report.success).toBe(true);
    expect(mockSpawnSync).toHaveBeenCalledTimes(2);
    expect(mockSpawnSync.mock.calls[0][0]).toBe("python3");
    expect(mockSpawnSync.mock.calls[0][1]).toEqual(["-m", "mypy", "."]);
    expect(mockSpawnSync.mock.calls[1][1]).toEqual(["-m", "pytest", "-v"]);
  });

  test("should fail Python verification if pytest fails", () => {
    const runner = new VerificationRunner("test-dir", "python");

    mockSpawnSync
      .mockReturnValueOnce({ status: 0, stdout: Buffer.from("mypy ok"), stderr: Buffer.from("") })
      .mockReturnValueOnce({ status: 1, stdout: Buffer.from("pytest error"), stderr: Buffer.from("") });

    const report = runner.verify();

    expect(report.success).toBe(false);
    expect(report.testError).toContain("pytest error");
    expect(mockSpawnSync).toHaveBeenCalledTimes(2);
  });
});
