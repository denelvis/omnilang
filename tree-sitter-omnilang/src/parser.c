#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#ifdef _MSC_VER
#pragma optimize("", off)
#elif defined(__clang__)
#pragma clang optimize off
#elif defined(__GNUC__)
#pragma GCC optimize ("O0")
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 336
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 151
#define ALIAS_COUNT 0
#define TOKEN_COUNT 73
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 11
#define MAX_ALIAS_SEQUENCE_LENGTH 7
#define PRODUCTION_ID_COUNT 18

enum ts_symbol_identifiers {
  anon_sym_module = 1,
  anon_sym_use = 2,
  anon_sym_DOT = 3,
  anon_sym_STAR = 4,
  anon_sym_LBRACE = 5,
  anon_sym_COMMA = 6,
  anon_sym_RBRACE = 7,
  anon_sym_as = 8,
  anon_sym_component = 9,
  anon_sym_pipeline = 10,
  anon_sym_workflow = 11,
  anon_sym_agent = 12,
  anon_sym_schema = 13,
  anon_sym_policy = 14,
  anon_sym_type = 15,
  anon_sym_EQ = 16,
  anon_sym_struct = 17,
  anon_sym_enum = 18,
  anon_sym_LPAREN = 19,
  anon_sym_RPAREN = 20,
  anon_sym_COLON = 21,
  anon_sym_LT = 22,
  anon_sym_GT = 23,
  anon_sym_service = 24,
  anon_sym_goal = 25,
  anon_sym_constraints = 26,
  anon_sym_DASH = 27,
  anon_sym_depends_on = 28,
  anon_sym_budget = 29,
  anon_sym_metrics = 30,
  anon_sym_counter = 31,
  anon_sym_gauge = 32,
  anon_sym_histogram = 33,
  anon_sym_rpc = 34,
  anon_sym_inputs = 35,
  anon_sym_outputs = 36,
  anon_sym_preconditions = 37,
  anon_sym_postconditions = 38,
  anon_sym_errors = 39,
  anon_sym_tests = 40,
  anon_sym_scenario = 41,
  anon_sym_given = 42,
  anon_sym_when = 43,
  anon_sym_expect = 44,
  anon_sym_expect_error = 45,
  anon_sym_property = 46,
  anon_sym_forall = 47,
  anon_sym_assert = 48,
  anon_sym_in = 49,
  anon_sym_EQ_EQ = 50,
  anon_sym_BANG_EQ = 51,
  anon_sym_LT_EQ = 52,
  anon_sym_GT_EQ = 53,
  anon_sym_AMP_AMP = 54,
  anon_sym_PIPE_PIPE = 55,
  anon_sym_notin = 56,
  anon_sym_DOT_DOT = 57,
  anon_sym_DOT_DOT_LT = 58,
  anon_sym_BANG = 59,
  anon_sym_LBRACK = 60,
  anon_sym_RBRACK = 61,
  sym_integer_literal = 62,
  sym_float_literal = 63,
  sym_string_literal = 64,
  anon_sym_true = 65,
  anon_sym_false = 66,
  sym_duration_literal = 67,
  sym_money_literal = 68,
  sym_percentage_literal = 69,
  sym_null_literal = 70,
  sym_identifier = 71,
  sym_comment = 72,
  sym_source_file = 73,
  sym_module_declaration = 74,
  sym_use_declaration = 75,
  sym_import_item = 76,
  sym_dotted_name = 77,
  sym__declaration = 78,
  sym_component_declaration = 79,
  sym_pipeline_declaration = 80,
  sym_workflow_declaration = 81,
  sym_agent_declaration = 82,
  sym_schema_declaration = 83,
  sym_policy_declaration = 84,
  sym_type_declaration = 85,
  sym__type_kind = 86,
  sym_struct_type = 87,
  sym_enum_type = 88,
  sym_enum_variant = 89,
  sym_refined_type = 90,
  sym_field = 91,
  sym_type_ref = 92,
  sym_service_declaration = 93,
  sym_service_block = 94,
  sym__service_member = 95,
  sym_goal_section = 96,
  sym_constraints_section = 97,
  sym_constraint_item = 98,
  sym_constraint_arg = 99,
  sym_depends_on_section = 100,
  sym_budget_section = 101,
  sym_metrics_section = 102,
  sym_metric_declaration = 103,
  sym_metric_kind = 104,
  sym_rpc_declaration = 105,
  sym_rpc_block = 106,
  sym__rpc_member = 107,
  sym_inputs_section = 108,
  sym_outputs_section = 109,
  sym_preconditions_section = 110,
  sym_postconditions_section = 111,
  sym_errors_section = 112,
  sym_error_definition = 113,
  sym_tests_section = 114,
  sym__test_block = 115,
  sym_scenario_block = 116,
  sym_property_block = 117,
  sym_quantifier = 118,
  sym_block = 119,
  sym__block_item = 120,
  sym_expression = 121,
  sym_binary_expression = 122,
  sym_unary_expression = 123,
  sym_call_expression = 124,
  sym_field_expression = 125,
  sym_list_expression = 126,
  sym__literal = 127,
  sym_boolean_literal = 128,
  aux_sym_source_file_repeat1 = 129,
  aux_sym_source_file_repeat2 = 130,
  aux_sym_use_declaration_repeat1 = 131,
  aux_sym_dotted_name_repeat1 = 132,
  aux_sym_enum_type_repeat1 = 133,
  aux_sym_enum_variant_repeat1 = 134,
  aux_sym_type_ref_repeat1 = 135,
  aux_sym_service_block_repeat1 = 136,
  aux_sym_constraints_section_repeat1 = 137,
  aux_sym_constraint_item_repeat1 = 138,
  aux_sym_depends_on_section_repeat1 = 139,
  aux_sym_metrics_section_repeat1 = 140,
  aux_sym_rpc_block_repeat1 = 141,
  aux_sym_inputs_section_repeat1 = 142,
  aux_sym_preconditions_section_repeat1 = 143,
  aux_sym_errors_section_repeat1 = 144,
  aux_sym_tests_section_repeat1 = 145,
  aux_sym_scenario_block_repeat1 = 146,
  aux_sym_scenario_block_repeat2 = 147,
  aux_sym_property_block_repeat1 = 148,
  aux_sym_property_block_repeat2 = 149,
  aux_sym_block_repeat1 = 150,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [anon_sym_module] = "module",
  [anon_sym_use] = "use",
  [anon_sym_DOT] = ".",
  [anon_sym_STAR] = "*",
  [anon_sym_LBRACE] = "{",
  [anon_sym_COMMA] = ",",
  [anon_sym_RBRACE] = "}",
  [anon_sym_as] = "as",
  [anon_sym_component] = "component",
  [anon_sym_pipeline] = "pipeline",
  [anon_sym_workflow] = "workflow",
  [anon_sym_agent] = "agent",
  [anon_sym_schema] = "schema",
  [anon_sym_policy] = "policy",
  [anon_sym_type] = "type",
  [anon_sym_EQ] = "=",
  [anon_sym_struct] = "struct",
  [anon_sym_enum] = "enum",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [anon_sym_COLON] = ":",
  [anon_sym_LT] = "<",
  [anon_sym_GT] = ">",
  [anon_sym_service] = "service",
  [anon_sym_goal] = "goal",
  [anon_sym_constraints] = "constraints",
  [anon_sym_DASH] = "-",
  [anon_sym_depends_on] = "depends_on",
  [anon_sym_budget] = "budget",
  [anon_sym_metrics] = "metrics",
  [anon_sym_counter] = "counter",
  [anon_sym_gauge] = "gauge",
  [anon_sym_histogram] = "histogram",
  [anon_sym_rpc] = "rpc",
  [anon_sym_inputs] = "inputs",
  [anon_sym_outputs] = "outputs",
  [anon_sym_preconditions] = "preconditions",
  [anon_sym_postconditions] = "postconditions",
  [anon_sym_errors] = "errors",
  [anon_sym_tests] = "tests",
  [anon_sym_scenario] = "scenario",
  [anon_sym_given] = "given",
  [anon_sym_when] = "when",
  [anon_sym_expect] = "expect",
  [anon_sym_expect_error] = "expect_error",
  [anon_sym_property] = "property",
  [anon_sym_forall] = "forall",
  [anon_sym_assert] = "assert",
  [anon_sym_in] = "in",
  [anon_sym_EQ_EQ] = "==",
  [anon_sym_BANG_EQ] = "!=",
  [anon_sym_LT_EQ] = "<=",
  [anon_sym_GT_EQ] = ">=",
  [anon_sym_AMP_AMP] = "&&",
  [anon_sym_PIPE_PIPE] = "||",
  [anon_sym_notin] = "not in",
  [anon_sym_DOT_DOT] = "..",
  [anon_sym_DOT_DOT_LT] = "..<",
  [anon_sym_BANG] = "!",
  [anon_sym_LBRACK] = "[",
  [anon_sym_RBRACK] = "]",
  [sym_integer_literal] = "integer_literal",
  [sym_float_literal] = "float_literal",
  [sym_string_literal] = "string_literal",
  [anon_sym_true] = "true",
  [anon_sym_false] = "false",
  [sym_duration_literal] = "duration_literal",
  [sym_money_literal] = "money_literal",
  [sym_percentage_literal] = "percentage_literal",
  [sym_null_literal] = "null_literal",
  [sym_identifier] = "identifier",
  [sym_comment] = "comment",
  [sym_source_file] = "source_file",
  [sym_module_declaration] = "module_declaration",
  [sym_use_declaration] = "use_declaration",
  [sym_import_item] = "import_item",
  [sym_dotted_name] = "dotted_name",
  [sym__declaration] = "_declaration",
  [sym_component_declaration] = "component_declaration",
  [sym_pipeline_declaration] = "pipeline_declaration",
  [sym_workflow_declaration] = "workflow_declaration",
  [sym_agent_declaration] = "agent_declaration",
  [sym_schema_declaration] = "schema_declaration",
  [sym_policy_declaration] = "policy_declaration",
  [sym_type_declaration] = "type_declaration",
  [sym__type_kind] = "_type_kind",
  [sym_struct_type] = "struct_type",
  [sym_enum_type] = "enum_type",
  [sym_enum_variant] = "enum_variant",
  [sym_refined_type] = "refined_type",
  [sym_field] = "field",
  [sym_type_ref] = "type_ref",
  [sym_service_declaration] = "service_declaration",
  [sym_service_block] = "service_block",
  [sym__service_member] = "_service_member",
  [sym_goal_section] = "goal_section",
  [sym_constraints_section] = "constraints_section",
  [sym_constraint_item] = "constraint_item",
  [sym_constraint_arg] = "constraint_arg",
  [sym_depends_on_section] = "depends_on_section",
  [sym_budget_section] = "budget_section",
  [sym_metrics_section] = "metrics_section",
  [sym_metric_declaration] = "metric_declaration",
  [sym_metric_kind] = "metric_kind",
  [sym_rpc_declaration] = "rpc_declaration",
  [sym_rpc_block] = "rpc_block",
  [sym__rpc_member] = "_rpc_member",
  [sym_inputs_section] = "inputs_section",
  [sym_outputs_section] = "outputs_section",
  [sym_preconditions_section] = "preconditions_section",
  [sym_postconditions_section] = "postconditions_section",
  [sym_errors_section] = "errors_section",
  [sym_error_definition] = "error_definition",
  [sym_tests_section] = "tests_section",
  [sym__test_block] = "_test_block",
  [sym_scenario_block] = "scenario_block",
  [sym_property_block] = "property_block",
  [sym_quantifier] = "quantifier",
  [sym_block] = "block",
  [sym__block_item] = "_block_item",
  [sym_expression] = "expression",
  [sym_binary_expression] = "binary_expression",
  [sym_unary_expression] = "unary_expression",
  [sym_call_expression] = "call_expression",
  [sym_field_expression] = "field_expression",
  [sym_list_expression] = "list_expression",
  [sym__literal] = "_literal",
  [sym_boolean_literal] = "boolean_literal",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
  [aux_sym_source_file_repeat2] = "source_file_repeat2",
  [aux_sym_use_declaration_repeat1] = "use_declaration_repeat1",
  [aux_sym_dotted_name_repeat1] = "dotted_name_repeat1",
  [aux_sym_enum_type_repeat1] = "enum_type_repeat1",
  [aux_sym_enum_variant_repeat1] = "enum_variant_repeat1",
  [aux_sym_type_ref_repeat1] = "type_ref_repeat1",
  [aux_sym_service_block_repeat1] = "service_block_repeat1",
  [aux_sym_constraints_section_repeat1] = "constraints_section_repeat1",
  [aux_sym_constraint_item_repeat1] = "constraint_item_repeat1",
  [aux_sym_depends_on_section_repeat1] = "depends_on_section_repeat1",
  [aux_sym_metrics_section_repeat1] = "metrics_section_repeat1",
  [aux_sym_rpc_block_repeat1] = "rpc_block_repeat1",
  [aux_sym_inputs_section_repeat1] = "inputs_section_repeat1",
  [aux_sym_preconditions_section_repeat1] = "preconditions_section_repeat1",
  [aux_sym_errors_section_repeat1] = "errors_section_repeat1",
  [aux_sym_tests_section_repeat1] = "tests_section_repeat1",
  [aux_sym_scenario_block_repeat1] = "scenario_block_repeat1",
  [aux_sym_scenario_block_repeat2] = "scenario_block_repeat2",
  [aux_sym_property_block_repeat1] = "property_block_repeat1",
  [aux_sym_property_block_repeat2] = "property_block_repeat2",
  [aux_sym_block_repeat1] = "block_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [anon_sym_module] = anon_sym_module,
  [anon_sym_use] = anon_sym_use,
  [anon_sym_DOT] = anon_sym_DOT,
  [anon_sym_STAR] = anon_sym_STAR,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_COMMA] = anon_sym_COMMA,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_as] = anon_sym_as,
  [anon_sym_component] = anon_sym_component,
  [anon_sym_pipeline] = anon_sym_pipeline,
  [anon_sym_workflow] = anon_sym_workflow,
  [anon_sym_agent] = anon_sym_agent,
  [anon_sym_schema] = anon_sym_schema,
  [anon_sym_policy] = anon_sym_policy,
  [anon_sym_type] = anon_sym_type,
  [anon_sym_EQ] = anon_sym_EQ,
  [anon_sym_struct] = anon_sym_struct,
  [anon_sym_enum] = anon_sym_enum,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [anon_sym_COLON] = anon_sym_COLON,
  [anon_sym_LT] = anon_sym_LT,
  [anon_sym_GT] = anon_sym_GT,
  [anon_sym_service] = anon_sym_service,
  [anon_sym_goal] = anon_sym_goal,
  [anon_sym_constraints] = anon_sym_constraints,
  [anon_sym_DASH] = anon_sym_DASH,
  [anon_sym_depends_on] = anon_sym_depends_on,
  [anon_sym_budget] = anon_sym_budget,
  [anon_sym_metrics] = anon_sym_metrics,
  [anon_sym_counter] = anon_sym_counter,
  [anon_sym_gauge] = anon_sym_gauge,
  [anon_sym_histogram] = anon_sym_histogram,
  [anon_sym_rpc] = anon_sym_rpc,
  [anon_sym_inputs] = anon_sym_inputs,
  [anon_sym_outputs] = anon_sym_outputs,
  [anon_sym_preconditions] = anon_sym_preconditions,
  [anon_sym_postconditions] = anon_sym_postconditions,
  [anon_sym_errors] = anon_sym_errors,
  [anon_sym_tests] = anon_sym_tests,
  [anon_sym_scenario] = anon_sym_scenario,
  [anon_sym_given] = anon_sym_given,
  [anon_sym_when] = anon_sym_when,
  [anon_sym_expect] = anon_sym_expect,
  [anon_sym_expect_error] = anon_sym_expect_error,
  [anon_sym_property] = anon_sym_property,
  [anon_sym_forall] = anon_sym_forall,
  [anon_sym_assert] = anon_sym_assert,
  [anon_sym_in] = anon_sym_in,
  [anon_sym_EQ_EQ] = anon_sym_EQ_EQ,
  [anon_sym_BANG_EQ] = anon_sym_BANG_EQ,
  [anon_sym_LT_EQ] = anon_sym_LT_EQ,
  [anon_sym_GT_EQ] = anon_sym_GT_EQ,
  [anon_sym_AMP_AMP] = anon_sym_AMP_AMP,
  [anon_sym_PIPE_PIPE] = anon_sym_PIPE_PIPE,
  [anon_sym_notin] = anon_sym_notin,
  [anon_sym_DOT_DOT] = anon_sym_DOT_DOT,
  [anon_sym_DOT_DOT_LT] = anon_sym_DOT_DOT_LT,
  [anon_sym_BANG] = anon_sym_BANG,
  [anon_sym_LBRACK] = anon_sym_LBRACK,
  [anon_sym_RBRACK] = anon_sym_RBRACK,
  [sym_integer_literal] = sym_integer_literal,
  [sym_float_literal] = sym_float_literal,
  [sym_string_literal] = sym_string_literal,
  [anon_sym_true] = anon_sym_true,
  [anon_sym_false] = anon_sym_false,
  [sym_duration_literal] = sym_duration_literal,
  [sym_money_literal] = sym_money_literal,
  [sym_percentage_literal] = sym_percentage_literal,
  [sym_null_literal] = sym_null_literal,
  [sym_identifier] = sym_identifier,
  [sym_comment] = sym_comment,
  [sym_source_file] = sym_source_file,
  [sym_module_declaration] = sym_module_declaration,
  [sym_use_declaration] = sym_use_declaration,
  [sym_import_item] = sym_import_item,
  [sym_dotted_name] = sym_dotted_name,
  [sym__declaration] = sym__declaration,
  [sym_component_declaration] = sym_component_declaration,
  [sym_pipeline_declaration] = sym_pipeline_declaration,
  [sym_workflow_declaration] = sym_workflow_declaration,
  [sym_agent_declaration] = sym_agent_declaration,
  [sym_schema_declaration] = sym_schema_declaration,
  [sym_policy_declaration] = sym_policy_declaration,
  [sym_type_declaration] = sym_type_declaration,
  [sym__type_kind] = sym__type_kind,
  [sym_struct_type] = sym_struct_type,
  [sym_enum_type] = sym_enum_type,
  [sym_enum_variant] = sym_enum_variant,
  [sym_refined_type] = sym_refined_type,
  [sym_field] = sym_field,
  [sym_type_ref] = sym_type_ref,
  [sym_service_declaration] = sym_service_declaration,
  [sym_service_block] = sym_service_block,
  [sym__service_member] = sym__service_member,
  [sym_goal_section] = sym_goal_section,
  [sym_constraints_section] = sym_constraints_section,
  [sym_constraint_item] = sym_constraint_item,
  [sym_constraint_arg] = sym_constraint_arg,
  [sym_depends_on_section] = sym_depends_on_section,
  [sym_budget_section] = sym_budget_section,
  [sym_metrics_section] = sym_metrics_section,
  [sym_metric_declaration] = sym_metric_declaration,
  [sym_metric_kind] = sym_metric_kind,
  [sym_rpc_declaration] = sym_rpc_declaration,
  [sym_rpc_block] = sym_rpc_block,
  [sym__rpc_member] = sym__rpc_member,
  [sym_inputs_section] = sym_inputs_section,
  [sym_outputs_section] = sym_outputs_section,
  [sym_preconditions_section] = sym_preconditions_section,
  [sym_postconditions_section] = sym_postconditions_section,
  [sym_errors_section] = sym_errors_section,
  [sym_error_definition] = sym_error_definition,
  [sym_tests_section] = sym_tests_section,
  [sym__test_block] = sym__test_block,
  [sym_scenario_block] = sym_scenario_block,
  [sym_property_block] = sym_property_block,
  [sym_quantifier] = sym_quantifier,
  [sym_block] = sym_block,
  [sym__block_item] = sym__block_item,
  [sym_expression] = sym_expression,
  [sym_binary_expression] = sym_binary_expression,
  [sym_unary_expression] = sym_unary_expression,
  [sym_call_expression] = sym_call_expression,
  [sym_field_expression] = sym_field_expression,
  [sym_list_expression] = sym_list_expression,
  [sym__literal] = sym__literal,
  [sym_boolean_literal] = sym_boolean_literal,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
  [aux_sym_source_file_repeat2] = aux_sym_source_file_repeat2,
  [aux_sym_use_declaration_repeat1] = aux_sym_use_declaration_repeat1,
  [aux_sym_dotted_name_repeat1] = aux_sym_dotted_name_repeat1,
  [aux_sym_enum_type_repeat1] = aux_sym_enum_type_repeat1,
  [aux_sym_enum_variant_repeat1] = aux_sym_enum_variant_repeat1,
  [aux_sym_type_ref_repeat1] = aux_sym_type_ref_repeat1,
  [aux_sym_service_block_repeat1] = aux_sym_service_block_repeat1,
  [aux_sym_constraints_section_repeat1] = aux_sym_constraints_section_repeat1,
  [aux_sym_constraint_item_repeat1] = aux_sym_constraint_item_repeat1,
  [aux_sym_depends_on_section_repeat1] = aux_sym_depends_on_section_repeat1,
  [aux_sym_metrics_section_repeat1] = aux_sym_metrics_section_repeat1,
  [aux_sym_rpc_block_repeat1] = aux_sym_rpc_block_repeat1,
  [aux_sym_inputs_section_repeat1] = aux_sym_inputs_section_repeat1,
  [aux_sym_preconditions_section_repeat1] = aux_sym_preconditions_section_repeat1,
  [aux_sym_errors_section_repeat1] = aux_sym_errors_section_repeat1,
  [aux_sym_tests_section_repeat1] = aux_sym_tests_section_repeat1,
  [aux_sym_scenario_block_repeat1] = aux_sym_scenario_block_repeat1,
  [aux_sym_scenario_block_repeat2] = aux_sym_scenario_block_repeat2,
  [aux_sym_property_block_repeat1] = aux_sym_property_block_repeat1,
  [aux_sym_property_block_repeat2] = aux_sym_property_block_repeat2,
  [aux_sym_block_repeat1] = aux_sym_block_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_module] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_use] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DOT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_STAR] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COMMA] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_as] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_component] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_pipeline] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_workflow] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_agent] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_schema] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_policy] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_type] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_struct] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_enum] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLON] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_service] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_goal] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_constraints] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_depends_on] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_budget] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_metrics] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_counter] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_gauge] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_histogram] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_rpc] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_inputs] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_outputs] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_preconditions] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_postconditions] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_errors] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_tests] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_scenario] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_given] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_when] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_expect] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_expect_error] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_property] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_forall] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_assert] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_in] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EQ_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BANG_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GT_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_AMP_AMP] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PIPE_PIPE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_notin] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DOT_DOT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DOT_DOT_LT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BANG] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACK] = {
    .visible = true,
    .named = false,
  },
  [sym_integer_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_float_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_string_literal] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_true] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_false] = {
    .visible = true,
    .named = false,
  },
  [sym_duration_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_money_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_percentage_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_null_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_identifier] = {
    .visible = true,
    .named = true,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym_module_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_use_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_import_item] = {
    .visible = true,
    .named = true,
  },
  [sym_dotted_name] = {
    .visible = true,
    .named = true,
  },
  [sym__declaration] = {
    .visible = false,
    .named = true,
  },
  [sym_component_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_pipeline_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_workflow_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_agent_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_schema_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_policy_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_type_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym__type_kind] = {
    .visible = false,
    .named = true,
  },
  [sym_struct_type] = {
    .visible = true,
    .named = true,
  },
  [sym_enum_type] = {
    .visible = true,
    .named = true,
  },
  [sym_enum_variant] = {
    .visible = true,
    .named = true,
  },
  [sym_refined_type] = {
    .visible = true,
    .named = true,
  },
  [sym_field] = {
    .visible = true,
    .named = true,
  },
  [sym_type_ref] = {
    .visible = true,
    .named = true,
  },
  [sym_service_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_service_block] = {
    .visible = true,
    .named = true,
  },
  [sym__service_member] = {
    .visible = false,
    .named = true,
  },
  [sym_goal_section] = {
    .visible = true,
    .named = true,
  },
  [sym_constraints_section] = {
    .visible = true,
    .named = true,
  },
  [sym_constraint_item] = {
    .visible = true,
    .named = true,
  },
  [sym_constraint_arg] = {
    .visible = true,
    .named = true,
  },
  [sym_depends_on_section] = {
    .visible = true,
    .named = true,
  },
  [sym_budget_section] = {
    .visible = true,
    .named = true,
  },
  [sym_metrics_section] = {
    .visible = true,
    .named = true,
  },
  [sym_metric_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_metric_kind] = {
    .visible = true,
    .named = true,
  },
  [sym_rpc_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_rpc_block] = {
    .visible = true,
    .named = true,
  },
  [sym__rpc_member] = {
    .visible = false,
    .named = true,
  },
  [sym_inputs_section] = {
    .visible = true,
    .named = true,
  },
  [sym_outputs_section] = {
    .visible = true,
    .named = true,
  },
  [sym_preconditions_section] = {
    .visible = true,
    .named = true,
  },
  [sym_postconditions_section] = {
    .visible = true,
    .named = true,
  },
  [sym_errors_section] = {
    .visible = true,
    .named = true,
  },
  [sym_error_definition] = {
    .visible = true,
    .named = true,
  },
  [sym_tests_section] = {
    .visible = true,
    .named = true,
  },
  [sym__test_block] = {
    .visible = false,
    .named = true,
  },
  [sym_scenario_block] = {
    .visible = true,
    .named = true,
  },
  [sym_property_block] = {
    .visible = true,
    .named = true,
  },
  [sym_quantifier] = {
    .visible = true,
    .named = true,
  },
  [sym_block] = {
    .visible = true,
    .named = true,
  },
  [sym__block_item] = {
    .visible = false,
    .named = true,
  },
  [sym_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_binary_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_unary_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_call_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_field_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_list_expression] = {
    .visible = true,
    .named = true,
  },
  [sym__literal] = {
    .visible = false,
    .named = true,
  },
  [sym_boolean_literal] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_source_file_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_source_file_repeat2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_use_declaration_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_dotted_name_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_enum_type_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_enum_variant_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_type_ref_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_service_block_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_constraints_section_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_constraint_item_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_depends_on_section_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_metrics_section_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_rpc_block_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_inputs_section_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_preconditions_section_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_errors_section_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_tests_section_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_scenario_block_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_scenario_block_repeat2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_property_block_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_property_block_repeat2] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_block_repeat1] = {
    .visible = false,
    .named = false,
  },
};

