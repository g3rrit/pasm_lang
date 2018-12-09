%include {
#include "exp.h"
#include "token_types.h"
#include "cassert"
#include "lexer.h"
#include "util.h"

using namespace tree;
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

%type id                            {id_token*}
%type integer                       {int_token*}
%type float                         {float_token*}
%type string                        {string_token*}

%type exp                           {exp*}
%type ref_exp                       {ref_exp*}
%type scalar_exp_int                {scalar_exp*}
%type multiplicative_exp            {infix_scalar_exp*}
%type additive_exp                  {infix_scalar_exp*}
%type shift_exp                     {infix_scalar_exp*}
%type and_exp                       {infix_scalar_exp*}
%type exclusive_or_exp              {infix_scalar_exp*}
%type inclusive_or_exp              {infix_scalar_exp*}
%type scalar_exp                    {infix_scalar_exp*}


%syntax_error {
    printf("syntax error\n");
}

/*----------------------------------------------------+
|                      GRAMMAR                        |
+----------------------------------------------------*/

package ::= package_opt  END . {
    log_debug("package ::= package_opt  END");
}

package_opt ::= /* empty */ . {
    log_debug("package_opt ::= /* empty */");
}
package_opt ::= package_opt function_def . {
    log_debug("package_opt ::= package_opt function_def");
}
package_opt ::= package_opt var_def . {
    log_debug("package_opt ::= package_opt var_def");
}
package_opt ::= package_opt var_decl . {
    log_debug("package_opt ::= package_opt var_decl");
}
package_opt ::= package_opt struct_def . {
    log_debug("package_opt ::= package_opt struct_def");
}

/*----------------------------------------------------+
|                       STRUCT                        |
+----------------------------------------------------*/

struct_def ::= struct_def_opt R_C_BRACKET . {
    log_debug("struct_def ::= struct_def_opt R_C_BRACKET");
}
struct_def_opt ::= id L_C_BRACKET var_decl . {
    log_debug("struct_def_opt ::= id L_C_BRACKET var_decl");
}
struct_def_opt ::= struct_def_opt var_decl . {
    log_debug("struct_def_opt ::= struct_def_opt var_decl");
}

/*----------------------------------------------------+
|                       FUNCTION                      |
+----------------------------------------------------*/

function_def ::= id function_type block_statement . {
    log_debug("function_def ::= id function_type block_statement");
}

/*----------------------------------------------------+
|                       VAR                           |
+----------------------------------------------------*/

/* -------------------- VAR --------------------------- */

var_decl ::= id COLON type . {
    log_debug("var_decl ::= id COLON type");
}

var_def ::= var_decl literal . {
    log_debug("var_def ::= var_decl literal");
}

/*----------------------------------------------------+
|                       TYPES                         |
+----------------------------------------------------*/

/* -------------------- FUNCTION_TYPE ----------------- */

function_type ::= function_type_opt R_R_BRACKET . {
    log_debug("function_type ::= function_type_opt R_R_BRACKET");
}
function_type ::= L_R_BRACKET R_R_BRACKET . {
    log_debug("function_type ::= L_R_BRACKET R_R_BRACKET");
}

function_type_opt ::= L_R_BRACKET var_decl . {
    log_debug("function_type_opt ::= L_R_BRACKET var_decl");
}
function_type_opt ::= function_type_opt COMMA var_decl . {
    log_debug("function_type_opt ::= function_type_opt COMMA var_decl");
}

/* -------------------- TYPE -------------------------- */

type ::= type ASTERIX . [POINTER_TYPE] {
    log_debug("type ::= type ASTERIX . [POINTER_TYP");
}
type ::= L_S_BRACKET type COMMA integer R_S_BRACKET . {
    log_debug("type ::= L_S_BRACKET type COMMA integer R_S_BRACKET");
}
type ::= U8 . {
    log_debug("type ::= U8");
}
type ::= U16 . {
    log_debug("type ::= U16");
}
type ::= U32 . {
    log_debug("type ::= U32");
}
type ::= U64 . {
    log_debug("type ::= U64");
}
type ::= I8 . {
    log_debug("type ::= I8");
}
type ::= I16 . {
    log_debug("type ::= I16");
}
type ::= I32 . {
    log_debug("type ::= I32");
}
type ::= I64 . {
    log_debug("type ::= I64");
}
type ::= F32 . {
    log_debug("type ::= F32");
}
type ::= F64 . {
    log_debug("type ::= F64");
}
type ::= function_type . {
    log_debug("type ::= function_type");
}
type ::= struct_def . {
    log_debug("type ::= struct_def");
}

/*----------------------------------------------------+
|                       STATEMENT                     |
+----------------------------------------------------*/

block_statement ::= block_statement_opt R_C_BRACKET . {
    log_debug("block_statement ::= block_statement_opt R_C_BRACKET");
}

block_statement_opt ::= L_C_BRACKET . {
    log_debug("block_statement_opt ::= L_C_BRACKET");
}
block_statement_opt ::= block_statement_opt statement . {
    log_debug("block_statement_opt ::= block_statement_opt statement");
}

statement ::= SEMICOLON . {
    log_debug("statement ::= SEMICOLON");
}
statement ::= var_decl . {
    log_debug("statement ::= var_decl");
}
statement ::= var_def . {
    log_debug("statement ::= var_def");
}
statement ::= u_mnemonic operand . {
    log_debug("statement ::= u_mnemonic operand");
}
statement ::= d_mnemonic operand COMMA operand . {
    log_debug("statement ::= d_mnemonic operand COMMA operand");
}

u_mnemonic ::= PUSH . {
    log_debug("u_mnemonic ::= PUSH");
}

d_mnemonic ::= MOV . {
    log_debug("d_mnemonic ::= MOV");
}
d_mnemonic ::= ADD . {
    log_debug("d_mnemonic ::= ADD");
}


/*----------------------------------------------------+
|                       EXPRESSION                    |
+----------------------------------------------------*/

/* -------------------- PRIMATIVES -------------------- */

id(A) ::= ID(B) . {
    log_debug("id ::= ID");
    A = static_cast<id_token*>(*B);
}
string(A) ::= STRING(B) . {
    log_debug("string ::= STRING");
    A = static_cast<string_token*>(*B);
}
float(A) ::= FLOAT(B) . {
    log_debug("float ::= FLOAT");
    A = static_cast<float_token*>(*B);
}
integer(A) ::= INTEGER(B) . {
    log_debug("integer ::= INTEGER");
    A = static_cast<int_token*>(*B);
}

/* -------------------- OPERAND ----------------------- */

operand ::= ref_exp . [EXP] {
    log_debug("operand ::= ref_exp");
}
operand ::= float . {
    log_debug("operand ::= float");
}
operand ::= scalar_exp . {
    log_debug("operand ::= scalar_exp");
}
operand ::= L_S_BRACKET scalar_exp R_S_BRACKET . {
    log_debug("operand ::= L_S_BRACKET scalar_exp R_S_BRACKET");
}

/* -------------------- COMPOUND_LITERAL -------------- */

literal ::= literal_opt R_C_BRACKET . {
    log_debug("literal ::= literal_opt R_C_BRACKET");
}

literal_opt ::= L_C_BRACKET exp . {
    log_debug("literal_opt ::= L_C_BRACKET exp");
}
literal_opt ::= literal_opt COMMA exp . {
    log_debug("literal_opt ::= literal_opt COMMA exp");
}

/* -------------------- EXPRESSION -------------------- */

exp(A) ::= scalar_exp(B) . {
    log_debug("exp ::= scalar_exp");
    A = B;
}
exp(A) ::= float(B) . {
    log_debug("exp ::= float");
    A = new float_exp(B);
}
exp(A) ::= string(B) . {
    log_debug("exp ::= string");
    A = new string_exp(B);
}
exp(A) ::= ref_exp(B) . {
    log_debug("exp ::= ref_exp");
    A = B;
}

/* -------------------- REF_EXP ----------------------- */

ref_exp(A) ::= id(B) . [EXP] {
    log_debug("ref_exp ::= id");
    A = new id_exp(B);
}
ref_exp(A) ::= LESS_THAN type(B) GREATER_THAN L_R_BRACKET ref_exp(C) R_R_BRACKET . {
    log_debug("ref_exp ::= CAST LESS_THAN type GREATER_THAN L_R_BRACKET ref_exp R_R_BRACKET");
    A = new cast_exp(C, B);
}
ref_exp(A) ::= ref_exp(B) L_S_BRACKET scalar_exp(C) R_S_BRACKET . {
    log_debug("ref_exp ::= ref_exp L_S_BRACKET scalar_exp R_S_BRACKET");
    A = new acc_exp(B, C);
}
ref_exp(A) ::= ref_exp(B) DOT id(C) . {
    log_debug("ref_exp ::= ref_exp DOT id");
    A = new ref_acc_exp(B, C, ref_acc_exp::REF_OP::DOT);
}
ref_exp(A) ::= ref_exp(B) ARROW id(C) . {
    log_debug("ref_exp ::= ref_exp ARROW id");
    A = new ref_acc_exp(B, C, ref_acc_exp::REF_OP::ARROW);
}
ref_exp(A) ::= ref_exp(B) PLUS scalar_exp(C) . {
    log_debug("ref_exp ::= ref_exp PLUS scalar_exp");
    A = new ref_off_exp(B, C, ref_off_exp::REF_OP::PLUS);
}
ref_exp(A) ::= ref_exp(B) MINUS scalar_exp(C) . {
    log_debug("ref_exp ::= ref_exp MINUS scalar_exp");
    A = new ref_off_exp(B, C, ref_off_exp::REF_OP::MINUS);
}

/* -------------------- SCALAR_EXP -------------------- */

scalar_exp_int(A) ::= integer(B) . {
    log_debug("scalar_exp_int ::= integer");
    A = new int_exp(B);
}

multiplicative_exp(A) ::= scalar_exp_int(B) . [EXP] {
    log_debug("multiplicative_exp ::= scalar_exp_int");
    A = B;
}
multiplicative_exp(A) ::= multiplicative_exp(B) ASTERIX scalar_exp(C) . {
    log_debug("multiplicative_exp ::= multiplicative_exp ASTERIX scalar_ex");
    A = new infix_scalar_exp(B, C, infix_scalar_exp::INFIX_OP::TIMES);
}
multiplicative_exp(A) ::= multiplicative_exp(B) SLASH scalar_exp(C) . {
    log_debug("multiplicative_exp ::= multiplicative_exp SLASH scalar_exp");
    A =new infix_scalar_exp(B, C, infix_scalar_exp::INFIX_OP::DIV);
}
multiplicative_exp(A) ::= multiplicative_exp(B) PERCENT scalar_exp(C) . {
    log_debug("multiplicative_exp ::= multiplicative_exp PERCENT scalar_exp");
    A = new infix_scalar_exp(B, C, infix_scalar_exp::INFIX_OP::MOD);
}

additive_exp(A) ::= multiplicative_exp(B) . [EXP] {
    log_debug("additive_exp ::= multiplicative_exp");
    A = B;
}
additive_exp(A) ::= additive_exp(B) PLUS multiplicative_exp(C) . {
    log_debug("additive_exp ::= additive_exp PLUS multiplicative_exp");
    A = new infix_scalar_exp(B, C, infix_scalar_exp::INFIX_OP::PLUS);
}
additive_exp(A) ::= additive_exp(B) MINUS multiplicative_exp(C) . {
    log_debug("additive_exp ::= additive_exp MINUS multiplicative_exp");
    A = new infix_scalar_exp(B, C, infix_scalar_exp::INFIX_OP::MINUS);
}

shift_exp(A) ::= additive_exp(B) . [EXP] {
    log_debug("shift_exp ::= additive_exp");
    A = B;
}
shift_exp(A) ::= shift_exp(B) DOUBLE_LESS_THAN additive_exp(C) . {
    log_debug("shift_exp ::= shift_exp DOUBLE_LESS_THAN additive_exp");
    A = new infix_scalar_exp(B, C, infix_scalar_exp::INFIX_OP::SHIFT_LEFT);
}
shift_exp(A) ::= shift_exp(B) DOUBLE_GREATER_THAN additive_exp(C) . {
    log_debug("shift_exp ::= shift_exp DOUBLE_GREATER_THAN additive_exp");
    A = new infix_scalar_exp(B, C, infix_scalar_exp::INFIX_OP::SHIFT_RIGHT);
}

and_exp(A) ::= shift_exp(B) . [EXP] {
    log_debug("and_exp ::= shift_exp");
    A = B;
}
and_exp(A) ::= and_exp(B) AMPERSAND shift_exp(C) . {
    log_debug("and_exp ::= and_exp AMPERSAND shift_exp");
    A = new infix_scalar_exp(B, C, infix_scalar_exp::INFIX_OP::AND);
}

exclusive_or_exp(A) ::= and_exp(B) . [EXP] {
    log_debug("exclusive_or_exp ::= and_exp");
    A = B;
}
exclusive_or_exp(A) ::= exclusive_or_exp(B) CIRCUMFLEX and_exp(C) . {
    log_debug("exclusive_or_exp ::= exclusive_or_exp CIRCUMFLEX and_exp");
    A = new infix_scalar_exp(B, C, infix_scalar_exp::INFIX_OP::NOR);
}

inclusive_or_exp(A) ::= exclusive_or_exp(B) . [EXP] {
    log_debug("inclusive_or_exp ::= exclusive_or_exp");
    A = B;
}
inclusive_or_exp(A) ::= inclusive_or_exp(B) PIPE exclusive_or_exp(C) . {
    log_debug("inclusive_or_exp ::= inclusive_or_exp PIPE exclusive_or_exp");
    A = new infix_scalar_exp(B, C, infix_scalar_exp::INFIX_OP::OR);
}

scalar_exp(A) ::= inclusive_or_exp(B) . [EXP] {
    log_debug("scalar_exp ::= inclusive_or_exp");
    A = B;
}
