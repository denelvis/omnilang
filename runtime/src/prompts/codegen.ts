import { SpecIR, ServiceDecl, TypeDecl } from "../types";

export function getSystemPrompt(target: string = "typescript"): string {
  if (target !== "typescript") {
    throw new Error(`Unsupported target: ${target}`);
  }
  return getTypeScriptSystemPrompt();
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
      return `${doc}type ${t.name} = ${JSON.stringify(t.kind)}`;
    })
    .join("\n");

  // Format service spec
  const specDetails = JSON.stringify(service, null, 2);

  const targetInfo = getTargetFileInfo(target, serviceName);

  return `Generate the implementation and tests for the service: "${serviceName}".

Here are the defined Type Definitions for the module:
${types}

Here is the Service Specification details:
${specDetails}

Generate:
1. The implementation file: "${targetInfo.implPath}"
2. The unit test file: "${targetInfo.testPath}"

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

function getTypeScriptSystemPrompt(): string {
  return `You are a Senior TypeScript and Test Engineer.
Your task is to generate a verified TypeScript implementation and matching Jest unit tests based on an OmniLang specification.

You MUST follow these rules:
1. Generate clean, well-typed TypeScript code using modern ES6+ features.
2. Implement all RPC functions defined in the service spec.
3. Validate inputs and enforce preconditions and postconditions.
4. If the service declares invariants, verify them before and after each RPC call.
5. If the service declares a "metrics" block, define and instrument those metrics (counters, gauges, histograms) inside the service. You can initialize them in the constructor and increment/record them at appropriate places in the RPC methods (e.g., tracking attempts, errors, or latency).
6. If the service declares custom error types, throw structured errors with the appropriate type.
7. Write comprehensive Jest unit tests covering all success scenarios and error cases defined in the test blocks. Ensure tests verify that the metrics are correctly invoked/incremented where applicable.
8. For property-based tests (forall blocks), use fast-check to generate arbitrary inputs and verify properties hold.
9. If the specification, type definitions, or fields contain documentation comments (e.g., in the "doc_comment" field or as "///" comments prefixing types), convert them into corresponding JSDoc comments (/** ... */) on the generated TypeScript classes, interfaces, methods, parameters, and properties.
10. In Jest unit tests, when testing for thrown errors, prefer using 'await expect(promise).rejects.toThrow(\'error message\')' instead of try/catch blocks. If you must use a catch block, assert the error type or cast it (e.g., '(error as any).message') to prevent TypeScript compile errors under strict mode where caught errors are of type 'unknown'.
11. Use single quotes for all string literals in the generated TypeScript implementation and tests. Avoid using unescaped double quotes inside code files to ensure the output is valid JSON.
12. Do NOT mock the service class under test (the class you are generating and testing) in the unit test file. Instantiate and test the real service class directly.
13. Use named exports (e.g., 'export class ServiceName') and named imports (e.g., 'import { ServiceName } from "./..."') for all generated files. Do NOT use default exports or default imports.
14. Return your output EXACTLY as a JSON object with the following structure, and do not wrap it in markdown code blocks or add any conversational text.

JSON Structure:
{
  "files": [
    {
      "path": "src/services/<ServiceName>.ts",
      "content": "string containing TypeScript implementation"
    },
    {
      "path": "tests/<ServiceName>.test.ts",
      "content": "string containing Jest unit tests"
    }
  ]
}`;
}
