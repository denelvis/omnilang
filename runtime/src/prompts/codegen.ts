export function getSystemPrompt(target: string = "typescript"): string {
  switch (target) {
    case "rust":
      return getRustSystemPrompt();
    case "python":
      return getPythonSystemPrompt();
    case "typescript":
    default:
      return getTypeScriptSystemPrompt();
  }
}

export function getUserPrompt(serviceName: string, ir: any, target: string = "typescript"): string {
  // Find the target service in IR
  const service = ir.source_file.declarations.find(
    (d: any) => d.Service && d.Service.name === serviceName
  )?.Service;

  if (!service) {
    throw new Error(`Service ${serviceName} not found in Spec IR AST.`);
  }

  // Format type definitions
  const types = ir.source_file.declarations
    .filter((d: any) => d.Type)
    .map((d: any) => {
      const t = d.Type;
      return `type ${t.name} = ${JSON.stringify(t.kind)}`;
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
  switch (target) {
    case "rust": {
      const snakeName = toSnakeCase(serviceName);
      return {
        implPath: `src/services/${snakeName}.rs`,
        testPath: `tests/${snakeName}_test.rs`,
        extra: `Ensure the test file uses \`use omni_build::services::${snakeName}::*;\` to import from the implementation.\nUse proptest for property-based tests where the spec contains forall/property blocks.`,
      };
    }
    case "python": {
      const snakeName = toSnakeCase(serviceName);
      return {
        implPath: `app/services/${snakeName}.py`,
        testPath: `tests/test_${snakeName}.py`,
        extra: `Ensure the test file imports from \`app.services.${snakeName}\`.\nUse hypothesis for property-based tests where the spec contains forall/property blocks.`,
      };
    }
    case "typescript":
    default:
      return {
        implPath: `src/services/${serviceName}.ts`,
        testPath: `tests/${serviceName}.test.ts`,
        extra: `Ensure that the unit tests import the implementation from "../src/services/${serviceName}".\nUse fast-check for property-based tests where the spec contains forall/property blocks.`,
      };
  }
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
9. Return your output EXACTLY as a JSON object with the following structure, and do not wrap it in markdown code blocks or add any conversational text.

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

function getRustSystemPrompt(): string {
  return `You are a Senior Rust Engineer and Test Specialist.
Your task is to generate a verified Rust implementation and matching tests based on an OmniLang specification.

You MUST follow these rules:
1. Generate clean, idiomatic Rust code using modern Rust features and strong typing.
2. Implement all RPC functions defined in the service spec as methods on a struct.
3. Validate inputs and enforce preconditions using Result return types. Enforce postconditions with debug_assert or explicit checks.
4. If the service declares invariants, implement an invariant check method and call it before/after each public method.
5. If the service declares custom error types, define a proper enum implementing thiserror::Error.
6. Write comprehensive tests covering all success scenarios and error cases defined in the test blocks.
7. For property-based tests (forall blocks), use proptest to generate arbitrary inputs and verify properties hold.
8. Use serde derives for data types that need serialization.
9. Return your output EXACTLY as a JSON object with the following structure.

JSON Structure:
{
  "files": [
    {
      "path": "src/services/<snake_case_name>.rs",
      "content": "string containing Rust implementation"
    },
    {
      "path": "tests/<snake_case_name>_test.rs",
      "content": "string containing Rust tests"
    }
  ]
}`;
}

function getPythonSystemPrompt(): string {
  return `You are a Senior Python Engineer and Test Specialist.
Your task is to generate a verified Python implementation and matching pytest tests based on an OmniLang specification.

You MUST follow these rules:
1. Generate clean, well-typed Python code using type hints and modern Python (3.10+) features.
2. Use pydantic BaseModel for data types and request/response objects.
3. Implement all RPC functions defined in the service spec as methods on a class.
4. Validate inputs and enforce preconditions by raising ValueError. Enforce postconditions with assertions.
5. If the service declares invariants, implement an invariant check method and call it before/after each public method.
6. If the service declares custom error types, define proper exception classes.
7. Write comprehensive pytest tests covering all success scenarios and error cases defined in the test blocks.
8. For property-based tests (forall blocks), use hypothesis to generate arbitrary inputs and verify properties hold.
9. Return your output EXACTLY as a JSON object with the following structure.

JSON Structure:
{
  "files": [
    {
      "path": "app/services/<snake_case_name>.py",
      "content": "string containing Python implementation"
    },
    {
      "path": "tests/test_<snake_case_name>.py",
      "content": "string containing pytest tests"
    }
  ]
}`;
}

function toSnakeCase(name: string): string {
  return name
    .replace(/([A-Z])/g, "_$1")
    .toLowerCase()
    .replace(/^_/, "");
}
