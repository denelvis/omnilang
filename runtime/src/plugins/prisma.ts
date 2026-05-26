import * as fs from "fs";
import * as path from "path";
import pc from "picocolors";
import { SchemaGeneratorPlugin, resolveTypeRef } from "./base";
import { SpecIR, SchemaDecl, TypeRef, EntityDecl, EntityField, Decorator, IndexDecl, RelationDecl, Expression } from "../types";

export interface PrismaRelationConfig {
  fields: string[];
  references: string[];
}

export type PrismaEntityField = EntityField & {
  relationConfig?: PrismaRelationConfig;
};

export type PrismaEntityDecl = Omit<EntityDecl, "fields"> & {
  fields: PrismaEntityField[];
};

export type PrismaSchemaDecl = Omit<SchemaDecl, "entities"> & {
  entities: PrismaEntityDecl[];
};

export function mapTypeToPrisma(typeRef: TypeRef, ir?: SpecIR): string {
  const resolved = resolveTypeRef(typeRef, ir);
  const name = resolved.name;
  if (name === "Option" && resolved.type_args.length > 0) {
    return mapTypeToPrisma(resolved.type_args[0], ir) + "?";
  }
  if (name === "List" && resolved.type_args.length > 0) {
    return mapTypeToPrisma(resolved.type_args[0], ir) + "[]";
  }

  switch (name) {
    case "UUID": return "String";
    case "String": return "String";
    case "Int": return "Int";
    case "Float": return "Float";
    case "Boolean": return "Boolean";
    case "DateTime": return "DateTime";
    case "Decimal": return "Decimal";
    default: return name;
  }
}

export function formatExpression(expr: Expression): string {
  if ("Literal" in expr) {
    const lit = expr.Literal;
    if (typeof lit === "string") {
      return lit === "Null" ? "null" : lit;
    }
    if ("Int" in lit) return String(lit.Int);
    if ("Float" in lit) return String(lit.Float);
    if ("String" in lit) return `"${lit.String}"`;
    if ("Bool" in lit) return String(lit.Bool);
    if ("Duration" in lit) return `"${lit.Duration}"`;
    if ("Money" in lit) return `"${lit.Money}"`;
    return "";
  }
  if ("Identifier" in expr) {
    return expr.Identifier[0];
  }
  if ("Call" in expr) {
    const argsStr = expr.Call.args.map(formatExpression).join(", ");
    return `${expr.Call.function}(${argsStr})`;
  }
  return "";
}

export function injectRelationFields(schema: PrismaSchemaDecl): void {
  if (!schema.relations) return;
  for (const rel of schema.relations) {
    const { lhs, rel_type, rhs } = rel;
    const lhsEntity = schema.entities.find((e) => e.name === lhs);
    const rhsEntity = schema.entities.find((e) => e.name === rhs);
    if (!lhsEntity || !rhsEntity) continue;

    const getPrimaryKey = (entity: PrismaEntityDecl): PrismaEntityField => {
      const pk = entity.fields.find((f) => f.decorators && f.decorators.some((d) => d.name === "primary"));
      return pk || {
        name: "id",
        ty: { name: "String", type_args: [], union_members: [], intersection_members: [], span: { start: 0, end: 0 } },
        default: null,
        decorators: [],
        doc_comment: null,
        span: { start: 0, end: 0 }
      };
    };
    const lhsPk = getPrimaryKey(lhsEntity);

    if (rel_type === "has_many") {
      const fieldNameLhs = rhs.toLowerCase() + "s";
      if (!lhsEntity.fields.some((f) => f.name === fieldNameLhs)) {
        lhsEntity.fields.push({
          name: fieldNameLhs,
          ty: { name: "List", type_args: [{ name: rhs, type_args: [], union_members: [], intersection_members: [], span: { start: 0, end: 0 } }], union_members: [], intersection_members: [], span: { start: 0, end: 0 } },
          decorators: [],
          doc_comment: null,
          span: { start: 0, end: 0 },
          default: null
        });
      }
      const relationFieldName = lhs.toLowerCase();
      const fkFieldName = lhs.toLowerCase() + "Id";
      if (!rhsEntity.fields.some((f) => f.name === relationFieldName)) {
        rhsEntity.fields.push({
          name: relationFieldName,
          ty: { name: lhs, type_args: [], union_members: [], intersection_members: [], span: { start: 0, end: 0 } },
          decorators: [],
          doc_comment: null,
          span: { start: 0, end: 0 },
          relationConfig: {
            fields: [fkFieldName],
            references: [lhsPk.name]
          },
          default: null
        });
      }
      if (!rhsEntity.fields.some((f) => f.name === fkFieldName)) {
        rhsEntity.fields.push({
          name: fkFieldName,
          ty: lhsPk.ty,
          decorators: [],
          doc_comment: null,
          span: { start: 0, end: 0 },
          default: null
        });
      }
    } else if (rel_type === "has_one") {
      const fieldNameLhs = rhs.toLowerCase();
      if (!lhsEntity.fields.some((f) => f.name === fieldNameLhs)) {
        lhsEntity.fields.push({
          name: fieldNameLhs,
          ty: { name: "Option", type_args: [{ name: rhs, type_args: [], union_members: [], intersection_members: [], span: { start: 0, end: 0 } }], union_members: [], intersection_members: [], span: { start: 0, end: 0 } },
          decorators: [],
          doc_comment: null,
          span: { start: 0, end: 0 },
          default: null
        });
      }
      const relationFieldName = lhs.toLowerCase();
      const fkFieldName = lhs.toLowerCase() + "Id";
      if (!rhsEntity.fields.some((f) => f.name === relationFieldName)) {
        rhsEntity.fields.push({
          name: relationFieldName,
          ty: { name: lhs, type_args: [], union_members: [], intersection_members: [], span: { start: 0, end: 0 } },
          decorators: [],
          doc_comment: null,
          span: { start: 0, end: 0 },
          relationConfig: {
            fields: [fkFieldName],
            references: [lhsPk.name]
          },
          default: null
        });
      }
      if (!rhsEntity.fields.some((f) => f.name === fkFieldName)) {
        rhsEntity.fields.push({
          name: fkFieldName,
          ty: lhsPk.ty,
          decorators: [{ name: "unique", args: [], span: { start: 0, end: 0 } }],
          doc_comment: null,
          span: { start: 0, end: 0 },
          default: null
        });
      }
    }
  }
}

