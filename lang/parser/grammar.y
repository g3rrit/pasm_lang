%include {
#include "token_types.h"
#include "cassert"
#include "lexer.h"
}

%name ImplParse

%extra_argument { void *state }

%token_type {token*}
%default_type {token*}

/*----------------------------------------------------+
|                      PRECEDENCE                     |
+----------------------------------------------------*/


/*----------------------------------------------------+
|                      TYPES                          |
+----------------------------------------------------*/


%syntax_error {
    printf("syntax error\n");
}

/*----------------------------------------------------+
|                      GRAMMAR                        |
+----------------------------------------------------*/

package ::= package_opt  END .

package_opt ::= /* empty */ .
package_opt ::= package_opt function_def .
package_opt ::= package_opt var_inst .
package_opt ::= package_opt var_decl .
package_opt ::= package_opt struct_def .

/*----------------------------------------------------+
|                       STRUCT                        |
+----------------------------------------------------*/

struct_def ::= struct_def_opt R_C_BRACKET .
struct_def_opt ::= ID L_C_BRACKET var_decl .
struct_def_opt ::= struct_def_opt var_decl .

/*----------------------------------------------------+
|                       FUNCTION                      |
+----------------------------------------------------*/

function_def ::= function_def_opt block_statement .
function_def ::= ID function_type block_statement .

function_def_opt ::= ID function_type PIPE var_decl .
function_def_opt ::= ID function_type PIPE var_inst .
function_def_opt ::= function_def_opt COMMA var_decl .
function_def_opt ::= function_def_opt COMMA var_inst .

/*----------------------------------------------------+
|                       VAR                           |
+----------------------------------------------------*/

/* -------------------- VAR --------------------------- */

var_decl ::= ID COLON type .

var_inst ::= var_decl compound_literal .

/*----------------------------------------------------+
|                       TYPES                         |
+----------------------------------------------------*/

/* -------------------- FUNCTION_TYPE ----------------- */

function_type ::= function_param ARROW type .
function_type ::= function_param .

function_param ::= function_param_opt R_R_BRACKET .
function_param ::= function_param_opt COMMA TRIPLE_DOT R_R_BRACKET .
function_param ::= L_R_BRACKET R_R_BRACKET .
function_param ::= L_R_BRACKET VOID R_R_BRACKET .

function_param_opt ::= L_R_BRACKET var_decl .
function_param_opt ::= function_param_opt COMMA var_decl .

/* -------------------- TYPE -------------------------- */

type ::= type ASTERIX . [POINTER_TYPE]
type ::= type_qualifier type . [POINTER_TYPE]
type ::= L_S_BRACKET type COMMA INTEGER R_S_BRACKET .
type ::= U8 .
type ::= U16 .
type ::= U32 .
type ::= U64 .
type ::= I8 .
type ::= I16 .
type ::= I32 .
type ::= I64 .
type ::= F32 .
type ::= F64 .
type ::= VOID .
type ::= function_type .
type ::= struct_def .

/*----------------------------------------------------+
|                       STATEMENT                     |
+----------------------------------------------------*/

block_statement ::= block_statement_opt R_C_BRACKET .

block_statement_opt ::= L_C_BRACKET .
block_statement_opt ::= block_statement_opt statement .

statement ::= SEMICOLON .
statement ::= var_decl .
statement ::= var_inst .

/*----------------------------------------------------+
|                       EXPRESSION                    |
+----------------------------------------------------*/

/* -------------------- COMPOUND_LITERAL -------------- */

compound_literal ::= compound_literal_opt R_C_BRACKET .

compound_literal_opt ::= L_C_BRACKET expression .
compound_literal_opt ::= DOT ID expression .
compound_literal_opt ::= L_S_BRACKET INTEGER R_S_BRACKET expression .
compound_literal_opt ::= compound_literal_opt COMMA expression .
compound_literal_opt ::= compound_literal_opt COMMA DOT ID expression .
compound_literal_opt ::= compound_literal_opt COMMA L_S_BRACKET INTEGER R_S_BRACKET expression .

/* -------------------- EXPRESSION_PREC --------------- */

expression ::= conditional_expresion . [EXP]
expression ::= STRING .

primary_expression ::= ID .

postfix_expression ::= primary_expression . [EXP]
postfix_expression ::= postfix_expression L_S_BRACKET INTEGER R_S_BRACKET .
postfix_expression ::= postfix_expression DOT ID .
postfix_expression ::= postfix_expression ARROW ID .

unary_expression ::= postfix_expression . [EXP]
unary_expression ::= ID .
unary_expression ::= unary_operator cast_expression .
unary_expression ::= SIZEOF L_R_BRACKET type R_R_BRACKET .

unary_operator ::= AMPERSAND .
unary_operator ::= ASTERIX .
unary_operator ::= PLUS .
unary_operator ::= MINUS .
unary_operator ::= TILDE .
unary_operator ::= EXCLAMATIONMARK .

cast_expression ::= unary_expression . [EXP]
cast_expression ::= INTERGER .
cast_expression ::= FLOAT .
cast_expression ::= L_R_BRACKET type R_R_BRACKET cast_expression .

multiplicative_expression ::= cast_expression . [EXP]
multiplicative_expression ::= multiplicative_expression ASTERIX cast_expression .
multiplicative_expression ::= multiplicative_expression SLASH cast_expression .
multiplicative_expression ::= multiplicative_expression PERCENT cast_expression .

additive_expression ::= multiplicative_expression . [EXP]
additive_expression ::= additive_expression PLUS multiplicative_expression .
additive_expression ::= additive_expression MINUS multiplicative_expression .

shift_expression ::= additive_expression . [EXP]
shift_expression ::= shift_expression DOUBLE_LESS_THAN additive_expression .
shift_expression ::= shift_expression DOUBLE_GREATER_THAN additive_expression .

relational_expression ::= shift_expression . [EXP]
relational_expression ::= relational_expression LESS_THAN shift_expression .
relational_expression ::= relational_expression GREATER_THAN shift_expression .
relational_expression ::= relational_expression LESS_EQUALS shift_expression .
relational_expression ::= relational_expression GREATER_EQUALS shift_expression .

equality_expression ::= relational_expression . [EXP]
equality_expression ::= equality_expression DOUBLE_EQUALS relational_expression .
equality_expression ::= equality_expression EXCLAMATIONMARK_EQUALS relational_expression .

and_expression ::= equality_expression . [EXP]
and_expression ::= and_expression AMPERSAND equality_expression .

exclusive_or_expression ::= and_expression . [EXP]
exclusive_or_expression ::= exclusive_or_expression CIRCUMFLEX and_expression .

inclusive_or_expression ::= exclusive_or_expression . [EXP]
inclusive_or_expression ::= inclusive_or_expression PIPE exclusive_or_expression .

logical_and_expression ::= inclusive_or_expression . [EXP]
logical_and_expression ::= logical_and_expression DOUBLE_AMPERSAND inclusive_or_expression .

logical_or_expression ::= logical_and_expression . [EXP]
logical_or_expression ::= logical_or_expression DOUBLE_PIPE logical_and_expression .

conditional_expression ::= logical_or_expression . [EXP]
conditional_expression ::= logical_or_expression QUESTIONMARK expression COLON conditional_expression .
