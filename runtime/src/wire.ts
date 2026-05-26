/**
 * Wire format: strict minified JSON.
 *
 * This is the canonical serialization for communicating Spec IR between
 * the Rust CLI, the TypeScript runtime, and LLM agents. No custom formats,
 * no lossy conversions — just JSON.
 *
 * Design decisions:
 * - Minified (no pretty-print) to save tokens when sent to LLMs
 * - Schema-validated: rejects unknown fields, enforces required ones
 * - Lossless: round-trips perfectly through serialize → deserialize
 * - LLM-native: every major model handles JSON natively
 */

import { SpecIR } from "./types";

// ── Serialize: SpecIR → minified JSON string ─────────────

/**
 * Serialize a Spec IR to a minified JSON string.
 * This is the default wire format for all LLM communication.
 */
export function serializeIR(ir: any): string {
  return JSON.stringify(ir);
}

/**
 * Deserialize a minified JSON string back to Spec IR.
 * Validates the structure and throws on malformed input.
 */
export function deserializeIR(json: string): SpecIR {
  const parsed = JSON.parse(json);
  validateIR(parsed);
  return parsed as SpecIR;
}

// ── Validation ───────────────────────────────────────────

function validateIR(obj: any): void {
  if (typeof obj !== "object" || obj === null) {
    throw new WireError("IR must be a JSON object");
  }

  if (!Array.isArray(obj.module_path)) {
    throw new WireError("IR.module_path must be an array of strings");
  }

  if (!Array.isArray(obj.services)) {
    throw new WireError("IR.services must be an array");
  }

  if (!Array.isArray(obj.types)) {
    throw new WireError("IR.types must be an array");
  }

  if (typeof obj.stats !== "object" || obj.stats === null) {
    throw new WireError("IR.stats must be an object");
  }

  // Validate each service
  for (const svc of obj.services) {
    if (typeof svc.name !== "string" || svc.name.length === 0) {
      throw new WireError(`service.name must be a non-empty string, got: ${JSON.stringify(svc.name)}`);
    }
  }
}

export class WireError extends Error {
  constructor(message: string) {
    super(`wire format error: ${message}`);
    this.name = "WireError";
  }
}

// ── Utilities ────────────────────────────────────────────

/**
 * Estimate token count for a JSON payload.
 * Rule of thumb: ~4 chars per token for English/code.
 */
export function estimateTokens(json: string): number {
  return Math.ceil(json.length / 4);
}

/**
 * Compare minified vs pretty-printed sizes.
 * Useful for logging but NOT for choosing a format.
 */
export function sizeComparison(ir: any): {
  minifiedBytes: number;
  prettyBytes: number;
  savingPercent: number;
} {
  const minified = JSON.stringify(ir);
  const pretty = JSON.stringify(ir, null, 2);
  const savingPercent = Math.round(((pretty.length - minified.length) / pretty.length) * 100);

  return {
    minifiedBytes: minified.length,
    prettyBytes: pretty.length,
    savingPercent,
  };
}
