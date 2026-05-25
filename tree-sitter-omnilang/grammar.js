module.exports = grammar({
  name: "omnilang",

  extras: $ => [
    /\s/,
    $.comment,
  ],

  conflicts: $ => [
    [$.type_ref, $.expression],
    [$.dotted_name],
  ],

  rules: {
    source_file: $ => seq(
      $.module_declaration,
      repeat($.use_declaration),
      repeat($._declaration)
    ),

    module_declaration: $ => seq(
      "module",
      field("name", $.dotted_name)
    ),

    use_declaration: $ => seq(
      "use",
      choice(
        seq(field("path", $.dotted_name), ".", "*"),
        seq(field("path", $.dotted_name), ".", "{", commaSep($.import_item), "}"),
        field("path", $.dotted_name)
      )
    ),

    import_item: $ => seq(
      field("name", $.identifier),
      optional(seq("as", field("alias", $.identifier)))
    ),

    dotted_name: $ => sep1($.identifier, "."),

    _declaration: $ => choice(
      $.type_declaration,
      $.service_declaration,
      // Phase 1+ blocks parsed as opaque / fallback
      $.component_declaration,
      $.pipeline_declaration,
      $.workflow_declaration,
      $.agent_declaration,
      $.schema_declaration,
      $.policy_declaration
    ),

    // Opaque fallback blocks for Phase 1+
    component_declaration: $ => seq("component", $.identifier, $.block),
    pipeline_declaration: $ => seq("pipeline", $.identifier, $.block),
    workflow_declaration: $ => seq("workflow", $.identifier, $.block),
    agent_declaration: $ => seq("agent", $.identifier, $.block),
    schema_declaration: $ => seq("schema", $.identifier, $.block),
    policy_declaration: $ => seq("policy", $.identifier, $.block),

    type_declaration: $ => seq(
      "type",
      field("name", $.identifier),
      "=",
      field("kind", $._type_kind)
    ),

    _type_kind: $ => choice(
      $.struct_type,
      $.enum_type,
      $.refined_type,
      $.type_ref
    ),

    struct_type: $ => seq(
      "struct",
      $.block
    ),

    enum_type: $ => seq(
      "enum",
      "{",
      repeat($.enum_variant),
      "}"
    ),

    enum_variant: $ => seq(
      field("name", $.identifier),
      optional(seq("(", commaSep($.field), ")"))
    ),

    refined_type: $ => seq(
      field("base", $.type_ref),
      $.block
    ),

    field: $ => seq(
      field("name", $.identifier),
      ":",
      field("type", $.type_ref),
      optional(seq("=", field("default", $.expression)))
    ),

    type_ref: $ => seq(
      field("name", $.identifier),
      optional(seq("<", commaSep($.type_ref), ">"))
    ),

    service_declaration: $ => seq(
      "service",
      field("name", $.identifier),
      $.service_block
    ),

    service_block: $ => seq(
      "{",
      repeat($._service_member),
      "}"
    ),

    _service_member: $ => choice(
      $.goal_section,
      $.constraints_section,
      $.depends_on_section,
      $.rpc_declaration,
      $.budget_section,
      $.metrics_section
    ),

    goal_section: $ => seq("goal", ":", $.string_literal),

    constraints_section: $ => seq(
      "constraints",
      ":",
      repeat1(seq("-", $.constraint_item))
    ),

    constraint_item: $ => seq(
      field("name", $.identifier),
      optional(seq("(", commaSep($.constraint_arg), ")"))
    ),

    constraint_arg: $ => seq(
      optional(seq(field("name", $.identifier), ":")),
      field("value", $.expression)
    ),

    depends_on_section: $ => seq(
      "depends_on",
      ":",
      repeat1(seq("-", field("dependency", $.dotted_name)))
    ),

    budget_section: $ => seq(
      "budget",
      ":",
      $.block
    ),

    metrics_section: $ => seq(
      "metrics",
      ":",
      repeat1(seq("-", $.metric_declaration))
    ),

    metric_declaration: $ => seq(
      field("kind", $.metric_kind),
      field("name", $.identifier),
      optional($.block)
    ),

    metric_kind: $ => choice(
      "counter",
      "gauge",
      "histogram"
    ),

    rpc_declaration: $ => seq(
      "rpc",
      field("name", $.identifier),
      $.rpc_block
    ),

    rpc_block: $ => seq(
      "{",
      repeat($._rpc_member),
      "}"
    ),

    _rpc_member: $ => choice(
      $.inputs_section,
      $.outputs_section,
      $.preconditions_section,
      $.postconditions_section,
      $.errors_section,
      $.tests_section
    ),

    inputs_section: $ => seq("inputs", ":", repeat1($.field)),
    outputs_section: $ => seq("outputs", ":", repeat1($.field)),
    preconditions_section: $ => seq("preconditions", ":", repeat1(seq("-", $.expression))),
    postconditions_section: $ => seq("postconditions", ":", repeat1(seq("-", $.expression))),

    errors_section: $ => seq(
      "errors",
      ":",
      repeat1($.error_definition)
    ),

    error_definition: $ => seq(
      "-",
      field("name", $.identifier),
      optional(seq("(", commaSep($.field), ")"))
    ),

    tests_section: $ => seq(
      "tests",
      ":",
      repeat1(seq("-", $._test_block))
    ),

    _test_block: $ => choice(
      $.scenario_block,
      $.property_block
    ),

    scenario_block: $ => seq(
      "scenario",
      ":",
      field("name", $.string_literal),
      repeat1(choice(
        seq("given", ":", sep1($.expression, ",")),
        seq("when", ":", sep1($.expression, ",")),
        seq("expect", ":", sep1($.expression, ",")),
        seq("expect_error", ":", $.identifier)
      ))
    ),

    property_block: $ => seq(
      "property",
      ":",
      field("name", $.string_literal),
      repeat1(choice(
        seq("forall", ":", commaSep($.quantifier)),
        seq("given", ":", sep1($.expression, ",")),
        seq("when", ":", sep1($.expression, ",")),
        seq("assert", ":", sep1($.expression, ","))
      ))
    ),

    quantifier: $ => seq(
      field("name", $.identifier),
      "in",
      field("generator", $.expression)
    ),

    block: $ => seq(
      "{",
      repeat($._block_item),
      "}"
    ),

    _block_item: $ => choice(
      $.field,
      seq($.identifier, ":", $.expression),
      seq("-", $.expression)
    ),

    expression: $ => choice(
      $.binary_expression,
      $.unary_expression,
      $.call_expression,
      $.field_expression,
      $.list_expression,
      $.identifier,
      $._literal
    ),

    binary_expression: $ => prec.left(choice(
      seq($.expression, "==", $.expression),
      seq($.expression, "!=", $.expression),
      seq($.expression, "<", $.expression),
      seq($.expression, ">", $.expression),
      seq($.expression, "<=", $.expression),
      seq($.expression, ">=", $.expression),
      seq($.expression, "&&", $.expression),
      seq($.expression, "||", $.expression),
      seq($.expression, "in", $.expression),
      seq($.expression, "not in", $.expression),
      seq($.expression, "..", $.expression),
      seq($.expression, "..<", $.expression)
    )),

    unary_expression: $ => prec(9, seq(
      choice("!", "-"),
      $.expression
    )),

    call_expression: $ => seq(
      field("function", $.identifier),
      "(",
      commaSep($.expression),
      ")"
    ),

    field_expression: $ => prec(10, seq(
      $.expression,
      ".",
      $.identifier
    )),

    list_expression: $ => seq(
      "[",
      commaSep($.expression),
      "]"
    ),

    _literal: $ => choice(
      $.integer_literal,
      $.float_literal,
      $.string_literal,
      $.boolean_literal,
      $.duration_literal,
      $.money_literal,
      $.percentage_literal,
      $.null_literal
    ),

    integer_literal: $ => /\d+/,
    float_literal: $ => /\d+\.\d+/,
    string_literal: $ => /"([^"\\]|\\.)*"/,
    boolean_literal: $ => choice("true", "false"),
    duration_literal: $ => /\d+(ms|s|m|h|d|w|y|min)/,
    money_literal: $ => /\$\d+(\.\d{2})?/,
    percentage_literal: $ => /\d+%/,
    null_literal: $ => "null",

    identifier: $ => /[a-zA-Z_][a-zA-Z0-9_]*/,

    comment: $ => token(choice(
      seq("//", /.*/),
      seq("/*", /[^*]*\*+([^/*][^*]*\*+)*/, "/")
    ))
  }
});

function sep1(rule, separator) {
  return seq(rule, repeat(seq(separator, rule)));
}

function commaSep(rule) {
  return optional(sep1(rule, ","));
}
