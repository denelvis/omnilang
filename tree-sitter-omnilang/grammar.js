module.exports = grammar({
  name: "omnilang",

  extras: $ => [
    /\s/,
    $.comment,
  ],

  conflicts: $ => [
    [$.type_ref, $.expression],
    [$.dotted_name],
    [$.policy_rule],
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
      $.policy_declaration,
      $.constraint_declaration
    ),

    // Opaque fallback blocks for Phase 1+
    component_declaration: $ => seq(
      "component",
      field("name", $.identifier),
      "{",
      repeat($._component_member),
      "}"
    ),

    _component_member: $ => choice(
      $.goal_section,
      $.props_section,
      $.state_section,
      $.events_section,
      $.slots_section,
      $.style_guide_section,
      $.visual_spec_section,
      $.tests_section,
      $.constraints_section
    ),

    props_section: $ => seq("props", ":", repeat1($.field)),
    state_section: $ => seq("state", ":", repeat1($.field)),
    slots_section: $ => seq("slots", ":", repeat1($.field)),
    style_guide_section: $ => seq("style_guide", ":", choice($.string_literal, $.identifier)),

    events_section: $ => seq(
      "events",
      ":",
      repeat1(seq("-", $.event_definition))
    ),
    event_definition: $ => seq(
      field("name", $.identifier),
      optional(seq("(", commaSep($.field), ")"))
    ),

    visual_spec_section: $ => seq(
      "visual_spec",
      ":",
      repeat1(seq("-", field("spec", $.visual_spec_item)))
    ),
    visual_spec_item: $ => repeat1($._visual_spec_token),
    _visual_spec_token: $ => choice(
      $.identifier,
      $.string_literal,
      $.integer_literal,
      $.float_literal,
      $.percentage_literal,
      $.duration_literal,
      $.money_literal,
      "--",
      ":",
      "=",
      ",",
      ".",
      "(",
      ")",
      "<",
      ">"
    ),

    pipeline_declaration: $ => seq(
      "pipeline",
      field("name", $.identifier),
      "{",
      repeat($._pipeline_member),
      "}"
    ),

    _pipeline_member: $ => choice(
      $.goal_section,
      $.source_section,
      $.stages_section,
      $.sink_section,
      $.constraints_section,
      $.schedule_section,
      $.tests_section
    ),

    source_section: $ => seq("source", ":", repeat1($.config_entry)),
    sink_section: $ => seq("sink", ":", repeat1($.config_entry)),
    schedule_section: $ => seq("schedule", ":", $.string_literal),

    config_entry: $ => seq(
      field("key", $.identifier),
      ":",
      field("value", $.expression)
    ),

    stages_section: $ => seq(
      "stages",
      ":",
      repeat1($.pipeline_stage)
    ),
    pipeline_stage: $ => seq(
      "-",
      repeat1($.config_entry)
    ),

    workflow_declaration: $ => seq(
      "workflow",
      field("name", $.identifier),
      "{",
      repeat($._workflow_member),
      "}"
    ),

    _workflow_member: $ => choice(
      $.goal_section,
      $.states_section,
      $.transitions_section,
      $.constraints_section,
      $.tests_section
    ),

    states_section: $ => seq(
      "states",
      ":",
      repeat1(field("state", $.identifier))
    ),

    transitions_section: $ => seq(
      "transitions",
      ":",
      repeat1($.workflow_transition)
    ),

    workflow_transition: $ => seq(
      field("from", choice($.identifier, "*")),
      "->",
      field("to", $.identifier),
      ":",
      repeat($._transition_member)
    ),

    _transition_member: $ => choice(
      seq("trigger", ":", field("trigger", $.identifier)),
      seq("guard", ":", field("guard", $.expression)),
      seq("action", ":", field("action", sep1($.identifier, ","))),
      seq("timeout", ":", field("timeout", $.workflow_timeout))
    ),

    workflow_timeout: $ => seq(
      field("duration", $.expression),
      "->",
      field("target_state", $.identifier)
    ),

    agent_declaration: $ => seq(
      "agent",
      field("name", $.identifier),
      "{",
      repeat($._agent_member),
      "}"
    ),

    _agent_member: $ => choice(
      $.goal_section,
      $.capabilities_section,
      $.boundaries_section,
      $.tools_section,
      $.model_section,
      $.budget_section,
      $.tests_section
    ),

    capabilities_section: $ => seq(
      "capabilities",
      ":",
      repeat1(seq("-", field("capability", $.identifier)))
    ),

    boundaries_section: $ => seq(
      "boundaries",
      ":",
      repeat1(seq("-", $.agent_boundary))
    ),

    agent_boundary: $ => seq(
      field("kind", choice("must", "cannot")),
      ":",
      field("expr", $.expression)
    ),

    tools_section: $ => seq(
      "tools",
      ":",
      repeat1(seq("-", $.agent_tool))
    ),

    agent_tool: $ => seq(
      field("name", $.identifier),
      "(",
      commaSep($.agent_tool_param),
      ")"
    ),

    agent_tool_param: $ => seq(
      field("direction", choice("input", "output")),
      ":",
      field("type", $.type_ref)
    ),

    model_section: $ => seq(
      "model",
      ":",
      repeat1($.config_entry)
    ),

    schema_declaration: $ => seq(
      "schema",
      field("name", $.identifier),
      "{",
      repeat($._schema_member),
      "}"
    ),

    _schema_member: $ => choice(
      $.goal_section,
      $.target_section,
      $.entity_declaration,
      $.relations_section,
      $.indexes_section,
      $.constraints_section
    ),

    target_section: $ => seq("target", ":", field("target", $.identifier)),

    entity_declaration: $ => seq(
      "entity",
      field("name", $.identifier),
      "{",
      repeat($.entity_field),
      "}"
    ),

    entity_field: $ => seq(
      field("name", $.identifier),
      ":",
      field("type", $.type_ref),
      optional(seq("=", field("default", $.expression))),
      repeat($.decorator)
    ),

    decorator: $ => seq(
      "@",
      field("name", $.identifier),
      optional(seq("(", commaSep($.expression), ")"))
    ),

    relations_section: $ => seq(
      "relations",
      ":",
      repeat1(seq("-", $.relation_definition))
    ),

    relation_definition: $ => seq(
      field("lhs", $.identifier),
      field("rel_type", $.identifier),
      field("rhs", $.identifier),
      optional(seq("(", commaSep($.config_entry), ")"))
    ),

    indexes_section: $ => seq(
      "indexes",
      ":",
      repeat1(seq("-", $.index_definition))
    ),

    index_definition: $ => seq(
      field("entity", $.identifier),
      "(",
      commaSep($.identifier),
      ")",
      optional(seq(
        choice("if", "where"),
        field("where", $.expression)
      ))
    ),

    policy_declaration: $ => seq(
      "policy",
      field("name", $.identifier),
      "{",
      repeat($._policy_member),
      "}"
    ),

    _policy_member: $ => choice(
      $.description_section,
      $.scope_section,
      $.rules_section
    ),

    description_section: $ => seq("description", ":", $.string_literal),
    scope_section: $ => seq("scope", ":", $.identifier),

    rules_section: $ => seq(
      "rules",
      ":",
      repeat1(seq("-", $.policy_rule))
    ),

    policy_rule: $ => seq(
      field("condition", $.policy_condition),
      ":",
      repeat1(seq("-", $.policy_clause))
    ),

    policy_condition: $ => repeat1($._policy_condition_token),
    _policy_condition_token: $ => choice(
      $.identifier,
      $.integer_literal,
      $.float_literal,
      $.string_literal
    ),

    policy_clause: $ => choice(
      $.policy_action_clause,
      $.policy_simple_clause
    ),

    policy_action_clause: $ => seq(
      field("verb", $.identifier),
      ":",
      field("value", $.expression)
    ),

    policy_simple_clause: $ => repeat1($._policy_simple_token),
    _policy_simple_token: $ => choice(
      $.identifier,
      $.integer_literal,
      $.float_literal,
      $.string_literal,
      "+",
      "*",
      "/"
    ),

    constraint_declaration: $ => seq(
      "constraint",
      field("name", $.identifier),
      "{",
      repeat($._constraint_decl_member),
      "}"
    ),

    _constraint_decl_member: $ => choice(
      $.requires_section,
      $.verification_section
    ),

    requires_section: $ => seq(
      "requires",
      ":",
      repeat1(seq("-", $.constraint_item))
    ),

    verification_section: $ => seq(
      "verification",
      ":",
      repeat1($.verification_entry)
    ),

    verification_entry: $ => seq(
      "-",
      repeat1($.config_entry)
    ),

    type_declaration: $ => seq(
      "type",
      field("name", $.identifier),
      optional(field("type_params", $.type_parameters)),
      "=",
      field("kind", $._type_kind)
    ),

    type_parameters: $ => seq(
      "<",
      commaSep($.type_parameter),
      ">"
    ),

    type_parameter: $ => seq(
      field("name", $.identifier),
      optional(seq(":", $.type_bounds))
    ),

    type_bounds: $ => prec.left(seq(
      $.type_ref,
      repeat(seq("+", $.type_ref))
    )),

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
      optional(field("base", $.type_ref)),
      $.block
    ),

    field: $ => seq(
      field("name", $.identifier),
      ":",
      field("type", $.type_ref),
      optional(seq("=", field("default", $.expression)))
    ),

    type_ref: $ => choice(
      prec(3, seq($.type_ref, "?")),
      prec.left(2, seq($.type_ref, "&", $.type_ref)),
      prec.left(1, seq($.type_ref, "|", $.type_ref)),
      seq(
        field("name", $.identifier),
        optional(seq("<", commaSep($.type_ref), ">"))
      )
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
      $.metrics_section,
      $.invariants_section
    ),

    invariants_section: $ => seq(
      "invariants",
      ":",
      repeat1(seq("-", $.expression))
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
