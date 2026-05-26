import { SpecIR, ServiceDecl, TypeDecl, TypeRef } from "../types";

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
      return `${doc}${formatTypeDecl(t)}`;
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
  const additionsText = promptAdditions ? `\n\n${promptAdditions}\n` : "";
  return `You are a Senior TypeScript and Test Engineer.
Your task is to generate a verified TypeScript implementation and matching Jest unit tests based on an OmniLang specification.

You MUST follow these rules:
1. Generate clean, well-typed TypeScript code using modern ES6+ features. Map all OmniLang built-in types to native lowercase TypeScript types:
   - 'String', 'Email', 'URL', 'UUID' map to lowercase 'string'.
   - 'Int', 'Float', 'Decimal', 'Money' map to lowercase 'number'.
   - 'Bool' maps to lowercase 'boolean'.
   - 'List<T>' maps to 'T[]'.
   - 'Option<T>' maps to 'T | null'.
   - **CRITICAL**: Do NOT use capitalized type names like 'String', 'Int', or 'Bool' in TypeScript signatures; always use lowercase 'string', 'number', 'boolean'. Do NOT import them.
2. Implement all RPC functions defined in the service spec.
3. Validate inputs and enforce preconditions and postconditions. **CRITICAL**: Always check preconditions on inputs (e.g., checking if amount <= 0, input format validation) at the very beginning of the RPC method, BEFORE performing any state lookups (like fetching from a Map). This ensures input validation errors are thrown first.
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
14. **Custom Types Imports & Re-exports**:
   - In implementation ('src/services/<ServiceName>.ts'): import custom types from '../types' (e.g., 'import { AccountId, Account } from \'../types\''). **You MUST also re-export all of them** using named exports (e.g., 'export { AccountId, Account };') so that consumer modules and tests can import them directly from the service file if needed.
   - In tests ('tests/<ServiceName>.test.ts'): you can import custom types either from '../src/types' or directly from the service module (e.g., 'import { PaymentService, AccountId } from \'../src/services/PaymentService\'').
   - **CRITICAL**: Do NOT import standard primitive/built-in types (such as String, Int, Bool, Money, Float, Decimal, Email, URL, UUID, Option, List) from the types file. Use TypeScript's native primitives (string, number, boolean, array, etc.) directly.
15. **No Private Property Access**:
   - Never access private class properties or methods in unit tests (e.g. accessing 'paymentService.accounts' or private 'paymentService.getAccount' will fail compilation).
   - **CRITICAL**: You MUST declare any internal state storage properties (like a Map or array of records, e.g., 'public accounts = new Map<AccountId, Account>()') and any helper/retrieval methods (e.g., 'public getAccount(...)', 'public addAccount(...)') as **public**. Do NOT make them private. This is required so tests can set up initial states and verify transitions using the public API.
16. **Proper Jest & Fast-Check Usage**:
   - Always declare Jest tests using standard Jest globals like 'describe(...)', 'test(...)', or 'it(...)'.
   - **CRITICAL**: There is NO 'fc.test(...)' function. Do NOT call 'fc.test'.
   - **CRITICAL**: 'fast-check' does NOT export functions/types like 'arbitraryNumber', 'arbitraryString', 'arbitraryInteger', etc. Do NOT import them. Only import 'fc' (e.g., 'import fc from \'fast-check\'') and use its standard generator helpers like 'fc.nat()', 'fc.integer()', 'fc.string()', 'fc.boolean()'.
   - To write property-based tests, call 'fc.assert(fc.property(...))' or 'fc.assert(fc.asyncProperty(...))' inside a standard Jest 'test(\'...\', () => { ... })' block.

Here is a reference example demonstrating the correct structure, imports, type exports, public state declaration, and testing:

Example:
For a spec with type ItemId = String, type Item = struct { id: ItemId, qty: Int }, and service InventoryService:

src/services/InventoryService.ts should look like:
\`\`\`typescript
import { ItemId, Item } from '../types';
export { ItemId, Item };

export class InventoryService {
  public items = new Map<ItemId, Item>();

  public addItem(id: ItemId, qty: number): number {
    if (qty <= 0) {
      throw new Error('Quantity must be positive');
    }
    let item = this.items.get(id);
    if (!item) {
      item = { id, qty: 0 };
      this.items.set(id, item);
    }
    item.qty += qty;
    return item.qty;
  }
}
\`\`\`

tests/InventoryService.test.ts should look like:
\`\`\`typescript
import { InventoryService } from '../src/services/InventoryService';
import { ItemId, Item } from '../src/types';
import fc from 'fast-check';

describe('InventoryService', () => {
  let service: InventoryService;

  beforeEach(() => {
    service = new InventoryService();
  });

  test('addItem increases quantity', () => {
    const id: ItemId = 'item-1';
    service.items.set(id, { id, qty: 10 });
    const result = service.addItem(id, 5);
    expect(result).toBe(15);
    expect(service.items.get(id)?.qty).toBe(15);
  });

  test('addItem property-based verification', () => {
    fc.assert(
      fc.property(fc.string(), fc.integer({ min: 1 }), (id, qty) => {
        const localService = new InventoryService();
        localService.addItem(id, qty);
        expect(localService.items.get(id)?.qty).toBe(qty);
      })
    );
  });
});
\`\`\`

${additionsText}
17. Return your output EXACTLY as a JSON object with the following structure, and do not wrap it in markdown code blocks or add any conversational text. The 'content' fields MUST contain the actual full source code of the implementation and tests. Do NOT output a JSON that just lists the paths.

JSON Structure:
{
  "files": [
    {
      "path": "src/services/<ServiceName>.ts",
      "content": "// Put the full, complete TypeScript implementation code here as a single string"
    },
    {
      "path": "tests/<ServiceName>.test.ts",
      "content": "// Put the full, complete Jest unit test code here as a single string"
    }
  ]
}`;
}

function formatTypeRef(ref: TypeRef): string {
  if (ref.name === "String" || ref.name === "Email" || ref.name === "URL" || ref.name === "UUID") {
    return "string";
  }
  if (ref.name === "Int" || ref.name === "Float" || ref.name === "Decimal" || ref.name === "Money") {
    return "number";
  }
  if (ref.name === "Bool") {
    return "boolean";
  }
  if (ref.name === "List") {
    const arg = ref.type_args[0] ? formatTypeRef(ref.type_args[0]) : "any";
    return `${arg}[]`;
  }
  if (ref.name === "Option") {
    const arg = ref.type_args[0] ? formatTypeRef(ref.type_args[0]) : "any";
    return `${arg} | null`;
  }

  // Handle generic type arguments
  if (ref.type_args.length > 0) {
    const args = ref.type_args.map(formatTypeRef).join(", ");
    return `${ref.name}<${args}>`;
  }
  
  return ref.name;
}

export function formatTypeDecl(t: TypeDecl): string {
  const name = t.name;
  const kind = t.kind;

  if ("Alias" in kind) {
    return `export type ${name} = ${formatTypeRef(kind.Alias)};`;
  }

  if ("Struct" in kind) {
    const fields = kind.Struct.fields.map(f => {
      const doc = f.doc_comment ? `  /** ${f.doc_comment} */\n` : "";
      return `${doc}  ${f.name}: ${formatTypeRef(f.ty)};`;
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
    const base = kind.Refined.base ? formatTypeRef(kind.Refined.base) : "any";
    return `export type ${name} = ${base}; // Refined type with constraints`;
  }

  return `export type ${name} = any;`;
}
