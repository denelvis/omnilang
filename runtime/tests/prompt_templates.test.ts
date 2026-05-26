import * as fs from "fs";
import * as path from "path";
import * as ts from "typescript";
import { getSystemPrompt } from "../src/prompts/codegen";

describe("Prompt Templates", () => {
  const templatesDir = path.resolve(__dirname, "../src/prompts/templates");
  const systemPromptPath = path.join(templatesDir, "system_prompt.md");
  const refImplPath = path.join(templatesDir, "reference_example.ts");
  const refTestPath = path.join(templatesDir, "reference_example.test.ts");

  test("should check that template files exist", () => {
    expect(fs.existsSync(systemPromptPath)).toBe(true);
    expect(fs.existsSync(refImplPath)).toBe(true);
    expect(fs.existsSync(refTestPath)).toBe(true);
  });

  test("should replace placeholders in system prompt correctly", () => {
    const prompt = getSystemPrompt("typescript", "ADDITIONAL_INSTRUCTION");
    expect(prompt).toContain("InventoryService");
    expect(prompt).toContain("addItem");
    expect(prompt).toContain("ADDITIONAL_INSTRUCTION");
    expect(prompt).not.toContain("{{reference_impl}}");
    expect(prompt).not.toContain("{{reference_test}}");
    expect(prompt).not.toContain("{{additions}}");
  });

  test("should verify that reference_example.ts compiles without syntax errors", () => {
    const code = fs.readFileSync(refImplPath, "utf8");
    const sourceFile = ts.createSourceFile(
      "reference_example.ts",
      code,
      ts.ScriptTarget.ES2022,
      true
    );
    // Source file should not contain syntax diagnostics / errors
    const diagnostics = (sourceFile as any).parseDiagnostics || [];
    expect(diagnostics).toHaveLength(0);
  });

  test("should verify that reference_example.test.ts compiles without syntax errors", () => {
    const code = fs.readFileSync(refTestPath, "utf8");
    const sourceFile = ts.createSourceFile(
      "reference_example.test.ts",
      code,
      ts.ScriptTarget.ES2022,
      true
    );
    const diagnostics = (sourceFile as any).parseDiagnostics || [];
    expect(diagnostics).toHaveLength(0);
  });
});
