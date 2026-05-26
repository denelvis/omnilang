import { SpecIR, TypeRef } from "../types";

export function resolveTypeRef(typeRef: TypeRef, ir?: SpecIR): TypeRef {
  if (!ir || !ir.source_file || !ir.source_file.declarations) {
    return typeRef;
  }
  const name = typeRef.name;
  const typeDecl = ir.source_file.declarations.find(
    (d) => "Type" in d && d.Type.name === name
  );
  if (typeDecl && "Type" in typeDecl && "Alias" in typeDecl.Type.kind) {
    return resolveTypeRef(typeDecl.Type.kind.Alias, ir);
  }
  return typeRef;
}

export interface SchemaGeneratorPlugin {
  name: string;
  supports(target: string): boolean;
  generate(ir: SpecIR, outputDir: string, target: string): Promise<void>;
}

export class SchemaGeneratorRegistry {
  private static plugins: SchemaGeneratorPlugin[] = [];

  public static register(plugin: SchemaGeneratorPlugin): void {
    if (!this.plugins.some((p) => p.name === plugin.name)) {
      this.plugins.push(plugin);
    }
  }

  public static getPluginForTarget(target: string): SchemaGeneratorPlugin | undefined {
    // If the target explicitly specifies a provider (e.g. "sql:postgresql" or "prisma:mysql")
    if (target.includes(":")) {
      const provider = target.split(":")[0].trim().toLowerCase();
      const plugin = this.plugins.find((p) => p.name === provider);
      if (plugin) {
        return plugin;
      }
    }

    // Try checking via supports()
    let found = this.plugins.find((p) => p.supports(target));
    if (found) {
      return found;
    }

    // Default fallback to the first registered plugin (e.g. Prisma)
    return this.plugins[0];
  }

  public static clear(): void {
    this.plugins = [];
  }
}
