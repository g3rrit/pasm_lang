%include {
#include "exp.h"
#include "token_types.h"
#include "cassert"
#include "lexer.h"
#include "util.h"
#include "literal.h"
#include "operand.h"
#include "statement.h"
#include "var_def.h"
#include "var_decl.h"

using namespace tree;
}

%name ImplParse

%extra_argument { void *state }

%token_type {token*}
%default_type {token*}

/*----------------------------------------------------+
|                      PRECEDENCE                     |
+----------------------------------------------------*/


%right              T_WHITESPACE T_END T_OTHER T_TAB T_NEW_LINE T_CARRIAGE_RETURN T_CHAR T_MULTICHAR T_LINE_COMMENT
                    T_MULTILINE_COMMENT T_INTEGER T_FLOAT T_STRING T_USE T_AS T_RET
                    T_U8 T_U16 T_U32 T_U64 T_I8 T_I16 T_I32 T_I64 T_F32 T_F64
                    T_EXCALAMATIONMARK_EQUALS
                    T_COLON T_SEMICOLON
                    T_EXCLAMATIONMARK T_QUESTIONMARK .

%left               T_EXP .

%right              T_COMMA
                    T_PIPE
                    T_CIRCUMFLEX
                    T_DOUBLE_LESS_THAN
                    T_DOUBLE_GREATER_THAN
                    T_SLASH
                    T_PERCENT
                    T_MINUS
                    T_PLUS
                    T_EXCLAMATION_MARK
                    T_TILDE
                    T_ASTERIX
                    T_AMPERSAND
                    T_L_C_BRACKET
                    T_R_C_BRACKET
                    T_L_S_BRACKET
                    T_R_S_BRACKET
                    T_L_R_BRACKET
                    T_R_R_BRACKET
                    T_DOT
                    T_ARROW
                    T_DOUBLE_COLON .

%left               T_POINTER_TYPE .

%right              T_VOID .

%right              T_ID .


/*----------------------------------------------------+
|                      TYPES                          |
+----------------------------------------------------*/

%type id                            {id_token*}
%type integer                       {int_token*}
%type float                         {float_token*}
%type string                        {string_token*}

%type var_decl                      {var_decl*}
%type var_def                       {var_def*}


%type type                          {type*}

%type block_statement               {block_statement*}
%type block_statement_opt           {block_statement*}
%type statement                     {statement*}
%type u_mnemonic                    {mnemonic}
%type d_mnemonic                    {mnemonic}

%type operand                       {operand*}
%type literal                       {literal*}
%type literal_opt                   {literal*}

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

