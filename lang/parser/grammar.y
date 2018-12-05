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


%right              WHITESPACE END OTHER TAB NEW_LINE CARRIAGE_RETURN CHAR MULTICHAR LINE_COMMENT
                    MULTILINE_COMMENT INTEGER FLOAT STRING USE AS RET
                    U8 U16 U32 U64 I8 I16 I32 I64 F32 F64
                    EXCALAMATIONMARK_EQUALS
                    COLON SEMICOLON
                    EXCLAMATIONMARK QUESTIONMARK .

%left               EXP .

%right              COMMA
                    PIPE
                    CIRCUMFLEX
                    DOUBLE_LESS_THAN
                    DOUBLE_GREATER_THAN
                    SLASH
                    PERCENT
                    MINUS
                    PLUS
                    EXCLAMATION_MARK
                    TILDE
                    ASTERIX
                    AMPERSAND
                    L_C_BRACKET
                    R_C_BRACKET
                    L_S_BRACKET
                    R_S_BRACKET
                    L_R_BRACKET
                    R_R_BRACKET
                    DOT
                    ARROW
                    DOUBLE_COLON .

%left               POINTER_TYPE .

%right              VOID .

%right              ID .


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

var_inst ::= var_decl literal .

/*----------------------------------------------------+
|                       TYPES                         |
+----------------------------------------------------*/

/* -------------------- FUNCTION_TYPE ----------------- */

function_type ::= function_type_opt R_R_BRACKET .
function_type ::= L_R_BRACKET R_R_BRACKET .

function_type_opt ::= L_R_BRACKET var_decl .
function_type_opt ::= function_type_opt COMMA var_decl .

/* -------------------- TYPE -------------------------- */

type ::= type ASTERIX . [POINTER_TYPE]
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
statement ::= u_mnemonic operand .
statement ::= d_mnemonic operand COMMA operand .

u_mnemonic ::= PUSH .

d_mnemonic ::= MOV .
d_mnemonic ::= ADD .


/*----------------------------------------------------+
|                       EXPRESSION                    |
+----------------------------------------------------*/

/* -------------------- COMPOUND_LITERAL -------------- */

literal ::= literal_opt R_C_BRACKET .

literal_opt ::= L_C_BRACKET INTEGER .
literal_opt ::= L_C_BRACKET FLOAT .
literal_opt ::= L_C_BRACKET STRING .
literal_opt ::= L_C_BRACKET ID .
literal_opt ::= literal_opt COMMA INTEGER .
literal_opt ::= literal_opt COMMA FLOAT .
literal_opt ::= literal_opt COMMA STRING .
literal_opt ::= literal_opt COMMA ID .

/* -------------------- OPERAND ----------------------- */

operand ::= postfix_operand . [EXP]
operand ::= STRING .
operand ::= FLOAT .
operand ::= scalar_operand .
operand ::= L_S_BRACKET scalar_operand R_S_BRACKET .

primary_operand ::= ID .
primary_operand ::= CAST LESS_THAN type GREATER_THAN L_R_BRACKET ID R_R_BRACKET .

postfix_operand ::= primary_operand . [EXP]
postfix_operand ::= postfix_operand L_S_BRACKET INTEGER R_S_BRACKET .
postfix_operand ::= postfix_operand DOT ID .
postfix_operand ::= postfix_operand ARROW ID .

/* -------------------- SCALAR_OPERAND ---------------- */

scalar_operand_int ::= INTEGER .

multiplicative_operand ::= scalar_operand_int . [EXP]
multiplicative_operand ::= multiplicative_operand ASTERIX scalar_operand.
multiplicative_operand ::= multiplicative_operand SLASH scalar_operand .
multiplicative_operand ::= multiplicative_operand PERCENT scalar_operand .

additive_operand ::= multiplicative_operand . [EXP]
additive_operand ::= additive_operand PLUS multiplicative_operand .
additive_operand ::= additive_operand MINUS multiplicative_operand .

shift_operand ::= additive_operand . [EXP]
shift_operand ::= shift_operand DOUBLE_LESS_THAN additive_operand .
shift_operand ::= shift_operand DOUBLE_GREATER_THAN additive_operand .

and_operand ::= shift_operand . [EXP]
and_operand ::= and_operand AMPERSAND shift_operand .

exclusive_or_operand ::= and_operand . [EXP]
exclusive_or_operand ::= exclusive_or_operand CIRCUMFLEX and_operand .

inclusive_or_operand ::= exclusive_or_operand . [EXP]
inclusive_or_operand ::= inclusive_or_operand PIPE exclusive_or_operand .

scalar_operand ::= inclusive_or_operand . [EXP]
