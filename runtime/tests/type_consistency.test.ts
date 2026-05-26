import { formatTypeDecl } from "../src/prompts/codegen";
import { TypeDecl, Span, TypeRef, Field } from "../src/types";

describe("Type Consistency Verification", () => {
  const dummySpan: Span = { start: 0, end: 0 };
  
  const createTypeRef = (name: string): TypeRef => ({
    name,
    type_args: [],
    union_members: [],
    intersection_members: [],
    span: dummySpan,
  });

  test("should format Alias types correctly", () => {
    const aliasDecl: TypeDecl = {
      name: "UserId",
      type_params: [],
      kind: { Alias: createTypeRef("UUID") },
      visibility: "Public",
      doc_comment: "The unique identifier of a user",
      span: dummySpan,
    };

    const formatted = formatTypeDecl(aliasDecl);
    expect(formatted).toBe("export type UserId = string;");
  });

  test("should format Struct types correctly", () => {
    const fields: Field[] = [
      {
        name: "id",
        ty: createTypeRef("UserId"),
        default: null,
        doc_comment: "Unique ID",
        span: dummySpan,
      },
      {
        name: "email",
        ty: createTypeRef("String"), // formatTypeRef maps String to string
        default: null,
        doc_comment: null,
        span: dummySpan,
      }
    ];

    const structDecl: TypeDecl = {
      name: "User",
      type_params: [],
      kind: { Struct: { fields, span: dummySpan } },
      visibility: "Public",
      doc_comment: null,
      span: dummySpan,
    };

    const formatted = formatTypeDecl(structDecl);
    expect(formatted).toContain("export interface User {");
    expect(formatted).toContain("id: UserId;");
    expect(formatted).toContain("email: string;");
  });

  test("should format Enum types correctly", () => {
    const enumDecl: TypeDecl = {
      name: "UserRole",
      type_params: [],
      kind: {
        Enum: {
          variants: [
            { name: "Admin", fields: [], span: dummySpan },
            { name: "User", fields: [], span: dummySpan }
          ],
          span: dummySpan
        }
      },
      visibility: "Public",
      doc_comment: null,
      span: dummySpan,
    };

    const formatted = formatTypeDecl(enumDecl);
    expect(formatted).toContain("export enum UserRole {");
    expect(formatted).toContain("Admin = 'Admin',");
    expect(formatted).toContain("User = 'User',");
  });

  test("should format Refined types correctly", () => {
    const refinedDecl: TypeDecl = {
      name: "DepositAmount",
      type_params: [],
      kind: {
        Refined: {
          base: createTypeRef("Money"),
          constraints: [],
          span: dummySpan
        }
      },
      visibility: "Public",
      doc_comment: null,
      span: dummySpan,
    };

    const formatted = formatTypeDecl(refinedDecl);
    expect(formatted).toBe("export type DepositAmount = number; // Refined type with constraints");
  });
});