package ::= package_opt T_END . {
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

struct_def ::= struct_def_opt T_R_C_BRACKET . {
    log_debug("struct_def ::= struct_def_opt R_C_BRACKET");
}
struct_def_opt ::= id T_L_C_BRACKET var_decl . {
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

var_decl ::= id T_COLON type . {
    log_debug("var_decl ::= id COLON type");
}

var_def ::= var_decl literal . {
    log_debug("var_def ::= var_decl literal");
}

/*----------------------------------------------------+
|                       TYPES                         |
+----------------------------------------------------*/

/* -------------------- FUNCTION_TYPE ----------------- */

function_type ::= function_type_opt T_R_R_BRACKET . {
    log_debug("function_type ::= function_type_opt R_R_BRACKET");
}
function_type ::= T_L_R_BRACKET T_R_R_BRACKET . {
    log_debug("function_type ::= L_R_BRACKET R_R_BRACKET");
}

function_type_opt ::= T_L_R_BRACKET var_decl . {
    log_debug("function_type_opt ::= L_R_BRACKET var_decl");
}
function_type_opt ::= function_type_opt T_COMMA var_decl . {
    log_debug("function_type_opt ::= function_type_opt COMMA var_decl");
}

/* -------------------- TYPE -------------------------- */

type ::= type T_ASTERIX . [T_POINTER_TYPE] {
    log_debug("type ::= type ASTERIX . [POINTER_TYP");
}
type ::= T_L_S_BRACKET type T_COMMA integer T_R_S_BRACKET . {
    log_debug("type ::= L_S_BRACKET type COMMA integer R_S_BRACKET");
}
type ::= T_U8 . {
    log_debug("type ::= U8");
}
type ::= T_U16 . {
    log_debug("type ::= U16");
}
type ::= T_U32 . {
    log_debug("type ::= U32");
}
type ::= T_U64 . {
    log_debug("type ::= U64");
}
type ::= T_I8 . {
    log_debug("type ::= I8");
}
type ::= T_I16 . {
    log_debug("type ::= I16");
}
type ::= T_I32 . {
    log_debug("type ::= I32");
}
type ::= T_I64 . {
    log_debug("type ::= I64");
}
type ::= T_F32 . {
    log_debug("type ::= F32");
}
type ::= T_F64 . {
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

block_statement(A) ::= block_statement_opt(B) T_R_C_BRACKET . {
    log_debug("block_statement ::= block_statement_opt R_C_BRACKET");
    A = B;
}

block_statement_opt(A) ::= T_L_C_BRACKET . {
    log_debug("block_statement_opt ::= L_C_BRACKET");
    A = new block_statement();
}
block_statement_opt(A) ::= block_statement_opt(B) statement(C) . {
    log_debug("block_statement_opt ::= block_statement_opt statement");
    if(C != nullptr) {
      B->push_back(C);
    }
    A = B;
}

statement(A) ::= T_SEMICOLON . {
    log_debug("statement ::= SEMICOLON");
    A = nullptr;
}
statement(A) ::= var_decl(B) . {
    log_debug("statement ::= var_decl");
    A = new var_def_statement(new var_def(B, 0));
}
statement(A) ::= var_def(B) . {
    log_debug("statement ::= var_def");
    A = new var_def_statement(B);
}
statement(A) ::= u_mnemonic(B) operand(C) . {
    log_debug("statement ::= u_mnemonic operand");
    A = new u_mnemonic_statement(B, C);
}
statement(A) ::= d_mnemonic(B) operand(C) T_COMMA operand(D) . {
    log_debug("statement ::= d_mnemonic operand COMMA operand");
    A = new d_mnemonic_statement(B, C, D);
}

u_mnemonic(A) ::= T_PUSH . {
    log_debug("u_mnemonic ::= PUSH");
    A = mnemonic::PUSH;
}

d_mnemonic(A) ::= T_MOV . {
    log_debug("d_mnemonic ::= MOV");
    A = mnemonic::MOV;
}
d_mnemonic(A) ::= T_ADD . {
    log_debug("d_mnemonic ::= ADD");
    A = mnemonic::ADD;
}


/*----------------------------------------------------+
|                       EXPRESSION                    |
+----------------------------------------------------*/

/* -------------------- PRIMATIVES -------------------- */

id(A) ::= T_ID(B) . {
    log_debug("id ::= ID");
    A = static_cast<id_token*>(*B);
}
string(A) ::= T_STRING(B) . {
    log_debug("string ::= STRING");
    A = static_cast<string_token*>(*B);
}
float(A) ::= T_FLOAT(B) . {
    log_debug("float ::= FLOAT");
    A = static_cast<float_token*>(*B);
}
integer(A) ::= T_INTEGER(B) . {
    log_debug("integer ::= INTEGER");
    A = static_cast<int_token*>(*B);
}

/* -------------------- OPERAND ----------------------- */

operand(A) ::= ref_exp(B) . [EXP] {
    log_debug("operand ::= ref_exp");
    A = new ref_operand(B);
}
operand(A) ::= float(B) . {
    log_debug("operand ::= float");
    A = new float_operand(B);
}
operand(A) ::= scalar_exp(B) . {
    log_debug("operand ::= scalar_exp");
    A = new scalar_operand(B);
}
operand(A) ::= T_L_S_BRACKET scalar_exp(B) T_R_S_BRACKET . {
    log_debug("operand ::= L_S_BRACKET scalar_exp R_S_BRACKET");
    A = new acc_operand(B);
}

/* -------------------- COMPOUND_LITERAL -------------- */

literal(A) ::= literal_opt(B) T_R_C_BRACKET . {
    log_debug("literal ::= literal_opt R_C_BRACKET");
    A = B;
}

literal_opt(A) ::= T_L_C_BRACKET exp(B) . {
    log_debug("literal_opt ::= L_C_BRACKET exp");
    A = new literal();
    A->push_back(B);
}
literal_opt(A) ::= literal_opt(B) T_COMMA exp(C) . {
    log_debug("literal_opt ::= literal_opt COMMA exp");
    B->push_back(C);
    A = B;
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

ref_exp(A) ::= id(B) . [T_EXP] {
    log_debug("ref_exp ::= id");
    A = new id_exp(B);
}
ref_exp(A) ::= T_LESS_THAN type(B) T_GREATER_THAN T_L_R_BRACKET ref_exp(C) T_R_R_BRACKET . {
    log_debug("ref_exp ::= CAST LESS_THAN type GREATER_THAN L_R_BRACKET ref_exp R_R_BRACKET");
    A = new cast_exp(C, B);
}
ref_exp(A) ::= ref_exp(B) T_L_S_BRACKET scalar_exp(C) T_R_S_BRACKET . {
    log_debug("ref_exp ::= ref_exp L_S_BRACKET scalar_exp R_S_BRACKET");
    A = new acc_exp(B, C);
}
ref_exp(A) ::= ref_exp(B) T_DOT id(C) . {
    log_debug("ref_exp ::= ref_exp DOT id");
    A = new ref_acc_exp(B, C, ref_acc_exp::REF_OP::DOT);
}
ref_exp(A) ::= ref_exp(B) T_ARROW id(C) . {
    log_debug("ref_exp ::= ref_exp ARROW id");
    A = new ref_acc_exp(B, C, ref_acc_exp::REF_OP::ARROW);
}
ref_exp(A) ::= ref_exp(B) T_PLUS scalar_exp(C) . {
    log_debug("ref_exp ::= ref_exp PLUS scalar_exp");
    A = new ref_off_exp(B, C, ref_off_exp::REF_OP::PLUS);
}
ref_exp(A) ::= ref_exp(B) T_MINUS scalar_exp(C) . {
    log_debug("ref_exp ::= ref_exp MINUS scalar_exp");
    A = new ref_off_exp(B, C, ref_off_exp::REF_OP::MINUS);
}

/* -------------------- SCALAR_EXP -------------------- */

scalar_exp_int(A) ::= integer(B) . {
    log_debug("scalar_exp_int ::= integer");
    A = new int_exp(B);
}

multiplicative_exp(A) ::= scalar_exp_int(B) T_ASTERIX scalar_exp(C) . {
    log_debug("multiplicative_exp ::= scalar_exp_int ASTERIX scalar_ex");
    A = new infix_scalar_exp(B, C, infix_scalar_exp::INFIX_OP::TIMES);
}
multiplicative_exp(A) ::= scalar_exp_int(B) T_SLASH scalar_exp(C) . {
    log_debug("multiplicative_exp ::= scalar_exp_int SLASH scalar_exp");
    A =new infix_scalar_exp(B, C, infix_scalar_exp::INFIX_OP::DIV);
}
multiplicative_exp(A) ::= scalar_exp_int(B) T_PERCENT scalar_exp(C) . {
    log_debug("multiplicative_exp ::= scalar_exp_int PERCENT scalar_exp");
    A = new infix_scalar_exp(B, C, infix_scalar_exp::INFIX_OP::MOD);
}

multiplicative_exp(A) ::= multiplicative_exp(B) T_ASTERIX scalar_exp(C) . {
    log_debug("multiplicative_exp ::= multiplicative_exp ASTERIX scalar_ex");
    A = new infix_scalar_exp(B, C, infix_scalar_exp::INFIX_OP::TIMES);
}
multiplicative_exp(A) ::= multiplicative_exp(B) T_SLASH scalar_exp(C) . {
    log_debug("multiplicative_exp ::= multiplicative_exp SLASH scalar_exp");
    A =new infix_scalar_exp(B, C, infix_scalar_exp::INFIX_OP::DIV);
}
multiplicative_exp(A) ::= multiplicative_exp(B) T_PERCENT scalar_exp(C) . {
    log_debug("multiplicative_exp ::= multiplicative_exp PERCENT scalar_exp");
    A = new infix_scalar_exp(B, C, infix_scalar_exp::INFIX_OP::MOD);
}

additive_exp(A) ::= multiplicative_exp(B) . [T_EXP] {
    log_debug("additive_exp ::= multiplicative_exp");
    A = B;
}
additive_exp(A) ::= additive_exp(B) T_PLUS multiplicative_exp(C) . {
    log_debug("additive_exp ::= additive_exp PLUS multiplicative_exp");
    A = new infix_scalar_exp(B, C, infix_scalar_exp::INFIX_OP::PLUS);
}
additive_exp(A) ::= additive_exp(B) T_MINUS multiplicative_exp(C) . {
    log_debug("additive_exp ::= additive_exp MINUS multiplicative_exp");
    A = new infix_scalar_exp(B, C, infix_scalar_exp::INFIX_OP::MINUS);
}

shift_exp(A) ::= additive_exp(B) . [T_EXP] {
    log_debug("shift_exp ::= additive_exp");
    A = B;
}
shift_exp(A) ::= shift_exp(B) T_DOUBLE_LESS_THAN additive_exp(C) . {
    log_debug("shift_exp ::= shift_exp DOUBLE_LESS_THAN additive_exp");
    A = new infix_scalar_exp(B, C, infix_scalar_exp::INFIX_OP::SHIFT_LEFT);
}
shift_exp(A) ::= shift_exp(B) T_DOUBLE_GREATER_THAN additive_exp(C) . {
    log_debug("shift_exp ::= shift_exp DOUBLE_GREATER_THAN additive_exp");
    A = new infix_scalar_exp(B, C, infix_scalar_exp::INFIX_OP::SHIFT_RIGHT);
}

and_exp(A) ::= shift_exp(B) . [T_EXP] {
    log_debug("and_exp ::= shift_exp");
    A = B;
}
and_exp(A) ::= and_exp(B) T_AMPERSAND shift_exp(C) . {
    log_debug("and_exp ::= and_exp T_AMPERSAND shift_exp");
    A = new infix_scalar_exp(B, C, infix_scalar_exp::INFIX_OP::AND);
}

exclusive_or_exp(A) ::= and_exp(B) . [T_EXP] {
    log_debug("exclusive_or_exp ::= and_exp");
    A = B;
}
exclusive_or_exp(A) ::= exclusive_or_exp(B) T_CIRCUMFLEX and_exp(C) . {
    log_debug("exclusive_or_exp ::= exclusive_or_exp CIRCUMFLEX and_exp");
    A = new infix_scalar_exp(B, C, infix_scalar_exp::INFIX_OP::NOR);
}

inclusive_or_exp(A) ::= exclusive_or_exp(B) . [T_EXP] {
    log_debug("inclusive_or_exp ::= exclusive_or_exp");
    A = B;
}
inclusive_or_exp(A) ::= inclusive_or_exp(B) T_PIPE exclusive_or_exp(C) . {
    log_debug("inclusive_or_exp ::= inclusive_or_exp PIPE exclusive_or_exp");
    A = new infix_scalar_exp(B, C, infix_scalar_exp::INFIX_OP::OR);
}

scalar_exp(A) ::= inclusive_or_exp(B) . [T_EXP] {
    log_debug("scalar_exp ::= inclusive_or_exp");
    A = B;
}
