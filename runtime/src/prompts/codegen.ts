export function getSystemPrompt(): string {
  return `You are a Senior TypeScript and Test Engineer.
Your task is to generate a verified TypeScript implementation and matching Jest unit tests based on an OmniLang specification.

You MUST follow these rules:
1. Generate clean, well-typed TypeScript code using modern ES6+ features.
2. Implement all RPC functions defined in the service spec.
3. Validate inputs and enforce preconditions and postconditions.
4. If the service declares a "metrics" block, define and instrument those metrics (counters, gauges, histograms) inside the service. You can initialize them in the constructor and increment/record them at appropriate places in the RPC methods (e.g., tracking attempts, errors, or latency).
5. Write comprehensive Jest unit tests covering all success scenarios and error cases defined in the test blocks. Ensure tests verify that the metrics are correctly invoked/incremented where applicable.
6. Return your output EXACTLY as a JSON object with the following structure, and do not wrap it in markdown code blocks or add any conversational text.

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

export function getUserPrompt(serviceName: string, ir: any): string {
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

  return `Generate the implementation and tests for the service: "${serviceName}".

Here are the defined Type Definitions for the module:
${types}

Here is the Service Specification details:
${specDetails}

Generate:
1. The implementation file: "src/services/${serviceName}.ts"
2. The unit test file: "tests/${serviceName}.test.ts" using Jest.

Ensure that the unit tests import the implementation from "../src/services/${serviceName}".
Remember to return ONLY the raw JSON string matches the required structure.`;
}
