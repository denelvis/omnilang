import * as fs from "fs";
import * as path from "path";
import pc from "picocolors";

export interface DocGeneratorOptions {
  irPath: string;
  outputDir: string;
}

export class DocGenerator {
  private irPath: string;
  private outputDir: string;

  constructor(options: DocGeneratorOptions) {
    this.irPath = options.irPath;
    this.outputDir = path.resolve(options.outputDir);
  }

  public async generate(): Promise<void> {
    // 1. Load Spec IR JSON
    const irContent = fs.readFileSync(this.irPath, "utf8");
    const ir = JSON.parse(irContent);

    // Ensure output directory exists
    fs.mkdirSync(this.outputDir, { recursive: true });

    // 2. Generate OpenAPI Spec
    const openapi = this.buildOpenAPISpec(ir);
    const openapiPath = path.join(this.outputDir, "openapi.json");
    fs.writeFileSync(openapiPath, JSON.stringify(openapi, null, 2));
    console.log(`   - Generated OpenAPI: ${pc.cyan(openapiPath)}`);

    // 3. Generate Incident Response Runbook
    const runbook = this.buildRunbook(ir);
    const runbookPath = path.join(this.outputDir, "runbook.md");
    fs.writeFileSync(runbookPath, runbook);
    console.log(`   - Generated Runbook: ${pc.cyan(runbookPath)}`);

    // 4. Generate Interactive HTML Documentation
    const html = this.buildHTMLDocs(ir, openapi, runbook);
    const htmlPath = path.join(this.outputDir, "index.html");
    fs.writeFileSync(htmlPath, html);
    console.log(`   - Generated HTML Docs: ${pc.cyan(htmlPath)}`);
  }

  private buildOpenAPISpec(ir: any): any {
    const paths: any = {};
    const schemas: any = {};

    // Retrieve declarations
    const declarations = ir.source_file?.declarations || [];

    // Simple Type Schemas
    for (const decl of declarations) {
      if (decl.Type) {
        const typeDecl = decl.Type;
        if (typeDecl.kind?.Struct) {
          const properties: any = {};
          const required: string[] = [];
          for (const field of typeDecl.kind.Struct.fields || []) {
            properties[field.name] = {
              type: this.mapTypeToOpenAPI(field.ty?.name),
              description: `Type: ${field.ty?.name}`
            };
            required.push(field.name);
          }
          schemas[typeDecl.name] = {
            type: "object",
            properties,
            required
          };
        } else if (typeDecl.kind?.Enum) {
          schemas[typeDecl.name] = {
            type: "string",
            enum: (typeDecl.kind.Enum.variants || []).map((v: any) => v.name)
          };
        }
      }
    }

    // Build Paths from Services & RPCs
    for (const decl of declarations) {
      if (decl.Service) {
        const service = decl.Service;
        for (const rpc of service.rpcs || []) {
          const pathName = `/api/${service.name}/${rpc.name}`;
          
          // Request schema definition
          const reqSchemaName = `${service.name}_${rpc.name}_Request`;
          const reqProperties: any = {};
          const reqRequired: string[] = [];
          for (const field of rpc.inputs || []) {
            reqProperties[field.name] = {
              type: this.mapTypeToOpenAPI(field.ty?.name),
              description: `Type: ${field.ty?.name}`
            };
            reqRequired.push(field.name);
          }
          schemas[reqSchemaName] = {
            type: "object",
            properties: reqProperties,
            required: reqRequired
          };

          // Response schema definition
          const resSchemaName = `${service.name}_${rpc.name}_Response`;
          const resProperties: any = {};
          const resRequired: string[] = [];
          for (const field of rpc.outputs || []) {
            resProperties[field.name] = {
              type: this.mapTypeToOpenAPI(field.ty?.name),
              description: `Type: ${field.ty?.name}`
            };
            resRequired.push(field.name);
          }
          schemas[resSchemaName] = {
            type: "object",
            properties: resProperties,
            required: resRequired
          };

          paths[pathName] = {
            post: {
              summary: rpc.name,
              description: `Invokes the RPC ${rpc.name} of ${service.name}.`,
              operationId: `${service.name}_${rpc.name}`,
              requestBody: {
                required: true,
                content: {
                  "application/json": {
                    schema: {
                      $ref: `#/components/schemas/${reqSchemaName}`
                    }
                  }
                }
              },
              responses: {
                "200": {
                  description: "Successful response",
                  content: {
                    "application/json": {
                      schema: {
                        $ref: `#/components/schemas/${resSchemaName}`
                      }
                    }
                  }
                },
                "400": {
                  description: "Precondition failed or invalid inputs"
                },
                "500": {
                  description: "Internal error or postcondition failed"
                }
              }
            }
          };
        }
      }
    }

    return {
      openapi: "3.0.0",
      info: {
        title: `OmniLang Service API: ${ir.module_path?.join(".") || "Spec"}`,
        version: "1.0.0",
        description: `Auto-generated OpenAPI spec from OmniLang specifications.`
      },
      paths,
      components: {
        schemas
      }
    };
  }

