#!/usr/bin/env node
// npm wrapper for OmniLang CLI binary
// This script downloads and runs the pre-built OmniLang binary

const { execFileSync } = require("child_process");
const path = require("path");
const fs = require("fs");
const os = require("os");

function getBinaryPath() {
  const binDir = path.join(__dirname);
  const platform = os.platform();
  const arch = os.arch();

  let binaryName = "omni";
  if (platform === "win32") binaryName = "omni.exe";

  const binaryPath = path.join(binDir, binaryName);
  if (fs.existsSync(binaryPath)) {
    return binaryPath;
  }

  // Fallback: try system PATH
  return "omni";
}

try {
  const binary = getBinaryPath();
  const args = process.argv.slice(2);
  const result = execFileSync(binary, args, {
    stdio: "inherit",
    env: process.env,
  });
} catch (err) {
  if (err.status !== undefined) {
    process.exit(err.status);
  }
  console.error("Failed to run OmniLang CLI:", err.message);
  console.error("Try installing manually: curl -sSL https://omnilang.dev/install.sh | sh");
  process.exit(1);
}
