import * as fs from "fs";
import * as path from "path";
import pc from "picocolors";
import { LLMProvider } from "../providers";
import { getSystemPrompt, getUserPrompt } from "../prompts/codegen";
import { SpecIR } from "../types";

export class CodeGenAgent {
  private provider: LLMProvider;

  constructor(provider: LLMProvider) {
    this.provider = provider;
  }

  public async generateService(
    serviceName: string,
    ir: SpecIR,
    outputDir: string,
    target: string = "typescript",
    promptAdditions: string = "",
    model?: string
  ): Promise<{ success: boolean; files: string[] }> {
    console.log(pc.yellow(`   Generating service: ${pc.cyan(serviceName)} [${target}]...`));

    let systemPrompt = getSystemPrompt(target);
    if (promptAdditions) {
      systemPrompt += promptAdditions;
    }
    const userPrompt = getUserPrompt(serviceName, ir, target);

    const response = await this.provider.generateCode(systemPrompt, userPrompt, model);
    const parsed = this.parseResponse(response, serviceName);

    const writtenFiles: string[] = [];

    for (const file of parsed.files) {
      const targetPath = path.join(outputDir, file.path);
      fs.mkdirSync(path.dirname(targetPath), { recursive: true });
      fs.writeFileSync(targetPath, file.content, "utf8");
      
      console.log(`     ${pc.green("✓")} Wrote ${pc.dim(file.path)}`);
      writtenFiles.push(targetPath);
    }

    // For Rust, update mod.rs to include the new service module
    if (target === "rust") {
      this.updateRustModFile(outputDir, serviceName);
    }

    return { success: true, files: writtenFiles };
  }

  private parseResponse(response: string, serviceName: string): { files: Array<{ path: string; content: string }> } {
    let cleanText = response.trim();

    // Try to extract JSON from markdown code block first
    const jsonBlockRegex = /```json\s*([\s\S]*?)\s*```/g;
    const match = jsonBlockRegex.exec(cleanText);
    if (match && match[1]) {
      cleanText = match[1].trim();
    } else {
      // Fallback: search for first '{' and last '}'
      const firstBrace = cleanText.indexOf("{");
      const lastBrace = cleanText.lastIndexOf("}");
      if (firstBrace !== -1 && lastBrace !== -1 && lastBrace > firstBrace) {
        cleanText = cleanText.substring(firstBrace, lastBrace + 1).trim();
      }
    }

    // Try to parse the clean text
    try {
      const parsed = JSON.parse(cleanText);
      this.normalizeResponse(parsed, serviceName);
      this.validateResponseStructure(parsed);
      return parsed;
    } catch (e: any) {
      // Attempt basic JSON recovery for simple hallucination cases (e.g., trailing commas, unescaped braces)
      try {
        const recoveredText = this.attemptJsonRecovery(cleanText);
        const parsed = JSON.parse(recoveredText);
        this.normalizeResponse(parsed, serviceName);
        this.validateResponseStructure(parsed);
        return parsed;
      } catch (recoveryErr: any) {
        console.error(pc.red("Failed to parse JSON response from LLM (even after recovery attempts):"));
        console.error(pc.dim(response));
        throw new Error(`Invalid JSON format from code generator: ${e.message}`);
      }
    }
  }

  private normalizeResponse(parsed: any, serviceName: string): void {
    if (!parsed || typeof parsed !== "object") {
      return;
    }

    // If 'files' array is already present, nothing to do
    if (Array.isArray(parsed.files)) {
      return;
    }

    // Case 1: Look for any other array property that might be the files array
    const arrayKey = Object.keys(parsed).find(k => Array.isArray(parsed[k]));
    if (arrayKey) {
      parsed.files = parsed[arrayKey];
      return;
    }

    // Case 2: Check for implementation/tests key-value objects or strings
    const implKey = Object.keys(parsed).find(k => ["implementation", "impl", "service", "src"].includes(k.toLowerCase()));
    const testKey = Object.keys(parsed).find(k => ["tests", "test", "spec"].includes(k.toLowerCase()));

    if (implKey && testKey) {
      const implVal = parsed[implKey];
      const testVal = parsed[testKey];

      if (implVal && typeof implVal === "object" && testVal && typeof testVal === "object") {
        parsed.files = [
          {
            path: implVal.file || implVal.path || `src/services/${serviceName}.ts`,
            content: implVal.content || ""
          },
          {
            path: testVal.file || testVal.path || `tests/${serviceName}.test.ts`,
            content: testVal.content || ""
          }
        ];
      } else if (typeof implVal === "string" && typeof testVal === "string") {
        parsed.files = [
          {
            path: `src/services/${serviceName}.ts`,
            content: implVal
          },
          {
            path: `tests/${serviceName}.test.ts`,
            content: testVal
          }
        ];
      }
    }
  }

  private validateResponseStructure(parsed: any): void {
    if (!parsed || typeof parsed !== "object") {
      throw new Error("Response is not a JSON object");
    }
    if (!Array.isArray(parsed.files)) {
      throw new Error("Response must contain a 'files' array");
    }
    for (const file of parsed.files) {
      if (typeof file !== "object" || file === null) {
        throw new Error("File entry in response must be an object");
      }
      if (typeof file.path !== "string" || typeof file.content !== "string") {
        throw new Error("File entry must contain 'path' and 'content' as strings");
      }
    }
  }

  private attemptJsonRecovery(text: string): string {
    let fixed = text.trim();
    
    // Remove trailing commas before closing braces/brackets
    fixed = fixed.replace(/,\s*([\]}])/g, "$1");
    
    // If it doesn't end with } but we can count braces and add missing closing braces
    let openBraces = 0;
    let openBrackets = 0;
    let inString = false;
    let escape = false;
    
    for (let i = 0; i < fixed.length; i++) {
      const char = fixed[i];
      if (escape) {
        escape = false;
        continue;
      }
      if (char === "\\") {
        escape = true;
        continue;
      }
      if (char === '"') {
        inString = !inString;
        continue;
      }
      if (!inString) {
        if (char === "{") openBraces++;
        else if (char === "}") openBraces--;
        else if (char === "[") openBrackets++;
        else if (char === "]") openBrackets--;
      }
    }
    
    // If it ends with } and has unclosed brackets, try inserting closing bracket before the last brace
    if (fixed.endsWith("}") && openBraces === 0 && openBrackets > 0) {
      const lastIndex = fixed.lastIndexOf("}");
      const candidate = fixed.substring(0, lastIndex) + "]" + fixed.substring(lastIndex);
      try {
        JSON.parse(candidate);
        return candidate;
      } catch (err) {
        // Fall through
      }
    }
    
    while (openBraces > 0) {
      fixed += "}";
      openBraces--;
    }
    while (openBrackets > 0) {
      fixed += "]";
      openBrackets--;
    }
    
    return fixed;
  }

  private updateRustModFile(outputDir: string, serviceName: string): void {
    const modRsPath = path.join(outputDir, "src", "services", "mod.rs");
    const modName = this.toSnakeCase(serviceName);
    const modLine = `pub mod ${modName};\n`;
    
    if (fs.existsSync(modRsPath)) {
      const content = fs.readFileSync(modRsPath, "utf8");
      if (!content.includes(modLine.trim())) {
        fs.appendFileSync(modRsPath, modLine);
      }
    }
  }

  private toSnakeCase(name: string): string {
    return name
      .replace(/([A-Z])/g, "_$1")
      .toLowerCase()
      .replace(/^_/, "");
  }
}
