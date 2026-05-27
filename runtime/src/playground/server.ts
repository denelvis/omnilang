import * as http from "http";
import * as fs from "fs";
import * as path from "path";
import { spawnSync } from "child_process";

const PORT = 3000;
const PROJECT_ROOT = path.resolve(__dirname, "../../..");

// Helper to recursively list files
function getFilesRecursive(dir: string, baseDir: string = dir): Array<{ path: string; content: string }> {
  let results: Array<{ path: string; content: string }> = [];
  if (!fs.existsSync(dir)) return results;

  const list = fs.readdirSync(dir);
  for (const file of list) {
    const filePath = path.join(dir, file);
    const stat = fs.statSync(filePath);
    if (stat.isDirectory()) {
      if (file !== "node_modules" && file !== "dist") {
        results = results.concat(getFilesRecursive(filePath, baseDir));
      }
    } else {
      const relPath = path.relative(baseDir, filePath);
      // Only return typescript files, test files, prisma/sql schemas, and mermaid diagrams
      if (relPath.endsWith(".ts") || relPath.endsWith(".prisma") || relPath.endsWith(".sql") || relPath.endsWith(".mmd")) {
        try {
          const content = fs.readFileSync(filePath, "utf8");
          results.push({ path: relPath, content });
        } catch (e) {
          // Ignore
        }
      }
    }
  }
  return results;
}

const server = http.createServer((req, res) => {
  const url = req.url || "/";
  const method = req.method || "GET";

  // Enable CORS
  res.setHeader("Access-Control-Allow-Origin", "*");
  res.setHeader("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
  res.setHeader("Access-Control-Allow-Headers", "Content-Type");

  if (method === "OPTIONS") {
    res.writeHead(204);
    res.end();
    return;
  }

  if (method === "GET" && (url === "/" || url === "/index.html")) {
    let htmlPath = path.join(__dirname, "static", "index.html");
    if (!fs.existsSync(htmlPath)) {
      htmlPath = path.resolve(__dirname, "../../src/playground/static/index.html");
    }
    
    if (fs.existsSync(htmlPath)) {
      res.writeHead(200, { "Content-Type": "text/html" });
      res.end(fs.readFileSync(htmlPath));
    } else {
      res.writeHead(404, { "Content-Type": "text/plain" });
      res.end(`index.html not found at: ${htmlPath}`);
    }
    return;
  }

  if (method === "POST" && url === "/api/compile") {
    let body = "";
    req.on("data", chunk => {
      body += chunk.toString();
    });

    req.on("end", () => {
      try {
        const payload = JSON.parse(body);
        const specContent = payload.spec || "";

        // 1. Write the spec to a temp file in project root
        const cacheDir = path.join(PROJECT_ROOT, ".omni-cache");
        if (!fs.existsSync(cacheDir)) {
          fs.mkdirSync(cacheDir, { recursive: true });
        }
        const tempSpecPath = path.join(cacheDir, "playground_spec.omni");
        fs.writeFileSync(tempSpecPath, specContent, "utf8");

        // 2. Clear previous build directory files to avoid stale outputs in response
        const buildDir = path.join(PROJECT_ROOT, "build");
        if (fs.existsSync(buildDir)) {
          const pathsToClean = [
            path.join(buildDir, "src", "services"),
            path.join(buildDir, "tests"),
            path.join(buildDir, "prisma")
          ];
          for (const p of pathsToClean) {
            if (fs.existsSync(p)) {
              fs.rmSync(p, { recursive: true, force: true });
            }
          }
        }

        // 3. Execute omni build using cargo
        console.log(`[Playground Server] Compiling spec: ${tempSpecPath}`);
        const buildProcess = spawnSync("cargo", ["run", "--bin", "omni", "--", "build", ".omni-cache/playground_spec.omni", "--target", "typescript"], {
          cwd: PROJECT_ROOT,
          stdio: "pipe",
          env: {
            ...process.env,
            OMNI_MOCK_LLM: "true"
          }
        });

        const stdout = buildProcess.stdout ? buildProcess.stdout.toString() : "";
        const stderr = buildProcess.stderr ? buildProcess.stderr.toString() : "";
        const logs = stdout + "\n" + stderr;
        const success = buildProcess.status === 0;

        if (success) {
          // Read all generated files from the build directory
          const files = getFilesRecursive(buildDir);
          res.writeHead(200, { "Content-Type": "application/json" });
          res.end(JSON.stringify({ success: true, logs, files }));
        } else {
          res.writeHead(200, { "Content-Type": "application/json" });
          res.end(JSON.stringify({ success: false, logs, files: [] }));
        }
      } catch (err: any) {
        res.writeHead(500, { "Content-Type": "application/json" });
        res.end(JSON.stringify({ success: false, logs: err.message, files: [] }));
      }
    });
    return;
  }

  res.writeHead(404, { "Content-Type": "text/plain" });
  res.end("Not Found");
});

server.listen(PORT, () => {
  console.log(`⚡ Playground Server running at http://localhost:${PORT}`);
});
