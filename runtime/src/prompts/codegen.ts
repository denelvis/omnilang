import * as fs from "fs";
import * as path from "path";
import { SpecIR, ServiceDecl, TypeDecl, TypeRef, TypeMapping } from "../types";

export function getSystemPrompt(target: string = "typescript", promptAdditions: string = ""): string {
  if (target !== "typescript") {
    throw new Error(`Unsupported target: ${target}`);
  }
  return getTypeScriptSystemPrompt(promptAdditions);
}

export function getUserPrompt(serviceName: string, ir: SpecIR, target: string = "typescript"): string {
  if (target !== "typescript") {
    throw new Error(`Unsupported target: ${target}`);
  }
  // Find the target service in IR
  const serviceDecl = ir.source_file.declarations.find(
    (d) => "Service" in d && d.Service.name === serviceName
  );
  const service = serviceDecl && "Service" in serviceDecl ? serviceDecl.Service : undefined;

  if (!service) {
    throw new Error(`Service ${serviceName} not found in Spec IR AST.`);
  }

  // Format type definitions
  const types = ir.source_file.declarations
    .filter((d): d is { Type: TypeDecl } => "Type" in d)
    .map((d) => {
      const t = d.Type;
      const doc = t.doc_comment
        ? t.doc_comment.split("\n").map((line: string) => `/// ${line}`).join("\n") + "\n"
        : "";
      return `${doc}${formatTypeDecl(t, ir.type_mappings)}`;
    })
    .join("\n\n");

  // Format service spec
  const specDetails = JSON.stringify(service, null, 2);

  const targetInfo = getTargetFileInfo(target, serviceName);

  return `Generate the implementation and tests for the service: "${serviceName}".

Here are the defined Type Definitions for the module:
${types}

Here is the Service Specification details:
${specDetails}

Please write the complete TypeScript source code for both the service implementation and its corresponding Jest unit tests.
- The implementation code must be generated for the path: "${targetInfo.implPath}"
- The unit test code must be generated for the path: "${targetInfo.testPath}"

${targetInfo.extra}
Remember to return ONLY the raw JSON string matching the required structure.`;
}

function getTargetFileInfo(target: string, serviceName: string): { implPath: string; testPath: string; extra: string } {
  if (target !== "typescript") {
    throw new Error(`Unsupported target: ${target}`);
  }
  return {
    implPath: `src/services/${serviceName}.ts`,
    testPath: `tests/${serviceName}.test.ts`,
    extra: `Ensure that the unit tests import the implementation from "../src/services/${serviceName}".\nUse fast-check for property-based tests where the spec contains forall/property blocks.`,
  };
}

function getTypeScriptSystemPrompt(promptAdditions: string = ""): string {
  let templatesDir = path.join(__dirname, "templates");
  let systemPromptPath = path.join(templatesDir, "system_prompt.md");
  if (!fs.existsSync(systemPromptPath)) {
    templatesDir = path.resolve(__dirname, "../../src/prompts/templates");
    systemPromptPath = path.join(templatesDir, "system_prompt.md");
  }
  const refImplPath = path.join(templatesDir, "reference_example.ts");
  const refTestPath = path.join(templatesDir, "reference_example.test.ts");

  if (!fs.existsSync(systemPromptPath) || !fs.existsSync(refImplPath) || !fs.existsSync(refTestPath)) {
    throw new Error(`Prompt template files not found in: ${templatesDir}`);
  }

  let systemPrompt = fs.readFileSync(systemPromptPath, "utf8");
  const refImpl = fs.readFileSync(refImplPath, "utf8");
  const refTest = fs.readFileSync(refTestPath, "utf8");

  const additionsText = promptAdditions ? `\n\n${promptAdditions}\n` : "";

  systemPrompt = systemPrompt
    .replace("{{reference_impl}}", refImpl.trim())
    .replace("{{reference_test}}", refTest.trim())
    .replace("{{additions}}", additionsText);

  return systemPrompt;
}

function formatTypeRef(ref: TypeRef, typeMappings?: TypeMapping[]): string {
  if (typeMappings) {
    const mapping = typeMappings.find(m => m.omni_type === ref.name);
    if (mapping) {
      return mapping.target_type;
    }
  }

  if (ref.name === "String" || ref.name === "Email" || ref.name === "URL" || ref.name === "UUID") {
    return "string";
  }
  if (ref.name === "Int" || ref.name === "Float" || ref.name === "Decimal" || ref.name === "Money" || ref.name === "Duration") {
    return "number";
  }
  if (ref.name === "Bool") {
    return "boolean";
  }
  if (ref.name === "DateTime" || ref.name === "Date") {
    return "Date";
  }
  if (ref.name === "Bytes") {
    return "Buffer";
  }
  if (ref.name === "Void") {
    return "void";
  }
  if (ref.name === "List") {
    const arg = ref.type_args[0] ? formatTypeRef(ref.type_args[0], typeMappings) : "any";
    return `${arg}[]`;
  }
  if (ref.name === "Option") {
    const arg = ref.type_args[0] ? formatTypeRef(ref.type_args[0], typeMappings) : "any";
    return `${arg} | null`;
  }

  // Handle generic type arguments
  if (ref.type_args.length > 0) {
    const args = ref.type_args.map(arg => formatTypeRef(arg, typeMappings)).join(", ");
    return `${ref.name}<${args}>`;
  }
  
  return ref.name;
}

export function formatTypeDecl(t: TypeDecl, typeMappings?: TypeMapping[]): string {
  const name = t.name;
  const kind = t.kind;

  if ("Alias" in kind) {
    return `export type ${name} = ${formatTypeRef(kind.Alias, typeMappings)};`;
  }

  if ("Struct" in kind) {
    const fields = kind.Struct.fields.map(f => {
      const doc = f.doc_comment ? `  /** ${f.doc_comment} */\n` : "";
      return `${doc}  ${f.name}: ${formatTypeRef(f.ty, typeMappings)};`;
    }).join("\n");
    return `export interface ${name} {\n${fields}\n}`;
  }

  if ("Enum" in kind) {
    const variants = kind.Enum.variants.map(v => {
      return `  ${v.name} = '${v.name}',`;
    }).join("\n");
    return `export enum ${name} {\n${variants}\n}`;
  }

  if ("Refined" in kind) {
    const base = kind.Refined.base ? formatTypeRef(kind.Refined.base, typeMappings) : "any";
    return `export type ${name} = ${base}; // Refined type with constraints`;
  }

  return `export type ${name} = any;`;
}