  private buildRunbook(ir: any): string {
    let md = `# Incident Response & Service Constraints Runbook\n\n`;
    md += `This document lists runtime constraints, performance SLAs, and troubleshooting runbooks for the **${ir.module_path?.join(".") || "System"}** module.\n\n`;

    const declarations = ir.source_file?.declarations || [];
    for (const decl of declarations) {
      if (decl.Service) {
        const service = decl.Service;
        md += `## Service: ${service.name}\n\n`;
        md += `**Goal:** ${service.goal || "No goal specified."}\n\n`;

        if (service.constraints && service.constraints.length > 0) {
          md += `### Service-Level Constraints\n\n`;
          for (const c of service.constraints) {
            md += `- **Constraint:** \`${c.name}\`\n`;
            if (c.args && c.args.length > 0) {
              md += `  - Parameters: ` + c.args.map((a: any) => `${a.name || ""}: ${a.value?.Literal || "expr"}`).join(", ") + `\n`;
            }
          }
          md += `\n`;
        }

        md += `### RPC Operations & SLOs\n\n`;
        for (const rpc of service.rpcs || []) {
          md += `#### RPC: \`${rpc.name}\`\n\n`;
          
          if (rpc.constraints && rpc.constraints.length > 0) {
            md += `##### Constraints & SLOs\n`;
            for (const c of rpc.constraints) {
              md += `- \`${c.name}\`\n`;
            }
            md += `\n`;
          }

          if (rpc.preconditions && rpc.preconditions.length > 0) {
            md += `##### Preconditions\n`;
            for (const p of rpc.preconditions) {
              md += `- \`${JSON.stringify(p)}\`\n`;
            }
            md += `\n`;
          }

          if (rpc.postconditions && rpc.postconditions.length > 0) {
            md += `##### Postconditions\n`;
            for (const p of rpc.postconditions) {
              md += `- \`${JSON.stringify(p)}\`\n`;
            }
            md += `\n`;
          }

          // Incident runbook section
          md += `##### 🚨 Incident Response & Mitigation for \`${rpc.name}\`\n\n`;
          md += `1. **Symptom:** Latency/SLO warnings or Precondition errors on \`${rpc.name}\`.\n`;
          md += `2. **Mitigation steps:**\n`;
          md += `   - Inspect logs for inputs violating defined preconditions.\n`;
          md += `   - Check downstream service health status if latency exceeds bounds.\n`;
          md += `   - Implement circuit-breaking or rate limiting overrides if throughput spike is observed.\n\n`;
        }
      }
    }

    return md;
  }