export function generatePrismaSchema(ir: SpecIR): string | null {
  let schemaDecl: SchemaDecl | null = null;
  if (ir.source_file && ir.source_file.declarations) {
    for (const decl of ir.source_file.declarations) {
      if ("Schema" in decl) {
        schemaDecl = decl.Schema;
        break;
      }
    }
  }

  if (!schemaDecl) {
    return null;
  }

  const schema: PrismaSchemaDecl = JSON.parse(JSON.stringify(schemaDecl));
  injectRelationFields(schema);

  let provider = schema.target || "postgresql";
  if (provider.includes(":")) {
    provider = provider.split(":")[1].trim();
  }

  const lines: string[] = [];
  lines.push(`// Generated by OmniLang Compiler. Do not edit manually.`);
  lines.push(``);
  lines.push(`datasource db {`);
  lines.push(`  provider = "${provider}"`);
  lines.push(`  url      = env("DATABASE_URL")`);
  lines.push(`}`);
  lines.push(``);
  lines.push(`generator client {`);
  lines.push(`  provider = "prisma-client-js"`);
  lines.push(`}`);
  lines.push(``);

  for (const entity of schema.entities) {
    lines.push(`model ${entity.name} {`);
    const modelIndexes: string[] = [];

    for (const field of entity.fields) {
      const mappedTy = mapTypeToPrisma(field.ty, ir);
      let decoratorsStr = "";
      let isPrimary = false;

      if (field.decorators) {
        for (const dec of field.decorators) {
          if (dec.name === "primary") {
            isPrimary = true;
          } else if (dec.name === "unique") {
            decoratorsStr += " @unique";
          } else if (dec.name === "updatedAt") {
            decoratorsStr += " @updatedAt";
          } else if (dec.name === "indexed") {
            modelIndexes.push(`@@index([${field.name}])`);
          } else if (dec.name === "default") {
            const argStr = dec.args.map(formatExpression).join(", ");
            decoratorsStr += ` @default(${argStr})`;
          }
        }
      }

      if (isPrimary) {
        if (mappedTy === "Int") {
          decoratorsStr = " @id @default(autoincrement())" + decoratorsStr;
        } else {
          decoratorsStr = " @id @default(uuid())" + decoratorsStr;
        }
      }

      if (field.relationConfig) {
        const fieldsStr = field.relationConfig.fields.join(", ");
        const refsStr = field.relationConfig.references.join(", ");
        decoratorsStr += ` @relation(fields: [${fieldsStr}], references: [${refsStr}])`;
      }

      if (field.default && !decoratorsStr.includes("@default")) {
        decoratorsStr += ` @default(${formatExpression(field.default)})`;
      }

      lines.push(`  ${field.name.padEnd(12)} ${mappedTy}${decoratorsStr}`);
    }

    if (schema.indexes) {
      for (const idx of schema.indexes) {
        if (idx.entity === entity.name) {
          const fieldList = idx.fields.join(", ");
          modelIndexes.push(`@@index([${fieldList}])`);
        }
      }
    }

    for (const idxStr of modelIndexes) {
      lines.push(`  ${idxStr}`);
    }

    lines.push(`}`);
    lines.push(``);
  }

  return lines.join("\n");
}

export class PrismaSchemaGenerator implements SchemaGeneratorPlugin {
  public name = "prisma";

  public supports(target: string): boolean {
    const lower = target.toLowerCase();
    return lower.startsWith("prisma:") || ["postgresql", "mysql", "sqlite", "mongodb", "cockroachdb", "sqlserver"].includes(lower);
  }

  public async generate(ir: SpecIR, outputDir: string, target: string): Promise<void> {
    const prismaContent = generatePrismaSchema(ir);
    if (prismaContent) {
      const prismaDir = path.join(outputDir, "prisma");
      fs.mkdirSync(prismaDir, { recursive: true });
      fs.writeFileSync(path.join(prismaDir, "schema.prisma"), prismaContent);
      console.log(pc.green(`   Generated Prisma schema at ${path.join(prismaDir, "schema.prisma")}`));
    }
  }
}
