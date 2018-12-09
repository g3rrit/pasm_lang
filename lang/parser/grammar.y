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
package_opt ::= package_opt var_def .
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

function_def ::= ID function_type block_statement .

/*----------------------------------------------------+
|                       VAR                           |
+----------------------------------------------------*/

/* -------------------- VAR --------------------------- */

var_decl ::= ID COLON type .

var_def ::= var_decl literal .

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
statement ::= var_def .
statement ::= u_mnemonic operand .
statement ::= d_mnemonic operand COMMA operand .

u_mnemonic ::= PUSH .

d_mnemonic ::= MOV .
d_mnemonic ::= ADD .


/*----------------------------------------------------+
|                       EXPRESSION                    |
+----------------------------------------------------*/

/* -------------------- OPERAND ----------------------- */

operand ::= ref_exp . [EXP]
operand ::= FLOAT .
operand ::= scalar_exp .
operand ::= L_S_BRACKET scalar_exp R_S_BRACKET .

/* -------------------- COMPOUND_LITERAL -------------- */

literal ::= literal_opt R_C_BRACKET .

literal_opt ::= L_C_BRACKET exp .
literal_opt ::= literal_opt COMMA exp .

/* -------------------- EXPRESSION -------------------- */

exp ::= scalar_exp .
exp ::= FLOAT .
exp ::= STRING .
exp ::= ref_exp .

/* -------------------- REF_EXP ----------------------- */

ref_exp ::= ID . [EXP]
ref_exp ::= CAST LESS_THAN type GREATER_THAN L_R_BRACKET ref_exp R_R_BRACKET .
ref_exp ::= ref_exp L_S_BRACKET scalar_exp R_S_BRACKET .
ref_exp ::= ref_exp DOT ID .
ref_exp ::= ref_exp ARROW ID .
ref_exp ::= ref_exp PLUS scalar_exp .
ref_exp ::= ref_exp MINUS scalar_exp .

/* -------------------- SCALAR_EXP -------------------- */

scalar_exp_int ::= INTEGER .

multiplicative_exp ::= scalar_exp_int . [EXP]
multiplicative_exp ::= multiplicative_exp ASTERIX scalar_exp.
multiplicative_exp ::= multiplicative_exp SLASH scalar_exp .
multiplicative_exp ::= multiplicative_exp PERCENT scalar_exp .

additive_exp ::= multiplicative_exp . [EXP]
additive_exp ::= additive_exp PLUS multiplicative_exp .
additive_exp ::= additive_exp MINUS multiplicative_exp .

shift_exp ::= additive_exp . [EXP]
shift_exp ::= shift_exp DOUBLE_LESS_THAN additive_exp .
shift_exp ::= shift_exp DOUBLE_GREATER_THAN additive_exp .

and_exp ::= shift_exp . [EXP]
and_exp ::= and_exp AMPERSAND shift_exp .

exclusive_or_exp ::= and_exp . [EXP]
exclusive_or_exp ::= exclusive_or_exp CIRCUMFLEX and_exp .

inclusive_or_exp ::= exclusive_or_exp . [EXP]
inclusive_or_exp ::= inclusive_or_exp PIPE exclusive_or_exp .

scalar_exp ::= inclusive_or_exp . [EXP]