  private buildHTMLDocs(ir: any, openapi: any, runbook: string): string {
    const services = ir.services || [];
    const moduleName = ir.module_path?.join(".") || "Spec";

    // Build lists for HTML templates
    const servicesListHTML = services.map((s: any) => `
      <div class="card service-card">
        <h3>${s.name}</h3>
        <p class="goal">${s.goal ? `<strong>Goal:</strong> ${s.goal}` : "No goal described."}</p>
        <div class="meta-row">
          <span><strong>RPCs:</strong> ${s.rpc_count}</span>
          <span><strong>Constraints:</strong> ${s.constraint_count}</span>
          <span><strong>Confidence:</strong> <span class="badge ${s.confidence.toLowerCase()}">${s.confidence}</span></span>
        </div>
        <div class="spec-section">
          <h4>RPC Endpoints:</h4>
          <ul>
            ${(s.rpc_names || []).map((name: string) => `<li><code>POST /api/${s.name}/${name}</code></li>`).join("")}
          </ul>
        </div>
        <div class="spec-section">
          <h4>Constraints Applied:</h4>
          <div class="tags">
            ${(s.constraint_names || []).map((name: string) => `<span class="tag">${name}</span>`).join("")}
          </div>
        </div>
      </div>
    `).join("");

    const schemaDeclarations = (ir.source_file?.declarations || []).filter((d: any) => d.Schema);
    const schemasListHTML = schemaDeclarations.map((d: any) => {
      const s = d.Schema;
      return `
        <div class="card schema-card">
          <h3>Schema: ${s.name}</h3>
          <p><strong>Goal:</strong> ${s.goal || "None"}</p>
          <p><strong>Target Database:</strong> <code>${s.target || "postgresql"}</code></p>
          
          <h4>Entities:</h4>
          <div class="entities-grid">
            ${(s.entities || []).map((ent: any) => `
              <div class="entity-item">
                <h5>${ent.name}</h5>
                <ul>
                  ${(ent.fields || []).map((f: any) => `
                    <li><strong>${f.name}</strong>: <code>${f.ty?.name}</code></li>
                  `).join("")}
                </ul>
              </div>
            `).join("")}
          </div>
        </div>
      `;
    }).join("");

    // Simple markdown to HTML replacement for runbook snippet
    const runbookHTML = runbook
      .replace(/# (.*)/g, "<h1>$1</h1>")
      .replace(/## (.*)/g, "<h2>$1</h2>")
      .replace(/### (.*)/g, "<h3>$1</h3>")
      .replace(/#### (.*)/g, "<h4>$1</h4>")
      .replace(/##### (.*)/g, "<h5>$1</h5>")
      .replace(/\- \*\*(.*)\*\*:(.*)/g, "<li><strong>$1</strong>: $2</li>")
      .replace(/\- (.*)/g, "<li>$1</li>")
      .replace(/`([^`]+)`/g, "<code>$1</code>")
      .replace(/\n\n/g, "<p></p>");

    return `<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>${moduleName} - Spec Dashboard</title>
  <link rel="preconnect" href="https://fonts.googleapis.com">
  <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
  <link href="https://fonts.googleapis.com/css2?family=Outfit:wght@300;400;600;800&family=JetBrains+Mono:wght@400;700&display=swap" rel="stylesheet">
  <style>
    :root {
      --bg: #090b10;
      --surface: #141824;
      --border: #232a3e;
      --text: #e2e8f0;
      --text-muted: #94a3b8;
      --primary: #6366f1;
      --primary-hover: #4f46e5;
      --accent: #10b981;
      --confidence-high: #10b981;
      --confidence-speculative: #f59e0b;
      --confidence-verified: #3b82f6;
    }

    * {
      box-sizing: border-box;
      margin: 0;
      padding: 0;
    }

    body {
      background-color: var(--bg);
      color: var(--text);
      font-family: 'Outfit', sans-serif;
      line-height: 1.6;
      display: flex;
      min-height: 100vh;
    }

    aside {
      width: 280px;
      background-color: var(--surface);
      border-right: 1px solid var(--border);
      padding: 2.5rem 1.5rem;
      display: flex;
      flex-direction: column;
      gap: 2rem;
      position: fixed;
      height: 100vh;
      overflow-y: auto;
    }

    .logo {
      font-size: 1.5rem;
      font-weight: 800;
      letter-spacing: -0.05em;
      background: linear-gradient(135deg, #a78bfa, #6366f1);
      -webkit-background-clip: text;
      -webkit-text-fill-color: transparent;
    }

    .nav-links {
      display: flex;
      flex-direction: column;
      gap: 0.5rem;
      list-style: none;
    }

    .nav-links button {
      background: none;
      border: none;
      color: var(--text-muted);
      text-align: left;
      font-size: 1rem;
      font-weight: 600;
      padding: 0.75rem 1rem;
      border-radius: 8px;
      cursor: pointer;
      width: 100%;
      transition: all 0.2s ease;
    }

    .nav-links button.active, .nav-links button:hover {
      color: var(--text);
      background-color: var(--border);
    }

    main {
      margin-left: 280px;
      flex: 1;
      padding: 3rem 4rem;
      max-width: 1200px;
    }

    header {
      margin-bottom: 3rem;
    }

    h1 {
      font-size: 2.5rem;
      font-weight: 800;
      letter-spacing: -0.03em;
      margin-bottom: 0.5rem;
    }

    .subtitle {
      color: var(--text-muted);
      font-size: 1.1rem;
    }

    .tab-content {
      display: none;
    }

    .tab-content.active {
      display: block;
    }

    .card {
      background-color: var(--surface);
      border: 1px solid var(--border);
      border-radius: 12px;
      padding: 2rem;
      margin-bottom: 1.5rem;
      box-shadow: 0 4px 20px -2px rgba(0, 0, 0, 0.3);
    }

    h3 {
      font-size: 1.5rem;
      margin-bottom: 0.75rem;
      color: #fff;
    }

    p.goal {
      margin-bottom: 1.25rem;
      font-size: 1.05rem;
    }

    .meta-row {
      display: flex;
      gap: 1.5rem;
      margin-bottom: 1.5rem;
      font-size: 0.9rem;
      color: var(--text-muted);
    }

    .badge {
      padding: 0.25rem 0.6rem;
      border-radius: 6px;
      font-weight: 700;
      font-size: 0.8rem;
      text-transform: uppercase;
    }

    .badge.high {
      background-color: rgba(16, 185, 129, 0.15);
      color: var(--confidence-high);
    }

    .badge.speculative {
      background-color: rgba(245, 158, 11, 0.15);
      color: var(--confidence-speculative);
    }

    .badge.verified {
      background-color: rgba(59, 130, 246, 0.15);
      color: var(--confidence-verified);
    }

    .spec-section {
      margin-bottom: 1.25rem;
    }

    h4 {
      font-size: 1.1rem;
      margin-bottom: 0.5rem;
      color: var(--text-muted);
      font-weight: 600;
    }

    ul {
      list-style: inside square;
      padding-left: 0.5rem;
    }

    li {
      margin-bottom: 0.4rem;
    }

    code {
      font-family: 'JetBrains Mono', monospace;
      background-color: rgba(0, 0, 0, 0.3);
      padding: 0.1rem 0.4rem;
      border-radius: 4px;
      font-size: 0.9em;
      color: #f472b6;
    }

    .tags {
      display: flex;
      flex-wrap: wrap;
      gap: 0.5rem;
    }

    .tag {
      background-color: var(--border);
      border: 1px solid var(--border);
      padding: 0.25rem 0.65rem;
      border-radius: 6px;
      font-size: 0.85rem;
      font-weight: 600;
      color: var(--text);
    }

    .entities-grid {
      display: grid;
      grid-template-columns: repeat(auto-fill, minmax(250px, 1fr));
      gap: 1.5rem;
      margin-top: 1rem;
    }

    .entity-item {
      background-color: rgba(0, 0, 0, 0.2);
      border: 1px solid var(--border);
      border-radius: 8px;
      padding: 1.25rem;
    }

    .entity-item h5 {
      font-size: 1.1rem;
      margin-bottom: 0.5rem;
      color: #fff;
    }

    .entity-item ul {
      list-style: none;
      padding-left: 0;
    }

    .entity-item li {
      font-size: 0.9rem;
      margin-bottom: 0.25rem;
    }

    pre {
      font-family: 'JetBrains Mono', monospace;
      background-color: #05070a;
      padding: 1.5rem;
      border-radius: 12px;
      border: 1px solid var(--border);
      overflow-x: auto;
      color: #34d399;
      font-size: 0.9rem;
    }

    /* Runbook Styling */
    .runbook-container h2 {
      margin-top: 2rem;
      margin-bottom: 1rem;
      border-bottom: 1px solid var(--border);
      padding-bottom: 0.5rem;
    }

    .runbook-container h3 {
      margin-top: 1.5rem;
      margin-bottom: 0.75rem;
    }

    .runbook-container p {
      margin-bottom: 1rem;
    }
  </style>
</head>
<body>
  <aside>
    <div class="logo">OmniLang Docs</div>
    <ul class="nav-links">
      <li><button onclick="showTab('services')" id="btn-services" class="active">Services</button></li>
      <li><button onclick="showTab('schemas')" id="btn-schemas">Database Schemas</button></li>
      <li><button onclick="showTab('openapi')" id="btn-openapi">OpenAPI Spec</button></li>
      <li><button onclick="showTab('runbook')" id="btn-runbook">Incident Runbook</button></li>
    </ul>
  </aside>

  <main>
    <header>
      <h1 id="title-header">Module: ${moduleName}</h1>
      <div class="subtitle">Auto-generated system documentation & SLAs</div>
    </header>

    <section id="tab-services" class="tab-content active">
      ${servicesListHTML || "<p>No services found in this module.</p>"}
    </section>

    <section id="tab-schemas" class="tab-content">
      ${schemasListHTML || "<p>No database schemas defined in this module.</p>"}
    </section>

    <section id="tab-openapi" class="tab-content">
      <div class="card">
        <h3>OpenAPI 3.0.0 Specification</h3>
        <p style="margin-bottom: 1.5rem;">Below is the generated REST API specification for integration purposes.</p>
        <pre><code>${JSON.stringify(openapi, null, 2)}</code></pre>
      </div>
    </section>

    <section id="tab-runbook" class="tab-content runbook-container">
      <div class="card">
        ${runbookHTML}
      </div>
    </section>
  </main>

  <script>
    function showTab(tabId) {
      document.querySelectorAll('.tab-content').forEach(el => {
        el.classList.remove('active');
      });
      document.querySelectorAll('.nav-links button').forEach(el => {
        el.classList.remove('active');
      });
      document.getElementById('tab-' + tabId).classList.add('active');
      document.getElementById('btn-' + tabId).classList.add('active');
    }
  </script>
</body>
</html>
`;
  }

  private mapTypeToOpenAPI(type: string): string {
    switch (type) {
      case "Int":
        return "integer";
      case "Float":
        return "number";
      case "Boolean":
      case "Bool":
        return "boolean";
      default:
        return "string";
    }
  }
}
