/**
 * OMWF (OmniLang Wire Format)
 *
 * STATUS: FROZEN EXPERIMENT — do not use in production.
 *
 * This module was an experiment in building a custom token-efficient
 * serialization format. It is preserved for reference but NOT used
 * in the build pipeline. The runtime uses minified JSON instead.
 *
 * Reasons for freezing:
 * - Lossy: drops field definitions, test bodies, RPC details
 * - Non-standard: custom parser with no formal spec
 * - Marginal gains: "savings" were measured vs pretty-printed JSON
 * - Fragile: any schema change breaks the parser
 * - LLMs work great with JSON natively
 *
 * @deprecated Use minified JSON via serializeIR() from ../wire.ts instead.
 */

// ── Serializer: SpecIR → OMWF ────────────────────────────
/** @deprecated */
export function serialize(ir: any): string {
  const lines: string[] = [];

  lines.push(`@OMWF/1.0`);
  lines.push(`@module ${ir.module || "unknown"}`);
  if (ir.target) lines.push(`@target ${ir.target}`);
  lines.push(``);

  if (ir.types && ir.types.length > 0) {
    lines.push(`## TYPES`);
    for (const type of ir.types) {
      lines.push(`  ${type.name} :: ${type.kind}${type.field_count ? ` [${type.field_count} fields]` : ""}`);
      if (type.generator) {
        lines.push(`    @gen format=${type.generator.format || "none"}`);
      }
    }
    lines.push(``);
  }

  if (ir.services && ir.services.length > 0) {
    lines.push(`## SERVICES`);
    for (const svc of ir.services) {
      lines.push(`  ${svc.name}:`);
      if (svc.goal) lines.push(`    goal: "${svc.goal}"`);
      if (svc.rpc_names && svc.rpc_names.length > 0) {
        lines.push(`    rpcs: ${svc.rpc_names.join(", ")}`);
      }
      if (svc.constraint_names && svc.constraint_names.length > 0) {
        lines.push(`    constraints: ${svc.constraint_names.join(", ")}`);
      }
      if (svc.metric_names && svc.metric_names.length > 0) {
        lines.push(`    metrics: ${svc.metric_names.join(", ")}`);
      }
      lines.push(`    tests: ${svc.test_count || 0}`);
    }
    lines.push(``);
  }

  if (ir.stats) {
    lines.push(`## STATS`);
    const s = ir.stats;
    lines.push(`  types=${s.total_types} services=${s.total_services} rpcs=${s.total_rpcs}`);
    lines.push(`  tests=${s.total_tests} constraints=${s.total_constraints}`);
  }

  return lines.join("\n");
}

/** @deprecated */
export function deserialize(omwf: string): any {
  const lines = omwf.split("\n");
  const result: any = {
    version: "1.0",
    module: "",
    target: "",
    types: [],
    services: [],
    stats: {},
  };

  let currentSection = "";

  for (const line of lines) {
    const trimmed = line.trim();

    if (trimmed.startsWith("@OMWF/")) {
      result.version = trimmed.replace("@OMWF/", "");
      continue;
    }
    if (trimmed.startsWith("@module ")) {
      result.module = trimmed.replace("@module ", "");
      continue;
    }
    if (trimmed.startsWith("@target ")) {
      result.target = trimmed.replace("@target ", "");
      continue;
    }

    if (trimmed.startsWith("## ")) {
      currentSection = trimmed.replace("## ", "").toLowerCase();
      continue;
    }

    if (trimmed === "") continue;

    switch (currentSection) {
      case "types": {
        const typeMatch = trimmed.match(/^(\w+)\s*::\s*(\w+)(?:\s*\[(\d+)\s*fields\])?/);
        if (typeMatch) {
          result.types.push({
            name: typeMatch[1],
            kind: typeMatch[2],
            field_count: typeMatch[3] ? parseInt(typeMatch[3]) : 0,
          });
        }
        break;
      }
      case "services": {
        const svcMatch = trimmed.match(/^(\w+):$/);
        if (svcMatch) {
          result.services.push({
            name: svcMatch[1],
            goal: null,
            rpc_names: [],
            constraint_names: [],
            metric_names: [],
            test_count: 0,
          });
        } else if (result.services.length > 0) {
          const current = result.services[result.services.length - 1];
          const kvMatch = trimmed.match(/^(\w+):\s*(.+)$/);
          if (kvMatch) {
            const [, key, value] = kvMatch;
            switch (key) {
              case "goal":
                current.goal = value.replace(/^"|"$/g, "");
                break;
              case "rpcs":
                current.rpc_names = value.split(",").map((s: string) => s.trim());
                break;
              case "constraints":
                current.constraint_names = value.split(",").map((s: string) => s.trim());
                break;
              case "metrics":
                current.metric_names = value.split(",").map((s: string) => s.trim());
                break;
              case "tests":
                current.test_count = parseInt(value) || 0;
                break;
            }
          }
        }
        break;
      }
      case "stats": {
        const pairs = trimmed.match(/(\w+)=(\d+)/g);
        if (pairs) {
          for (const pair of pairs) {
            const [key, val] = pair.split("=");
            result.stats[key] = parseInt(val);
          }
        }
        break;
      }
    }
  }

  return result;
}

/** @deprecated */
export function jsonToOmwf(json: string): string {
  const parsed = JSON.parse(json);
  return serialize(parsed);
}

/** @deprecated */
export function omwfToJson(omwf: string): string {
  const parsed = deserialize(omwf);
  return JSON.stringify(parsed, null, 2);
}

/** @deprecated */
export function estimateTokenSavings(ir: any): {
  jsonTokens: number;
  omwfTokens: number;
  savingsPercent: number;
} {
  const jsonStr = JSON.stringify(ir, null, 2);
  const omwfStr = serialize(ir);

  const jsonTokens = Math.ceil(jsonStr.length / 4);
  const omwfTokens = Math.ceil(omwfStr.length / 4);
  const savingsPercent = Math.round(((jsonTokens - omwfTokens) / jsonTokens) * 100);

  return { jsonTokens, omwfTokens, savingsPercent };
}
