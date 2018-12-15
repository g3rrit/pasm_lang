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
#include "function_type.h"
#include "function.h"
#include "type_def.h"
#include "package.h"
#include "parser.h"
#include "program.h"


using namespace tree;
}

%name FParse

%extra_argument { prog::prog_state *state }

%token_type {token*}
%default_type {token*}

/*----------------------------------------------------+
|                      PRECEDENCE                     |
+----------------------------------------------------*/


%right              T_WHITESPACE T_END T_OTHER T_TAB T_NEW_LINE T_CARRIAGE_RETURN T_CHAR T_MULTICHAR T_LINE_COMMENT
                    T_MULTILINE_COMMENT T_INTEGER T_FLOAT T_STRING T_USE T_AS T_RET
                    T_U8 T_U16 T_U32 T_U64 T_I8 T_I16 T_I32 T_I64 T_F32 T_F64
                    T_EXCALAMATIONMARK_EQUALS T_PACKAGE
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

%type package                       {package*}
%type package_opt                   {package*}

%type package_decl                  {id_token_vec*}

%type id                            {id_token*}
%type id_vec                        {id_token_vec*}
%type integer                       {int_token*}
%type float                         {float_token*}
%type string                        {string_token*}

%type struct_def                    {type_def*}
%type struct_def_opt                {type_def*}

%type var_decl                      {var_decl*}
%type var_def                       {var_def*}

%type function_def                  {function*}
%type function_def_opt              {function*}
%type function_def_opt_v            {function*}

%type function_type                 {function_type*}
%type function_type_opt             {function_type*}

%type type                          {type*}

%type statement                     {statement*}
%type mnemonic                      {mnemonic}

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

%destructor package {
(void)state;
}

%syntax_error {
printf("syntax error\n");
}

/*----------------------------------------------------+
|                      GRAMMAR                        |
+----------------------------------------------------*/

package(A) ::= package_opt(B) T_END . {
log_debug("package ::= package_opt  END");
(void)state;
A = B;
}

