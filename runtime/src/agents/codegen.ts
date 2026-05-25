import * as fs from "fs";
import * as path from "path";
import pc from "picocolors";
import { LLMProvider } from "../providers/anthropic";
import { getSystemPrompt, getUserPrompt } from "../prompts/codegen";

export class CodeGenAgent {
  private provider: LLMProvider;

  constructor(provider: LLMProvider) {
    this.provider = provider;
  }

  public async generateService(
    serviceName: string,
    ir: any,
    outputDir: string
  ): Promise<{ success: boolean; files: string[] }> {
    console.log(pc.yellow(`   Generating service: ${pc.cyan(serviceName)}...`));

    const systemPrompt = getSystemPrompt();
    const userPrompt = getUserPrompt(serviceName, ir);

    const response = await this.provider.generateCode(systemPrompt, userPrompt);
    const parsed = this.parseResponse(response);

    const writtenFiles: string[] = [];

    for (const file of parsed.files) {
      const targetPath = path.join(outputDir, file.path);
      fs.mkdirSync(path.dirname(targetPath), { recursive: true });
      fs.writeFileSync(targetPath, file.content, "utf8");
      
      console.log(`     ${pc.green("✓")} Wrote ${pc.dim(file.path)}`);
      writtenFiles.push(targetPath);
    }

    return { success: true, files: writtenFiles };
  }

  private parseResponse(response: string): { files: Array<{ path: string; content: string }> } {
    let cleanText = response.trim();

    // Remove markdown code block wrappers if Claude added them
    if (cleanText.startsWith("```json")) {
      cleanText = cleanText.substring(7);
    } else if (cleanText.startsWith("```")) {
      cleanText = cleanText.substring(3);
    }

    if (cleanText.endsWith("```")) {
      cleanText = cleanText.substring(0, cleanText.length - 3);
    }

    cleanText = cleanText.trim();

    try {
      return JSON.parse(cleanText);
    } catch (e: any) {
      console.error(pc.red("Failed to parse JSON response from LLM:"));
      console.error(pc.dim(response));
      throw new Error(`Invalid JSON format from code generator: ${e.message}`);
    }
  }
}