enum ts_field_identifiers {
  field_alias = 1,
  field_base = 2,
  field_default = 3,
  field_dependency = 4,
  field_function = 5,
  field_generator = 6,
  field_kind = 7,
  field_name = 8,
  field_path = 9,
  field_type = 10,
  field_value = 11,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_alias] = "alias",
  [field_base] = "base",
  [field_default] = "default",
  [field_dependency] = "dependency",
  [field_function] = "function",
  [field_generator] = "generator",
  [field_kind] = "kind",
  [field_name] = "name",
  [field_path] = "path",
  [field_type] = "type",
  [field_value] = "value",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 1},
  [2] = {.index = 1, .length = 1},
  [3] = {.index = 2, .length = 1},
  [4] = {.index = 3, .length = 2},
  [5] = {.index = 5, .length = 1},
  [6] = {.index = 6, .length = 2},
  [7] = {.index = 8, .length = 1},
  [8] = {.index = 9, .length = 2},
  [9] = {.index = 11, .length = 1},
  [10] = {.index = 12, .length = 1},
  [11] = {.index = 13, .length = 2},
  [12] = {.index = 15, .length = 3},
  [13] = {.index = 18, .length = 2},
  [14] = {.index = 20, .length = 1},
  [15] = {.index = 21, .length = 2},
  [16] = {.index = 23, .length = 1},
  [17] = {.index = 24, .length = 2},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_name, 1},
  [1] =
    {field_path, 1},
  [2] =
    {field_name, 0},
  [3] =
    {field_kind, 3},
    {field_name, 1},
  [5] =
    {field_base, 0},
  [6] =
    {field_name, 0},
    {field_type, 2},
  [8] =
    {field_dependency, 2, .inherited = true},
  [9] =
    {field_alias, 2},
    {field_name, 0},
  [11] =
    {field_function, 0},
  [12] =
    {field_dependency, 1},
  [13] =
    {field_dependency, 0, .inherited = true},
    {field_dependency, 1, .inherited = true},
  [15] =
    {field_default, 4},
    {field_name, 0},
    {field_type, 2},
  [18] =
    {field_kind, 0},
    {field_name, 1},
  [20] =
    {field_value, 0},
  [21] =
    {field_name, 0},
    {field_value, 2},
  [23] =
    {field_name, 2},
  [24] =
    {field_generator, 2},
    {field_name, 0},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static const TSStateId ts_primary_state_ids[STATE_COUNT] = {
  [0] = 0,
  [1] = 1,
  [2] = 2,
  [3] = 3,
  [4] = 4,
  [5] = 5,
  [6] = 6,
  [7] = 7,
  [8] = 8,
  [9] = 9,
  [10] = 10,
  [11] = 11,
  [12] = 12,
  [13] = 13,
  [14] = 14,
  [15] = 15,
  [16] = 16,
  [17] = 17,
  [18] = 18,
  [19] = 19,
  [20] = 20,
  [21] = 21,
  [22] = 21,
  [23] = 2,
  [24] = 20,
  [25] = 20,
  [26] = 26,
  [27] = 20,
  [28] = 28,
  [29] = 21,
  [30] = 21,
  [31] = 31,
  [32] = 9,
  [33] = 33,
  [34] = 34,
  [35] = 4,
  [36] = 11,
  [37] = 8,
  [38] = 38,
  [39] = 10,
  [40] = 38,
  [41] = 41,
  [42] = 41,
  [43] = 43,
  [44] = 44,
  [45] = 45,
  [46] = 46,
  [47] = 47,
  [48] = 48,
  [49] = 14,
  [50] = 13,
  [51] = 51,
  [52] = 52,
  [53] = 46,
  [54] = 34,
  [55] = 38,
  [56] = 12,
  [57] = 41,
  [58] = 7,
  [59] = 6,
  [60] = 5,
  [61] = 46,
  [62] = 46,
  [63] = 41,
  [64] = 64,
  [65] = 65,
  [66] = 66,
  [67] = 67,
  [68] = 68,
  [69] = 69,
  [70] = 70,
  [71] = 71,
  [72] = 72,
  [73] = 2,
  [74] = 2,
  [75] = 75,
  [76] = 76,
  [77] = 6,
  [78] = 78,
  [79] = 13,
  [80] = 78,
  [81] = 78,
  [82] = 4,
  [83] = 14,
  [84] = 12,
  [85] = 85,
  [86] = 5,
  [87] = 7,
  [88] = 7,
  [89] = 5,
  [90] = 78,
  [91] = 6,
  [92] = 4,
  [93] = 11,
  [94] = 3,
  [95] = 9,
  [96] = 85,
  [97] = 33,
  [98] = 85,
  [99] = 8,
  [100] = 100,
  [101] = 101,
  [102] = 10,
  [103] = 13,
  [104] = 85,
  [105] = 10,
  [106] = 14,
  [107] = 11,
  [108] = 12,
  [109] = 109,
  [110] = 9,
  [111] = 8,
  [112] = 112,
  [113] = 33,
  [114] = 114,
  [115] = 115,
  [116] = 116,
  [117] = 117,
  [118] = 118,
  [119] = 119,
  [120] = 120,
  [121] = 121,
  [122] = 122,
  [123] = 123,
  [124] = 124,
  [125] = 125,
  [126] = 126,
  [127] = 127,
  [128] = 128,
  [129] = 129,
  [130] = 130,
  [131] = 131,
  [132] = 132,
  [133] = 133,
  [134] = 134,
  [135] = 135,
  [136] = 136,
  [137] = 64,
  [138] = 66,
  [139] = 139,
  [140] = 140,
  [141] = 141,
  [142] = 142,
  [143] = 143,
  [144] = 144,
  [145] = 114,
  [146] = 146,
  [147] = 147,
  [148] = 148,
  [149] = 149,
  [150] = 150,
  [151] = 151,
  [152] = 152,
  [153] = 153,
  [154] = 154,
  [155] = 155,
  [156] = 156,
  [157] = 157,
  [158] = 130,
  [159] = 159,
  [160] = 160,
  [161] = 161,
  [162] = 162,
  [163] = 163,
  [164] = 164,
  [165] = 165,
  [166] = 166,
  [167] = 167,
  [168] = 168,
  [169] = 122,
  [170] = 170,
  [171] = 171,
  [172] = 172,
  [173] = 123,
  [174] = 174,
  [175] = 175,
  [176] = 176,
  [177] = 177,
  [178] = 178,
  [179] = 179,
  [180] = 180,
  [181] = 181,
  [182] = 182,
  [183] = 183,
  [184] = 184,
  [185] = 185,
  [186] = 186,
  [187] = 187,
  [188] = 188,
  [189] = 189,
  [190] = 190,
  [191] = 191,
  [192] = 192,
  [193] = 193,
  [194] = 194,
  [195] = 195,
  [196] = 196,
  [197] = 197,
  [198] = 198,
  [199] = 199,
  [200] = 200,
  [201] = 201,
  [202] = 202,
  [203] = 203,
  [204] = 204,
  [205] = 205,
  [206] = 206,
  [207] = 207,
  [208] = 208,
  [209] = 209,
  [210] = 130,
  [211] = 123,
  [212] = 122,
  [213] = 109,
  [214] = 157,
  [215] = 215,
  [216] = 216,
  [217] = 217,
  [218] = 218,
  [219] = 219,
  [220] = 220,
  [221] = 221,
  [222] = 157,
  [223] = 223,
  [224] = 224,
  [225] = 225,
  [226] = 226,
  [227] = 227,
  [228] = 228,
  [229] = 229,
  [230] = 230,
  [231] = 227,
  [232] = 232,
  [233] = 233,
  [234] = 234,
  [235] = 235,
  [236] = 236,
  [237] = 237,
  [238] = 221,
  [239] = 239,
  [240] = 240,
  [241] = 241,
  [242] = 220,
  [243] = 221,
  [244] = 224,
  [245] = 217,
  [246] = 224,
  [247] = 247,
  [248] = 217,
  [249] = 227,
  [250] = 220,
  [251] = 221,
  [252] = 227,
  [253] = 253,
  [254] = 254,
  [255] = 255,
  [256] = 256,
  [257] = 257,
  [258] = 258,
  [259] = 259,
  [260] = 260,
  [261] = 261,
  [262] = 262,
  [263] = 263,
  [264] = 264,
  [265] = 265,
  [266] = 266,
  [267] = 267,
  [268] = 268,
  [269] = 269,
  [270] = 270,
  [271] = 271,
  [272] = 272,
  [273] = 273,
  [274] = 274,
  [275] = 270,
  [276] = 276,
  [277] = 277,
  [278] = 278,
  [279] = 279,
  [280] = 280,
  [281] = 281,
  [282] = 282,
  [283] = 283,
  [284] = 284,
  [285] = 285,
  [286] = 286,
  [287] = 287,
  [288] = 288,
  [289] = 289,
  [290] = 290,
  [291] = 291,
  [292] = 292,
  [293] = 293,
  [294] = 294,
  [295] = 295,
  [296] = 296,
  [297] = 297,
  [298] = 298,
  [299] = 299,
  [300] = 300,
  [301] = 301,
  [302] = 302,
  [303] = 303,
  [304] = 304,
  [305] = 305,
  [306] = 306,
  [307] = 290,
  [308] = 308,
  [309] = 309,
  [310] = 310,
  [311] = 311,
  [312] = 312,
  [313] = 313,
  [314] = 314,
  [315] = 315,
  [316] = 311,
  [317] = 317,
  [318] = 318,
  [319] = 319,
  [320] = 320,
  [321] = 321,
  [322] = 290,
  [323] = 323,
  [324] = 324,
  [325] = 325,
  [326] = 326,
  [327] = 327,
  [328] = 328,
  [329] = 329,
  [330] = 330,
  [331] = 331,
  [332] = 290,
  [333] = 333,
  [334] = 334,
  [335] = 335,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(233);
      ADVANCE_MAP(
        '!', 311,
        '"', 7,
        '$', 227,
        '&', 8,
        '(', 255,
        ')', 256,
        '*', 237,
        ',', 239,
        '-', 265,
        '.', 236,
        '/', 10,
        ':', 257,
        '<', 259,
        '=', 250,
        '>', 261,
        '[', 312,
        ']', 313,
        'a', 72,
        'b', 211,
        'c', 131,
        'd', 52,
        'e', 119,
        'f', 19,
        'g', 23,
        'h', 80,
        'i', 111,
        'm', 42,
        'n', 136,
        'o', 213,
        'p', 88,
        'r', 149,
        's', 27,
        't', 67,
        'u', 183,
        'w', 78,
        '{', 238,
        '|', 226,
        '}', 240,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(314);
      END_STATE();
    case 1:
      if (lookahead == ' ') ADVANCE(85);
      END_STATE();
    case 2:
      ADVANCE_MAP(
        '!', 16,
        '&', 8,
        '(', 255,
        ')', 256,
        ',', 239,
        '.', 236,
        '/', 10,
        ':', 257,
        '<', 259,
        '=', 17,
        '>', 261,
        ']', 313,
        'i', 117,
        'n', 135,
        '|', 226,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(2);
      END_STATE();
    case 3:
      ADVANCE_MAP(
        '!', 16,
        '&', 8,
        '(', 255,
        ',', 239,
        '-', 265,
        '.', 236,
        '/', 10,
        '<', 259,
        '=', 17,
        '>', 261,
        'a', 190,
        'e', 157,
        'f', 134,
        'g', 79,
        'i', 111,
        'n', 135,
        'o', 213,
        'p', 147,
        't', 66,
        'w', 77,
        '|', 226,
        '}', 240,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(3);
      END_STATE();
    case 4:
      ADVANCE_MAP(
        '!', 16,
        '&', 8,
        '(', 255,
        '-', 265,
        '.', 236,
        '/', 10,
        '<', 259,
        '=', 250,
        '>', 261,
        'i', 357,
        'n', 365,
        '|', 226,
        '}', 240,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(4);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 5:
      ADVANCE_MAP(
        '!', 16,
        '&', 8,
        '(', 255,
        '.', 236,
        '/', 10,
        '<', 259,
        '=', 17,
        '>', 261,
        'e', 377,
        'i', 355,
        'n', 365,
        'o', 407,
        'p', 366,
        't', 342,
        '|', 226,
        '}', 240,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(5);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 6:
      ADVANCE_MAP(
        '!', 310,
        '"', 7,
        '$', 227,
        ')', 256,
        ',', 239,
        '-', 265,
        '/', 10,
        '>', 260,
        '[', 312,
        ']', 313,
        'f', 329,
        'n', 406,
        't', 375,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(6);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(314);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 7:
      if (lookahead == '"') ADVANCE(316);
      if (lookahead == '\\') ADVANCE(231);
      if (lookahead != 0) ADVANCE(7);
      END_STATE();
    case 8:
      if (lookahead == '&') ADVANCE(305);
      END_STATE();
    case 9:
      if (lookahead == '(') ADVANCE(255);
      if (lookahead == ')') ADVANCE(256);
      if (lookahead == '-') ADVANCE(265);
      if (lookahead == '/') ADVANCE(10);
      if (lookahead == '=') ADVANCE(249);
      if (lookahead == '>') ADVANCE(260);
      if (lookahead == '}') ADVANCE(240);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(9);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 10:
      if (lookahead == '*') ADVANCE(12);
      if (lookahead == '/') ADVANCE(414);
      END_STATE();
    case 11:
      if (lookahead == '*') ADVANCE(11);
      if (lookahead == '/') ADVANCE(413);
      if (lookahead != 0) ADVANCE(12);
      END_STATE();
    case 12:
      if (lookahead == '*') ADVANCE(11);
      if (lookahead != 0) ADVANCE(12);
      END_STATE();
    case 13:
      ADVANCE_MAP(
        '-', 265,
        '/', 10,
        'a', 392,
        'e', 377,
        'f', 370,
        'g', 344,
        'i', 363,
        'o', 407,
        'p', 366,
        't', 342,
        'w', 343,
        '}', 240,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(13);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 14:
      ADVANCE_MAP(
        '/', 10,
        '<', 258,
        '=', 249,
        'e', 377,
        'i', 363,
        'o', 407,
        'p', 366,
        't', 342,
        '}', 240,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(14);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 15:
      if (lookahead == '/') ADVANCE(10);
      if (lookahead == 'e') ADVANCE(360);
      if (lookahead == 's') ADVANCE(401);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(15);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 16:
      if (lookahead == '=') ADVANCE(302);
      END_STATE();
    case 17:
      if (lookahead == '=') ADVANCE(301);
      END_STATE();
    case 18:
      if (lookahead == '_') ADVANCE(143);
      END_STATE();
    case 19:
      if (lookahead == 'a') ADVANCE(104);
      if (lookahead == 'o') ADVANCE(170);
      END_STATE();
    case 20:
      if (lookahead == 'a') ADVANCE(246);
      END_STATE();
    case 21:
      if (lookahead == 'a') ADVANCE(95);
      END_STATE();
    case 22:
      if (lookahead == 'a') ADVANCE(107);
      END_STATE();
    case 23:
      if (lookahead == 'a') ADVANCE(218);
      if (lookahead == 'i') ADVANCE(221);
      if (lookahead == 'o') ADVANCE(21);
      END_STATE();
    case 24:
      if (lookahead == 'a') ADVANCE(90);
      END_STATE();
    case 25:
      if (lookahead == 'a') ADVANCE(163);
      END_STATE();
    case 26:
      if (lookahead == 'a') ADVANCE(102);
      END_STATE();
    case 27:
      if (lookahead == 'c') ADVANCE(56);
      if (lookahead == 'e') ADVANCE(162);
      if (lookahead == 't') ADVANCE(167);
      END_STATE();
    case 28:
      if (lookahead == 'c') ADVANCE(272);
      END_STATE();
    case 29:
      if (lookahead == 'c') ADVANCE(223);
      END_STATE();
    case 30:
      if (lookahead == 'c') ADVANCE(178);
      END_STATE();
    case 31:
      if (lookahead == 'c') ADVANCE(194);
      END_STATE();
    case 32:
      if (lookahead == 'c') ADVANCE(195);
      END_STATE();
    case 33:
      if (lookahead == 'c') ADVANCE(49);
      END_STATE();
    case 34:
      if (lookahead == 'c') ADVANCE(76);
      if (lookahead == 'e') ADVANCE(162);
      END_STATE();
    case 35:
      if (lookahead == 'c') ADVANCE(142);
      END_STATE();
    case 36:
      if (lookahead == 'c') ADVANCE(148);
      END_STATE();
    case 37:
      if (lookahead == 'd') ADVANCE(73);
      END_STATE();
    case 38:
      if (lookahead == 'd') ADVANCE(214);
      END_STATE();
    case 39:
      if (lookahead == 'd') ADVANCE(87);
      END_STATE();
    case 40:
      if (lookahead == 'd') ADVANCE(177);
      END_STATE();
    case 41:
      if (lookahead == 'd') ADVANCE(93);
      END_STATE();
    case 42:
      if (lookahead == 'e') ADVANCE(203);
      if (lookahead == 'o') ADVANCE(38);
      END_STATE();
    case 43:
      if (lookahead == 'e') ADVANCE(235);
      END_STATE();
    case 44:
      if (lookahead == 'e') ADVANCE(317);
      END_STATE();
    case 45:
      if (lookahead == 'e') ADVANCE(248);
      END_STATE();
    case 46:
      if (lookahead == 'e') ADVANCE(319);
      END_STATE();
    case 47:
      if (lookahead == 'e') ADVANCE(270);
      END_STATE();
    case 48:
      if (lookahead == 'e') ADVANCE(234);
      END_STATE();
    case 49:
      if (lookahead == 'e') ADVANCE(262);
      END_STATE();
    case 50:
      if (lookahead == 'e') ADVANCE(243);
      END_STATE();
    case 51:
      if (lookahead == 'e') ADVANCE(122);
      END_STATE();
    case 52:
      if (lookahead == 'e') ADVANCE(156);
      END_STATE();
    case 53:
      if (lookahead == 'e') ADVANCE(35);
      END_STATE();
    case 54:
      if (lookahead == 'e') ADVANCE(35);
      if (lookahead == 'o') ADVANCE(154);
      END_STATE();
    case 55:
      if (lookahead == 'e') ADVANCE(108);
      END_STATE();
    case 56:
      if (lookahead == 'e') ADVANCE(118);
      if (lookahead == 'h') ADVANCE(55);
      END_STATE();
    case 57:
      if (lookahead == 'e') ADVANCE(31);
      END_STATE();
    case 58:
      if (lookahead == 'e') ADVANCE(113);
      END_STATE();
    case 59:
      if (lookahead == 'e') ADVANCE(120);
      END_STATE();
    case 60:
      if (lookahead == 'e') ADVANCE(105);
      END_STATE();
    case 61:
      if (lookahead == 'e') ADVANCE(114);
      END_STATE();
    case 62:
      if (lookahead == 'e') ADVANCE(168);
      END_STATE();
    case 63:
      if (lookahead == 'e') ADVANCE(193);
      END_STATE();
    case 64:
      if (lookahead == 'e') ADVANCE(159);
      END_STATE();
    case 65:
      if (lookahead == 'e') ADVANCE(173);
      END_STATE();
    case 66:
      if (lookahead == 'e') ADVANCE(186);
      END_STATE();
    case 67:
      if (lookahead == 'e') ADVANCE(186);
      if (lookahead == 'r') ADVANCE(215);
      if (lookahead == 'y') ADVANCE(153);
      END_STATE();
    case 68:
      if (lookahead == 'e') ADVANCE(169);
      END_STATE();
    case 69:
      if (lookahead == 'e') ADVANCE(126);
      END_STATE();
    case 70:
      if (lookahead == 'f') ADVANCE(101);
      END_STATE();
    case 71:
      if (lookahead == 'g') ADVANCE(51);
      END_STATE();
    case 72:
      if (lookahead == 'g') ADVANCE(51);
      if (lookahead == 's') ADVANCE(241);
      END_STATE();
    case 73:
      if (lookahead == 'g') ADVANCE(63);
      END_STATE();
    case 74:
      if (lookahead == 'g') ADVANCE(47);
      END_STATE();
    case 75:
      if (lookahead == 'g') ADVANCE(166);
      END_STATE();
    case 76:
      if (lookahead == 'h') ADVANCE(55);
      END_STATE();
    case 77:
      if (lookahead == 'h') ADVANCE(58);
      END_STATE();
    case 78:
      if (lookahead == 'h') ADVANCE(58);
      if (lookahead == 'o') ADVANCE(158);
      END_STATE();
    case 79:
      if (lookahead == 'i') ADVANCE(221);
      END_STATE();
    case 80:
      if (lookahead == 'i') ADVANCE(184);
      END_STATE();
    case 81:
      if (lookahead == 'i') ADVANCE(29);
      END_STATE();
    case 82:
      if (lookahead == 'i') ADVANCE(30);
      END_STATE();
    case 83:
      if (lookahead == 'i') ADVANCE(133);
      END_STATE();
    case 84:
      if (lookahead == 'i') ADVANCE(33);
      END_STATE();
    case 85:
      if (lookahead == 'i') ADVANCE(115);
      END_STATE();
    case 86:
      if (lookahead == 'i') ADVANCE(127);
      END_STATE();
    case 87:
      if (lookahead == 'i') ADVANCE(204);
      END_STATE();
    case 88:
      if (lookahead == 'i') ADVANCE(152);
      if (lookahead == 'o') ADVANCE(99);
      if (lookahead == 'r') ADVANCE(54);
      END_STATE();
    case 89:
      if (lookahead == 'i') ADVANCE(152);
      if (lookahead == 'o') ADVANCE(98);
      END_STATE();
    case 90:
      if (lookahead == 'i') ADVANCE(128);
      END_STATE();
    case 91:
      if (lookahead == 'i') ADVANCE(144);
      END_STATE();
    case 92:
      if (lookahead == 'i') ADVANCE(145);
      END_STATE();
    case 93:
      if (lookahead == 'i') ADVANCE(209);
      END_STATE();
    case 94:
      if (lookahead == 'k') ADVANCE(70);
      END_STATE();
    case 95:
      if (lookahead == 'l') ADVANCE(263);
      END_STATE();
    case 96:
      if (lookahead == 'l') ADVANCE(326);
      END_STATE();
    case 97:
      if (lookahead == 'l') ADVANCE(293);
      END_STATE();
    case 98:
      if (lookahead == 'l') ADVANCE(81);
      END_STATE();
    case 99:
      if (lookahead == 'l') ADVANCE(81);
      if (lookahead == 's') ADVANCE(210);
      END_STATE();
    case 100:
      if (lookahead == 'l') ADVANCE(96);
      END_STATE();
    case 101:
      if (lookahead == 'l') ADVANCE(132);
      END_STATE();
    case 102:
      if (lookahead == 'l') ADVANCE(97);
      END_STATE();
    case 103:
      if (lookahead == 'l') ADVANCE(48);
      END_STATE();
    case 104:
      if (lookahead == 'l') ADVANCE(187);
      END_STATE();
    case 105:
      if (lookahead == 'l') ADVANCE(86);
      END_STATE();
    case 106:
      if (lookahead == 'm') ADVANCE(253);
      END_STATE();
    case 107:
      if (lookahead == 'm') ADVANCE(271);
      END_STATE();
    case 108:
      if (lookahead == 'm') ADVANCE(20);
      END_STATE();
    case 109:
      if (lookahead == 'm') ADVANCE(150);
      END_STATE();
    case 110:
      if (lookahead == 'm') ADVANCE(150);
      if (lookahead == 'n') ADVANCE(188);
      if (lookahead == 'u') ADVANCE(123);
      END_STATE();
    case 111:
      if (lookahead == 'n') ADVANCE(299);
      END_STATE();
    case 112:
      if (lookahead == 'n') ADVANCE(321);
      END_STATE();
    case 113:
      if (lookahead == 'n') ADVANCE(288);
      END_STATE();
    case 114:
      if (lookahead == 'n') ADVANCE(286);
      END_STATE();
    case 115:
      if (lookahead == 'n') ADVANCE(307);
      END_STATE();
    case 116:
      if (lookahead == 'n') ADVANCE(266);
      END_STATE();
    case 117:
      if (lookahead == 'n') ADVANCE(297);
      END_STATE();
    case 118:
      if (lookahead == 'n') ADVANCE(25);
      END_STATE();
    case 119:
      if (lookahead == 'n') ADVANCE(212);
      if (lookahead == 'r') ADVANCE(161);
      if (lookahead == 'x') ADVANCE(151);
      END_STATE();
    case 120:
      if (lookahead == 'n') ADVANCE(40);
      END_STATE();
    case 121:
      if (lookahead == 'n') ADVANCE(39);
      END_STATE();
    case 122:
      if (lookahead == 'n') ADVANCE(192);
      END_STATE();
    case 123:
      if (lookahead == 'n') ADVANCE(208);
      END_STATE();
    case 124:
      if (lookahead == 'n') ADVANCE(181);
      END_STATE();
    case 125:
      if (lookahead == 'n') ADVANCE(182);
      END_STATE();
    case 126:
      if (lookahead == 'n') ADVANCE(196);
      END_STATE();
    case 127:
      if (lookahead == 'n') ADVANCE(50);
      END_STATE();
    case 128:
      if (lookahead == 'n') ADVANCE(207);
      END_STATE();
    case 129:
      if (lookahead == 'n') ADVANCE(69);
      END_STATE();
    case 130:
      if (lookahead == 'n') ADVANCE(41);
      END_STATE();
    case 131:
      if (lookahead == 'o') ADVANCE(110);
      END_STATE();
    case 132:
      if (lookahead == 'o') ADVANCE(222);
      END_STATE();
    case 133:
      if (lookahead == 'o') ADVANCE(285);
      END_STATE();
    case 134:
      if (lookahead == 'o') ADVANCE(170);
      END_STATE();
    case 135:
      if (lookahead == 'o') ADVANCE(191);
      END_STATE();
    case 136:
      if (lookahead == 'o') ADVANCE(191);
      if (lookahead == 'u') ADVANCE(100);
      END_STATE();
    case 137:
      if (lookahead == 'o') ADVANCE(75);
      END_STATE();
    case 138:
      if (lookahead == 'o') ADVANCE(109);
      END_STATE();
    case 139:
      if (lookahead == 'o') ADVANCE(158);
      END_STATE();
    case 140:
      if (lookahead == 'o') ADVANCE(165);
      END_STATE();
    case 141:
      if (lookahead == 'o') ADVANCE(129);
      END_STATE();
    case 142:
      if (lookahead == 'o') ADVANCE(121);
      END_STATE();
    case 143:
      if (lookahead == 'o') ADVANCE(116);
      END_STATE();
    case 144:
      if (lookahead == 'o') ADVANCE(124);
      END_STATE();
    case 145:
      if (lookahead == 'o') ADVANCE(125);
      END_STATE();
    case 146:
      if (lookahead == 'o') ADVANCE(160);
      END_STATE();
    case 147:
      if (lookahead == 'o') ADVANCE(185);
      if (lookahead == 'r') ADVANCE(53);
      END_STATE();
    case 148:
      if (lookahead == 'o') ADVANCE(130);
      END_STATE();
    case 149:
      if (lookahead == 'p') ADVANCE(28);
      END_STATE();
    case 150:
      if (lookahead == 'p') ADVANCE(141);
      END_STATE();
    case 151:
      if (lookahead == 'p') ADVANCE(57);
      END_STATE();
    case 152:
      if (lookahead == 'p') ADVANCE(60);
      END_STATE();
    case 153:
      if (lookahead == 'p') ADVANCE(45);
      END_STATE();
    case 154:
      if (lookahead == 'p') ADVANCE(62);
      END_STATE();
    case 155:
      if (lookahead == 'p') ADVANCE(217);
      END_STATE();
    case 156:
      if (lookahead == 'p') ADVANCE(59);
      END_STATE();
    case 157:
      if (lookahead == 'r') ADVANCE(161);
      if (lookahead == 'x') ADVANCE(151);
      END_STATE();
    case 158:
      if (lookahead == 'r') ADVANCE(94);
      END_STATE();
    case 159:
      if (lookahead == 'r') ADVANCE(269);
      END_STATE();
    case 160:
      if (lookahead == 'r') ADVANCE(291);
      END_STATE();
    case 161:
      if (lookahead == 'r') ADVANCE(140);
      END_STATE();
    case 162:
      if (lookahead == 'r') ADVANCE(220);
      END_STATE();
    case 163:
      if (lookahead == 'r') ADVANCE(83);
      END_STATE();
    case 164:
      if (lookahead == 'r') ADVANCE(24);
      END_STATE();
    case 165:
      if (lookahead == 'r') ADVANCE(175);
      END_STATE();
    case 166:
      if (lookahead == 'r') ADVANCE(22);
      END_STATE();
    case 167:
      if (lookahead == 'r') ADVANCE(219);
      END_STATE();
    case 168:
      if (lookahead == 'r') ADVANCE(198);
      END_STATE();
    case 169:
      if (lookahead == 'r') ADVANCE(197);
      END_STATE();
    case 170:
      if (lookahead == 'r') ADVANCE(26);
      END_STATE();
    case 171:
      if (lookahead == 'r') ADVANCE(146);
      END_STATE();
    case 172:
      if (lookahead == 'r') ADVANCE(82);
      END_STATE();
    case 173:
      if (lookahead == 'r') ADVANCE(171);
      END_STATE();
    case 174:
      if (lookahead == 's') ADVANCE(283);
      END_STATE();
    case 175:
      if (lookahead == 's') ADVANCE(281);
      END_STATE();
    case 176:
      if (lookahead == 's') ADVANCE(273);
      END_STATE();
    case 177:
      if (lookahead == 's') ADVANCE(18);
      END_STATE();
    case 178:
      if (lookahead == 's') ADVANCE(268);
      END_STATE();
    case 179:
      if (lookahead == 's') ADVANCE(275);
      END_STATE();
    case 180:
      if (lookahead == 's') ADVANCE(264);
      END_STATE();
    case 181:
      if (lookahead == 's') ADVANCE(277);
      END_STATE();
    case 182:
      if (lookahead == 's') ADVANCE(279);
      END_STATE();
    case 183:
      if (lookahead == 's') ADVANCE(43);
      END_STATE();
    case 184:
      if (lookahead == 's') ADVANCE(199);
      END_STATE();
    case 185:
      if (lookahead == 's') ADVANCE(210);
      END_STATE();
    case 186:
      if (lookahead == 's') ADVANCE(200);
      END_STATE();
    case 187:
      if (lookahead == 's') ADVANCE(46);
      END_STATE();
    case 188:
      if (lookahead == 's') ADVANCE(205);
      END_STATE();
    case 189:
      if (lookahead == 's') ADVANCE(68);
      END_STATE();
    case 190:
      if (lookahead == 's') ADVANCE(189);
      END_STATE();
    case 191:
      if (lookahead == 't') ADVANCE(1);
      END_STATE();
    case 192:
      if (lookahead == 't') ADVANCE(245);
      END_STATE();
    case 193:
      if (lookahead == 't') ADVANCE(267);
      END_STATE();
    case 194:
      if (lookahead == 't') ADVANCE(290);
      END_STATE();
    case 195:
      if (lookahead == 't') ADVANCE(251);
      END_STATE();
    case 196:
      if (lookahead == 't') ADVANCE(242);
      END_STATE();
    case 197:
      if (lookahead == 't') ADVANCE(295);
      END_STATE();
    case 198:
      if (lookahead == 't') ADVANCE(224);
      END_STATE();
    case 199:
      if (lookahead == 't') ADVANCE(137);
      END_STATE();
    case 200:
      if (lookahead == 't') ADVANCE(174);
      END_STATE();
    case 201:
      if (lookahead == 't') ADVANCE(155);
      END_STATE();
    case 202:
      if (lookahead == 't') ADVANCE(176);
      END_STATE();
    case 203:
      if (lookahead == 't') ADVANCE(172);
      END_STATE();
    case 204:
      if (lookahead == 't') ADVANCE(91);
      END_STATE();
    case 205:
      if (lookahead == 't') ADVANCE(164);
      END_STATE();
    case 206:
      if (lookahead == 't') ADVANCE(179);
      END_STATE();
    case 207:
      if (lookahead == 't') ADVANCE(180);
      END_STATE();
    case 208:
      if (lookahead == 't') ADVANCE(64);
      END_STATE();
    case 209:
      if (lookahead == 't') ADVANCE(92);
      END_STATE();
    case 210:
      if (lookahead == 't') ADVANCE(36);
      END_STATE();
    case 211:
      if (lookahead == 'u') ADVANCE(37);
      END_STATE();
    case 212:
      if (lookahead == 'u') ADVANCE(106);
      END_STATE();
    case 213:
      if (lookahead == 'u') ADVANCE(201);
      END_STATE();
    case 214:
      if (lookahead == 'u') ADVANCE(103);
      END_STATE();
    case 215:
      if (lookahead == 'u') ADVANCE(44);
      END_STATE();
    case 216:
      if (lookahead == 'u') ADVANCE(202);
      END_STATE();
    case 217:
      if (lookahead == 'u') ADVANCE(206);
      END_STATE();
    case 218:
      if (lookahead == 'u') ADVANCE(74);
      END_STATE();
    case 219:
      if (lookahead == 'u') ADVANCE(32);
      END_STATE();
    case 220:
      if (lookahead == 'v') ADVANCE(84);
      END_STATE();
    case 221:
      if (lookahead == 'v') ADVANCE(61);
      END_STATE();
    case 222:
      if (lookahead == 'w') ADVANCE(244);
      END_STATE();
    case 223:
      if (lookahead == 'y') ADVANCE(247);
      END_STATE();
    case 224:
      if (lookahead == 'y') ADVANCE(292);
      END_STATE();
    case 225:
      if (lookahead == 'y') ADVANCE(153);
      END_STATE();
    case 226:
      if (lookahead == '|') ADVANCE(306);
      END_STATE();
    case 227:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(324);
      END_STATE();
    case 228:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(315);
      END_STATE();
    case 229:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(323);
      END_STATE();
    case 230:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(229);
      END_STATE();
    case 231:
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(7);
      END_STATE();
    case 232:
      if (eof) ADVANCE(233);
      ADVANCE_MAP(
        ')', 256,
        ',', 239,
        '/', 10,
        '<', 258,
        '=', 249,
        '>', 260,
        'a', 71,
        'c', 138,
        'p', 89,
        's', 34,
        't', 225,
        'w', 139,
        '{', 238,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(232);
      END_STATE();
    case 233:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 234:
      ACCEPT_TOKEN(anon_sym_module);
      END_STATE();
    case 235:
      ACCEPT_TOKEN(anon_sym_use);
      END_STATE();
    case 236:
      ACCEPT_TOKEN(anon_sym_DOT);
      if (lookahead == '.') ADVANCE(308);
      END_STATE();
    case 237:
      ACCEPT_TOKEN(anon_sym_STAR);
      END_STATE();
    case 238:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 239:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 240:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 241:
      ACCEPT_TOKEN(anon_sym_as);
      END_STATE();
    case 242:
      ACCEPT_TOKEN(anon_sym_component);
      END_STATE();
    case 243:
      ACCEPT_TOKEN(anon_sym_pipeline);
      END_STATE();
    case 244:
      ACCEPT_TOKEN(anon_sym_workflow);
      END_STATE();
    case 245:
      ACCEPT_TOKEN(anon_sym_agent);
      END_STATE();
    case 246:
      ACCEPT_TOKEN(anon_sym_schema);
      END_STATE();
    case 247:
      ACCEPT_TOKEN(anon_sym_policy);
      END_STATE();
    case 248:
      ACCEPT_TOKEN(anon_sym_type);
      END_STATE();
    case 249:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 250:
      ACCEPT_TOKEN(anon_sym_EQ);
      if (lookahead == '=') ADVANCE(301);
      END_STATE();
    case 251:
      ACCEPT_TOKEN(anon_sym_struct);
      END_STATE();
    case 252:
      ACCEPT_TOKEN(anon_sym_struct);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 253:
      ACCEPT_TOKEN(anon_sym_enum);
      END_STATE();
    case 254:
      ACCEPT_TOKEN(anon_sym_enum);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 255:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 256:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 257:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 258:
      ACCEPT_TOKEN(anon_sym_LT);
      END_STATE();
    case 259:
      ACCEPT_TOKEN(anon_sym_LT);
      if (lookahead == '=') ADVANCE(303);
      END_STATE();
    case 260:
      ACCEPT_TOKEN(anon_sym_GT);
      END_STATE();
    case 261:
      ACCEPT_TOKEN(anon_sym_GT);
      if (lookahead == '=') ADVANCE(304);
      END_STATE();
    case 262:
      ACCEPT_TOKEN(anon_sym_service);
      END_STATE();
    case 263:
      ACCEPT_TOKEN(anon_sym_goal);
      END_STATE();
    case 264:
      ACCEPT_TOKEN(anon_sym_constraints);
      END_STATE();
    case 265:
      ACCEPT_TOKEN(anon_sym_DASH);
      END_STATE();
    case 266:
      ACCEPT_TOKEN(anon_sym_depends_on);
      END_STATE();
    case 267:
      ACCEPT_TOKEN(anon_sym_budget);
      END_STATE();
    case 268:
      ACCEPT_TOKEN(anon_sym_metrics);
      END_STATE();
    case 269:
      ACCEPT_TOKEN(anon_sym_counter);
      END_STATE();
    case 270:
      ACCEPT_TOKEN(anon_sym_gauge);
      END_STATE();
    case 271:
      ACCEPT_TOKEN(anon_sym_histogram);
      END_STATE();
    case 272:
      ACCEPT_TOKEN(anon_sym_rpc);
      END_STATE();
    case 273:
      ACCEPT_TOKEN(anon_sym_inputs);
      END_STATE();
    case 274:
      ACCEPT_TOKEN(anon_sym_inputs);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 275:
      ACCEPT_TOKEN(anon_sym_outputs);
      END_STATE();
    case 276:
      ACCEPT_TOKEN(anon_sym_outputs);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 277:
      ACCEPT_TOKEN(anon_sym_preconditions);
      END_STATE();
    case 278:
      ACCEPT_TOKEN(anon_sym_preconditions);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 279:
      ACCEPT_TOKEN(anon_sym_postconditions);
      END_STATE();
    case 280:
      ACCEPT_TOKEN(anon_sym_postconditions);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 281:
      ACCEPT_TOKEN(anon_sym_errors);
      END_STATE();
    case 282:
      ACCEPT_TOKEN(anon_sym_errors);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 283:
      ACCEPT_TOKEN(anon_sym_tests);
      END_STATE();
    case 284:
      ACCEPT_TOKEN(anon_sym_tests);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 285:
      ACCEPT_TOKEN(anon_sym_scenario);
      END_STATE();
    case 286:
      ACCEPT_TOKEN(anon_sym_given);
      END_STATE();
    case 287:
      ACCEPT_TOKEN(anon_sym_given);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 288:
      ACCEPT_TOKEN(anon_sym_when);
      END_STATE();
    case 289:
      ACCEPT_TOKEN(anon_sym_when);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 290:
      ACCEPT_TOKEN(anon_sym_expect);
      if (lookahead == '_') ADVANCE(65);
      END_STATE();
    case 291:
      ACCEPT_TOKEN(anon_sym_expect_error);
      END_STATE();
    case 292:
      ACCEPT_TOKEN(anon_sym_property);
      END_STATE();
    case 293:
      ACCEPT_TOKEN(anon_sym_forall);
      END_STATE();
    case 294:
      ACCEPT_TOKEN(anon_sym_forall);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 295:
      ACCEPT_TOKEN(anon_sym_assert);
      END_STATE();
    case 296:
      ACCEPT_TOKEN(anon_sym_assert);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 297:
      ACCEPT_TOKEN(anon_sym_in);
      END_STATE();
    case 298:
      ACCEPT_TOKEN(anon_sym_in);
      if (lookahead == 'p') ADVANCE(409);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 299:
      ACCEPT_TOKEN(anon_sym_in);
      if (lookahead == 'p') ADVANCE(216);
      END_STATE();
    case 300:
      ACCEPT_TOKEN(anon_sym_in);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 301:
      ACCEPT_TOKEN(anon_sym_EQ_EQ);
      END_STATE();
    case 302:
      ACCEPT_TOKEN(anon_sym_BANG_EQ);
      END_STATE();
    case 303:
      ACCEPT_TOKEN(anon_sym_LT_EQ);
      END_STATE();
    case 304:
      ACCEPT_TOKEN(anon_sym_GT_EQ);
      END_STATE();
    case 305:
      ACCEPT_TOKEN(anon_sym_AMP_AMP);
      END_STATE();
    case 306:
      ACCEPT_TOKEN(anon_sym_PIPE_PIPE);
      END_STATE();
    case 307:
      ACCEPT_TOKEN(anon_sym_notin);
      END_STATE();
    case 308:
      ACCEPT_TOKEN(anon_sym_DOT_DOT);
      if (lookahead == '<') ADVANCE(309);
      END_STATE();
    case 309:
      ACCEPT_TOKEN(anon_sym_DOT_DOT_LT);
      END_STATE();
    case 310:
      ACCEPT_TOKEN(anon_sym_BANG);
      END_STATE();
    case 311:
      ACCEPT_TOKEN(anon_sym_BANG);
      if (lookahead == '=') ADVANCE(302);
      END_STATE();
    case 312:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 313:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 314:
      ACCEPT_TOKEN(sym_integer_literal);
      ADVANCE_MAP(
        '%', 325,
        '.', 228,
        'm', 322,
        'd', 321,
        'h', 321,
        's', 321,
        'w', 321,
        'y', 321,
      );
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(314);
      END_STATE();
    case 315:
      ACCEPT_TOKEN(sym_float_literal);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(315);
      END_STATE();
    case 316:
      ACCEPT_TOKEN(sym_string_literal);
      END_STATE();
    case 317:
      ACCEPT_TOKEN(anon_sym_true);
      END_STATE();
    case 318:
      ACCEPT_TOKEN(anon_sym_true);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 319:
      ACCEPT_TOKEN(anon_sym_false);
      END_STATE();
    case 320:
      ACCEPT_TOKEN(anon_sym_false);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 321:
      ACCEPT_TOKEN(sym_duration_literal);
      END_STATE();
    case 322:
      ACCEPT_TOKEN(sym_duration_literal);
      if (lookahead == 'i') ADVANCE(112);
      if (lookahead == 's') ADVANCE(321);
      END_STATE();
    case 323:
      ACCEPT_TOKEN(sym_money_literal);
      END_STATE();
    case 324:
      ACCEPT_TOKEN(sym_money_literal);
      if (lookahead == '.') ADVANCE(230);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(324);
      END_STATE();
    case 325:
      ACCEPT_TOKEN(sym_percentage_literal);
      END_STATE();
    case 326:
      ACCEPT_TOKEN(sym_null_literal);
      END_STATE();
    case 327:
      ACCEPT_TOKEN(sym_null_literal);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 328:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == ' ') ADVANCE(85);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 329:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(349);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 330:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(353);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 331:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'c') ADVANCE(367);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 332:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'c') ADVANCE(396);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 333:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'c') ADVANCE(372);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 334:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'd') ADVANCE(346);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 335:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'd') ADVANCE(348);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 336:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(318);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 337:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(320);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 338:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(331);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 339:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(380);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 340:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(358);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 341:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(359);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 342:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(390);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 343:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'h') ADVANCE(340);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 344:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(411);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 345:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(368);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 346:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(397);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 347:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(371);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 348:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(402);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 349:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(388);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 350:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(327);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 351:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(294);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 352:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(350);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 353:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(351);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 354:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'm') ADVANCE(254);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 355:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(298);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 356:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(334);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 357:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(300);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 358:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(289);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 359:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(287);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 360:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(405);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 361:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(386);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 362:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(387);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 363:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(373);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 364:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(335);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 365:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(393);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 366:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(389);
      if (lookahead == 'r') ADVANCE(338);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 367:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(356);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 368:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(361);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 369:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(378);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 370:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(381);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 371:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(362);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 372:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'o') ADVANCE(364);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 373:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'p') ADVANCE(409);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 374:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'p') ADVANCE(410);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 375:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(404);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 376:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(369);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 377:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(376);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 378:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(383);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 379:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(408);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 380:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(395);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 381:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(330);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 382:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(284);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 383:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(282);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 384:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(274);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 385:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(276);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 386:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(278);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 387:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(280);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 388:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(337);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 389:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(403);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 390:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(398);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 391:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(339);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 392:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(391);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 393:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(328);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 394:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(374);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 395:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(296);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 396:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(252);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 397:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(345);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 398:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(382);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 399:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(384);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 400:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(385);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 401:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(379);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 402:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(347);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 403:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(333);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 404:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(336);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 405:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(354);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 406:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(352);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 407:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(394);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 408:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(332);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 409:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(399);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 410:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(400);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 411:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'v') ADVANCE(341);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 412:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(412);
      END_STATE();
    case 413:
      ACCEPT_TOKEN(sym_comment);
      END_STATE();
    case 414:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(414);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 0},
  [2] = {.lex_state = 3},
  [3] = {.lex_state = 3},
  [4] = {.lex_state = 3},
  [5] = {.lex_state = 3},
  [6] = {.lex_state = 3},
  [7] = {.lex_state = 3},
  [8] = {.lex_state = 3},
  [9] = {.lex_state = 3},
  [10] = {.lex_state = 3},
  [11] = {.lex_state = 3},
  [12] = {.lex_state = 3},
  [13] = {.lex_state = 3},
  [14] = {.lex_state = 3},
  [15] = {.lex_state = 3},
  [16] = {.lex_state = 3},
  [17] = {.lex_state = 3},
  [18] = {.lex_state = 6},
  [19] = {.lex_state = 0},
  [20] = {.lex_state = 6},
  [21] = {.lex_state = 6},
  [22] = {.lex_state = 6},
  [23] = {.lex_state = 5},
  [24] = {.lex_state = 6},
  [25] = {.lex_state = 6},
  [26] = {.lex_state = 6},
  [27] = {.lex_state = 6},
  [28] = {.lex_state = 6},
  [29] = {.lex_state = 6},
  [30] = {.lex_state = 6},
  [31] = {.lex_state = 0},
  [32] = {.lex_state = 5},
  [33] = {.lex_state = 5},
  [34] = {.lex_state = 6},
  [35] = {.lex_state = 5},
  [36] = {.lex_state = 5},
  [37] = {.lex_state = 5},
  [38] = {.lex_state = 6},
  [39] = {.lex_state = 5},
  [40] = {.lex_state = 6},
  [41] = {.lex_state = 6},
  [42] = {.lex_state = 6},
  [43] = {.lex_state = 6},
  [44] = {.lex_state = 6},
  [45] = {.lex_state = 6},
  [46] = {.lex_state = 6},
  [47] = {.lex_state = 3},
  [48] = {.lex_state = 6},
  [49] = {.lex_state = 5},
  [50] = {.lex_state = 5},
  [51] = {.lex_state = 6},
  [52] = {.lex_state = 6},
  [53] = {.lex_state = 6},
  [54] = {.lex_state = 6},
  [55] = {.lex_state = 6},
  [56] = {.lex_state = 5},
  [57] = {.lex_state = 6},
  [58] = {.lex_state = 5},
  [59] = {.lex_state = 5},
  [60] = {.lex_state = 5},
  [61] = {.lex_state = 6},
  [62] = {.lex_state = 6},
  [63] = {.lex_state = 6},
  [64] = {.lex_state = 0},
  [65] = {.lex_state = 0},
  [66] = {.lex_state = 0},
  [67] = {.lex_state = 0},
  [68] = {.lex_state = 0},
  [69] = {.lex_state = 0},
  [70] = {.lex_state = 0},
  [71] = {.lex_state = 4},
  [72] = {.lex_state = 2},
  [73] = {.lex_state = 2},
  [74] = {.lex_state = 4},
  [75] = {.lex_state = 0},
  [76] = {.lex_state = 0},
  [77] = {.lex_state = 4},
  [78] = {.lex_state = 2},
  [79] = {.lex_state = 2},
  [80] = {.lex_state = 2},
  [81] = {.lex_state = 2},
  [82] = {.lex_state = 2},
  [83] = {.lex_state = 4},
  [84] = {.lex_state = 2},
  [85] = {.lex_state = 2},
  [86] = {.lex_state = 4},
  [87] = {.lex_state = 2},
  [88] = {.lex_state = 4},
  [89] = {.lex_state = 2},
  [90] = {.lex_state = 2},
  [91] = {.lex_state = 2},
  [92] = {.lex_state = 4},
  [93] = {.lex_state = 4},
  [94] = {.lex_state = 2},
  [95] = {.lex_state = 2},
  [96] = {.lex_state = 2},
  [97] = {.lex_state = 4},
  [98] = {.lex_state = 2},
  [99] = {.lex_state = 4},
  [100] = {.lex_state = 4},
  [101] = {.lex_state = 4},
  [102] = {.lex_state = 4},
  [103] = {.lex_state = 4},
  [104] = {.lex_state = 2},
  [105] = {.lex_state = 2},
  [106] = {.lex_state = 2},
  [107] = {.lex_state = 2},
  [108] = {.lex_state = 4},
  [109] = {.lex_state = 3},
  [110] = {.lex_state = 4},
  [111] = {.lex_state = 2},
  [112] = {.lex_state = 0},
  [113] = {.lex_state = 2},
  [114] = {.lex_state = 232},
  [115] = {.lex_state = 0},
  [116] = {.lex_state = 0},
  [117] = {.lex_state = 0},
  [118] = {.lex_state = 0},
  [119] = {.lex_state = 2},
  [120] = {.lex_state = 0},
  [121] = {.lex_state = 2},
  [122] = {.lex_state = 232},
  [123] = {.lex_state = 232},
  [124] = {.lex_state = 3},
  [125] = {.lex_state = 3},
  [126] = {.lex_state = 3},
  [127] = {.lex_state = 0},
  [128] = {.lex_state = 3},
  [129] = {.lex_state = 13},
  [130] = {.lex_state = 232},
  [131] = {.lex_state = 3},
  [132] = {.lex_state = 0},
  [133] = {.lex_state = 3},
  [134] = {.lex_state = 0},
  [135] = {.lex_state = 3},
  [136] = {.lex_state = 0},
  [137] = {.lex_state = 0},
  [138] = {.lex_state = 0},
  [139] = {.lex_state = 0},
  [140] = {.lex_state = 0},
  [141] = {.lex_state = 0},
  [142] = {.lex_state = 14},
  [143] = {.lex_state = 0},
  [144] = {.lex_state = 0},
  [145] = {.lex_state = 14},
  [146] = {.lex_state = 0},
  [147] = {.lex_state = 0},
  [148] = {.lex_state = 14},
  [149] = {.lex_state = 0},
  [150] = {.lex_state = 0},
  [151] = {.lex_state = 0},
  [152] = {.lex_state = 0},
  [153] = {.lex_state = 14},
  [154] = {.lex_state = 0},
  [155] = {.lex_state = 0},
  [156] = {.lex_state = 0},
  [157] = {.lex_state = 14},
  [158] = {.lex_state = 14},
  [159] = {.lex_state = 0},
  [160] = {.lex_state = 0},
  [161] = {.lex_state = 0},
  [162] = {.lex_state = 0},
  [163] = {.lex_state = 0},
  [164] = {.lex_state = 0},
  [165] = {.lex_state = 0},
  [166] = {.lex_state = 0},
  [167] = {.lex_state = 0},
  [168] = {.lex_state = 0},
  [169] = {.lex_state = 14},
  [170] = {.lex_state = 0},
  [171] = {.lex_state = 0},
  [172] = {.lex_state = 0},
  [173] = {.lex_state = 14},
  [174] = {.lex_state = 0},
  [175] = {.lex_state = 0},
  [176] = {.lex_state = 0},
  [177] = {.lex_state = 0},
  [178] = {.lex_state = 0},
  [179] = {.lex_state = 0},
  [180] = {.lex_state = 0},
  [181] = {.lex_state = 0},
  [182] = {.lex_state = 0},
  [183] = {.lex_state = 0},
  [184] = {.lex_state = 0},
  [185] = {.lex_state = 0},
  [186] = {.lex_state = 0},
  [187] = {.lex_state = 0},
  [188] = {.lex_state = 0},
  [189] = {.lex_state = 0},
  [190] = {.lex_state = 0},
  [191] = {.lex_state = 0},
  [192] = {.lex_state = 0},
  [193] = {.lex_state = 0},
  [194] = {.lex_state = 0},
  [195] = {.lex_state = 0},
  [196] = {.lex_state = 15},
  [197] = {.lex_state = 0},
  [198] = {.lex_state = 0},
  [199] = {.lex_state = 0},
  [200] = {.lex_state = 0},
  [201] = {.lex_state = 0},
  [202] = {.lex_state = 9},
  [203] = {.lex_state = 9},
  [204] = {.lex_state = 9},
  [205] = {.lex_state = 0},
  [206] = {.lex_state = 0},
  [207] = {.lex_state = 0},
  [208] = {.lex_state = 3},
  [209] = {.lex_state = 9},
  [210] = {.lex_state = 9},
  [211] = {.lex_state = 9},
  [212] = {.lex_state = 9},
  [213] = {.lex_state = 0},
  [214] = {.lex_state = 9},
  [215] = {.lex_state = 9},
  [216] = {.lex_state = 9},
  [217] = {.lex_state = 6},
  [218] = {.lex_state = 9},
  [219] = {.lex_state = 0},
  [220] = {.lex_state = 6},
  [221] = {.lex_state = 0},
  [222] = {.lex_state = 0},
  [223] = {.lex_state = 0},
  [224] = {.lex_state = 9},
  [225] = {.lex_state = 9},
  [226] = {.lex_state = 9},
  [227] = {.lex_state = 0},
  [228] = {.lex_state = 9},
  [229] = {.lex_state = 0},
  [230] = {.lex_state = 6},
  [231] = {.lex_state = 0},
  [232] = {.lex_state = 0},
  [233] = {.lex_state = 0},
  [234] = {.lex_state = 0},
  [235] = {.lex_state = 0},
  [236] = {.lex_state = 0},
  [237] = {.lex_state = 0},
  [238] = {.lex_state = 0},
  [239] = {.lex_state = 0},
  [240] = {.lex_state = 9},
  [241] = {.lex_state = 0},
  [242] = {.lex_state = 6},
  [243] = {.lex_state = 0},
  [244] = {.lex_state = 9},
  [245] = {.lex_state = 6},
  [246] = {.lex_state = 9},
  [247] = {.lex_state = 0},
  [248] = {.lex_state = 6},
  [249] = {.lex_state = 0},
  [250] = {.lex_state = 6},
  [251] = {.lex_state = 0},
  [252] = {.lex_state = 0},
  [253] = {.lex_state = 9},
  [254] = {.lex_state = 0},
  [255] = {.lex_state = 0},
  [256] = {.lex_state = 9},
  [257] = {.lex_state = 9},
  [258] = {.lex_state = 0},
  [259] = {.lex_state = 0},
  [260] = {.lex_state = 0},
  [261] = {.lex_state = 0},
  [262] = {.lex_state = 9},
  [263] = {.lex_state = 0},
  [264] = {.lex_state = 0},
  [265] = {.lex_state = 0},
  [266] = {.lex_state = 9},
  [267] = {.lex_state = 0},
  [268] = {.lex_state = 0},
  [269] = {.lex_state = 9},
  [270] = {.lex_state = 9},
  [271] = {.lex_state = 0},
  [272] = {.lex_state = 0},
  [273] = {.lex_state = 9},
  [274] = {.lex_state = 9},
  [275] = {.lex_state = 9},
  [276] = {.lex_state = 0},
  [277] = {.lex_state = 0},
  [278] = {.lex_state = 0},
  [279] = {.lex_state = 6},
  [280] = {.lex_state = 0},
  [281] = {.lex_state = 9},
  [282] = {.lex_state = 0},
  [283] = {.lex_state = 0},
  [284] = {.lex_state = 0},
  [285] = {.lex_state = 9},
  [286] = {.lex_state = 0},
  [287] = {.lex_state = 0},
  [288] = {.lex_state = 9},
  [289] = {.lex_state = 9},
  [290] = {.lex_state = 9},
  [291] = {.lex_state = 9},
  [292] = {.lex_state = 0},
  [293] = {.lex_state = 9},
  [294] = {.lex_state = 9},
  [295] = {.lex_state = 0},
  [296] = {.lex_state = 2},
  [297] = {.lex_state = 9},
  [298] = {.lex_state = 0},
  [299] = {.lex_state = 0},
  [300] = {.lex_state = 0},
  [301] = {.lex_state = 0},
  [302] = {.lex_state = 0},
  [303] = {.lex_state = 9},
  [304] = {.lex_state = 0},
  [305] = {.lex_state = 0},
  [306] = {.lex_state = 0},
  [307] = {.lex_state = 9},
  [308] = {.lex_state = 0},
  [309] = {.lex_state = 0},
  [310] = {.lex_state = 0},
  [311] = {.lex_state = 0},
  [312] = {.lex_state = 0},
  [313] = {.lex_state = 0},
  [314] = {.lex_state = 0},
  [315] = {.lex_state = 0},
  [316] = {.lex_state = 0},
  [317] = {.lex_state = 0},
  [318] = {.lex_state = 0},
  [319] = {.lex_state = 0},
  [320] = {.lex_state = 0},
  [321] = {.lex_state = 0},
  [322] = {.lex_state = 9},
  [323] = {.lex_state = 0},
  [324] = {.lex_state = 9},
  [325] = {.lex_state = 9},
  [326] = {.lex_state = 9},
  [327] = {.lex_state = 9},
  [328] = {.lex_state = 9},
  [329] = {.lex_state = 9},
  [330] = {.lex_state = 9},
  [331] = {.lex_state = 9},
  [332] = {.lex_state = 9},
  [333] = {.lex_state = 9},
  [334] = {.lex_state = 9},
  [335] = {.lex_state = 0},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_module] = ACTIONS(1),
    [anon_sym_use] = ACTIONS(1),
    [anon_sym_DOT] = ACTIONS(1),
    [anon_sym_STAR] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_as] = ACTIONS(1),
    [anon_sym_component] = ACTIONS(1),
    [anon_sym_pipeline] = ACTIONS(1),
    [anon_sym_workflow] = ACTIONS(1),
    [anon_sym_agent] = ACTIONS(1),
    [anon_sym_schema] = ACTIONS(1),
    [anon_sym_policy] = ACTIONS(1),
    [anon_sym_type] = ACTIONS(1),
    [anon_sym_EQ] = ACTIONS(1),
    [anon_sym_struct] = ACTIONS(1),
    [anon_sym_enum] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [anon_sym_LT] = ACTIONS(1),
    [anon_sym_GT] = ACTIONS(1),
    [anon_sym_service] = ACTIONS(1),
    [anon_sym_goal] = ACTIONS(1),
    [anon_sym_constraints] = ACTIONS(1),
    [anon_sym_DASH] = ACTIONS(1),
    [anon_sym_depends_on] = ACTIONS(1),
    [anon_sym_budget] = ACTIONS(1),
    [anon_sym_metrics] = ACTIONS(1),
    [anon_sym_counter] = ACTIONS(1),
    [anon_sym_gauge] = ACTIONS(1),
    [anon_sym_histogram] = ACTIONS(1),
    [anon_sym_rpc] = ACTIONS(1),
    [anon_sym_inputs] = ACTIONS(1),
    [anon_sym_outputs] = ACTIONS(1),
    [anon_sym_preconditions] = ACTIONS(1),
    [anon_sym_postconditions] = ACTIONS(1),
    [anon_sym_errors] = ACTIONS(1),
    [anon_sym_tests] = ACTIONS(1),
    [anon_sym_scenario] = ACTIONS(1),
    [anon_sym_given] = ACTIONS(1),
    [anon_sym_when] = ACTIONS(1),
    [anon_sym_expect] = ACTIONS(1),
    [anon_sym_expect_error] = ACTIONS(1),
    [anon_sym_property] = ACTIONS(1),
    [anon_sym_forall] = ACTIONS(1),
    [anon_sym_in] = ACTIONS(1),
    [anon_sym_EQ_EQ] = ACTIONS(1),
    [anon_sym_BANG_EQ] = ACTIONS(1),
    [anon_sym_LT_EQ] = ACTIONS(1),
    [anon_sym_GT_EQ] = ACTIONS(1),
    [anon_sym_AMP_AMP] = ACTIONS(1),
    [anon_sym_PIPE_PIPE] = ACTIONS(1),
    [anon_sym_notin] = ACTIONS(1),
    [anon_sym_DOT_DOT] = ACTIONS(1),
    [anon_sym_DOT_DOT_LT] = ACTIONS(1),
    [anon_sym_BANG] = ACTIONS(1),
    [anon_sym_LBRACK] = ACTIONS(1),
    [anon_sym_RBRACK] = ACTIONS(1),
    [sym_integer_literal] = ACTIONS(1),
    [sym_float_literal] = ACTIONS(1),
    [sym_string_literal] = ACTIONS(1),
    [anon_sym_true] = ACTIONS(1),
    [anon_sym_false] = ACTIONS(1),
    [sym_duration_literal] = ACTIONS(1),
    [sym_money_literal] = ACTIONS(1),
    [sym_percentage_literal] = ACTIONS(1),
    [sym_null_literal] = ACTIONS(1),
    [sym_comment] = ACTIONS(3),
  },
  [1] = {
    [sym_source_file] = STATE(335),
    [sym_module_declaration] = STATE(31),
    [anon_sym_module] = ACTIONS(5),
    [sym_comment] = ACTIONS(3),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(11), 1,
      anon_sym_LPAREN,
    ACTIONS(7), 6,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_expect,
      anon_sym_in,
      anon_sym_DOT_DOT,
    ACTIONS(9), 22,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_given,
      anon_sym_when,
      anon_sym_expect_error,
      anon_sym_forall,
      anon_sym_assert,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [39] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(13), 1,
      anon_sym_DOT,
    ACTIONS(19), 1,
      anon_sym_expect,
    ACTIONS(17), 4,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_in,
      anon_sym_DOT_DOT,
    ACTIONS(21), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
    ACTIONS(15), 14,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_given,
      anon_sym_when,
      anon_sym_expect_error,
      anon_sym_forall,
      anon_sym_assert,
  [81] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(13), 1,
      anon_sym_DOT,
    ACTIONS(25), 5,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_expect,
      anon_sym_in,
      anon_sym_DOT_DOT,
    ACTIONS(23), 22,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_given,
      anon_sym_when,
      anon_sym_expect_error,
      anon_sym_forall,
      anon_sym_assert,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [119] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(27), 6,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_expect,
      anon_sym_in,
      anon_sym_DOT_DOT,
    ACTIONS(29), 22,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_given,
      anon_sym_when,
      anon_sym_expect_error,
      anon_sym_forall,
      anon_sym_assert,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [155] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(31), 6,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_expect,
      anon_sym_in,
      anon_sym_DOT_DOT,
    ACTIONS(33), 22,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_given,
      anon_sym_when,
      anon_sym_expect_error,
      anon_sym_forall,
      anon_sym_assert,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [191] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(35), 6,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_expect,
      anon_sym_in,
      anon_sym_DOT_DOT,
    ACTIONS(37), 22,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_given,
      anon_sym_when,
      anon_sym_expect_error,
      anon_sym_forall,
      anon_sym_assert,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [227] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 6,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_expect,
      anon_sym_in,
      anon_sym_DOT_DOT,
    ACTIONS(9), 22,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_given,
      anon_sym_when,
      anon_sym_expect_error,
      anon_sym_forall,
      anon_sym_assert,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [263] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(13), 1,
      anon_sym_DOT,
    ACTIONS(41), 5,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_expect,
      anon_sym_in,
      anon_sym_DOT_DOT,
    ACTIONS(39), 22,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_given,
      anon_sym_when,
      anon_sym_expect_error,
      anon_sym_forall,
      anon_sym_assert,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [301] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(43), 6,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_expect,
      anon_sym_in,
      anon_sym_DOT_DOT,
    ACTIONS(45), 22,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_given,
      anon_sym_when,
      anon_sym_expect_error,
      anon_sym_forall,
      anon_sym_assert,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [337] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(47), 6,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_expect,
      anon_sym_in,
      anon_sym_DOT_DOT,
    ACTIONS(49), 22,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_given,
      anon_sym_when,
      anon_sym_expect_error,
      anon_sym_forall,
      anon_sym_assert,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [373] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(51), 6,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_expect,
      anon_sym_in,
      anon_sym_DOT_DOT,
    ACTIONS(53), 22,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_given,
      anon_sym_when,
      anon_sym_expect_error,
      anon_sym_forall,
      anon_sym_assert,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [409] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 6,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_expect,
      anon_sym_in,
      anon_sym_DOT_DOT,
    ACTIONS(57), 22,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_given,
      anon_sym_when,
      anon_sym_expect_error,
      anon_sym_forall,
      anon_sym_assert,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [445] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(59), 6,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_expect,
      anon_sym_in,
      anon_sym_DOT_DOT,
    ACTIONS(61), 22,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_given,
      anon_sym_when,
      anon_sym_expect_error,
      anon_sym_forall,
      anon_sym_assert,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [481] = 8,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(13), 1,
      anon_sym_DOT,
    ACTIONS(63), 1,
      anon_sym_COMMA,
    ACTIONS(67), 1,
      anon_sym_expect,
    STATE(127), 1,
      aux_sym_scenario_block_repeat1,
    ACTIONS(17), 4,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_in,
      anon_sym_DOT_DOT,
    ACTIONS(21), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
    ACTIONS(65), 11,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_given,
      anon_sym_when,
      anon_sym_expect_error,
  [526] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(13), 1,
      anon_sym_DOT,
    ACTIONS(63), 1,
      anon_sym_COMMA,
    STATE(126), 1,
      aux_sym_scenario_block_repeat1,
    ACTIONS(17), 4,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_in,
      anon_sym_DOT_DOT,
    ACTIONS(21), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
    ACTIONS(69), 12,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_given,
      anon_sym_when,
      anon_sym_forall,
      anon_sym_assert,
  [569] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(13), 1,
      anon_sym_DOT,
    ACTIONS(17), 4,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_in,
      anon_sym_DOT_DOT,
    ACTIONS(21), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
    ACTIONS(71), 13,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_given,
      anon_sym_when,
      anon_sym_forall,
      anon_sym_assert,
  [607] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(73), 1,
      anon_sym_RPAREN,
    ACTIONS(77), 1,
      anon_sym_LBRACK,
    ACTIONS(85), 1,
      sym_identifier,
    STATE(119), 1,
      sym_expression,
    STATE(239), 1,
      sym_constraint_arg,
    ACTIONS(75), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(79), 2,
      sym_integer_literal,
      sym_null_literal,
    ACTIONS(83), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(81), 5,
      sym_float_literal,
      sym_string_literal,
      sym_duration_literal,
      sym_money_literal,
      sym_percentage_literal,
    STATE(111), 7,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_field_expression,
      sym_list_expression,
      sym__literal,
      sym_boolean_literal,
  [654] = 13,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(87), 1,
      ts_builtin_sym_end,
    ACTIONS(89), 1,
      anon_sym_use,
    ACTIONS(91), 1,
      anon_sym_component,
    ACTIONS(93), 1,
      anon_sym_pipeline,
    ACTIONS(95), 1,
      anon_sym_workflow,
    ACTIONS(97), 1,
      anon_sym_agent,
    ACTIONS(99), 1,
      anon_sym_schema,
    ACTIONS(101), 1,
      anon_sym_policy,
    ACTIONS(103), 1,
      anon_sym_type,
    ACTIONS(105), 1,
      anon_sym_service,
    STATE(139), 2,
      sym_use_declaration,
      aux_sym_source_file_repeat1,
    STATE(68), 10,
      sym__declaration,
      sym_component_declaration,
      sym_pipeline_declaration,
      sym_workflow_declaration,
      sym_agent_declaration,
      sym_schema_declaration,
      sym_policy_declaration,
      sym_type_declaration,
      sym_service_declaration,
      aux_sym_source_file_repeat2,
  [704] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(77), 1,
      anon_sym_LBRACK,
    ACTIONS(107), 1,
      anon_sym_RBRACK,
    ACTIONS(109), 1,
      sym_identifier,
    STATE(81), 1,
      sym_expression,
    ACTIONS(75), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(79), 2,
      sym_integer_literal,
      sym_null_literal,
    ACTIONS(83), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(81), 5,
      sym_float_literal,
      sym_string_literal,
      sym_duration_literal,
      sym_money_literal,
      sym_percentage_literal,
    STATE(111), 7,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_field_expression,
      sym_list_expression,
      sym__literal,
      sym_boolean_literal,
  [748] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(77), 1,
      anon_sym_LBRACK,
    ACTIONS(109), 1,
      sym_identifier,
    ACTIONS(111), 1,
      anon_sym_RPAREN,
    STATE(98), 1,
      sym_expression,
    ACTIONS(75), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(79), 2,
      sym_integer_literal,
      sym_null_literal,
    ACTIONS(83), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(81), 5,
      sym_float_literal,
      sym_string_literal,
      sym_duration_literal,
      sym_money_literal,
      sym_percentage_literal,
    STATE(111), 7,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_field_expression,
      sym_list_expression,
      sym__literal,
      sym_boolean_literal,
  [792] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(77), 1,
      anon_sym_LBRACK,
    ACTIONS(109), 1,
      sym_identifier,
    ACTIONS(113), 1,
      anon_sym_RPAREN,
    STATE(96), 1,
      sym_expression,
    ACTIONS(75), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(79), 2,
      sym_integer_literal,
      sym_null_literal,
    ACTIONS(83), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(81), 5,
      sym_float_literal,
      sym_string_literal,
      sym_duration_literal,
      sym_money_literal,
      sym_percentage_literal,
    STATE(111), 7,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_field_expression,
      sym_list_expression,
      sym__literal,
      sym_boolean_literal,
  [836] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(115), 1,
      anon_sym_LPAREN,
    ACTIONS(9), 9,
      anon_sym_RBRACE,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
    ACTIONS(7), 12,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_in,
      anon_sym_DOT_DOT,
      sym_identifier,
  [868] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(77), 1,
      anon_sym_LBRACK,
    ACTIONS(109), 1,
      sym_identifier,
    ACTIONS(117), 1,
      anon_sym_RBRACK,
    STATE(80), 1,
      sym_expression,
    ACTIONS(75), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(79), 2,
      sym_integer_literal,
      sym_null_literal,
    ACTIONS(83), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(81), 5,
      sym_float_literal,
      sym_string_literal,
      sym_duration_literal,
      sym_money_literal,
      sym_percentage_literal,
    STATE(111), 7,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_field_expression,
      sym_list_expression,
      sym__literal,
      sym_boolean_literal,
  [912] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(77), 1,
      anon_sym_LBRACK,
    ACTIONS(109), 1,
      sym_identifier,
    ACTIONS(119), 1,
      anon_sym_RBRACK,
    STATE(78), 1,
      sym_expression,
    ACTIONS(75), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(79), 2,
      sym_integer_literal,
      sym_null_literal,
    ACTIONS(83), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(81), 5,
      sym_float_literal,
      sym_string_literal,
      sym_duration_literal,
      sym_money_literal,
      sym_percentage_literal,
    STATE(111), 7,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_field_expression,
      sym_list_expression,
      sym__literal,
      sym_boolean_literal,
  [956] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(123), 1,
      anon_sym_LBRACK,
    ACTIONS(131), 1,
      sym_identifier,
    STATE(100), 1,
      sym_expression,
    STATE(214), 1,
      sym_type_ref,
    ACTIONS(121), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(125), 2,
      sym_integer_literal,
      sym_null_literal,
    ACTIONS(129), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(127), 5,
      sym_float_literal,
      sym_string_literal,
      sym_duration_literal,
      sym_money_literal,
      sym_percentage_literal,
    STATE(99), 7,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_field_expression,
      sym_list_expression,
      sym__literal,
      sym_boolean_literal,
  [1000] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(77), 1,
      anon_sym_LBRACK,
    ACTIONS(109), 1,
      sym_identifier,
    ACTIONS(133), 1,
      anon_sym_RBRACK,
    STATE(90), 1,
      sym_expression,
    ACTIONS(75), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(79), 2,
      sym_integer_literal,
      sym_null_literal,
    ACTIONS(83), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(81), 5,
      sym_float_literal,
      sym_string_literal,
      sym_duration_literal,
      sym_money_literal,
      sym_percentage_literal,
    STATE(111), 7,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_field_expression,
      sym_list_expression,
      sym__literal,
      sym_boolean_literal,
  [1044] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(77), 1,
      anon_sym_LBRACK,
    ACTIONS(85), 1,
      sym_identifier,
    STATE(119), 1,
      sym_expression,
    STATE(260), 1,
      sym_constraint_arg,
    ACTIONS(75), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(79), 2,
      sym_integer_literal,
      sym_null_literal,
    ACTIONS(83), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(81), 5,
      sym_float_literal,
      sym_string_literal,
      sym_duration_literal,
      sym_money_literal,
      sym_percentage_literal,
    STATE(111), 7,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_field_expression,
      sym_list_expression,
      sym__literal,
      sym_boolean_literal,
  [1088] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(77), 1,
      anon_sym_LBRACK,
    ACTIONS(109), 1,
      sym_identifier,
    ACTIONS(135), 1,
      anon_sym_RPAREN,
    STATE(85), 1,
      sym_expression,
    ACTIONS(75), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(79), 2,
      sym_integer_literal,
      sym_null_literal,
    ACTIONS(83), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(81), 5,
      sym_float_literal,
      sym_string_literal,
      sym_duration_literal,
      sym_money_literal,
      sym_percentage_literal,
    STATE(111), 7,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_field_expression,
      sym_list_expression,
      sym__literal,
      sym_boolean_literal,
  [1132] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(77), 1,
      anon_sym_LBRACK,
    ACTIONS(109), 1,
      sym_identifier,
    ACTIONS(137), 1,
      anon_sym_RPAREN,
    STATE(104), 1,
      sym_expression,
    ACTIONS(75), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(79), 2,
      sym_integer_literal,
      sym_null_literal,
    ACTIONS(83), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(81), 5,
      sym_float_literal,
      sym_string_literal,
      sym_duration_literal,
      sym_money_literal,
      sym_percentage_literal,
    STATE(111), 7,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_field_expression,
      sym_list_expression,
      sym__literal,
      sym_boolean_literal,
  [1176] = 13,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(89), 1,
      anon_sym_use,
    ACTIONS(91), 1,
      anon_sym_component,
    ACTIONS(93), 1,
      anon_sym_pipeline,
    ACTIONS(95), 1,
      anon_sym_workflow,
    ACTIONS(97), 1,
      anon_sym_agent,
    ACTIONS(99), 1,
      anon_sym_schema,
    ACTIONS(101), 1,
      anon_sym_policy,
    ACTIONS(103), 1,
      anon_sym_type,
    ACTIONS(105), 1,
      anon_sym_service,
    ACTIONS(139), 1,
      ts_builtin_sym_end,
    STATE(19), 2,
      sym_use_declaration,
      aux_sym_source_file_repeat1,
    STATE(67), 10,
      sym__declaration,
      sym_component_declaration,
      sym_pipeline_declaration,
      sym_workflow_declaration,
      sym_agent_declaration,
      sym_schema_declaration,
      sym_policy_declaration,
      sym_type_declaration,
      sym_service_declaration,
      aux_sym_source_file_repeat2,
  [1226] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(141), 1,
      anon_sym_DOT,
    ACTIONS(39), 9,
      anon_sym_RBRACE,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
    ACTIONS(41), 11,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_in,
      anon_sym_DOT_DOT,
      sym_identifier,
  [1257] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(141), 1,
      anon_sym_DOT,
    ACTIONS(143), 1,
      anon_sym_RBRACE,
    ACTIONS(145), 4,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_in,
      anon_sym_DOT_DOT,
    ACTIONS(147), 7,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      sym_identifier,
    ACTIONS(149), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [1292] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(77), 1,
      anon_sym_LBRACK,
    ACTIONS(109), 1,
      sym_identifier,
    STATE(94), 1,
      sym_expression,
    ACTIONS(75), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(79), 2,
      sym_integer_literal,
      sym_null_literal,
    ACTIONS(83), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(81), 5,
      sym_float_literal,
      sym_string_literal,
      sym_duration_literal,
      sym_money_literal,
      sym_percentage_literal,
    STATE(111), 7,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_field_expression,
      sym_list_expression,
      sym__literal,
      sym_boolean_literal,
  [1333] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(141), 1,
      anon_sym_DOT,
    ACTIONS(23), 9,
      anon_sym_RBRACE,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
    ACTIONS(25), 11,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_in,
      anon_sym_DOT_DOT,
      sym_identifier,
  [1364] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(49), 9,
      anon_sym_RBRACE,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
    ACTIONS(47), 12,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_in,
      anon_sym_DOT_DOT,
      sym_identifier,
  [1393] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(9), 9,
      anon_sym_RBRACE,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
    ACTIONS(7), 12,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_in,
      anon_sym_DOT_DOT,
      sym_identifier,
  [1422] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(123), 1,
      anon_sym_LBRACK,
    ACTIONS(151), 1,
      sym_identifier,
    STATE(97), 1,
      sym_expression,
    ACTIONS(121), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(125), 2,
      sym_integer_literal,
      sym_null_literal,
    ACTIONS(129), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(127), 5,
      sym_float_literal,
      sym_string_literal,
      sym_duration_literal,
      sym_money_literal,
      sym_percentage_literal,
    STATE(99), 7,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_field_expression,
      sym_list_expression,
      sym__literal,
      sym_boolean_literal,
  [1463] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(45), 9,
      anon_sym_RBRACE,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
    ACTIONS(43), 12,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_in,
      anon_sym_DOT_DOT,
      sym_identifier,
  [1492] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(77), 1,
      anon_sym_LBRACK,
    ACTIONS(109), 1,
      sym_identifier,
    STATE(113), 1,
      sym_expression,
    ACTIONS(75), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(79), 2,
      sym_integer_literal,
      sym_null_literal,
    ACTIONS(83), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(81), 5,
      sym_float_literal,
      sym_string_literal,
      sym_duration_literal,
      sym_money_literal,
      sym_percentage_literal,
    STATE(111), 7,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_field_expression,
      sym_list_expression,
      sym__literal,
      sym_boolean_literal,
  [1533] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(123), 1,
      anon_sym_LBRACK,
    ACTIONS(151), 1,
      sym_identifier,
    STATE(110), 1,
      sym_expression,
    ACTIONS(121), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(125), 2,
      sym_integer_literal,
      sym_null_literal,
    ACTIONS(129), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(127), 5,
      sym_float_literal,
      sym_string_literal,
      sym_duration_literal,
      sym_money_literal,
      sym_percentage_literal,
    STATE(99), 7,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_field_expression,
      sym_list_expression,
      sym__literal,
      sym_boolean_literal,
  [1574] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(155), 1,
      anon_sym_LBRACK,
    ACTIONS(163), 1,
      sym_identifier,
    STATE(32), 1,
      sym_expression,
    ACTIONS(153), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(157), 2,
      sym_integer_literal,
      sym_null_literal,
    ACTIONS(161), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(159), 5,
      sym_float_literal,
      sym_string_literal,
      sym_duration_literal,
      sym_money_literal,
      sym_percentage_literal,
    STATE(37), 7,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_field_expression,
      sym_list_expression,
      sym__literal,
      sym_boolean_literal,
  [1615] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(167), 1,
      anon_sym_LBRACK,
    ACTIONS(175), 1,
      sym_identifier,
    STATE(17), 1,
      sym_expression,
    ACTIONS(165), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(169), 2,
      sym_integer_literal,
      sym_null_literal,
    ACTIONS(173), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(171), 5,
      sym_float_literal,
      sym_string_literal,
      sym_duration_literal,
      sym_money_literal,
      sym_percentage_literal,
    STATE(8), 7,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_field_expression,
      sym_list_expression,
      sym__literal,
      sym_boolean_literal,
  [1656] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(167), 1,
      anon_sym_LBRACK,
    ACTIONS(175), 1,
      sym_identifier,
    STATE(16), 1,
      sym_expression,
    ACTIONS(165), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(169), 2,
      sym_integer_literal,
      sym_null_literal,
    ACTIONS(173), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(171), 5,
      sym_float_literal,
      sym_string_literal,
      sym_duration_literal,
      sym_money_literal,
      sym_percentage_literal,
    STATE(8), 7,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_field_expression,
      sym_list_expression,
      sym__literal,
      sym_boolean_literal,
  [1697] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(167), 1,
      anon_sym_LBRACK,
    ACTIONS(175), 1,
      sym_identifier,
    STATE(15), 1,
      sym_expression,
    ACTIONS(165), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(169), 2,
      sym_integer_literal,
      sym_null_literal,
    ACTIONS(173), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(171), 5,
      sym_float_literal,
      sym_string_literal,
      sym_duration_literal,
      sym_money_literal,
      sym_percentage_literal,
    STATE(8), 7,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_field_expression,
      sym_list_expression,
      sym__literal,
      sym_boolean_literal,
  [1738] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(167), 1,
      anon_sym_LBRACK,
    ACTIONS(175), 1,
      sym_identifier,
    STATE(4), 1,
      sym_expression,
    ACTIONS(165), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(169), 2,
      sym_integer_literal,
      sym_null_literal,
    ACTIONS(173), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(171), 5,
      sym_float_literal,
      sym_string_literal,
      sym_duration_literal,
      sym_money_literal,
      sym_percentage_literal,
    STATE(8), 7,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_field_expression,
      sym_list_expression,
      sym__literal,
      sym_boolean_literal,
  [1779] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(13), 1,
      anon_sym_DOT,
    ACTIONS(17), 4,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_in,
      anon_sym_DOT_DOT,
    ACTIONS(21), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
    ACTIONS(177), 8,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
  [1812] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(77), 1,
      anon_sym_LBRACK,
    ACTIONS(109), 1,
      sym_identifier,
    STATE(121), 1,
      sym_expression,
    ACTIONS(75), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(79), 2,
      sym_integer_literal,
      sym_null_literal,
    ACTIONS(83), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(81), 5,
      sym_float_literal,
      sym_string_literal,
      sym_duration_literal,
      sym_money_literal,
      sym_percentage_literal,
    STATE(111), 7,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_field_expression,
      sym_list_expression,
      sym__literal,
      sym_boolean_literal,
  [1853] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(61), 9,
      anon_sym_RBRACE,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
    ACTIONS(59), 12,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_in,
      anon_sym_DOT_DOT,
      sym_identifier,
  [1882] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(57), 9,
      anon_sym_RBRACE,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
    ACTIONS(55), 12,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_in,
      anon_sym_DOT_DOT,
      sym_identifier,
  [1911] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(123), 1,
      anon_sym_LBRACK,
    ACTIONS(151), 1,
      sym_identifier,
    STATE(101), 1,
      sym_expression,
    ACTIONS(121), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(125), 2,
      sym_integer_literal,
      sym_null_literal,
    ACTIONS(129), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(127), 5,
      sym_float_literal,
      sym_string_literal,
      sym_duration_literal,
      sym_money_literal,
      sym_percentage_literal,
    STATE(99), 7,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_field_expression,
      sym_list_expression,
      sym__literal,
      sym_boolean_literal,
  [1952] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(167), 1,
      anon_sym_LBRACK,
    ACTIONS(175), 1,
      sym_identifier,
    STATE(47), 1,
      sym_expression,
    ACTIONS(165), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(169), 2,
      sym_integer_literal,
      sym_null_literal,
    ACTIONS(173), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(171), 5,
      sym_float_literal,
      sym_string_literal,
      sym_duration_literal,
      sym_money_literal,
      sym_percentage_literal,
    STATE(8), 7,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_field_expression,
      sym_list_expression,
      sym__literal,
      sym_boolean_literal,
  [1993] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(155), 1,
      anon_sym_LBRACK,
    ACTIONS(163), 1,
      sym_identifier,
    STATE(35), 1,
      sym_expression,
    ACTIONS(153), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(157), 2,
      sym_integer_literal,
      sym_null_literal,
    ACTIONS(161), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(159), 5,
      sym_float_literal,
      sym_string_literal,
      sym_duration_literal,
      sym_money_literal,
      sym_percentage_literal,
    STATE(37), 7,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_field_expression,
      sym_list_expression,
      sym__literal,
      sym_boolean_literal,
  [2034] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(167), 1,
      anon_sym_LBRACK,
    ACTIONS(175), 1,
      sym_identifier,
    STATE(3), 1,
      sym_expression,
    ACTIONS(165), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(169), 2,
      sym_integer_literal,
      sym_null_literal,
    ACTIONS(173), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(171), 5,
      sym_float_literal,
      sym_string_literal,
      sym_duration_literal,
      sym_money_literal,
      sym_percentage_literal,
    STATE(8), 7,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_field_expression,
      sym_list_expression,
      sym__literal,
      sym_boolean_literal,
  [2075] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(155), 1,
      anon_sym_LBRACK,
    ACTIONS(163), 1,
      sym_identifier,
    STATE(33), 1,
      sym_expression,
    ACTIONS(153), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(157), 2,
      sym_integer_literal,
      sym_null_literal,
    ACTIONS(161), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(159), 5,
      sym_float_literal,
      sym_string_literal,
      sym_duration_literal,
      sym_money_literal,
      sym_percentage_literal,
    STATE(37), 7,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_field_expression,
      sym_list_expression,
      sym__literal,
      sym_boolean_literal,
  [2116] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(53), 9,
      anon_sym_RBRACE,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
    ACTIONS(51), 12,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_in,
      anon_sym_DOT_DOT,
      sym_identifier,
  [2145] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(167), 1,
      anon_sym_LBRACK,
    ACTIONS(175), 1,
      sym_identifier,
    STATE(9), 1,
      sym_expression,
    ACTIONS(165), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(169), 2,
      sym_integer_literal,
      sym_null_literal,
    ACTIONS(173), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(171), 5,
      sym_float_literal,
      sym_string_literal,
      sym_duration_literal,
      sym_money_literal,
      sym_percentage_literal,
    STATE(8), 7,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_field_expression,
      sym_list_expression,
      sym__literal,
      sym_boolean_literal,
  [2186] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(37), 9,
      anon_sym_RBRACE,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
    ACTIONS(35), 12,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_in,
      anon_sym_DOT_DOT,
      sym_identifier,
  [2215] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(33), 9,
      anon_sym_RBRACE,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
    ACTIONS(31), 12,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_in,
      anon_sym_DOT_DOT,
      sym_identifier,
  [2244] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(29), 9,
      anon_sym_RBRACE,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
    ACTIONS(27), 12,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_in,
      anon_sym_DOT_DOT,
      sym_identifier,
  [2273] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(123), 1,
      anon_sym_LBRACK,
    ACTIONS(151), 1,
      sym_identifier,
    STATE(92), 1,
      sym_expression,
    ACTIONS(121), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(125), 2,
      sym_integer_literal,
      sym_null_literal,
    ACTIONS(129), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(127), 5,
      sym_float_literal,
      sym_string_literal,
      sym_duration_literal,
      sym_money_literal,
      sym_percentage_literal,
    STATE(99), 7,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_field_expression,
      sym_list_expression,
      sym__literal,
      sym_boolean_literal,
  [2314] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(77), 1,
      anon_sym_LBRACK,
    ACTIONS(109), 1,
      sym_identifier,
    STATE(82), 1,
      sym_expression,
    ACTIONS(75), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(79), 2,
      sym_integer_literal,
      sym_null_literal,
    ACTIONS(83), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(81), 5,
      sym_float_literal,
      sym_string_literal,
      sym_duration_literal,
      sym_money_literal,
      sym_percentage_literal,
    STATE(111), 7,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_field_expression,
      sym_list_expression,
      sym__literal,
      sym_boolean_literal,
  [2355] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(77), 1,
      anon_sym_LBRACK,
    ACTIONS(109), 1,
      sym_identifier,
    STATE(95), 1,
      sym_expression,
    ACTIONS(75), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(79), 2,
      sym_integer_literal,
      sym_null_literal,
    ACTIONS(83), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(81), 5,
      sym_float_literal,
      sym_string_literal,
      sym_duration_literal,
      sym_money_literal,
      sym_percentage_literal,
    STATE(111), 7,
      sym_binary_expression,
      sym_unary_expression,
      sym_call_expression,
      sym_field_expression,
      sym_list_expression,
      sym__literal,
      sym_boolean_literal,
  [2396] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(181), 1,
      anon_sym_DOT,
    STATE(66), 1,
      aux_sym_dotted_name_repeat1,
    ACTIONS(179), 18,
      ts_builtin_sym_end,
      anon_sym_use,
      anon_sym_RBRACE,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_service,
      anon_sym_goal,
      anon_sym_constraints,
      anon_sym_DASH,
      anon_sym_depends_on,
      anon_sym_budget,
      anon_sym_metrics,
      anon_sym_rpc,
  [2426] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(185), 1,
      anon_sym_DOT,
    STATE(65), 1,
      aux_sym_dotted_name_repeat1,
    ACTIONS(183), 18,
      ts_builtin_sym_end,
      anon_sym_use,
      anon_sym_RBRACE,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_service,
      anon_sym_goal,
      anon_sym_constraints,
      anon_sym_DASH,
      anon_sym_depends_on,
      anon_sym_budget,
      anon_sym_metrics,
      anon_sym_rpc,
  [2456] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(181), 1,
      anon_sym_DOT,
    STATE(65), 1,
      aux_sym_dotted_name_repeat1,
    ACTIONS(188), 18,
      ts_builtin_sym_end,
      anon_sym_use,
      anon_sym_RBRACE,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_service,
      anon_sym_goal,
      anon_sym_constraints,
      anon_sym_DASH,
      anon_sym_depends_on,
      anon_sym_budget,
      anon_sym_metrics,
      anon_sym_rpc,
  [2486] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(87), 1,
      ts_builtin_sym_end,
    ACTIONS(91), 1,
      anon_sym_component,
    ACTIONS(93), 1,
      anon_sym_pipeline,
    ACTIONS(95), 1,
      anon_sym_workflow,
    ACTIONS(97), 1,
      anon_sym_agent,
    ACTIONS(99), 1,
      anon_sym_schema,
    ACTIONS(101), 1,
      anon_sym_policy,
    ACTIONS(103), 1,
      anon_sym_type,
    ACTIONS(105), 1,
      anon_sym_service,
    STATE(69), 10,
      sym__declaration,
      sym_component_declaration,
      sym_pipeline_declaration,
      sym_workflow_declaration,
      sym_agent_declaration,
      sym_schema_declaration,
      sym_policy_declaration,
      sym_type_declaration,
      sym_service_declaration,
      aux_sym_source_file_repeat2,
  [2529] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(91), 1,
      anon_sym_component,
    ACTIONS(93), 1,
      anon_sym_pipeline,
    ACTIONS(95), 1,
      anon_sym_workflow,
    ACTIONS(97), 1,
      anon_sym_agent,
    ACTIONS(99), 1,
      anon_sym_schema,
    ACTIONS(101), 1,
      anon_sym_policy,
    ACTIONS(103), 1,
      anon_sym_type,
    ACTIONS(105), 1,
      anon_sym_service,
    ACTIONS(190), 1,
      ts_builtin_sym_end,
    STATE(69), 10,
      sym__declaration,
      sym_component_declaration,
      sym_pipeline_declaration,
      sym_workflow_declaration,
      sym_agent_declaration,
      sym_schema_declaration,
      sym_policy_declaration,
      sym_type_declaration,
      sym_service_declaration,
      aux_sym_source_file_repeat2,
  [2572] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(192), 1,
      ts_builtin_sym_end,
    ACTIONS(194), 1,
      anon_sym_component,
    ACTIONS(197), 1,
      anon_sym_pipeline,
    ACTIONS(200), 1,
      anon_sym_workflow,
    ACTIONS(203), 1,
      anon_sym_agent,
    ACTIONS(206), 1,
      anon_sym_schema,
    ACTIONS(209), 1,
      anon_sym_policy,
    ACTIONS(212), 1,
      anon_sym_type,
    ACTIONS(215), 1,
      anon_sym_service,
    STATE(69), 10,
      sym__declaration,
      sym_component_declaration,
      sym_pipeline_declaration,
      sym_workflow_declaration,
      sym_agent_declaration,
      sym_schema_declaration,
      sym_policy_declaration,
      sym_type_declaration,
      sym_service_declaration,
      aux_sym_source_file_repeat2,
  [2615] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(183), 19,
      ts_builtin_sym_end,
      anon_sym_use,
      anon_sym_DOT,
      anon_sym_RBRACE,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_service,
      anon_sym_goal,
      anon_sym_constraints,
      anon_sym_DASH,
      anon_sym_depends_on,
      anon_sym_budget,
      anon_sym_metrics,
      anon_sym_rpc,
  [2640] = 8,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(221), 1,
      anon_sym_EQ,
    ACTIONS(223), 1,
      anon_sym_LPAREN,
    ACTIONS(225), 1,
      anon_sym_LT,
    ACTIONS(228), 1,
      sym_identifier,
    ACTIONS(218), 2,
      anon_sym_RBRACE,
      anon_sym_DASH,
    ACTIONS(7), 4,
      anon_sym_DOT,
      anon_sym_GT,
      anon_sym_in,
      anon_sym_DOT_DOT,
    ACTIONS(9), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [2676] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(231), 1,
      anon_sym_LPAREN,
    ACTIONS(233), 1,
      anon_sym_COLON,
    ACTIONS(7), 4,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_DOT_DOT,
    ACTIONS(9), 11,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_in,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [2705] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(231), 1,
      anon_sym_LPAREN,
    ACTIONS(7), 4,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_DOT_DOT,
    ACTIONS(9), 12,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_in,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
      anon_sym_RBRACK,
  [2732] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(223), 1,
      anon_sym_LPAREN,
    ACTIONS(7), 6,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_in,
      anon_sym_DOT_DOT,
      sym_identifier,
    ACTIONS(9), 10,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [2759] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(235), 17,
      ts_builtin_sym_end,
      anon_sym_RBRACE,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_service,
      anon_sym_goal,
      anon_sym_constraints,
      anon_sym_DASH,
      anon_sym_depends_on,
      anon_sym_budget,
      anon_sym_metrics,
      anon_sym_rpc,
  [2782] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(237), 17,
      ts_builtin_sym_end,
      anon_sym_RBRACE,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_service,
      anon_sym_goal,
      anon_sym_constraints,
      anon_sym_DASH,
      anon_sym_depends_on,
      anon_sym_budget,
      anon_sym_metrics,
      anon_sym_rpc,
  [2805] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(31), 6,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_in,
      anon_sym_DOT_DOT,
      sym_identifier,
    ACTIONS(33), 10,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [2829] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(239), 1,
      anon_sym_DOT,
    ACTIONS(241), 1,
      anon_sym_COMMA,
    ACTIONS(247), 1,
      anon_sym_RBRACK,
    STATE(227), 1,
      aux_sym_scenario_block_repeat1,
    ACTIONS(243), 3,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_DOT_DOT,
    ACTIONS(245), 9,
      anon_sym_in,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [2861] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 4,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_DOT_DOT,
    ACTIONS(57), 12,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_in,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
      anon_sym_RBRACK,
  [2885] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(239), 1,
      anon_sym_DOT,
    ACTIONS(241), 1,
      anon_sym_COMMA,
    ACTIONS(249), 1,
      anon_sym_RBRACK,
    STATE(249), 1,
      aux_sym_scenario_block_repeat1,
    ACTIONS(243), 3,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_DOT_DOT,
    ACTIONS(245), 9,
      anon_sym_in,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [2917] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(239), 1,
      anon_sym_DOT,
    ACTIONS(241), 1,
      anon_sym_COMMA,
    ACTIONS(251), 1,
      anon_sym_RBRACK,
    STATE(231), 1,
      aux_sym_scenario_block_repeat1,
    ACTIONS(243), 3,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_DOT_DOT,
    ACTIONS(245), 9,
      anon_sym_in,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [2949] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(239), 1,
      anon_sym_DOT,
    ACTIONS(25), 3,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_DOT_DOT,
    ACTIONS(23), 12,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_in,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
      anon_sym_RBRACK,
  [2975] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(59), 6,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_in,
      anon_sym_DOT_DOT,
      sym_identifier,
    ACTIONS(61), 10,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [2999] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(51), 4,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_DOT_DOT,
    ACTIONS(53), 12,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_in,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
      anon_sym_RBRACK,
  [3023] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(239), 1,
      anon_sym_DOT,
    ACTIONS(241), 1,
      anon_sym_COMMA,
    ACTIONS(253), 1,
      anon_sym_RPAREN,
    STATE(221), 1,
      aux_sym_scenario_block_repeat1,
    ACTIONS(243), 3,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_DOT_DOT,
    ACTIONS(245), 9,
      anon_sym_in,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [3055] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(27), 6,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_in,
      anon_sym_DOT_DOT,
      sym_identifier,
    ACTIONS(29), 10,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [3079] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(35), 4,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_DOT_DOT,
    ACTIONS(37), 12,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_in,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
      anon_sym_RBRACK,
  [3103] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(35), 6,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_in,
      anon_sym_DOT_DOT,
      sym_identifier,
    ACTIONS(37), 10,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [3127] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(27), 4,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_DOT_DOT,
    ACTIONS(29), 12,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_in,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
      anon_sym_RBRACK,
  [3151] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(239), 1,
      anon_sym_DOT,
    ACTIONS(241), 1,
      anon_sym_COMMA,
    ACTIONS(255), 1,
      anon_sym_RBRACK,
    STATE(252), 1,
      aux_sym_scenario_block_repeat1,
    ACTIONS(243), 3,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_DOT_DOT,
    ACTIONS(245), 9,
      anon_sym_in,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [3183] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(31), 4,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_DOT_DOT,
    ACTIONS(33), 12,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_in,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
      anon_sym_RBRACK,
  [3207] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(257), 1,
      anon_sym_DOT,
    ACTIONS(25), 5,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_in,
      anon_sym_DOT_DOT,
      sym_identifier,
    ACTIONS(23), 10,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [3233] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(47), 6,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_in,
      anon_sym_DOT_DOT,
      sym_identifier,
    ACTIONS(49), 10,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [3257] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(239), 1,
      anon_sym_DOT,
    ACTIONS(15), 3,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_RBRACK,
    ACTIONS(243), 3,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_DOT_DOT,
    ACTIONS(245), 9,
      anon_sym_in,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [3285] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(239), 1,
      anon_sym_DOT,
    ACTIONS(41), 3,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_DOT_DOT,
    ACTIONS(39), 12,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_in,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
      anon_sym_RBRACK,
  [3311] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(239), 1,
      anon_sym_DOT,
    ACTIONS(241), 1,
      anon_sym_COMMA,
    ACTIONS(259), 1,
      anon_sym_RPAREN,
    STATE(243), 1,
      aux_sym_scenario_block_repeat1,
    ACTIONS(243), 3,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_DOT_DOT,
    ACTIONS(245), 9,
      anon_sym_in,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [3343] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(147), 1,
      sym_identifier,
    ACTIONS(257), 1,
      anon_sym_DOT,
    ACTIONS(143), 2,
      anon_sym_RBRACE,
      anon_sym_DASH,
    ACTIONS(261), 4,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_in,
      anon_sym_DOT_DOT,
    ACTIONS(263), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [3373] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(239), 1,
      anon_sym_DOT,
    ACTIONS(241), 1,
      anon_sym_COMMA,
    ACTIONS(265), 1,
      anon_sym_RPAREN,
    STATE(251), 1,
      aux_sym_scenario_block_repeat1,
    ACTIONS(243), 3,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_DOT_DOT,
    ACTIONS(245), 9,
      anon_sym_in,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [3405] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 6,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_in,
      anon_sym_DOT_DOT,
      sym_identifier,
    ACTIONS(9), 10,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [3429] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(257), 1,
      anon_sym_DOT,
    ACTIONS(269), 1,
      sym_identifier,
    ACTIONS(267), 2,
      anon_sym_RBRACE,
      anon_sym_DASH,
    ACTIONS(261), 4,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_in,
      anon_sym_DOT_DOT,
    ACTIONS(263), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [3459] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(257), 1,
      anon_sym_DOT,
    ACTIONS(273), 1,
      sym_identifier,
    ACTIONS(271), 2,
      anon_sym_RBRACE,
      anon_sym_DASH,
    ACTIONS(261), 4,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_in,
      anon_sym_DOT_DOT,
    ACTIONS(263), 8,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [3489] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(43), 6,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_in,
      anon_sym_DOT_DOT,
      sym_identifier,
    ACTIONS(45), 10,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [3513] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(55), 6,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_in,
      anon_sym_DOT_DOT,
      sym_identifier,
    ACTIONS(57), 10,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [3537] = 7,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(239), 1,
      anon_sym_DOT,
    ACTIONS(241), 1,
      anon_sym_COMMA,
    ACTIONS(275), 1,
      anon_sym_RPAREN,
    STATE(238), 1,
      aux_sym_scenario_block_repeat1,
    ACTIONS(243), 3,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_DOT_DOT,
    ACTIONS(245), 9,
      anon_sym_in,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [3569] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(43), 4,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_DOT_DOT,
    ACTIONS(45), 12,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_in,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
      anon_sym_RBRACK,
  [3593] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(59), 4,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_DOT_DOT,
    ACTIONS(61), 12,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_in,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
      anon_sym_RBRACK,
  [3617] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(47), 4,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_DOT_DOT,
    ACTIONS(49), 12,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_in,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
      anon_sym_RBRACK,
  [3641] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(51), 6,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_in,
      anon_sym_DOT_DOT,
      sym_identifier,
    ACTIONS(53), 10,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [3665] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(19), 1,
      anon_sym_expect,
    ACTIONS(277), 1,
      anon_sym_COMMA,
    STATE(109), 1,
      aux_sym_scenario_block_repeat1,
    ACTIONS(15), 13,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_given,
      anon_sym_when,
      anon_sym_expect_error,
      anon_sym_forall,
      anon_sym_assert,
  [3693] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(257), 1,
      anon_sym_DOT,
    ACTIONS(41), 5,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_in,
      anon_sym_DOT_DOT,
      sym_identifier,
    ACTIONS(39), 10,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [3719] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(7), 4,
      anon_sym_DOT,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_DOT_DOT,
    ACTIONS(9), 12,
      anon_sym_COMMA,
      anon_sym_RPAREN,
      anon_sym_in,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
      anon_sym_RBRACK,
  [3743] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(280), 1,
      anon_sym_RBRACE,
    ACTIONS(282), 1,
      anon_sym_goal,
    ACTIONS(284), 1,
      anon_sym_constraints,
    ACTIONS(286), 1,
      anon_sym_depends_on,
    ACTIONS(288), 1,
      anon_sym_budget,
    ACTIONS(290), 1,
      anon_sym_metrics,
    ACTIONS(292), 1,
      anon_sym_rpc,
    STATE(117), 8,
      sym__service_member,
      sym_goal_section,
      sym_constraints_section,
      sym_depends_on_section,
      sym_budget_section,
      sym_metrics_section,
      sym_rpc_declaration,
      aux_sym_service_block_repeat1,
  [3778] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(239), 1,
      anon_sym_DOT,
    ACTIONS(143), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
    ACTIONS(243), 3,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_DOT_DOT,
    ACTIONS(245), 9,
      anon_sym_in,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [3805] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(296), 1,
      anon_sym_LT,
    ACTIONS(294), 14,
      ts_builtin_sym_end,
      anon_sym_LBRACE,
      anon_sym_COMMA,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_EQ,
      anon_sym_RPAREN,
      anon_sym_GT,
      anon_sym_service,
  [3828] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(298), 1,
      anon_sym_RBRACE,
    ACTIONS(300), 1,
      anon_sym_inputs,
    ACTIONS(303), 1,
      anon_sym_outputs,
    ACTIONS(306), 1,
      anon_sym_preconditions,
    ACTIONS(309), 1,
      anon_sym_postconditions,
    ACTIONS(312), 1,
      anon_sym_errors,
    ACTIONS(315), 1,
      anon_sym_tests,
    STATE(115), 8,
      sym__rpc_member,
      sym_inputs_section,
      sym_outputs_section,
      sym_preconditions_section,
      sym_postconditions_section,
      sym_errors_section,
      sym_tests_section,
      aux_sym_rpc_block_repeat1,
  [3863] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(318), 1,
      anon_sym_RBRACE,
    ACTIONS(320), 1,
      anon_sym_inputs,
    ACTIONS(322), 1,
      anon_sym_outputs,
    ACTIONS(324), 1,
      anon_sym_preconditions,
    ACTIONS(326), 1,
      anon_sym_postconditions,
    ACTIONS(328), 1,
      anon_sym_errors,
    ACTIONS(330), 1,
      anon_sym_tests,
    STATE(115), 8,
      sym__rpc_member,
      sym_inputs_section,
      sym_outputs_section,
      sym_preconditions_section,
      sym_postconditions_section,
      sym_errors_section,
      sym_tests_section,
      aux_sym_rpc_block_repeat1,
  [3898] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(332), 1,
      anon_sym_RBRACE,
    ACTIONS(334), 1,
      anon_sym_goal,
    ACTIONS(337), 1,
      anon_sym_constraints,
    ACTIONS(340), 1,
      anon_sym_depends_on,
    ACTIONS(343), 1,
      anon_sym_budget,
    ACTIONS(346), 1,
      anon_sym_metrics,
    ACTIONS(349), 1,
      anon_sym_rpc,
    STATE(117), 8,
      sym__service_member,
      sym_goal_section,
      sym_constraints_section,
      sym_depends_on_section,
      sym_budget_section,
      sym_metrics_section,
      sym_rpc_declaration,
      aux_sym_service_block_repeat1,
  [3933] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(320), 1,
      anon_sym_inputs,
    ACTIONS(322), 1,
      anon_sym_outputs,
    ACTIONS(324), 1,
      anon_sym_preconditions,
    ACTIONS(326), 1,
      anon_sym_postconditions,
    ACTIONS(328), 1,
      anon_sym_errors,
    ACTIONS(330), 1,
      anon_sym_tests,
    ACTIONS(352), 1,
      anon_sym_RBRACE,
    STATE(116), 8,
      sym__rpc_member,
      sym_inputs_section,
      sym_outputs_section,
      sym_preconditions_section,
      sym_postconditions_section,
      sym_errors_section,
      sym_tests_section,
      aux_sym_rpc_block_repeat1,
  [3968] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(239), 1,
      anon_sym_DOT,
    ACTIONS(354), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
    ACTIONS(243), 3,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_DOT_DOT,
    ACTIONS(245), 9,
      anon_sym_in,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [3995] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(282), 1,
      anon_sym_goal,
    ACTIONS(284), 1,
      anon_sym_constraints,
    ACTIONS(286), 1,
      anon_sym_depends_on,
    ACTIONS(288), 1,
      anon_sym_budget,
    ACTIONS(290), 1,
      anon_sym_metrics,
    ACTIONS(292), 1,
      anon_sym_rpc,
    ACTIONS(356), 1,
      anon_sym_RBRACE,
    STATE(112), 8,
      sym__service_member,
      sym_goal_section,
      sym_constraints_section,
      sym_depends_on_section,
      sym_budget_section,
      sym_metrics_section,
      sym_rpc_declaration,
      aux_sym_service_block_repeat1,
  [4030] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(239), 1,
      anon_sym_DOT,
    ACTIONS(358), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
    ACTIONS(243), 3,
      anon_sym_LT,
      anon_sym_GT,
      anon_sym_DOT_DOT,
    ACTIONS(245), 9,
      anon_sym_in,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_LT_EQ,
      anon_sym_GT_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_notin,
      anon_sym_DOT_DOT_LT,
  [4057] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(360), 14,
      ts_builtin_sym_end,
      anon_sym_LBRACE,
      anon_sym_COMMA,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_EQ,
      anon_sym_RPAREN,
      anon_sym_GT,
      anon_sym_service,
  [4077] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(362), 14,
      ts_builtin_sym_end,
      anon_sym_LBRACE,
      anon_sym_COMMA,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_EQ,
      anon_sym_RPAREN,
      anon_sym_GT,
      anon_sym_service,
  [4097] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(364), 1,
      anon_sym_COMMA,
    STATE(124), 1,
      aux_sym_property_block_repeat1,
    ACTIONS(367), 12,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_given,
      anon_sym_when,
      anon_sym_forall,
      anon_sym_assert,
  [4121] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(369), 1,
      anon_sym_COMMA,
    STATE(124), 1,
      aux_sym_property_block_repeat1,
    ACTIONS(371), 12,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_given,
      anon_sym_when,
      anon_sym_forall,
      anon_sym_assert,
  [4145] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(63), 1,
      anon_sym_COMMA,
    STATE(109), 1,
      aux_sym_scenario_block_repeat1,
    ACTIONS(371), 12,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_given,
      anon_sym_when,
      anon_sym_forall,
      anon_sym_assert,
  [4169] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(63), 1,
      anon_sym_COMMA,
    ACTIONS(375), 1,
      anon_sym_expect,
    STATE(109), 1,
      aux_sym_scenario_block_repeat1,
    ACTIONS(373), 11,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_given,
      anon_sym_when,
      anon_sym_expect_error,
  [4195] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(369), 1,
      anon_sym_COMMA,
    STATE(125), 1,
      aux_sym_property_block_repeat1,
    ACTIONS(69), 12,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_given,
      anon_sym_when,
      anon_sym_forall,
      anon_sym_assert,
  [4219] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(381), 1,
      sym_identifier,
    STATE(128), 1,
      sym_quantifier,
    ACTIONS(377), 2,
      anon_sym_RBRACE,
      anon_sym_DASH,
    ACTIONS(379), 10,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_given,
      anon_sym_when,
      anon_sym_forall,
      anon_sym_assert,
  [4245] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(383), 14,
      ts_builtin_sym_end,
      anon_sym_LBRACE,
      anon_sym_COMMA,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_EQ,
      anon_sym_RPAREN,
      anon_sym_GT,
      anon_sym_service,
  [4265] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(367), 13,
      anon_sym_COMMA,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_given,
      anon_sym_when,
      anon_sym_forall,
      anon_sym_assert,
  [4284] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(390), 1,
      anon_sym_expect,
    ACTIONS(393), 1,
      anon_sym_expect_error,
    STATE(132), 1,
      aux_sym_scenario_block_repeat2,
    ACTIONS(387), 2,
      anon_sym_given,
      anon_sym_when,
    ACTIONS(385), 8,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
  [4311] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(400), 1,
      anon_sym_forall,
    STATE(135), 1,
      aux_sym_property_block_repeat2,
    ACTIONS(398), 3,
      anon_sym_given,
      anon_sym_when,
      anon_sym_assert,
    ACTIONS(396), 8,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
  [4336] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(406), 1,
      anon_sym_expect,
    ACTIONS(408), 1,
      anon_sym_expect_error,
    STATE(132), 1,
      aux_sym_scenario_block_repeat2,
    ACTIONS(404), 2,
      anon_sym_given,
      anon_sym_when,
    ACTIONS(402), 8,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
  [4363] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(413), 1,
      anon_sym_forall,
    STATE(135), 1,
      aux_sym_property_block_repeat2,
    ACTIONS(410), 3,
      anon_sym_given,
      anon_sym_when,
      anon_sym_assert,
    ACTIONS(377), 8,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
  [4388] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(67), 1,
      anon_sym_expect,
    ACTIONS(65), 11,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      anon_sym_given,
      anon_sym_when,
      anon_sym_expect_error,
  [4408] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(416), 1,
      anon_sym_DOT,
    STATE(138), 1,
      aux_sym_dotted_name_repeat1,
    ACTIONS(179), 10,
      ts_builtin_sym_end,
      anon_sym_use,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_service,
  [4430] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(419), 1,
      anon_sym_DOT,
    STATE(65), 1,
      aux_sym_dotted_name_repeat1,
    ACTIONS(188), 10,
      ts_builtin_sym_end,
      anon_sym_use,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_service,
  [4452] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(424), 1,
      anon_sym_use,
    STATE(139), 2,
      sym_use_declaration,
      aux_sym_source_file_repeat1,
    ACTIONS(422), 9,
      ts_builtin_sym_end,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_service,
  [4474] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(429), 1,
      anon_sym_DOT,
    ACTIONS(427), 10,
      ts_builtin_sym_end,
      anon_sym_use,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_service,
  [4493] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(433), 1,
      anon_sym_LBRACE,
    STATE(160), 1,
      sym_block,
    ACTIONS(431), 9,
      ts_builtin_sym_end,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_service,
  [4514] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(435), 1,
      anon_sym_RBRACE,
    ACTIONS(439), 1,
      sym_identifier,
    STATE(148), 2,
      sym_field,
      aux_sym_inputs_section_repeat1,
    ACTIONS(437), 6,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
  [4536] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(441), 10,
      ts_builtin_sym_end,
      anon_sym_use,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_service,
  [4552] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(443), 10,
      ts_builtin_sym_end,
      anon_sym_use,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_service,
  [4568] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(445), 1,
      anon_sym_LT,
    ACTIONS(294), 2,
      anon_sym_RBRACE,
      anon_sym_EQ,
    ACTIONS(221), 7,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      sym_identifier,
  [4588] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(447), 10,
      ts_builtin_sym_end,
      anon_sym_use,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_service,
  [4604] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(451), 1,
      anon_sym_DASH,
    STATE(147), 2,
      sym_error_definition,
      aux_sym_errors_section_repeat1,
    ACTIONS(449), 7,
      anon_sym_RBRACE,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
  [4624] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(454), 1,
      anon_sym_RBRACE,
    ACTIONS(458), 1,
      sym_identifier,
    STATE(148), 2,
      sym_field,
      aux_sym_inputs_section_repeat1,
    ACTIONS(456), 6,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
  [4646] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(463), 1,
      anon_sym_DASH,
    STATE(147), 2,
      sym_error_definition,
      aux_sym_errors_section_repeat1,
    ACTIONS(461), 7,
      anon_sym_RBRACE,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
  [4666] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(465), 10,
      ts_builtin_sym_end,
      anon_sym_use,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_service,
  [4682] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(433), 1,
      anon_sym_LBRACE,
    STATE(185), 1,
      sym_block,
    ACTIONS(467), 8,
      anon_sym_RBRACE,
      anon_sym_goal,
      anon_sym_constraints,
      anon_sym_DASH,
      anon_sym_depends_on,
      anon_sym_budget,
      anon_sym_metrics,
      anon_sym_rpc,
  [4702] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(469), 10,
      ts_builtin_sym_end,
      anon_sym_use,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_service,
  [4718] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(439), 1,
      sym_identifier,
    ACTIONS(471), 1,
      anon_sym_RBRACE,
    STATE(148), 2,
      sym_field,
      aux_sym_inputs_section_repeat1,
    ACTIONS(473), 6,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
  [4740] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(475), 9,
      ts_builtin_sym_end,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_service,
  [4755] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(477), 9,
      ts_builtin_sym_end,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_service,
  [4770] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(479), 9,
      ts_builtin_sym_end,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_service,
  [4785] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(481), 1,
      anon_sym_RBRACE,
    ACTIONS(483), 1,
      anon_sym_EQ,
    ACTIONS(485), 7,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      sym_identifier,
  [4804] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(383), 2,
      anon_sym_RBRACE,
      anon_sym_EQ,
    ACTIONS(487), 7,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      sym_identifier,
  [4821] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(489), 9,
      ts_builtin_sym_end,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_service,
  [4836] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(491), 9,
      ts_builtin_sym_end,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_service,
  [4851] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(493), 9,
      ts_builtin_sym_end,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_service,
  [4866] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(497), 1,
      anon_sym_DASH,
    STATE(162), 1,
      aux_sym_metrics_section_repeat1,
    ACTIONS(495), 7,
      anon_sym_RBRACE,
      anon_sym_goal,
      anon_sym_constraints,
      anon_sym_depends_on,
      anon_sym_budget,
      anon_sym_metrics,
      anon_sym_rpc,
  [4885] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(502), 1,
      anon_sym_DASH,
    STATE(176), 1,
      aux_sym_constraints_section_repeat1,
    ACTIONS(500), 7,
      anon_sym_RBRACE,
      anon_sym_goal,
      anon_sym_constraints,
      anon_sym_depends_on,
      anon_sym_budget,
      anon_sym_metrics,
      anon_sym_rpc,
  [4904] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(506), 1,
      anon_sym_DASH,
    STATE(177), 1,
      aux_sym_depends_on_section_repeat1,
    ACTIONS(504), 7,
      anon_sym_RBRACE,
      anon_sym_goal,
      anon_sym_constraints,
      anon_sym_depends_on,
      anon_sym_budget,
      anon_sym_metrics,
      anon_sym_rpc,
  [4923] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(508), 9,
      ts_builtin_sym_end,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_service,
  [4938] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(510), 9,
      ts_builtin_sym_end,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_service,
  [4953] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(514), 1,
      anon_sym_DASH,
    STATE(162), 1,
      aux_sym_metrics_section_repeat1,
    ACTIONS(512), 7,
      anon_sym_RBRACE,
      anon_sym_goal,
      anon_sym_constraints,
      anon_sym_depends_on,
      anon_sym_budget,
      anon_sym_metrics,
      anon_sym_rpc,
  [4972] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(516), 9,
      ts_builtin_sym_end,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_service,
  [4987] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(360), 2,
      anon_sym_RBRACE,
      anon_sym_EQ,
    ACTIONS(518), 7,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      sym_identifier,
  [5004] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(522), 1,
      anon_sym_LPAREN,
    ACTIONS(520), 8,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
  [5021] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(524), 9,
      ts_builtin_sym_end,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_service,
  [5036] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(526), 9,
      ts_builtin_sym_end,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_service,
  [5051] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(362), 2,
      anon_sym_RBRACE,
      anon_sym_EQ,
    ACTIONS(528), 7,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
      sym_identifier,
  [5068] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(530), 1,
      anon_sym_DASH,
    STATE(174), 1,
      aux_sym_preconditions_section_repeat1,
    ACTIONS(177), 7,
      anon_sym_RBRACE,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
  [5087] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(535), 1,
      anon_sym_DASH,
    STATE(184), 1,
      aux_sym_tests_section_repeat1,
    ACTIONS(533), 7,
      anon_sym_RBRACE,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
  [5106] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(539), 1,
      anon_sym_DASH,
    STATE(176), 1,
      aux_sym_constraints_section_repeat1,
    ACTIONS(537), 7,
      anon_sym_RBRACE,
      anon_sym_goal,
      anon_sym_constraints,
      anon_sym_depends_on,
      anon_sym_budget,
      anon_sym_metrics,
      anon_sym_rpc,
  [5125] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(544), 1,
      anon_sym_DASH,
    STATE(177), 1,
      aux_sym_depends_on_section_repeat1,
    ACTIONS(542), 7,
      anon_sym_RBRACE,
      anon_sym_goal,
      anon_sym_constraints,
      anon_sym_depends_on,
      anon_sym_budget,
      anon_sym_metrics,
      anon_sym_rpc,
  [5144] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(547), 9,
      ts_builtin_sym_end,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_service,
  [5159] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(549), 9,
      ts_builtin_sym_end,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_service,
  [5174] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(553), 1,
      anon_sym_DASH,
    STATE(174), 1,
      aux_sym_preconditions_section_repeat1,
    ACTIONS(551), 7,
      anon_sym_RBRACE,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
  [5193] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(553), 1,
      anon_sym_DASH,
    STATE(174), 1,
      aux_sym_preconditions_section_repeat1,
    ACTIONS(555), 7,
      anon_sym_RBRACE,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
  [5212] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(557), 9,
      ts_builtin_sym_end,
      anon_sym_component,
      anon_sym_pipeline,
      anon_sym_workflow,
      anon_sym_agent,
      anon_sym_schema,
      anon_sym_policy,
      anon_sym_type,
      anon_sym_service,
  [5227] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(561), 1,
      anon_sym_LPAREN,
    ACTIONS(559), 8,
      anon_sym_RBRACE,
      anon_sym_goal,
      anon_sym_constraints,
      anon_sym_DASH,
      anon_sym_depends_on,
      anon_sym_budget,
      anon_sym_metrics,
      anon_sym_rpc,
  [5244] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(565), 1,
      anon_sym_DASH,
    STATE(184), 1,
      aux_sym_tests_section_repeat1,
    ACTIONS(563), 7,
      anon_sym_RBRACE,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
  [5263] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(568), 8,
      anon_sym_RBRACE,
      anon_sym_goal,
      anon_sym_constraints,
      anon_sym_DASH,
      anon_sym_depends_on,
      anon_sym_budget,
      anon_sym_metrics,
      anon_sym_rpc,
  [5277] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(570), 8,
      anon_sym_RBRACE,
      anon_sym_goal,
      anon_sym_constraints,
      anon_sym_DASH,
      anon_sym_depends_on,
      anon_sym_budget,
      anon_sym_metrics,
      anon_sym_rpc,
  [5291] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(537), 8,
      anon_sym_RBRACE,
      anon_sym_goal,
      anon_sym_constraints,
      anon_sym_DASH,
      anon_sym_depends_on,
      anon_sym_budget,
      anon_sym_metrics,
      anon_sym_rpc,
  [5305] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(572), 8,
      anon_sym_RBRACE,
      anon_sym_goal,
      anon_sym_constraints,
      anon_sym_DASH,
      anon_sym_depends_on,
      anon_sym_budget,
      anon_sym_metrics,
      anon_sym_rpc,
  [5319] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(574), 8,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
  [5333] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(576), 8,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
  [5347] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(578), 8,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
  [5361] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(580), 8,
      anon_sym_RBRACE,
      anon_sym_goal,
      anon_sym_constraints,
      anon_sym_DASH,
      anon_sym_depends_on,
      anon_sym_budget,
      anon_sym_metrics,
      anon_sym_rpc,
  [5375] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(563), 8,
      anon_sym_RBRACE,
      anon_sym_DASH,
      anon_sym_inputs,
      anon_sym_outputs,
      anon_sym_preconditions,
      anon_sym_postconditions,
      anon_sym_errors,
      anon_sym_tests,
  [5389] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(582), 8,
      anon_sym_RBRACE,
      anon_sym_goal,
      anon_sym_constraints,
      anon_sym_DASH,
      anon_sym_depends_on,
      anon_sym_budget,
      anon_sym_metrics,
      anon_sym_rpc,
  [5403] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(495), 8,
      anon_sym_RBRACE,
      anon_sym_goal,
      anon_sym_constraints,
      anon_sym_DASH,
      anon_sym_depends_on,
      anon_sym_budget,
      anon_sym_metrics,
      anon_sym_rpc,
  [5417] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(584), 1,
      anon_sym_struct,
    ACTIONS(586), 1,
      anon_sym_enum,
    ACTIONS(588), 1,
      sym_identifier,
    STATE(141), 1,
      sym_type_ref,
    STATE(179), 4,
      sym__type_kind,
      sym_struct_type,
      sym_enum_type,
      sym_refined_type,
  [5439] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(590), 7,
      anon_sym_RBRACE,
      anon_sym_goal,
      anon_sym_constraints,
      anon_sym_depends_on,
      anon_sym_budget,
      anon_sym_metrics,
      anon_sym_rpc,
  [5452] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(592), 7,
      anon_sym_RBRACE,
      anon_sym_goal,
      anon_sym_constraints,
      anon_sym_depends_on,
      anon_sym_budget,
      anon_sym_metrics,
      anon_sym_rpc,
  [5465] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(594), 7,
      anon_sym_RBRACE,
      anon_sym_goal,
      anon_sym_constraints,
      anon_sym_depends_on,
      anon_sym_budget,
      anon_sym_metrics,
      anon_sym_rpc,
  [5478] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(596), 7,
      anon_sym_RBRACE,
      anon_sym_goal,
      anon_sym_constraints,
      anon_sym_depends_on,
      anon_sym_budget,
      anon_sym_metrics,
      anon_sym_rpc,
  [5491] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(598), 7,
      anon_sym_RBRACE,
      anon_sym_goal,
      anon_sym_constraints,
      anon_sym_depends_on,
      anon_sym_budget,
      anon_sym_metrics,
      anon_sym_rpc,
  [5504] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(600), 1,
      anon_sym_RBRACE,
    ACTIONS(602), 1,
      anon_sym_DASH,
    ACTIONS(604), 1,
      sym_identifier,
    STATE(204), 3,
      sym_field,
      sym__block_item,
      aux_sym_block_repeat1,
  [5522] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(606), 1,
      anon_sym_RBRACE,
    ACTIONS(608), 1,
      anon_sym_DASH,
    ACTIONS(611), 1,
      sym_identifier,
    STATE(203), 3,
      sym_field,
      sym__block_item,
      aux_sym_block_repeat1,
  [5540] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(602), 1,
      anon_sym_DASH,
    ACTIONS(604), 1,
      sym_identifier,
    ACTIONS(614), 1,
      anon_sym_RBRACE,
    STATE(203), 3,
      sym_field,
      sym__block_item,
      aux_sym_block_repeat1,
  [5558] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(616), 1,
      anon_sym_scenario,
    ACTIONS(618), 1,
      anon_sym_property,
    STATE(193), 3,
      sym__test_block,
      sym_scenario_block,
      sym_property_block,
  [5573] = 4,
    ACTIONS(3), 1,
      sym_comment,
    STATE(195), 1,
      sym_metric_declaration,
    STATE(293), 1,
      sym_metric_kind,
    ACTIONS(620), 3,
      anon_sym_counter,
      anon_sym_gauge,
      anon_sym_histogram,
  [5588] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(406), 1,
      anon_sym_expect,
    ACTIONS(408), 1,
      anon_sym_expect_error,
    STATE(134), 1,
      aux_sym_scenario_block_repeat2,
    ACTIONS(404), 2,
      anon_sym_given,
      anon_sym_when,
  [5605] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(400), 1,
      anon_sym_forall,
    STATE(133), 1,
      aux_sym_property_block_repeat2,
    ACTIONS(398), 3,
      anon_sym_given,
      anon_sym_when,
      anon_sym_assert,
  [5620] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(622), 1,
      anon_sym_RBRACE,
    ACTIONS(624), 1,
      sym_identifier,
    STATE(209), 2,
      sym_enum_variant,
      aux_sym_enum_type_repeat1,
  [5634] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(383), 4,
      anon_sym_RBRACE,
      anon_sym_EQ,
      anon_sym_DASH,
      sym_identifier,
  [5644] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(362), 4,
      anon_sym_RBRACE,
      anon_sym_EQ,
      anon_sym_DASH,
      sym_identifier,
  [5654] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(360), 4,
      anon_sym_RBRACE,
      anon_sym_EQ,
      anon_sym_DASH,
      sym_identifier,
  [5664] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(627), 1,
      anon_sym_COMMA,
    STATE(213), 1,
      aux_sym_scenario_block_repeat1,
    ACTIONS(15), 2,
      anon_sym_RPAREN,
      anon_sym_RBRACK,
  [5678] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(630), 1,
      anon_sym_EQ,
    ACTIONS(481), 3,
      anon_sym_RBRACE,
      anon_sym_DASH,
      sym_identifier,
  [5690] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(632), 1,
      anon_sym_RBRACE,
    ACTIONS(634), 1,
      sym_identifier,
    STATE(216), 2,
      sym_enum_variant,
      aux_sym_enum_type_repeat1,
  [5704] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(634), 1,
      sym_identifier,
    ACTIONS(636), 1,
      anon_sym_RBRACE,
    STATE(209), 2,
      sym_enum_variant,
      aux_sym_enum_type_repeat1,
  [5718] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(638), 1,
      anon_sym_COMMA,
    ACTIONS(640), 1,
      anon_sym_GT,
    STATE(242), 1,
      aux_sym_type_ref_repeat1,
  [5731] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(642), 1,
      anon_sym_RPAREN,
    ACTIONS(644), 1,
      sym_identifier,
    STATE(235), 1,
      sym_field,
  [5744] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(646), 1,
      anon_sym_COMMA,
    ACTIONS(648), 1,
      anon_sym_RPAREN,
    STATE(247), 1,
      aux_sym_enum_variant_repeat1,
  [5757] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(638), 1,
      anon_sym_COMMA,
    ACTIONS(650), 1,
      anon_sym_GT,
    STATE(230), 1,
      aux_sym_type_ref_repeat1,
  [5770] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(241), 1,
      anon_sym_COMMA,
    ACTIONS(652), 1,
      anon_sym_RPAREN,
    STATE(213), 1,
      aux_sym_scenario_block_repeat1,
  [5783] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(654), 1,
      anon_sym_EQ,
    ACTIONS(481), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [5794] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(463), 1,
      anon_sym_DASH,
    STATE(149), 2,
      sym_error_definition,
      aux_sym_errors_section_repeat1,
  [5805] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(656), 1,
      anon_sym_GT,
    ACTIONS(658), 1,
      sym_identifier,
    STATE(217), 1,
      sym_type_ref,
  [5818] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(644), 1,
      sym_identifier,
    ACTIONS(660), 1,
      anon_sym_RPAREN,
    STATE(233), 1,
      sym_field,
  [5831] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(662), 1,
      sym_identifier,
    STATE(142), 2,
      sym_field,
      aux_sym_inputs_section_repeat1,
  [5842] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(241), 1,
      anon_sym_COMMA,
    ACTIONS(664), 1,
      anon_sym_RBRACK,
    STATE(213), 1,
      aux_sym_scenario_block_repeat1,
  [5855] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(662), 1,
      sym_identifier,
    STATE(153), 2,
      sym_field,
      aux_sym_inputs_section_repeat1,
  [5866] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(666), 1,
      anon_sym_COMMA,
    ACTIONS(669), 1,
      anon_sym_RBRACE,
    STATE(229), 1,
      aux_sym_use_declaration_repeat1,
  [5879] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(671), 1,
      anon_sym_COMMA,
    ACTIONS(674), 1,
      anon_sym_GT,
    STATE(230), 1,
      aux_sym_type_ref_repeat1,
  [5892] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(241), 1,
      anon_sym_COMMA,
    ACTIONS(676), 1,
      anon_sym_RBRACK,
    STATE(213), 1,
      aux_sym_scenario_block_repeat1,
  [5905] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(680), 1,
      anon_sym_as,
    ACTIONS(678), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [5916] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(646), 1,
      anon_sym_COMMA,
    ACTIONS(682), 1,
      anon_sym_RPAREN,
    STATE(236), 1,
      aux_sym_enum_variant_repeat1,
  [5929] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(684), 1,
      anon_sym_COMMA,
    ACTIONS(686), 1,
      anon_sym_RBRACE,
    STATE(254), 1,
      aux_sym_use_declaration_repeat1,
  [5942] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(646), 1,
      anon_sym_COMMA,
    ACTIONS(688), 1,
      anon_sym_RPAREN,
    STATE(219), 1,
      aux_sym_enum_variant_repeat1,
  [5955] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(646), 1,
      anon_sym_COMMA,
    ACTIONS(690), 1,
      anon_sym_RPAREN,
    STATE(247), 1,
      aux_sym_enum_variant_repeat1,
  [5968] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(692), 1,
      anon_sym_COMMA,
    ACTIONS(695), 1,
      anon_sym_RPAREN,
    STATE(237), 1,
      aux_sym_constraint_item_repeat1,
  [5981] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(241), 1,
      anon_sym_COMMA,
    ACTIONS(697), 1,
      anon_sym_RPAREN,
    STATE(213), 1,
      aux_sym_scenario_block_repeat1,
  [5994] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(699), 1,
      anon_sym_COMMA,
    ACTIONS(701), 1,
      anon_sym_RPAREN,
    STATE(241), 1,
      aux_sym_constraint_item_repeat1,
  [6007] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(705), 1,
      anon_sym_LPAREN,
    ACTIONS(703), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [6018] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(699), 1,
      anon_sym_COMMA,
    ACTIONS(707), 1,
      anon_sym_RPAREN,
    STATE(237), 1,
      aux_sym_constraint_item_repeat1,
  [6031] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(638), 1,
      anon_sym_COMMA,
    ACTIONS(709), 1,
      anon_sym_GT,
    STATE(230), 1,
      aux_sym_type_ref_repeat1,
  [6044] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(241), 1,
      anon_sym_COMMA,
    ACTIONS(711), 1,
      anon_sym_RPAREN,
    STATE(213), 1,
      aux_sym_scenario_block_repeat1,
  [6057] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(658), 1,
      sym_identifier,
    ACTIONS(713), 1,
      anon_sym_GT,
    STATE(248), 1,
      sym_type_ref,
  [6070] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(638), 1,
      anon_sym_COMMA,
    ACTIONS(715), 1,
      anon_sym_GT,
    STATE(220), 1,
      aux_sym_type_ref_repeat1,
  [6083] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(658), 1,
      sym_identifier,
    ACTIONS(717), 1,
      anon_sym_GT,
    STATE(245), 1,
      sym_type_ref,
  [6096] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(719), 1,
      anon_sym_COMMA,
    ACTIONS(722), 1,
      anon_sym_RPAREN,
    STATE(247), 1,
      aux_sym_enum_variant_repeat1,
  [6109] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(638), 1,
      anon_sym_COMMA,
    ACTIONS(724), 1,
      anon_sym_GT,
    STATE(250), 1,
      aux_sym_type_ref_repeat1,
  [6122] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(241), 1,
      anon_sym_COMMA,
    ACTIONS(726), 1,
      anon_sym_RBRACK,
    STATE(213), 1,
      aux_sym_scenario_block_repeat1,
  [6135] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(638), 1,
      anon_sym_COMMA,
    ACTIONS(728), 1,
      anon_sym_GT,
    STATE(230), 1,
      aux_sym_type_ref_repeat1,
  [6148] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(241), 1,
      anon_sym_COMMA,
    ACTIONS(730), 1,
      anon_sym_RPAREN,
    STATE(213), 1,
      aux_sym_scenario_block_repeat1,
  [6161] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(241), 1,
      anon_sym_COMMA,
    ACTIONS(732), 1,
      anon_sym_RBRACK,
    STATE(213), 1,
      aux_sym_scenario_block_repeat1,
  [6174] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(734), 1,
      anon_sym_RBRACE,
    ACTIONS(736), 1,
      sym_identifier,
    STATE(234), 1,
      sym_import_item,
  [6187] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(684), 1,
      anon_sym_COMMA,
    ACTIONS(738), 1,
      anon_sym_RBRACE,
    STATE(229), 1,
      aux_sym_use_declaration_repeat1,
  [6200] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(514), 1,
      anon_sym_DASH,
    STATE(167), 1,
      aux_sym_metrics_section_repeat1,
  [6210] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(740), 1,
      sym_identifier,
    STATE(144), 1,
      sym_dotted_name,
  [6220] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(742), 1,
      sym_identifier,
    STATE(140), 1,
      sym_dotted_name,
  [6230] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(433), 1,
      anon_sym_LBRACE,
    STATE(166), 1,
      sym_block,
  [6240] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(433), 1,
      anon_sym_LBRACE,
    STATE(168), 1,
      sym_block,
  [6250] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(695), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [6258] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(433), 1,
      anon_sym_LBRACE,
    STATE(154), 1,
      sym_block,
  [6268] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(744), 1,
      sym_identifier,
    STATE(131), 1,
      sym_quantifier,
  [6278] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(433), 1,
      anon_sym_LBRACE,
    STATE(171), 1,
      sym_block,
  [6288] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(433), 1,
      anon_sym_LBRACE,
    STATE(182), 1,
      sym_block,
  [6298] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(433), 1,
      anon_sym_LBRACE,
    STATE(155), 1,
      sym_block,
  [6308] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(658), 1,
      sym_identifier,
    STATE(279), 1,
      sym_type_ref,
  [6318] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(746), 1,
      anon_sym_LBRACE,
    STATE(161), 1,
      sym_service_block,
  [6328] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(748), 1,
      anon_sym_STAR,
    ACTIONS(750), 1,
      anon_sym_LBRACE,
  [6338] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(752), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [6346] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(754), 1,
      sym_identifier,
    STATE(157), 1,
      sym_type_ref,
  [6356] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(722), 2,
      anon_sym_COMMA,
      anon_sym_RPAREN,
  [6364] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(433), 1,
      anon_sym_LBRACE,
    STATE(165), 1,
      sym_block,
  [6374] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(756), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [6382] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(644), 1,
      sym_identifier,
    STATE(271), 1,
      sym_field,
  [6392] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(658), 1,
      sym_identifier,
    STATE(222), 1,
      sym_type_ref,
  [6402] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(535), 1,
      anon_sym_DASH,
    STATE(175), 1,
      aux_sym_tests_section_repeat1,
  [6412] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(553), 1,
      anon_sym_DASH,
    STATE(180), 1,
      aux_sym_preconditions_section_repeat1,
  [6422] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(553), 1,
      anon_sym_DASH,
    STATE(181), 1,
      aux_sym_preconditions_section_repeat1,
  [6432] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(674), 2,
      anon_sym_COMMA,
      anon_sym_GT,
  [6440] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(502), 1,
      anon_sym_DASH,
    STATE(163), 1,
      aux_sym_constraints_section_repeat1,
  [6450] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(758), 2,
      anon_sym_RBRACE,
      sym_identifier,
  [6458] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(506), 1,
      anon_sym_DASH,
    STATE(164), 1,
      aux_sym_depends_on_section_repeat1,
  [6468] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(433), 1,
      anon_sym_LBRACE,
    STATE(199), 1,
      sym_block,
  [6478] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(760), 1,
      anon_sym_LBRACE,
    STATE(200), 1,
      sym_rpc_block,
  [6488] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(736), 1,
      sym_identifier,
    STATE(286), 1,
      sym_import_item,
  [6498] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(669), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [6506] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(762), 2,
      anon_sym_COMMA,
      anon_sym_RBRACE,
  [6514] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(740), 1,
      sym_identifier,
    STATE(194), 1,
      sym_dotted_name,
  [6524] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(764), 1,
      sym_identifier,
    STATE(187), 1,
      sym_constraint_item,
  [6534] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(766), 1,
      sym_identifier,
  [6541] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(768), 1,
      sym_identifier,
  [6548] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(770), 1,
      anon_sym_COLON,
  [6555] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(772), 1,
      sym_identifier,
  [6562] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(774), 1,
      sym_identifier,
  [6569] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(776), 1,
      anon_sym_COLON,
  [6576] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(778), 1,
      anon_sym_in,
  [6583] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(780), 1,
      sym_identifier,
  [6590] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(782), 1,
      anon_sym_COLON,
  [6597] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(784), 1,
      anon_sym_COLON,
  [6604] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(786), 1,
      anon_sym_COLON,
  [6611] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(788), 1,
      anon_sym_COLON,
  [6618] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(790), 1,
      sym_string_literal,
  [6625] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(792), 1,
      sym_identifier,
  [6632] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(794), 1,
      anon_sym_COLON,
  [6639] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(796), 1,
      anon_sym_COLON,
  [6646] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(798), 1,
      anon_sym_COLON,
  [6653] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(800), 1,
      sym_identifier,
  [6660] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(802), 1,
      anon_sym_COLON,
  [6667] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(804), 1,
      anon_sym_COLON,
  [6674] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(806), 1,
      anon_sym_LBRACE,
  [6681] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(808), 1,
      anon_sym_COLON,
  [6688] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(810), 1,
      anon_sym_COLON,
  [6695] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(812), 1,
      anon_sym_COLON,
  [6702] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(814), 1,
      anon_sym_COLON,
  [6709] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(816), 1,
      anon_sym_EQ,
  [6716] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(818), 1,
      anon_sym_COLON,
  [6723] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(820), 1,
      anon_sym_COLON,
  [6730] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(822), 1,
      sym_string_literal,
  [6737] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(824), 1,
      sym_string_literal,
  [6744] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(826), 1,
      anon_sym_COLON,
  [6751] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(828), 1,
      anon_sym_COLON,
  [6758] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(830), 1,
      sym_identifier,
  [6765] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(832), 1,
      anon_sym_COLON,
  [6772] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(834), 1,
      sym_identifier,
  [6779] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(836), 1,
      sym_identifier,
  [6786] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(838), 1,
      sym_identifier,
  [6793] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(840), 1,
      sym_identifier,
  [6800] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(842), 1,
      sym_identifier,
  [6807] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(844), 1,
      sym_identifier,
  [6814] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(846), 1,
      sym_identifier,
  [6821] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(848), 1,
      sym_identifier,
  [6828] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(850), 1,
      sym_identifier,
  [6835] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(852), 1,
      sym_identifier,
  [6842] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(854), 1,
      sym_identifier,
  [6849] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(856), 1,
      ts_builtin_sym_end,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 39,
  [SMALL_STATE(4)] = 81,
  [SMALL_STATE(5)] = 119,
  [SMALL_STATE(6)] = 155,
  [SMALL_STATE(7)] = 191,
  [SMALL_STATE(8)] = 227,
  [SMALL_STATE(9)] = 263,
  [SMALL_STATE(10)] = 301,
  [SMALL_STATE(11)] = 337,
  [SMALL_STATE(12)] = 373,
  [SMALL_STATE(13)] = 409,
  [SMALL_STATE(14)] = 445,
  [SMALL_STATE(15)] = 481,
  [SMALL_STATE(16)] = 526,
  [SMALL_STATE(17)] = 569,
  [SMALL_STATE(18)] = 607,
  [SMALL_STATE(19)] = 654,
  [SMALL_STATE(20)] = 704,
  [SMALL_STATE(21)] = 748,
  [SMALL_STATE(22)] = 792,
  [SMALL_STATE(23)] = 836,
  [SMALL_STATE(24)] = 868,
  [SMALL_STATE(25)] = 912,
  [SMALL_STATE(26)] = 956,
  [SMALL_STATE(27)] = 1000,
  [SMALL_STATE(28)] = 1044,
  [SMALL_STATE(29)] = 1088,
  [SMALL_STATE(30)] = 1132,
  [SMALL_STATE(31)] = 1176,
  [SMALL_STATE(32)] = 1226,
  [SMALL_STATE(33)] = 1257,
  [SMALL_STATE(34)] = 1292,
  [SMALL_STATE(35)] = 1333,
  [SMALL_STATE(36)] = 1364,
  [SMALL_STATE(37)] = 1393,
  [SMALL_STATE(38)] = 1422,
  [SMALL_STATE(39)] = 1463,
  [SMALL_STATE(40)] = 1492,
  [SMALL_STATE(41)] = 1533,
  [SMALL_STATE(42)] = 1574,
  [SMALL_STATE(43)] = 1615,
  [SMALL_STATE(44)] = 1656,
  [SMALL_STATE(45)] = 1697,
  [SMALL_STATE(46)] = 1738,
  [SMALL_STATE(47)] = 1779,
  [SMALL_STATE(48)] = 1812,
  [SMALL_STATE(49)] = 1853,
  [SMALL_STATE(50)] = 1882,
  [SMALL_STATE(51)] = 1911,
  [SMALL_STATE(52)] = 1952,
  [SMALL_STATE(53)] = 1993,
  [SMALL_STATE(54)] = 2034,
  [SMALL_STATE(55)] = 2075,
  [SMALL_STATE(56)] = 2116,
  [SMALL_STATE(57)] = 2145,
  [SMALL_STATE(58)] = 2186,
  [SMALL_STATE(59)] = 2215,
  [SMALL_STATE(60)] = 2244,
  [SMALL_STATE(61)] = 2273,
  [SMALL_STATE(62)] = 2314,
  [SMALL_STATE(63)] = 2355,
  [SMALL_STATE(64)] = 2396,
  [SMALL_STATE(65)] = 2426,
  [SMALL_STATE(66)] = 2456,
  [SMALL_STATE(67)] = 2486,
  [SMALL_STATE(68)] = 2529,
  [SMALL_STATE(69)] = 2572,
  [SMALL_STATE(70)] = 2615,
  [SMALL_STATE(71)] = 2640,
  [SMALL_STATE(72)] = 2676,
  [SMALL_STATE(73)] = 2705,
  [SMALL_STATE(74)] = 2732,
  [SMALL_STATE(75)] = 2759,
  [SMALL_STATE(76)] = 2782,
  [SMALL_STATE(77)] = 2805,
  [SMALL_STATE(78)] = 2829,
  [SMALL_STATE(79)] = 2861,
  [SMALL_STATE(80)] = 2885,
  [SMALL_STATE(81)] = 2917,
  [SMALL_STATE(82)] = 2949,
  [SMALL_STATE(83)] = 2975,
  [SMALL_STATE(84)] = 2999,
  [SMALL_STATE(85)] = 3023,
  [SMALL_STATE(86)] = 3055,
  [SMALL_STATE(87)] = 3079,
  [SMALL_STATE(88)] = 3103,
  [SMALL_STATE(89)] = 3127,
  [SMALL_STATE(90)] = 3151,
  [SMALL_STATE(91)] = 3183,
  [SMALL_STATE(92)] = 3207,
  [SMALL_STATE(93)] = 3233,
  [SMALL_STATE(94)] = 3257,
  [SMALL_STATE(95)] = 3285,
  [SMALL_STATE(96)] = 3311,
  [SMALL_STATE(97)] = 3343,
  [SMALL_STATE(98)] = 3373,
  [SMALL_STATE(99)] = 3405,
  [SMALL_STATE(100)] = 3429,
  [SMALL_STATE(101)] = 3459,
  [SMALL_STATE(102)] = 3489,
  [SMALL_STATE(103)] = 3513,
  [SMALL_STATE(104)] = 3537,
  [SMALL_STATE(105)] = 3569,
  [SMALL_STATE(106)] = 3593,
  [SMALL_STATE(107)] = 3617,
  [SMALL_STATE(108)] = 3641,
  [SMALL_STATE(109)] = 3665,
  [SMALL_STATE(110)] = 3693,
  [SMALL_STATE(111)] = 3719,
  [SMALL_STATE(112)] = 3743,
  [SMALL_STATE(113)] = 3778,
  [SMALL_STATE(114)] = 3805,
  [SMALL_STATE(115)] = 3828,
  [SMALL_STATE(116)] = 3863,
  [SMALL_STATE(117)] = 3898,
  [SMALL_STATE(118)] = 3933,
  [SMALL_STATE(119)] = 3968,
  [SMALL_STATE(120)] = 3995,
  [SMALL_STATE(121)] = 4030,
  [SMALL_STATE(122)] = 4057,
  [SMALL_STATE(123)] = 4077,
  [SMALL_STATE(124)] = 4097,
  [SMALL_STATE(125)] = 4121,
  [SMALL_STATE(126)] = 4145,
  [SMALL_STATE(127)] = 4169,
  [SMALL_STATE(128)] = 4195,
  [SMALL_STATE(129)] = 4219,
  [SMALL_STATE(130)] = 4245,
  [SMALL_STATE(131)] = 4265,
  [SMALL_STATE(132)] = 4284,
  [SMALL_STATE(133)] = 4311,
  [SMALL_STATE(134)] = 4336,
  [SMALL_STATE(135)] = 4363,
  [SMALL_STATE(136)] = 4388,
  [SMALL_STATE(137)] = 4408,
  [SMALL_STATE(138)] = 4430,
  [SMALL_STATE(139)] = 4452,
  [SMALL_STATE(140)] = 4474,
  [SMALL_STATE(141)] = 4493,
  [SMALL_STATE(142)] = 4514,
  [SMALL_STATE(143)] = 4536,
  [SMALL_STATE(144)] = 4552,
  [SMALL_STATE(145)] = 4568,
  [SMALL_STATE(146)] = 4588,
  [SMALL_STATE(147)] = 4604,
  [SMALL_STATE(148)] = 4624,
  [SMALL_STATE(149)] = 4646,
  [SMALL_STATE(150)] = 4666,
  [SMALL_STATE(151)] = 4682,
  [SMALL_STATE(152)] = 4702,
  [SMALL_STATE(153)] = 4718,
  [SMALL_STATE(154)] = 4740,
  [SMALL_STATE(155)] = 4755,
  [SMALL_STATE(156)] = 4770,
  [SMALL_STATE(157)] = 4785,
  [SMALL_STATE(158)] = 4804,
  [SMALL_STATE(159)] = 4821,
  [SMALL_STATE(160)] = 4836,
  [SMALL_STATE(161)] = 4851,
  [SMALL_STATE(162)] = 4866,
  [SMALL_STATE(163)] = 4885,
  [SMALL_STATE(164)] = 4904,
  [SMALL_STATE(165)] = 4923,
  [SMALL_STATE(166)] = 4938,
  [SMALL_STATE(167)] = 4953,
  [SMALL_STATE(168)] = 4972,
  [SMALL_STATE(169)] = 4987,
  [SMALL_STATE(170)] = 5004,
  [SMALL_STATE(171)] = 5021,
  [SMALL_STATE(172)] = 5036,
  [SMALL_STATE(173)] = 5051,
  [SMALL_STATE(174)] = 5068,
  [SMALL_STATE(175)] = 5087,
  [SMALL_STATE(176)] = 5106,
  [SMALL_STATE(177)] = 5125,
  [SMALL_STATE(178)] = 5144,
  [SMALL_STATE(179)] = 5159,
  [SMALL_STATE(180)] = 5174,
  [SMALL_STATE(181)] = 5193,
  [SMALL_STATE(182)] = 5212,
  [SMALL_STATE(183)] = 5227,
  [SMALL_STATE(184)] = 5244,
  [SMALL_STATE(185)] = 5263,
  [SMALL_STATE(186)] = 5277,
  [SMALL_STATE(187)] = 5291,
  [SMALL_STATE(188)] = 5305,
  [SMALL_STATE(189)] = 5319,
  [SMALL_STATE(190)] = 5333,
  [SMALL_STATE(191)] = 5347,
  [SMALL_STATE(192)] = 5361,
  [SMALL_STATE(193)] = 5375,
  [SMALL_STATE(194)] = 5389,
  [SMALL_STATE(195)] = 5403,
  [SMALL_STATE(196)] = 5417,
  [SMALL_STATE(197)] = 5439,
  [SMALL_STATE(198)] = 5452,
  [SMALL_STATE(199)] = 5465,
  [SMALL_STATE(200)] = 5478,
  [SMALL_STATE(201)] = 5491,
  [SMALL_STATE(202)] = 5504,
  [SMALL_STATE(203)] = 5522,
  [SMALL_STATE(204)] = 5540,
  [SMALL_STATE(205)] = 5558,
  [SMALL_STATE(206)] = 5573,
  [SMALL_STATE(207)] = 5588,
  [SMALL_STATE(208)] = 5605,
  [SMALL_STATE(209)] = 5620,
  [SMALL_STATE(210)] = 5634,
  [SMALL_STATE(211)] = 5644,
  [SMALL_STATE(212)] = 5654,
  [SMALL_STATE(213)] = 5664,
  [SMALL_STATE(214)] = 5678,
  [SMALL_STATE(215)] = 5690,
  [SMALL_STATE(216)] = 5704,
  [SMALL_STATE(217)] = 5718,
  [SMALL_STATE(218)] = 5731,
  [SMALL_STATE(219)] = 5744,
  [SMALL_STATE(220)] = 5757,
  [SMALL_STATE(221)] = 5770,
  [SMALL_STATE(222)] = 5783,
  [SMALL_STATE(223)] = 5794,
  [SMALL_STATE(224)] = 5805,
  [SMALL_STATE(225)] = 5818,
  [SMALL_STATE(226)] = 5831,
  [SMALL_STATE(227)] = 5842,
  [SMALL_STATE(228)] = 5855,
  [SMALL_STATE(229)] = 5866,
  [SMALL_STATE(230)] = 5879,
  [SMALL_STATE(231)] = 5892,
  [SMALL_STATE(232)] = 5905,
  [SMALL_STATE(233)] = 5916,
  [SMALL_STATE(234)] = 5929,
  [SMALL_STATE(235)] = 5942,
  [SMALL_STATE(236)] = 5955,
  [SMALL_STATE(237)] = 5968,
  [SMALL_STATE(238)] = 5981,
  [SMALL_STATE(239)] = 5994,
  [SMALL_STATE(240)] = 6007,
  [SMALL_STATE(241)] = 6018,
  [SMALL_STATE(242)] = 6031,
  [SMALL_STATE(243)] = 6044,
  [SMALL_STATE(244)] = 6057,
  [SMALL_STATE(245)] = 6070,
  [SMALL_STATE(246)] = 6083,
  [SMALL_STATE(247)] = 6096,
  [SMALL_STATE(248)] = 6109,
  [SMALL_STATE(249)] = 6122,
  [SMALL_STATE(250)] = 6135,
  [SMALL_STATE(251)] = 6148,
  [SMALL_STATE(252)] = 6161,
  [SMALL_STATE(253)] = 6174,
  [SMALL_STATE(254)] = 6187,
  [SMALL_STATE(255)] = 6200,
  [SMALL_STATE(256)] = 6210,
  [SMALL_STATE(257)] = 6220,
  [SMALL_STATE(258)] = 6230,
  [SMALL_STATE(259)] = 6240,
  [SMALL_STATE(260)] = 6250,
  [SMALL_STATE(261)] = 6258,
  [SMALL_STATE(262)] = 6268,
  [SMALL_STATE(263)] = 6278,
  [SMALL_STATE(264)] = 6288,
  [SMALL_STATE(265)] = 6298,
  [SMALL_STATE(266)] = 6308,
  [SMALL_STATE(267)] = 6318,
  [SMALL_STATE(268)] = 6328,
  [SMALL_STATE(269)] = 6338,
  [SMALL_STATE(270)] = 6346,
  [SMALL_STATE(271)] = 6356,
  [SMALL_STATE(272)] = 6364,
  [SMALL_STATE(273)] = 6374,
  [SMALL_STATE(274)] = 6382,
  [SMALL_STATE(275)] = 6392,
  [SMALL_STATE(276)] = 6402,
  [SMALL_STATE(277)] = 6412,
  [SMALL_STATE(278)] = 6422,
  [SMALL_STATE(279)] = 6432,
  [SMALL_STATE(280)] = 6440,
  [SMALL_STATE(281)] = 6450,
  [SMALL_STATE(282)] = 6458,
  [SMALL_STATE(283)] = 6468,
  [SMALL_STATE(284)] = 6478,
  [SMALL_STATE(285)] = 6488,
  [SMALL_STATE(286)] = 6498,
  [SMALL_STATE(287)] = 6506,
  [SMALL_STATE(288)] = 6514,
  [SMALL_STATE(289)] = 6524,
  [SMALL_STATE(290)] = 6534,
  [SMALL_STATE(291)] = 6541,
  [SMALL_STATE(292)] = 6548,
  [SMALL_STATE(293)] = 6555,
  [SMALL_STATE(294)] = 6562,
  [SMALL_STATE(295)] = 6569,
  [SMALL_STATE(296)] = 6576,
  [SMALL_STATE(297)] = 6583,
  [SMALL_STATE(298)] = 6590,
  [SMALL_STATE(299)] = 6597,
  [SMALL_STATE(300)] = 6604,
  [SMALL_STATE(301)] = 6611,
  [SMALL_STATE(302)] = 6618,
  [SMALL_STATE(303)] = 6625,
  [SMALL_STATE(304)] = 6632,
  [SMALL_STATE(305)] = 6639,
  [SMALL_STATE(306)] = 6646,
  [SMALL_STATE(307)] = 6653,
  [SMALL_STATE(308)] = 6660,
  [SMALL_STATE(309)] = 6667,
  [SMALL_STATE(310)] = 6674,
  [SMALL_STATE(311)] = 6681,
  [SMALL_STATE(312)] = 6688,
  [SMALL_STATE(313)] = 6695,
  [SMALL_STATE(314)] = 6702,
  [SMALL_STATE(315)] = 6709,
  [SMALL_STATE(316)] = 6716,
  [SMALL_STATE(317)] = 6723,
  [SMALL_STATE(318)] = 6730,
  [SMALL_STATE(319)] = 6737,
  [SMALL_STATE(320)] = 6744,
  [SMALL_STATE(321)] = 6751,
  [SMALL_STATE(322)] = 6758,
  [SMALL_STATE(323)] = 6765,
  [SMALL_STATE(324)] = 6772,
  [SMALL_STATE(325)] = 6779,
  [SMALL_STATE(326)] = 6786,
  [SMALL_STATE(327)] = 6793,
  [SMALL_STATE(328)] = 6800,
  [SMALL_STATE(329)] = 6807,
  [SMALL_STATE(330)] = 6814,
  [SMALL_STATE(331)] = 6821,
  [SMALL_STATE(332)] = 6828,
  [SMALL_STATE(333)] = 6835,
  [SMALL_STATE(334)] = 6842,
  [SMALL_STATE(335)] = 6849,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(256),
  [7] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_expression, 1, 0, 0),
  [9] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expression, 1, 0, 0),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [13] = {.entry = {.count = 1, .reusable = false}}, SHIFT(322),
  [15] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_scenario_block_repeat1, 2, 0, 0),
  [17] = {.entry = {.count = 1, .reusable = false}}, SHIFT(57),
  [19] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_scenario_block_repeat1, 2, 0, 0),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [23] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_unary_expression, 2, 0, 0),
  [25] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_unary_expression, 2, 0, 0),
  [27] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_call_expression, 5, 0, 9),
  [29] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call_expression, 5, 0, 9),
  [31] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_call_expression, 4, 0, 9),
  [33] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call_expression, 4, 0, 9),
  [35] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_list_expression, 4, 0, 0),
  [37] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list_expression, 4, 0, 0),
  [39] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binary_expression, 3, 0, 0),
  [41] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_binary_expression, 3, 0, 0),
  [43] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_boolean_literal, 1, 0, 0),
  [45] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_boolean_literal, 1, 0, 0),
  [47] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_list_expression, 2, 0, 0),
  [49] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list_expression, 2, 0, 0),
  [51] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_field_expression, 3, 0, 0),
  [53] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field_expression, 3, 0, 0),
  [55] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_call_expression, 3, 0, 9),
  [57] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call_expression, 3, 0, 9),
  [59] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_list_expression, 3, 0, 0),
  [61] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list_expression, 3, 0, 0),
  [63] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [65] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_scenario_block_repeat2, 3, 0, 0),
  [67] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_scenario_block_repeat2, 3, 0, 0),
  [69] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_property_block_repeat2, 3, 0, 0),
  [71] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_quantifier, 3, 0, 17),
  [73] = {.entry = {.count = 1, .reusable = true}}, SHIFT(188),
  [75] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [77] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [79] = {.entry = {.count = 1, .reusable = false}}, SHIFT(111),
  [81] = {.entry = {.count = 1, .reusable = true}}, SHIFT(111),
  [83] = {.entry = {.count = 1, .reusable = false}}, SHIFT(105),
  [85] = {.entry = {.count = 1, .reusable = false}}, SHIFT(72),
  [87] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 2, 0, 0),
  [89] = {.entry = {.count = 1, .reusable = true}}, SHIFT(257),
  [91] = {.entry = {.count = 1, .reusable = true}}, SHIFT(333),
  [93] = {.entry = {.count = 1, .reusable = true}}, SHIFT(331),
  [95] = {.entry = {.count = 1, .reusable = true}}, SHIFT(330),
  [97] = {.entry = {.count = 1, .reusable = true}}, SHIFT(329),
  [99] = {.entry = {.count = 1, .reusable = true}}, SHIFT(328),
  [101] = {.entry = {.count = 1, .reusable = true}}, SHIFT(327),
  [103] = {.entry = {.count = 1, .reusable = true}}, SHIFT(326),
  [105] = {.entry = {.count = 1, .reusable = true}}, SHIFT(325),
  [107] = {.entry = {.count = 1, .reusable = true}}, SHIFT(107),
  [109] = {.entry = {.count = 1, .reusable = false}}, SHIFT(73),
  [111] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [113] = {.entry = {.count = 1, .reusable = true}}, SHIFT(79),
  [115] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [117] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [119] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [121] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [123] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [125] = {.entry = {.count = 1, .reusable = false}}, SHIFT(99),
  [127] = {.entry = {.count = 1, .reusable = true}}, SHIFT(99),
  [129] = {.entry = {.count = 1, .reusable = false}}, SHIFT(102),
  [131] = {.entry = {.count = 1, .reusable = false}}, SHIFT(71),
  [133] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [135] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [137] = {.entry = {.count = 1, .reusable = true}}, SHIFT(103),
  [139] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1, 0, 0),
  [141] = {.entry = {.count = 1, .reusable = false}}, SHIFT(332),
  [143] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field, 5, 0, 12),
  [145] = {.entry = {.count = 1, .reusable = false}}, SHIFT(42),
  [147] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_field, 5, 0, 12),
  [149] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [151] = {.entry = {.count = 1, .reusable = false}}, SHIFT(74),
  [153] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [155] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [157] = {.entry = {.count = 1, .reusable = false}}, SHIFT(37),
  [159] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [161] = {.entry = {.count = 1, .reusable = false}}, SHIFT(39),
  [163] = {.entry = {.count = 1, .reusable = false}}, SHIFT(23),
  [165] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [167] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [169] = {.entry = {.count = 1, .reusable = false}}, SHIFT(8),
  [171] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [173] = {.entry = {.count = 1, .reusable = false}}, SHIFT(10),
  [175] = {.entry = {.count = 1, .reusable = false}}, SHIFT(2),
  [177] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_preconditions_section_repeat1, 2, 0, 0),
  [179] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_dotted_name, 1, 0, 0),
  [181] = {.entry = {.count = 1, .reusable = true}}, SHIFT(324),
  [183] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_dotted_name_repeat1, 2, 0, 0),
  [185] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_dotted_name_repeat1, 2, 0, 0), SHIFT_REPEAT(324),
  [188] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_dotted_name, 2, 0, 0),
  [190] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 3, 0, 0),
  [192] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0),
  [194] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0), SHIFT_REPEAT(333),
  [197] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0), SHIFT_REPEAT(331),
  [200] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0), SHIFT_REPEAT(330),
  [203] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0), SHIFT_REPEAT(329),
  [206] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0), SHIFT_REPEAT(328),
  [209] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0), SHIFT_REPEAT(327),
  [212] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0), SHIFT_REPEAT(326),
  [215] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat2, 2, 0, 0), SHIFT_REPEAT(325),
  [218] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_type_ref, 1, 0, 3), REDUCE(sym_expression, 1, 0, 0),
  [221] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_type_ref, 1, 0, 3),
  [223] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [225] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_expression, 1, 0, 0), SHIFT(224),
  [228] = {.entry = {.count = 2, .reusable = false}}, REDUCE(sym_type_ref, 1, 0, 3), REDUCE(sym_expression, 1, 0, 0),
  [231] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [233] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [235] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block, 3, 0, 0),
  [237] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block, 2, 0, 0),
  [239] = {.entry = {.count = 1, .reusable = false}}, SHIFT(307),
  [241] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [243] = {.entry = {.count = 1, .reusable = false}}, SHIFT(63),
  [245] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [247] = {.entry = {.count = 1, .reusable = true}}, SHIFT(83),
  [249] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [251] = {.entry = {.count = 1, .reusable = true}}, SHIFT(106),
  [253] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [255] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [257] = {.entry = {.count = 1, .reusable = false}}, SHIFT(290),
  [259] = {.entry = {.count = 1, .reusable = true}}, SHIFT(91),
  [261] = {.entry = {.count = 1, .reusable = false}}, SHIFT(41),
  [263] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [265] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [267] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__block_item, 3, 0, 0),
  [269] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__block_item, 3, 0, 0),
  [271] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__block_item, 2, 0, 0),
  [273] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__block_item, 2, 0, 0),
  [275] = {.entry = {.count = 1, .reusable = true}}, SHIFT(77),
  [277] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_scenario_block_repeat1, 2, 0, 0), SHIFT_REPEAT(54),
  [280] = {.entry = {.count = 1, .reusable = true}}, SHIFT(159),
  [282] = {.entry = {.count = 1, .reusable = true}}, SHIFT(309),
  [284] = {.entry = {.count = 1, .reusable = true}}, SHIFT(308),
  [286] = {.entry = {.count = 1, .reusable = true}}, SHIFT(306),
  [288] = {.entry = {.count = 1, .reusable = true}}, SHIFT(305),
  [290] = {.entry = {.count = 1, .reusable = true}}, SHIFT(304),
  [292] = {.entry = {.count = 1, .reusable = true}}, SHIFT(303),
  [294] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_ref, 1, 0, 3),
  [296] = {.entry = {.count = 1, .reusable = true}}, SHIFT(246),
  [298] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_rpc_block_repeat1, 2, 0, 0),
  [300] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_rpc_block_repeat1, 2, 0, 0), SHIFT_REPEAT(292),
  [303] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_rpc_block_repeat1, 2, 0, 0), SHIFT_REPEAT(313),
  [306] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_rpc_block_repeat1, 2, 0, 0), SHIFT_REPEAT(298),
  [309] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_rpc_block_repeat1, 2, 0, 0), SHIFT_REPEAT(299),
  [312] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_rpc_block_repeat1, 2, 0, 0), SHIFT_REPEAT(300),
  [315] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_rpc_block_repeat1, 2, 0, 0), SHIFT_REPEAT(301),
  [318] = {.entry = {.count = 1, .reusable = true}}, SHIFT(201),
  [320] = {.entry = {.count = 1, .reusable = true}}, SHIFT(292),
  [322] = {.entry = {.count = 1, .reusable = true}}, SHIFT(313),
  [324] = {.entry = {.count = 1, .reusable = true}}, SHIFT(298),
  [326] = {.entry = {.count = 1, .reusable = true}}, SHIFT(299),
  [328] = {.entry = {.count = 1, .reusable = true}}, SHIFT(300),
  [330] = {.entry = {.count = 1, .reusable = true}}, SHIFT(301),
  [332] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_service_block_repeat1, 2, 0, 0),
  [334] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_service_block_repeat1, 2, 0, 0), SHIFT_REPEAT(309),
  [337] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_service_block_repeat1, 2, 0, 0), SHIFT_REPEAT(308),
  [340] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_service_block_repeat1, 2, 0, 0), SHIFT_REPEAT(306),
  [343] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_service_block_repeat1, 2, 0, 0), SHIFT_REPEAT(305),
  [346] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_service_block_repeat1, 2, 0, 0), SHIFT_REPEAT(304),
  [349] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_service_block_repeat1, 2, 0, 0), SHIFT_REPEAT(303),
  [352] = {.entry = {.count = 1, .reusable = true}}, SHIFT(197),
  [354] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_constraint_arg, 1, 0, 14),
  [356] = {.entry = {.count = 1, .reusable = true}}, SHIFT(178),
  [358] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_constraint_arg, 3, 0, 15),
  [360] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_ref, 5, 0, 3),
  [362] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_ref, 3, 0, 3),
  [364] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_property_block_repeat1, 2, 0, 0), SHIFT_REPEAT(262),
  [367] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_property_block_repeat1, 2, 0, 0),
  [369] = {.entry = {.count = 1, .reusable = true}}, SHIFT(262),
  [371] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_property_block_repeat2, 4, 0, 0),
  [373] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_scenario_block_repeat2, 4, 0, 0),
  [375] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_scenario_block_repeat2, 4, 0, 0),
  [377] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_property_block_repeat2, 2, 0, 0),
  [379] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_property_block_repeat2, 2, 0, 0),
  [381] = {.entry = {.count = 1, .reusable = false}}, SHIFT(296),
  [383] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_ref, 4, 0, 3),
  [385] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_scenario_block_repeat2, 2, 0, 0),
  [387] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_scenario_block_repeat2, 2, 0, 0), SHIFT_REPEAT(295),
  [390] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_scenario_block_repeat2, 2, 0, 0), SHIFT_REPEAT(295),
  [393] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_scenario_block_repeat2, 2, 0, 0), SHIFT_REPEAT(323),
  [396] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_property_block, 4, 0, 16),
  [398] = {.entry = {.count = 1, .reusable = true}}, SHIFT(321),
  [400] = {.entry = {.count = 1, .reusable = true}}, SHIFT(320),
  [402] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_scenario_block, 4, 0, 16),
  [404] = {.entry = {.count = 1, .reusable = true}}, SHIFT(295),
  [406] = {.entry = {.count = 1, .reusable = false}}, SHIFT(295),
  [408] = {.entry = {.count = 1, .reusable = true}}, SHIFT(323),
  [410] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_property_block_repeat2, 2, 0, 0), SHIFT_REPEAT(321),
  [413] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_property_block_repeat2, 2, 0, 0), SHIFT_REPEAT(320),
  [416] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_dotted_name, 1, 0, 0), SHIFT(324),
  [419] = {.entry = {.count = 2, .reusable = true}}, REDUCE(sym_dotted_name, 2, 0, 0), SHIFT(324),
  [422] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0),
  [424] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(257),
  [427] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_use_declaration, 2, 0, 2),
  [429] = {.entry = {.count = 1, .reusable = true}}, SHIFT(268),
  [431] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__type_kind, 1, 0, 0),
  [433] = {.entry = {.count = 1, .reusable = true}}, SHIFT(202),
  [435] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_outputs_section, 3, 0, 0),
  [437] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_outputs_section, 3, 0, 0),
  [439] = {.entry = {.count = 1, .reusable = false}}, SHIFT(316),
  [441] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_use_declaration, 4, 0, 2),
  [443] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_module_declaration, 2, 0, 1),
  [445] = {.entry = {.count = 1, .reusable = true}}, SHIFT(244),
  [447] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_use_declaration, 7, 0, 2),
  [449] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_errors_section_repeat1, 2, 0, 0),
  [451] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_errors_section_repeat1, 2, 0, 0), SHIFT_REPEAT(291),
  [454] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_inputs_section_repeat1, 2, 0, 0),
  [456] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_inputs_section_repeat1, 2, 0, 0),
  [458] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_inputs_section_repeat1, 2, 0, 0), SHIFT_REPEAT(316),
  [461] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_errors_section, 3, 0, 0),
  [463] = {.entry = {.count = 1, .reusable = true}}, SHIFT(291),
  [465] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_use_declaration, 5, 0, 2),
  [467] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_metric_declaration, 2, 0, 13),
  [469] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_use_declaration, 6, 0, 2),
  [471] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_inputs_section, 3, 0, 0),
  [473] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_inputs_section, 3, 0, 0),
  [475] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_workflow_declaration, 3, 0, 0),
  [477] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_policy_declaration, 3, 0, 0),
  [479] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_type, 3, 0, 0),
  [481] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_field, 3, 0, 6),
  [483] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [485] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_field, 3, 0, 6),
  [487] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_type_ref, 4, 0, 3),
  [489] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_service_block, 3, 0, 0),
  [491] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_refined_type, 2, 0, 5),
  [493] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_service_declaration, 3, 0, 1),
  [495] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_metrics_section_repeat1, 2, 0, 0),
  [497] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_metrics_section_repeat1, 2, 0, 0), SHIFT_REPEAT(206),
  [500] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_constraints_section, 3, 0, 0),
  [502] = {.entry = {.count = 1, .reusable = true}}, SHIFT(289),
  [504] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_depends_on_section, 3, 0, 7),
  [506] = {.entry = {.count = 1, .reusable = true}}, SHIFT(288),
  [508] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_struct_type, 2, 0, 0),
  [510] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_component_declaration, 3, 0, 0),
  [512] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_metrics_section, 3, 0, 0),
  [514] = {.entry = {.count = 1, .reusable = true}}, SHIFT(206),
  [516] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_pipeline_declaration, 3, 0, 0),
  [518] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_type_ref, 5, 0, 3),
  [520] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_error_definition, 2, 0, 1),
  [522] = {.entry = {.count = 1, .reusable = true}}, SHIFT(218),
  [524] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_agent_declaration, 3, 0, 0),
  [526] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_type, 4, 0, 0),
  [528] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_type_ref, 3, 0, 3),
  [530] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_preconditions_section_repeat1, 2, 0, 0), SHIFT_REPEAT(52),
  [533] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_tests_section, 3, 0, 0),
  [535] = {.entry = {.count = 1, .reusable = true}}, SHIFT(205),
  [537] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_constraints_section_repeat1, 2, 0, 0),
  [539] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_constraints_section_repeat1, 2, 0, 0), SHIFT_REPEAT(289),
  [542] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_depends_on_section_repeat1, 2, 0, 11),
  [544] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_depends_on_section_repeat1, 2, 0, 11), SHIFT_REPEAT(288),
  [547] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_service_block, 2, 0, 0),
  [549] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type_declaration, 4, 0, 4),
  [551] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_postconditions_section, 3, 0, 0),
  [553] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [555] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_preconditions_section, 3, 0, 0),
  [557] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_schema_declaration, 3, 0, 0),
  [559] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_constraint_item, 1, 0, 3),
  [561] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [563] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_tests_section_repeat1, 2, 0, 0),
  [565] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_tests_section_repeat1, 2, 0, 0), SHIFT_REPEAT(205),
  [568] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_metric_declaration, 3, 0, 13),
  [570] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_constraint_item, 5, 0, 3),
  [572] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_constraint_item, 3, 0, 3),
  [574] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_error_definition, 4, 0, 1),
  [576] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_error_definition, 5, 0, 1),
  [578] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_error_definition, 6, 0, 1),
  [580] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_constraint_item, 4, 0, 3),
  [582] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_depends_on_section_repeat1, 2, 0, 10),
  [584] = {.entry = {.count = 1, .reusable = false}}, SHIFT(272),
  [586] = {.entry = {.count = 1, .reusable = false}}, SHIFT(310),
  [588] = {.entry = {.count = 1, .reusable = false}}, SHIFT(114),
  [590] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rpc_block, 2, 0, 0),
  [592] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_goal_section, 3, 0, 0),
  [594] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_budget_section, 3, 0, 0),
  [596] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rpc_declaration, 3, 0, 1),
  [598] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_rpc_block, 3, 0, 0),
  [600] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [602] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [604] = {.entry = {.count = 1, .reusable = true}}, SHIFT(312),
  [606] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_block_repeat1, 2, 0, 0),
  [608] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_block_repeat1, 2, 0, 0), SHIFT_REPEAT(51),
  [611] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_block_repeat1, 2, 0, 0), SHIFT_REPEAT(312),
  [614] = {.entry = {.count = 1, .reusable = true}}, SHIFT(75),
  [616] = {.entry = {.count = 1, .reusable = true}}, SHIFT(314),
  [618] = {.entry = {.count = 1, .reusable = true}}, SHIFT(317),
  [620] = {.entry = {.count = 1, .reusable = true}}, SHIFT(294),
  [622] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_enum_type_repeat1, 2, 0, 0),
  [624] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_enum_type_repeat1, 2, 0, 0), SHIFT_REPEAT(240),
  [627] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_scenario_block_repeat1, 2, 0, 0), SHIFT_REPEAT(34),
  [630] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [632] = {.entry = {.count = 1, .reusable = true}}, SHIFT(156),
  [634] = {.entry = {.count = 1, .reusable = true}}, SHIFT(240),
  [636] = {.entry = {.count = 1, .reusable = true}}, SHIFT(172),
  [638] = {.entry = {.count = 1, .reusable = true}}, SHIFT(266),
  [640] = {.entry = {.count = 1, .reusable = true}}, SHIFT(210),
  [642] = {.entry = {.count = 1, .reusable = true}}, SHIFT(189),
  [644] = {.entry = {.count = 1, .reusable = true}}, SHIFT(311),
  [646] = {.entry = {.count = 1, .reusable = true}}, SHIFT(274),
  [648] = {.entry = {.count = 1, .reusable = true}}, SHIFT(191),
  [650] = {.entry = {.count = 1, .reusable = true}}, SHIFT(122),
  [652] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [654] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [656] = {.entry = {.count = 1, .reusable = true}}, SHIFT(211),
  [658] = {.entry = {.count = 1, .reusable = true}}, SHIFT(114),
  [660] = {.entry = {.count = 1, .reusable = true}}, SHIFT(281),
  [662] = {.entry = {.count = 1, .reusable = true}}, SHIFT(316),
  [664] = {.entry = {.count = 1, .reusable = true}}, SHIFT(88),
  [666] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_use_declaration_repeat1, 2, 0, 0), SHIFT_REPEAT(285),
  [669] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_use_declaration_repeat1, 2, 0, 0),
  [671] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_type_ref_repeat1, 2, 0, 0), SHIFT_REPEAT(266),
  [674] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_type_ref_repeat1, 2, 0, 0),
  [676] = {.entry = {.count = 1, .reusable = true}}, SHIFT(87),
  [678] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_item, 1, 0, 3),
  [680] = {.entry = {.count = 1, .reusable = true}}, SHIFT(297),
  [682] = {.entry = {.count = 1, .reusable = true}}, SHIFT(273),
  [684] = {.entry = {.count = 1, .reusable = true}}, SHIFT(285),
  [686] = {.entry = {.count = 1, .reusable = true}}, SHIFT(152),
  [688] = {.entry = {.count = 1, .reusable = true}}, SHIFT(190),
  [690] = {.entry = {.count = 1, .reusable = true}}, SHIFT(269),
  [692] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_constraint_item_repeat1, 2, 0, 0), SHIFT_REPEAT(28),
  [695] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_constraint_item_repeat1, 2, 0, 0),
  [697] = {.entry = {.count = 1, .reusable = true}}, SHIFT(86),
  [699] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [701] = {.entry = {.count = 1, .reusable = true}}, SHIFT(192),
  [703] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_variant, 1, 0, 3),
  [705] = {.entry = {.count = 1, .reusable = true}}, SHIFT(225),
  [707] = {.entry = {.count = 1, .reusable = true}}, SHIFT(186),
  [709] = {.entry = {.count = 1, .reusable = true}}, SHIFT(212),
  [711] = {.entry = {.count = 1, .reusable = true}}, SHIFT(89),
  [713] = {.entry = {.count = 1, .reusable = true}}, SHIFT(173),
  [715] = {.entry = {.count = 1, .reusable = true}}, SHIFT(130),
  [717] = {.entry = {.count = 1, .reusable = true}}, SHIFT(123),
  [719] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_enum_variant_repeat1, 2, 0, 0), SHIFT_REPEAT(274),
  [722] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_enum_variant_repeat1, 2, 0, 0),
  [724] = {.entry = {.count = 1, .reusable = true}}, SHIFT(158),
  [726] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [728] = {.entry = {.count = 1, .reusable = true}}, SHIFT(169),
  [730] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [732] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [734] = {.entry = {.count = 1, .reusable = true}}, SHIFT(150),
  [736] = {.entry = {.count = 1, .reusable = true}}, SHIFT(232),
  [738] = {.entry = {.count = 1, .reusable = true}}, SHIFT(146),
  [740] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [742] = {.entry = {.count = 1, .reusable = true}}, SHIFT(137),
  [744] = {.entry = {.count = 1, .reusable = true}}, SHIFT(296),
  [746] = {.entry = {.count = 1, .reusable = true}}, SHIFT(120),
  [748] = {.entry = {.count = 1, .reusable = true}}, SHIFT(143),
  [750] = {.entry = {.count = 1, .reusable = true}}, SHIFT(253),
  [752] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_variant, 5, 0, 3),
  [754] = {.entry = {.count = 1, .reusable = true}}, SHIFT(145),
  [756] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_variant, 4, 0, 3),
  [758] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_enum_variant, 3, 0, 3),
  [760] = {.entry = {.count = 1, .reusable = true}}, SHIFT(118),
  [762] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_import_item, 3, 0, 8),
  [764] = {.entry = {.count = 1, .reusable = true}}, SHIFT(183),
  [766] = {.entry = {.count = 1, .reusable = true}}, SHIFT(108),
  [768] = {.entry = {.count = 1, .reusable = true}}, SHIFT(170),
  [770] = {.entry = {.count = 1, .reusable = true}}, SHIFT(228),
  [772] = {.entry = {.count = 1, .reusable = true}}, SHIFT(151),
  [774] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_metric_kind, 1, 0, 0),
  [776] = {.entry = {.count = 1, .reusable = true}}, SHIFT(45),
  [778] = {.entry = {.count = 1, .reusable = true}}, SHIFT(43),
  [780] = {.entry = {.count = 1, .reusable = true}}, SHIFT(287),
  [782] = {.entry = {.count = 1, .reusable = true}}, SHIFT(278),
  [784] = {.entry = {.count = 1, .reusable = true}}, SHIFT(277),
  [786] = {.entry = {.count = 1, .reusable = true}}, SHIFT(223),
  [788] = {.entry = {.count = 1, .reusable = true}}, SHIFT(276),
  [790] = {.entry = {.count = 1, .reusable = true}}, SHIFT(198),
  [792] = {.entry = {.count = 1, .reusable = true}}, SHIFT(284),
  [794] = {.entry = {.count = 1, .reusable = true}}, SHIFT(255),
  [796] = {.entry = {.count = 1, .reusable = true}}, SHIFT(283),
  [798] = {.entry = {.count = 1, .reusable = true}}, SHIFT(282),
  [800] = {.entry = {.count = 1, .reusable = true}}, SHIFT(84),
  [802] = {.entry = {.count = 1, .reusable = true}}, SHIFT(280),
  [804] = {.entry = {.count = 1, .reusable = true}}, SHIFT(302),
  [806] = {.entry = {.count = 1, .reusable = true}}, SHIFT(215),
  [808] = {.entry = {.count = 1, .reusable = true}}, SHIFT(275),
  [810] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [812] = {.entry = {.count = 1, .reusable = true}}, SHIFT(226),
  [814] = {.entry = {.count = 1, .reusable = true}}, SHIFT(319),
  [816] = {.entry = {.count = 1, .reusable = true}}, SHIFT(196),
  [818] = {.entry = {.count = 1, .reusable = true}}, SHIFT(270),
  [820] = {.entry = {.count = 1, .reusable = true}}, SHIFT(318),
  [822] = {.entry = {.count = 1, .reusable = true}}, SHIFT(208),
  [824] = {.entry = {.count = 1, .reusable = true}}, SHIFT(207),
  [826] = {.entry = {.count = 1, .reusable = true}}, SHIFT(129),
  [828] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [830] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [832] = {.entry = {.count = 1, .reusable = true}}, SHIFT(334),
  [834] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [836] = {.entry = {.count = 1, .reusable = true}}, SHIFT(267),
  [838] = {.entry = {.count = 1, .reusable = true}}, SHIFT(315),
  [840] = {.entry = {.count = 1, .reusable = true}}, SHIFT(265),
  [842] = {.entry = {.count = 1, .reusable = true}}, SHIFT(264),
  [844] = {.entry = {.count = 1, .reusable = true}}, SHIFT(263),
  [846] = {.entry = {.count = 1, .reusable = true}}, SHIFT(261),
  [848] = {.entry = {.count = 1, .reusable = true}}, SHIFT(259),
  [850] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [852] = {.entry = {.count = 1, .reusable = true}}, SHIFT(258),
  [854] = {.entry = {.count = 1, .reusable = true}}, SHIFT(136),
  [856] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef TREE_SITTER_HIDE_SYMBOLS
#define TS_PUBLIC
#elif defined(_WIN32)
#define TS_PUBLIC __declspec(dllexport)
#else
#define TS_PUBLIC __attribute__((visibility("default")))
#endif

TS_PUBLIC const TSLanguage *tree_sitter_omnilang(void) {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .field_names = ts_field_names,
    .field_map_slices = ts_field_map_slices,
    .field_map_entries = ts_field_map_entries,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