package_opt(A) ::= package_decl(B) . {
log_debug("package_opt ::= package_decl");
A = new package(B);
}
package_opt(A) ::= package_opt(B) function_def(C) . {
log_debug("package_opt ::= package_opt function_def");
B->add_function(C);
A = B;
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

package_decl(A) ::= T_PACKAGE id_vec(B) . {
log_debug("package_decl ::= T_PACKAGE id");
A = B;
}

package_decl(A) ::= T_PACKAGE id(B) . {
log_debug("package_decl ::= T_PACKAGE id");
A = new id_token_vec();
A->push_back(B);
}


/*----------------------------------------------------+
|                       STRUCT                        |
+----------------------------------------------------*/

struct_def(A) ::= struct_def_opt(B) T_R_C_BRACKET . {
log_debug("struct_def ::= struct_def_opt R_C_BRACKET");
A = B;
}
struct_def_opt(A) ::= id(B) T_L_C_BRACKET var_decl(C) . {
log_debug("struct_def_opt ::= id L_C_BRACKET var_decl");
A = new type_def(B);
A->add_elem(C);
}
struct_def_opt(A) ::= struct_def_opt(B) var_decl(C) . {
log_debug("struct_def_opt ::= struct_def_opt var_decl");
B->add_elem(C);
A = B;
}

/*----------------------------------------------------+
|                       FUNCTION                      |
+----------------------------------------------------*/

function_def(A) ::= function_def_opt(B) T_R_C_BRACKET . {
log_debug("function_def ::= function_def_opt T_R_C_BRACKET");
A = B;
}

function_def_opt(A) ::= function_def_opt_v(B) statement(C) . {
log_debug("function_def_opt ::= function_def_opt_v statement");
B->add_stm(C);
A = B;
}

function_def_opt(A) ::= function_def_opt(B) statement(C) . {
log_debug("function_def_opt ::= function_def_opt_v statement");
B->add_stm(C);
A = B;
}

function_def_opt_v(A) ::= id(B) function_type(C) T_L_C_BRACKET . {
log_debug("function_def_opt_v ::= id function_type L_C_BRACKET");
A = new function(B, C);
}

function_def_opt_v(A) ::= function_def_opt_v(B) var_def(C) . {
log_debug("function_def_opt_v ::= function_def_opt_v var_def");
B->add_def(C);
A = B;
}

function_def_opt_v(A) ::= function_def_opt_v(B) var_decl(C) . {
log_debug("function_def_opt_v ::= function_def_opt_v var_decl");
B->add_def(new var_def(C, nullptr));
A = B;
}

/*----------------------------------------------------+
|                       VAR                           |
+----------------------------------------------------*/

/* -------------------- VAR --------------------------- */

var_decl(A) ::= id(B) T_COLON type(C) . {
log_debug("var_decl ::= id COLON type");
A = new var_decl(B, C);
}

var_def(A) ::= var_decl(B) literal(C) . {
log_debug("var_def ::= var_decl literal");
A = new var_def(B, C);
}

/*----------------------------------------------------+
|                       TYPES                         |
+----------------------------------------------------*/

/* -------------------- FUNCTION_TYPE ----------------- */

function_type(A) ::= function_type_opt(B) T_R_R_BRACKET . {
log_debug("function_type ::= function_type_opt R_R_BRACKET");
A = B;
}
function_type(A) ::= T_L_R_BRACKET T_R_R_BRACKET . {
log_debug("function_type ::= L_R_BRACKET R_R_BRACKET");
A = new function_type();
}

function_type_opt(A) ::= T_L_R_BRACKET var_decl(C) . {
log_debug("function_type_opt ::= L_R_BRACKET var_decl");
A = new function_type();
A->add_param(C);
}
function_type_opt(A) ::= function_type_opt(B) T_COMMA var_decl(C) . {
log_debug("function_type_opt ::= function_type_opt COMMA var_decl");
B->add_param(C);
A = B;
}

/* -------------------- TYPE -------------------------- */

type(A) ::= type(B) T_ASTERIX . [T_POINTER_TYPE] {
log_debug("type ::= type ASTERIX . [POINTER_TYP");
A = new pointer_type(B);
}
type(A) ::= T_L_S_BRACKET type(B) T_COMMA integer(C) T_R_S_BRACKET . {
log_debug("type ::= L_S_BRACKET type COMMA integer R_S_BRACKET");
A = new array_type(B, C);
}
type(A) ::= T_U8 . {
log_debug("type ::= U8");
A = new primative_type(primative_type::p_type::U8);
}
type(A) ::= T_U16 . {
log_debug("type ::= U16");
A = new primative_type(primative_type::p_type::U16);
}
type(A) ::= T_U32 . {
log_debug("type ::= U32");
A = new primative_type(primative_type::p_type::U32);
}
type(A) ::= T_U64 . {
log_debug("type ::= U64");
A = new primative_type(primative_type::p_type::U64);
}
type(A) ::= T_I8 . {
log_debug("type ::= I8");
A = new primative_type(primative_type::p_type::I8);
}
type(A) ::= T_I16 . {
log_debug("type ::= I16");
A = new primative_type(primative_type::p_type::I16);
}
type(A) ::= T_I32 . {
log_debug("type ::= I32");
A = new primative_type(primative_type::p_type::I32);
}
type(A) ::= T_I64 . {
log_debug("type ::= I64");
A = new primative_type(primative_type::p_type::I64);
}
type(A) ::= T_F32 . {
log_debug("type ::= F32");
A = new primative_type(primative_type::p_type::F32);
}
type(A) ::= T_F64 . {
log_debug("type ::= F64");
A = new primative_type(primative_type::p_type::F64);
}
type(A) ::= function_type(B) . {
log_debug("type ::= function_type");
A = B;
}
type(A) ::= id(B) . {
log_debug("type ::= id");
id_token_vec *temp = new id_token_vec();
temp->push_back(B);
A = new unresolved_type(temp);
}
type(A) ::= id_vec(B) . {
log_debug("type ::= id_vec");
A = new unresolved_type(B);
}

/*----------------------------------------------------+
|                       STATEMENT                     |
+----------------------------------------------------*/

statement(A) ::= mnemonic(B) operand(C) . {
log_debug("statement ::= mnemonic operand");
A = new mnemonic_statement(B, C, nullptr);
}
statement(A) ::= mnemonic(B) operand(C) T_COMMA operand(D) . {
log_debug("statement ::= mnemonic operand COMMA operand");
A = new mnemonic_statement(B, C, D);
}

statement(A) ::= id(B) T_COLON . {
log_debug("statement ::= id T_COLON");
A = new label_statement(B);
}

mnemonic(A) ::= T_PUSH . {
log_debug("u_mnemonic ::= PUSH");
A = mnemonic::PUSH;
}
mnemonic(A) ::= T_MOV . {
log_debug("d_mnemonic ::= MOV");
A = mnemonic::MOV;
}
mnemonic(A) ::= T_ADD . {
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
id_vec(A) ::= id(B) T_DOUBLE_COLON . {
log_debug("id_vec ::= id DOUBLE_COLON");
A = new id_token_vec();
A->push_back(B);
}
id_vec(A) ::= id_vec(B) T_DOUBLE_COLON id(C) . {
log_debug("id_vec ::= id_vec T_DOUBLE_COLON id");
A = B;
B->push_back(C);
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

literal(A) ::= literal_opt(B) T_R_R_BRACKET . {
log_debug("literal ::= literal_opt R_R_BRACKET");
A = B;
}

literal_opt(A) ::= T_L_R_BRACKET exp(B) . {
log_debug("literal_opt ::= L_R_BRACKET exp");
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
ref_exp(A) ::= id_vec(B) . [T_EXP] {
log_debug("ref_exp ::= id_vec");
A = new id_vec_exp(B);
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
