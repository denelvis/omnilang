; Keywords
"module" @keyword
"use" @keyword
"type" @keyword
"struct" @keyword
"enum" @keyword
"service" @keyword
"component" @keyword
"pipeline" @keyword
"workflow" @keyword
"agent" @keyword
"schema" @keyword
"policy" @keyword
"rpc" @keyword
"goal" @keyword
"constraints" @keyword
"metrics" @keyword
"counter" @keyword
"gauge" @keyword
"histogram" @keyword
"inputs" @keyword
"outputs" @keyword
"preconditions" @keyword
"postconditions" @keyword
"errors" @keyword
"tests" @keyword
"scenario" @keyword
"property" @keyword
"forall" @keyword
"given" @keyword
"when" @keyword
"expect" @keyword
"expect_error" @keyword
"assert" @keyword
"in" @keyword
"as" @keyword

; Operators
"==" @operator
"!=" @operator
"<" @operator
">" @operator
"<=" @operator
">=" @operator
"&&" @operator
"||" @operator
"!" @operator
".." @operator
"..<" @operator

; Literals
(integer_literal) @number
(float_literal) @number
(string_literal) @string
(boolean_literal) @boolean
(duration_literal) @string.special
(money_literal) @float
(percentage_literal) @number
(null_literal) @constant.builtin

; Functions
(call_expression
  function: (identifier) @function)

; Types
(type_declaration
  name: (identifier) @type)
(type_ref
  name: (identifier) @type)

; Service and RPC declarations
(service_declaration
  name: (identifier) @type)
(rpc_declaration
  name: (identifier) @function)

; Fields
(field
  name: (identifier) @property)

; Comments
(comment) @comment
