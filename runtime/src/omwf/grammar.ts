/**
 * OMWF Constrained Decoding Grammar — generates BNF-like grammars
 * for constrained decoding with vLLM, llama.cpp, or Outlines.
 *
 * Ensures LLM outputs conform to expected OMWF structure.
 */

export interface GrammarOptions {
  /** Grammar format: 'bnf', 'regex', or 'json_schema' */
  format: "bnf" | "regex" | "json_schema";
  /** Which sections to constrain */
  sections: ("files" | "service" | "test")[];
}

/**
 * Generate a constrained decoding grammar from a spec IR.
 * This ensures the LLM's output is parseable and follows the expected format.
 */
export function generateGrammar(ir: any, options: GrammarOptions): string {
  switch (options.format) {
    case "bnf":
      return generateBNF(ir, options.sections);
    case "regex":
      return generateRegex(ir, options.sections);
    case "json_schema":
      return generateJsonSchema(ir, options.sections);
    default:
      throw new Error(`Unsupported grammar format: ${options.format}`);
  }
}

function generateBNF(ir: any, sections: string[]): string {
  const rules: string[] = [];

  rules.push(`# OMWF Constrained Decoding Grammar (BNF)`);
  rules.push(`# Generated for module: ${ir.module || "unknown"}`);
  rules.push(``);

  if (sections.includes("files")) {
    rules.push(`root ::= file_response`);
    rules.push(`file_response ::= '{"files":[' file_list ']}' `);
    rules.push(`file_list ::= file_entry (',' file_entry)*`);
    rules.push(`file_entry ::= '{"path":"' filepath '","content":"' code_content '"}'`);
    rules.push(`filepath ::= [a-zA-Z0-9_/.-]+`);
    rules.push(`code_content ::= [^"]*`);
  }

  if (sections.includes("service")) {
    rules.push(``);
    rules.push(`# Service implementation structure`);
    rules.push(`service_impl ::= imports service_class exports`);
    rules.push(`imports ::= (import_line newline)*`);
    rules.push(`import_line ::= 'import' ws '{' identifier_list '}' ws 'from' ws string_literal ';'`);
    rules.push(`service_class ::= 'export' ws 'class' ws identifier ws '{' method_list '}'`);
    rules.push(`method_list ::= (method newline)*`);
    rules.push(`method ::= 'async' ws identifier '(' params ')' ':' ws 'Promise<' type '>' ws '{' body '}'`);
  }

  if (sections.includes("test")) {
    rules.push(``);
    rules.push(`# Test file structure`);
    rules.push(`test_file ::= imports describe_block`);
    rules.push(`describe_block ::= 'describe(' string_literal ',' ws '()' ws '=>' ws '{' it_blocks '})'`);
    rules.push(`it_blocks ::= (it_block newline)*`);
    rules.push(`it_block ::= 'it(' string_literal ',' ws 'async' ws '()' ws '=>' ws '{' test_body '})'`);
  }

  rules.push(``);
  rules.push(`# Common rules`);
  rules.push(`ws ::= [ \\t]*`);
  rules.push(`newline ::= '\\n'`);
  rules.push(`identifier ::= [a-zA-Z_][a-zA-Z0-9_]*`);
  rules.push(`identifier_list ::= identifier (',' ws identifier)*`);
  rules.push(`string_literal ::= '"' [^"]* '"' | "'" [^']* "'"`);
  rules.push(`type ::= identifier ('<' type_list '>')? | identifier '[]'`);
  rules.push(`type_list ::= type (',' ws type)*`);
  rules.push(`params ::= (param (',' ws param)*)?`);
  rules.push(`param ::= identifier ':' ws type`);
  rules.push(`body ::= [^}]*`);
  rules.push(`test_body ::= [^}]*`);
  rules.push(`exports ::= ('export' ws '{' identifier_list '}' ';')?`);

  return rules.join("\n");
}

function generateRegex(_ir: any, sections: string[]): string {
  const patterns: string[] = [];

  if (sections.includes("files")) {
    patterns.push(`# File response pattern`);
    patterns.push(`^\\{"files":\\[(?:\\{"path":"[\\w\\/.-]+","content":"[^"]*"\\},?)+\\]\\}$`);
  }

  return patterns.join("\n");
}

function generateJsonSchema(ir: any, sections: string[]): string {
  const schema: any = {
    $schema: "http://json-schema.org/draft-07/schema#",
    title: "OMWF Response",
    description: `Constrained output schema for module ${ir.module || "unknown"}`,
  };

  if (sections.includes("files")) {
    schema.type = "object";
    schema.required = ["files"];
    schema.properties = {
      files: {
        type: "array",
        items: {
          type: "object",
          required: ["path", "content"],
          properties: {
            path: { type: "string", pattern: "^[\\w/.-]+$" },
            content: { type: "string" },
          },
        },
        minItems: 1,
      },
    };
  }

  return JSON.stringify(schema, null, 2);
}

/**
 * Export all OMWF utilities as a namespace.
 */
export { serialize, deserialize, jsonToOmwf, omwfToJson, estimateTokenSavings } from "./serializer";
