/*
** 2000-05-29
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** Driver template for the LEMON parser generator.
**
** The "lemon" program processes an LALR(1) input grammar file, then uses
** this template to construct a parser.  The "lemon" program inserts text
** at each "%%" line.  Also, any "P-a-r-s-e" identifer prefix (without the
** interstitial "-" characters) contained in this template is changed into
** the value of the %name directive from the grammar.  Otherwise, the content
** of this template is copied straight through into the generate parser
** source file.
**
** The following is the concatenation of all %include directives from the
** input grammar file:
*/
#include <stdio.h>
/************ Begin %include sections from the grammar ************************/
#line 1 "./parser/grammar.y"

#include "token_types.h"
#include "cassert"
#include "lexer.h"
#line 33 "./parser/out/grammar.c"
/**************** End of %include directives **********************************/
/* These constants specify the various numeric values for terminal symbols
** in a format understandable to "makeheaders".  This section is blank unless
** "lemon" is run with the "-m" command-line option.
***************** Begin makeheaders token definitions *************************/
/**************** End makeheaders token definitions ***************************/

/* The next sections is a series of control #defines.
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used to store the integer codes
**                       that represent terminal and non-terminal symbols.
**                       "unsigned char" is used if there are fewer than
**                       256 symbols.  Larger types otherwise.
**    YYNOCODE           is a number of type YYCODETYPE that is not used for
**                       any terminal or nonterminal symbol.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       (also known as: "terminal symbols") have fall-back
**                       values which should be used if the original symbol
**                       would not parse.  This permits keywords to sometimes
**                       be used as identifiers, for example.
**    YYACTIONTYPE       is the data type used for "action codes" - numbers
**                       that indicate what to do in response to the next
**                       token.
**    ImplParseTOKENTYPE     is the data type used for minor type for terminal
**                       symbols.  Background: A "minor type" is a semantic
**                       value associated with a terminal or non-terminal
**                       symbols.  For example, for an "ID" terminal symbol,
**                       the minor type might be the name of the identifier.
**                       Each non-terminal can have a different minor type.
**                       Terminal symbols all have the same minor type, though.
**                       This macros defines the minor type for terminal 
**                       symbols.
**    YYMINORTYPE        is the data type used for all minor types.
**                       This is typically a union of many types, one of
**                       which is ImplParseTOKENTYPE.  The entry in the union
**                       for terminal symbols is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    ImplParseARG_SDECL     A static variable declaration for the %extra_argument
**    ImplParseARG_PDECL     A parameter declaration for the %extra_argument
**    ImplParseARG_PARAM     Code to pass %extra_argument as a subroutine parameter
**    ImplParseARG_STORE     Code to store %extra_argument into yypParser
**    ImplParseARG_FETCH     Code to extract %extra_argument from yypParser
**    ImplParseCTX_*         As ImplParseARG_ except for %extra_context
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYNTOKEN           Number of terminal symbols
**    YY_MAX_SHIFT       Maximum value for shift actions
**    YY_MIN_SHIFTREDUCE Minimum value for shift-reduce actions
**    YY_MAX_SHIFTREDUCE Maximum value for shift-reduce actions
**    YY_ERROR_ACTION    The yy_action[] code for syntax error
**    YY_ACCEPT_ACTION   The yy_action[] code for accept
**    YY_NO_ACTION       The yy_action[] code for no-op
**    YY_MIN_REDUCE      Minimum value for reduce actions
**    YY_MAX_REDUCE      Maximum value for reduce actions
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/************* Begin control #defines *****************************************/
#define YYCODETYPE unsigned char
#define YYNOCODE 92
#define YYACTIONTYPE unsigned short int
#define ImplParseTOKENTYPE token*
typedef union {
  int yyinit;
  ImplParseTOKENTYPE yy0;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ImplParseARG_SDECL  void *state ;
#define ImplParseARG_PDECL , void *state 
#define ImplParseARG_PARAM ,state 
#define ImplParseARG_FETCH  void *state =yypParser->state ;
#define ImplParseARG_STORE yypParser->state =state ;
#define ImplParseCTX_SDECL
#define ImplParseCTX_PDECL
#define ImplParseCTX_PARAM
#define ImplParseCTX_FETCH
#define ImplParseCTX_STORE
#define YYNSTATE             67
#define YYNRULE              77
#define YYNTOKEN             64
#define YY_MAX_SHIFT         66
#define YY_MIN_SHIFTREDUCE   124
#define YY_MAX_SHIFTREDUCE   200
#define YY_ERROR_ACTION      201
#define YY_ACCEPT_ACTION     202
#define YY_NO_ACTION         203
#define YY_MIN_REDUCE        204
#define YY_MAX_REDUCE        280
/************* End control #defines *******************************************/
#define YY_NLOOKAHEAD ((int)(sizeof(yy_lookahead)/sizeof(yy_lookahead[0])))

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N <= YY_MAX_SHIFT             Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   N between YY_MIN_SHIFTREDUCE       Shift to an arbitrary state then
**     and YY_MAX_SHIFTREDUCE           reduce by rule N-YY_MIN_SHIFTREDUCE.
**
**   N == YY_ERROR_ACTION               A syntax error has occurred.
**
**   N == YY_ACCEPT_ACTION              The parser accepts its input.
**
**   N == YY_NO_ACTION                  No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
**   N between YY_MIN_REDUCE            Reduce by rule N-YY_MIN_REDUCE
**     and YY_MAX_REDUCE
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as either:
**
**    (A)   N = yy_action[ yy_shift_ofst[S] + X ]
**    (B)   N = yy_default[S]
**
** The (A) formula is preferred.  The B formula is used instead if
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X.
**
** The formulas above are for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
**
*********** Begin parsing tables **********************************************/
#define YY_ACTTAB_COUNT (257)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   241,   34,   35,  241,  202,   18,   39,   39,   47,   46,
 /*    10 */    64,   63,   61,   39,   39,   47,   44,  142,  143,  144,
 /*    20 */   145,  146,  147,  148,  149,  150,  151,   49,  183,   35,
 /*    30 */    49,   15,   66,   39,   39,   47,   46,   64,   63,   61,
 /*    40 */    39,   39,   47,   46,   64,   60,  218,   25,   14,   33,
 /*    50 */    30,   42,  240,   30,   35,  240,   53,   55,   39,   39,
 /*    60 */    47,   46,   64,   63,   61,   36,  250,  140,  250,   39,
 /*    70 */    39,   47,   46,   64,   63,   61,   36,  251,  130,  251,
 /*    80 */    39,   39,   47,   46,   64,   63,   61,   23,   56,   50,
 /*    90 */   215,    4,   39,   39,   47,   46,   64,   63,   61,   48,
 /*   100 */   262,   26,   27,   39,   39,   47,   46,   64,   63,   61,
 /*   110 */   261,   37,   37,   39,   39,   47,   46,   64,   63,   61,
 /*   120 */   267,   38,   38,   39,   39,   47,   46,   64,   63,   61,
 /*   130 */   155,  266,   22,   21,   39,   39,   47,   46,   64,   63,
 /*   140 */    61,  265,  212,  157,   39,   39,   47,   46,   64,   63,
 /*   150 */    61,   65,  183,  166,   39,   39,   47,   46,   64,   63,
 /*   160 */    61,  154,  183,  173,  174,   56,  219,    7,    8,    7,
 /*   170 */     8,   56,  162,  163,  164,   12,    1,   12,  177,   59,
 /*   180 */    58,   59,   58,  213,   41,   31,   41,   17,   41,    6,
 /*   190 */    42,  211,  140,   54,   31,   54,  176,   54,  176,   42,
 /*   200 */    57,  168,   57,  141,  137,   40,   31,   40,  176,   40,
 /*   210 */    56,   42,   57,  236,   24,  206,  207,   28,  209,   31,
 /*   220 */    39,   39,   43,  236,    3,  140,    2,   39,   39,   47,
 /*   230 */    46,   62,   39,   39,   45,   29,   10,    9,   32,    5,
 /*   240 */    52,   33,   11,   15,   51,   16,  180,  179,   19,   20,
 /*   250 */    13,  178,  204,  169,  203,  203,  136,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    79,   81,   81,   82,   64,   65,   85,   86,   87,   88,
 /*    10 */    89,   90,   91,   85,   86,   87,   88,   17,   18,   19,
 /*    20 */    20,   21,   22,   23,   24,   25,   26,   79,   11,   81,
 /*    30 */    82,   28,    2,   85,   86,   87,   88,   89,   90,   91,
 /*    40 */    85,   86,   87,   88,   89,   90,   68,   71,   48,   46,
 /*    50 */    50,   75,   79,   50,   81,   82,   33,   57,   85,   86,
 /*    60 */    87,   88,   89,   90,   91,   81,   82,   44,   84,   85,
 /*    70 */    86,   87,   88,   89,   90,   91,   81,   82,   47,   84,
 /*    80 */    85,   86,   87,   88,   89,   90,   91,   57,   57,   82,
 /*    90 */    74,   46,   85,   86,   87,   88,   89,   90,   91,   83,
 /*   100 */    82,   40,   41,   85,   86,   87,   88,   89,   90,   91,
 /*   110 */    82,   85,   86,   85,   86,   87,   88,   89,   90,   91,
 /*   120 */    82,   85,   86,   85,   86,   87,   88,   89,   90,   91,
 /*   130 */    46,   82,   36,   37,   85,   86,   87,   88,   89,   90,
 /*   140 */    91,   82,   68,   29,   85,   86,   87,   88,   89,   90,
 /*   150 */    91,   82,   11,   12,   85,   86,   87,   88,   89,   90,
 /*   160 */    91,   47,   11,   12,   13,   57,   68,   40,   41,   40,
 /*   170 */    41,   57,   58,   59,   60,   48,   33,   48,   51,   52,
 /*   180 */    53,   52,   53,   72,   69,   70,   71,   76,   73,   48,
 /*   190 */    75,   68,   44,   69,   70,   71,   57,   73,   57,   75,
 /*   200 */    61,   49,   61,   49,   51,   69,   70,   71,   57,   73,
 /*   210 */    57,   75,   61,   67,   68,   66,   67,   68,   69,   70,
 /*   220 */    85,   86,   87,   77,   78,   44,   80,   85,   86,   87,
 /*   230 */    88,   89,   85,   86,   87,   50,   38,   39,   33,   33,
 /*   240 */    11,   46,   44,   28,   63,   62,   57,   57,   35,   45,
 /*   250 */    34,   49,    0,   47,   92,   92,   51,   92,   92,   92,
 /*   260 */    92,   92,   92,   92,   92,   92,   92,   92,   92,   92,
 /*   270 */    92,   92,   92,   92,   92,   92,   92,   92,   92,   92,
 /*   280 */    92,   92,   92,   92,   92,   92,   92,   92,   92,   92,
 /*   290 */    92,   92,   92,   92,   92,   92,   92,   92,   92,   92,
 /*   300 */    92,   92,   92,   92,   92,   92,   92,   92,   92,   92,
 /*   310 */    92,   92,   92,   92,   92,   92,   92,
};
#define YY_SHIFT_COUNT    (66)
#define YY_SHIFT_MIN      (0)
#define YY_SHIFT_MAX      (252)
static const unsigned short int yy_shift_ofst[] = {
 /*     0 */   257,  141,  141,  141,  151,  151,   17,   17,   17,   17,
 /*    10 */    17,   17,   17,   17,    0,    0,    0,  114,   30,   17,
 /*    20 */    17,   17,   17,    3,   45,   84,   17,   17,   45,  139,
 /*    30 */   153,   31,  108,  108,  127,  129,  129,  198,  198,  198,
 /*    40 */   181,   23,  205,   61,   96,   61,   96,   61,  206,  143,
 /*    50 */   152,  185,  154,  229,  148,  195,  215,  183,  189,  190,
 /*    60 */   213,  216,  204,  213,  204,  202,  252,
};
#define YY_REDUCE_COUNT (33)
#define YY_REDUCE_MIN   (-80)
#define YY_REDUCE_MAX   (149)
static const short yy_reduce_ofst[] = {
 /*     0 */   -60,  -79,  -52,  -27,  -16,   -5,    7,   18,   28,   38,
 /*    10 */    49,   59,   69,  -45,  115,  124,  136,  146,  149,  142,
 /*    20 */   -72,  135,  147,  -24,   16,  111,   26,   36,   16,  -80,
 /*    30 */   -22,   74,   98,  123,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   205,  201,  201,  201,  201,  201,  201,  201,  201,  201,
 /*    10 */   201,  201,  201,  201,  201,  201,  201,  201,  201,  201,
 /*    20 */   201,  201,  201,  201,  238,  201,  201,  201,  208,  201,
 /*    30 */   201,  201,  201,  201,  201,  245,  255,  270,  269,  268,
 /*    40 */   201,  201,  201,  273,  275,  272,  274,  271,  201,  201,
 /*    50 */   201,  201,  201,  201,  214,  201,  201,  201,  201,  201,
 /*    60 */   279,  280,  277,  278,  276,  201,  201,
};
/********** End of lemon-generated parsing tables *****************************/

/* The next table maps tokens (terminal symbols) into fallback tokens.  
** If a construct like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
**
** This feature can be used, for example, to cause some keywords in a language
** to revert to identifiers if they keyword does not apply in the context where
** it appears.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
**
** After the "shift" half of a SHIFTREDUCE action, the stateno field
** actually contains the reduce action for the second half of the
** SHIFTREDUCE.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number, or reduce action in SHIFTREDUCE */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  yyStackEntry *yytos;          /* Pointer to top element of the stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyhwm;                    /* High-water mark of the stack */
#endif
#ifndef YYNOERRORRECOVERY
  int yyerrcnt;                 /* Shifts left before out of the error */
#endif
  ImplParseARG_SDECL                /* A place to hold %extra_argument */
  ImplParseCTX_SDECL                /* A place to hold %extra_context */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
  yyStackEntry yystk0;          /* First stack entry */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
  yyStackEntry *yystackEnd;            /* Last entry in the stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void ImplParseTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#if defined(YYCOVERAGE) || !defined(NDEBUG)
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  /*    0 */ "$",
  /*    1 */ "WHITESPACE",
  /*    2 */ "END",
  /*    3 */ "OTHER",
  /*    4 */ "TAB",
  /*    5 */ "NEW_LINE",
  /*    6 */ "CARRIAGE_RETURN",
  /*    7 */ "CHAR",
  /*    8 */ "MULTICHAR",
  /*    9 */ "LINE_COMMENT",
  /*   10 */ "MULTILINE_COMMENT",
  /*   11 */ "INTEGER",
  /*   12 */ "FLOAT",
  /*   13 */ "STRING",
  /*   14 */ "USE",
  /*   15 */ "AS",
  /*   16 */ "RET",
  /*   17 */ "U8",
  /*   18 */ "U16",
  /*   19 */ "U32",
  /*   20 */ "U64",
  /*   21 */ "I8",
  /*   22 */ "I16",
  /*   23 */ "I32",
  /*   24 */ "I64",
  /*   25 */ "F32",
  /*   26 */ "F64",
  /*   27 */ "EXCALAMATIONMARK_EQUALS",
  /*   28 */ "COLON",
  /*   29 */ "SEMICOLON",
  /*   30 */ "EXCLAMATIONMARK",
  /*   31 */ "QUESTIONMARK",
  /*   32 */ "EXP",
  /*   33 */ "COMMA",
  /*   34 */ "PIPE",
  /*   35 */ "CIRCUMFLEX",
  /*   36 */ "DOUBLE_LESS_THAN",
  /*   37 */ "DOUBLE_GREATER_THAN",
  /*   38 */ "SLASH",
  /*   39 */ "PERCENT",
  /*   40 */ "MINUS",
  /*   41 */ "PLUS",
  /*   42 */ "EXCLAMATION_MARK",
  /*   43 */ "TILDE",
  /*   44 */ "ASTERIX",
  /*   45 */ "AMPERSAND",
  /*   46 */ "L_C_BRACKET",
  /*   47 */ "R_C_BRACKET",
  /*   48 */ "L_S_BRACKET",
  /*   49 */ "R_S_BRACKET",
  /*   50 */ "L_R_BRACKET",
  /*   51 */ "R_R_BRACKET",
  /*   52 */ "DOT",
  /*   53 */ "ARROW",
  /*   54 */ "DOUBLE_COLON",
  /*   55 */ "POINTER_TYPE",
  /*   56 */ "VOID",
  /*   57 */ "ID",
  /*   58 */ "PUSH",
  /*   59 */ "MOV",
  /*   60 */ "ADD",
  /*   61 */ "CAST",
  /*   62 */ "LESS_THAN",
  /*   63 */ "GREATER_THAN",
  /*   64 */ "package",
  /*   65 */ "package_opt",
  /*   66 */ "function_def",
  /*   67 */ "var_def",
  /*   68 */ "var_decl",
  /*   69 */ "struct_def",
  /*   70 */ "struct_def_opt",
  /*   71 */ "function_type",
  /*   72 */ "block_statement",
  /*   73 */ "type",
  /*   74 */ "literal",
  /*   75 */ "function_type_opt",
  /*   76 */ "block_statement_opt",
  /*   77 */ "statement",
  /*   78 */ "u_mnemonic",
  /*   79 */ "operand",
  /*   80 */ "d_mnemonic",
  /*   81 */ "ref_exp",
  /*   82 */ "scalar_exp",
  /*   83 */ "literal_opt",
  /*   84 */ "exp",
  /*   85 */ "scalar_exp_int",
  /*   86 */ "multiplicative_exp",
  /*   87 */ "additive_exp",
  /*   88 */ "shift_exp",
  /*   89 */ "and_exp",
  /*   90 */ "exclusive_or_exp",
  /*   91 */ "inclusive_or_exp",
};
#endif /* defined(YYCOVERAGE) || !defined(NDEBUG) */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "package ::= package_opt END",
 /*   1 */ "package_opt ::=",
 /*   2 */ "package_opt ::= package_opt function_def",
 /*   3 */ "package_opt ::= package_opt var_def",
 /*   4 */ "package_opt ::= package_opt var_decl",
 /*   5 */ "package_opt ::= package_opt struct_def",
 /*   6 */ "struct_def ::= struct_def_opt R_C_BRACKET",
 /*   7 */ "struct_def_opt ::= ID L_C_BRACKET var_decl",
 /*   8 */ "struct_def_opt ::= struct_def_opt var_decl",
 /*   9 */ "function_def ::= ID function_type block_statement",
 /*  10 */ "var_decl ::= ID COLON type",
 /*  11 */ "var_def ::= var_decl literal",
 /*  12 */ "function_type ::= function_type_opt R_R_BRACKET",
 /*  13 */ "function_type ::= L_R_BRACKET R_R_BRACKET",
 /*  14 */ "function_type_opt ::= L_R_BRACKET var_decl",
 /*  15 */ "function_type_opt ::= function_type_opt COMMA var_decl",
 /*  16 */ "type ::= type ASTERIX",
 /*  17 */ "type ::= L_S_BRACKET type COMMA INTEGER R_S_BRACKET",
 /*  18 */ "type ::= U8",
 /*  19 */ "type ::= U16",
 /*  20 */ "type ::= U32",
 /*  21 */ "type ::= U64",
 /*  22 */ "type ::= I8",
 /*  23 */ "type ::= I16",
 /*  24 */ "type ::= I32",
 /*  25 */ "type ::= I64",
 /*  26 */ "type ::= F32",
 /*  27 */ "type ::= F64",
 /*  28 */ "type ::= function_type",
 /*  29 */ "type ::= struct_def",
 /*  30 */ "block_statement ::= block_statement_opt R_C_BRACKET",
 /*  31 */ "block_statement_opt ::= L_C_BRACKET",
 /*  32 */ "block_statement_opt ::= block_statement_opt statement",
 /*  33 */ "statement ::= SEMICOLON",
 /*  34 */ "statement ::= var_decl",
 /*  35 */ "statement ::= var_def",
 /*  36 */ "statement ::= u_mnemonic operand",
 /*  37 */ "statement ::= d_mnemonic operand COMMA operand",
 /*  38 */ "u_mnemonic ::= PUSH",
 /*  39 */ "d_mnemonic ::= MOV",
 /*  40 */ "d_mnemonic ::= ADD",
 /*  41 */ "operand ::= ref_exp",
 /*  42 */ "operand ::= FLOAT",
 /*  43 */ "operand ::= scalar_exp",
 /*  44 */ "operand ::= L_S_BRACKET scalar_exp R_S_BRACKET",
 /*  45 */ "literal ::= literal_opt R_C_BRACKET",
 /*  46 */ "literal_opt ::= L_C_BRACKET exp",
 /*  47 */ "literal_opt ::= literal_opt COMMA exp",
 /*  48 */ "exp ::= scalar_exp",
 /*  49 */ "exp ::= FLOAT",
 /*  50 */ "exp ::= STRING",
 /*  51 */ "exp ::= ref_exp",
 /*  52 */ "ref_exp ::= ID",
 /*  53 */ "ref_exp ::= CAST LESS_THAN type GREATER_THAN L_R_BRACKET ref_exp R_R_BRACKET",
 /*  54 */ "ref_exp ::= ref_exp L_S_BRACKET scalar_exp R_S_BRACKET",
 /*  55 */ "ref_exp ::= ref_exp DOT ID",
 /*  56 */ "ref_exp ::= ref_exp ARROW ID",
 /*  57 */ "ref_exp ::= ref_exp PLUS scalar_exp",
 /*  58 */ "ref_exp ::= ref_exp MINUS scalar_exp",
 /*  59 */ "scalar_exp_int ::= INTEGER",
 /*  60 */ "multiplicative_exp ::= scalar_exp_int",
 /*  61 */ "multiplicative_exp ::= multiplicative_exp ASTERIX scalar_exp",
 /*  62 */ "multiplicative_exp ::= multiplicative_exp SLASH scalar_exp",
 /*  63 */ "multiplicative_exp ::= multiplicative_exp PERCENT scalar_exp",
 /*  64 */ "additive_exp ::= multiplicative_exp",
 /*  65 */ "additive_exp ::= additive_exp PLUS multiplicative_exp",
 /*  66 */ "additive_exp ::= additive_exp MINUS multiplicative_exp",
 /*  67 */ "shift_exp ::= additive_exp",
 /*  68 */ "shift_exp ::= shift_exp DOUBLE_LESS_THAN additive_exp",
 /*  69 */ "shift_exp ::= shift_exp DOUBLE_GREATER_THAN additive_exp",
 /*  70 */ "and_exp ::= shift_exp",
 /*  71 */ "and_exp ::= and_exp AMPERSAND shift_exp",
 /*  72 */ "exclusive_or_exp ::= and_exp",
 /*  73 */ "exclusive_or_exp ::= exclusive_or_exp CIRCUMFLEX and_exp",
 /*  74 */ "inclusive_or_exp ::= exclusive_or_exp",
 /*  75 */ "inclusive_or_exp ::= inclusive_or_exp PIPE exclusive_or_exp",
 /*  76 */ "scalar_exp ::= inclusive_or_exp",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.  Return the number
** of errors.  Return 0 on success.
*/
static int yyGrowStack(yyParser *p){
  int newSize;
  int idx;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  idx = p->yytos ? (int)(p->yytos - p->yystack) : 0;
  if( p->yystack==&p->yystk0 ){
    pNew = malloc(newSize*sizeof(pNew[0]));
    if( pNew ) pNew[0] = p->yystk0;
  }else{
    pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  }
  if( pNew ){
    p->yystack = pNew;
    p->yytos = &p->yystack[idx];
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows from %d to %d entries.\n",
              yyTracePrompt, p->yystksz, newSize);
    }
#endif
    p->yystksz = newSize;
  }
  return pNew==0; 
}
#endif

/* Datatype of the argument to the memory allocated passed as the
** second argument to ImplParseAlloc() below.  This can be changed by
** putting an appropriate #define in the %include section of the input
** grammar.
*/
#ifndef YYMALLOCARGTYPE
# define YYMALLOCARGTYPE size_t
#endif

/* Initialize a new parser that has already been allocated.
*/
void ImplParseInit(void *yypRawParser ImplParseCTX_PDECL){
  yyParser *yypParser = (yyParser*)yypRawParser;
  ImplParseCTX_STORE
#ifdef YYTRACKMAXSTACKDEPTH
  yypParser->yyhwm = 0;
#endif
#if YYSTACKDEPTH<=0
  yypParser->yytos = NULL;
  yypParser->yystack = NULL;
  yypParser->yystksz = 0;
  if( yyGrowStack(yypParser) ){
    yypParser->yystack = &yypParser->yystk0;
    yypParser->yystksz = 1;
  }
#endif
#ifndef YYNOERRORRECOVERY
  yypParser->yyerrcnt = -1;
#endif
  yypParser->yytos = yypParser->yystack;
  yypParser->yystack[0].stateno = 0;
  yypParser->yystack[0].major = 0;
#if YYSTACKDEPTH>0
  yypParser->yystackEnd = &yypParser->yystack[YYSTACKDEPTH-1];
#endif
}

#ifndef ImplParse_ENGINEALWAYSONSTACK
/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to ImplParse and ImplParseFree.
*/
void *ImplParseAlloc(void *(*mallocProc)(YYMALLOCARGTYPE) ImplParseCTX_PDECL){
  yyParser *yypParser;
  yypParser = (yyParser*)(*mallocProc)( (YYMALLOCARGTYPE)sizeof(yyParser) );
  if( yypParser ){
    ImplParseCTX_STORE
    ImplParseInit(yypParser ImplParseCTX_PARAM);
  }
  return (void*)yypParser;
}
#endif /* ImplParse_ENGINEALWAYSONSTACK */


/* The following function deletes the "minor type" or semantic value
** associated with a symbol.  The symbol can be either a terminal
** or nonterminal. "yymajor" is the symbol code, and "yypminor" is
** a pointer to the value to be deleted.  The code used to do the 
** deletions is derived from the %destructor and/or %token_destructor
** directives of the input grammar.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  ImplParseARG_FETCH
  ImplParseCTX_FETCH
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are *not* used
    ** inside the C code.
    */
/********* Begin destructor definitions ***************************************/
/********* End destructor definitions *****************************************/
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
*/
static void yy_pop_parser_stack(yyParser *pParser){
  yyStackEntry *yytos;
  assert( pParser->yytos!=0 );
  assert( pParser->yytos > pParser->yystack );
  yytos = pParser->yytos--;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yy_destructor(pParser, yytos->major, &yytos->minor);
}

/*
** Clear all secondary memory allocations from the parser
*/
void ImplParseFinalize(void *p){
  yyParser *pParser = (yyParser*)p;
  while( pParser->yytos>pParser->yystack ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  if( pParser->yystack!=&pParser->yystk0 ) free(pParser->yystack);
#endif
}

#ifndef ImplParse_ENGINEALWAYSONSTACK
/* 
** Deallocate and destroy a parser.  Destructors are called for
** all stack elements before shutting the parser down.
**
** If the YYPARSEFREENEVERNULL macro exists (for example because it
** is defined in a %include section of the input grammar) then it is
** assumed that the input pointer is never NULL.
*/
void ImplParseFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
#ifndef YYPARSEFREENEVERNULL
  if( p==0 ) return;
#endif
  ImplParseFinalize(p);
  (*freeProc)(p);
}
#endif /* ImplParse_ENGINEALWAYSONSTACK */

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int ImplParseStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyhwm;
}
#endif

/* This array of booleans keeps track of the parser statement
** coverage.  The element yycoverage[X][Y] is set when the parser
** is in state X and has a lookahead token Y.  In a well-tested
** systems, every element of this matrix should end up being set.
*/
#if defined(YYCOVERAGE)
static unsigned char yycoverage[YYNSTATE][YYNTOKEN];
#endif

/*
** Write into out a description of every state/lookahead combination that
**
**   (1)  has not been used by the parser, and
**   (2)  is not a syntax error.
**
** Return the number of missed state/lookahead combinations.
*/
#if defined(YYCOVERAGE)
int ImplParseCoverage(FILE *out){
  int stateno, iLookAhead, i;
  int nMissed = 0;
  for(stateno=0; stateno<YYNSTATE; stateno++){
    i = yy_shift_ofst[stateno];
    for(iLookAhead=0; iLookAhead<YYNTOKEN; iLookAhead++){
      if( yy_lookahead[i+iLookAhead]!=iLookAhead ) continue;
      if( yycoverage[stateno][iLookAhead]==0 ) nMissed++;
      if( out ){
        fprintf(out,"State %d lookahead %s %s\n", stateno,
                yyTokenName[iLookAhead],
                yycoverage[stateno][iLookAhead] ? "ok" : "missed");
      }
    }
  }
  return nMissed;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
*/
static YYACTIONTYPE yy_find_shift_action(
  YYCODETYPE iLookAhead,    /* The look-ahead token */
  YYACTIONTYPE stateno      /* Current state number */
){
  int i;

  if( stateno>YY_MAX_SHIFT ) return stateno;
  assert( stateno <= YY_SHIFT_COUNT );
#if defined(YYCOVERAGE)
  yycoverage[stateno][iLookAhead] = 1;
#endif
  do{
    i = yy_shift_ofst[stateno];
    assert( i>=0 );
    /* assert( i+YYNTOKEN<=(int)YY_NLOOKAHEAD ); */
    assert( iLookAhead!=YYNOCODE );
    assert( iLookAhead < YYNTOKEN );
    i += iLookAhead;
    if( i>=YY_NLOOKAHEAD || yy_lookahead[i]!=iLookAhead ){
#ifdef YYFALLBACK
      YYCODETYPE iFallback;            /* Fallback token */
      if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
             && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        assert( yyFallback[iFallback]==0 ); /* Fallback loop must terminate */
        iLookAhead = iFallback;
        continue;
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        if( 
#if YY_SHIFT_MIN+YYWILDCARD<0
          j>=0 &&
#endif
#if YY_SHIFT_MAX+YYWILDCARD>=YY_ACTTAB_COUNT
          j<YY_ACTTAB_COUNT &&
#endif
          j<(int)(sizeof(yy_lookahead)/sizeof(yy_lookahead[0])) &&
          yy_lookahead[j]==YYWILDCARD && iLookAhead>0
        ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead],
               yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
      return yy_default[stateno];
    }else{
      return yy_action[i];
    }
  }while(1);
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
*/
static YYACTIONTYPE yy_find_reduce_action(
  YYACTIONTYPE stateno,     /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_COUNT ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_COUNT );
#endif
  i = yy_reduce_ofst[stateno];
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_ACTTAB_COUNT );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser){
   ImplParseARG_FETCH
   ImplParseCTX_FETCH
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
/******** Begin %stack_overflow code ******************************************/
/******** End %stack_overflow code ********************************************/
   ImplParseARG_STORE /* Suppress warning about unused %extra_argument var */
   ImplParseCTX_STORE
}

/*
** Print tracing information for a SHIFT action
*/
#ifndef NDEBUG
static void yyTraceShift(yyParser *yypParser, int yyNewState, const char *zTag){
  if( yyTraceFILE ){
    if( yyNewState<YYNSTATE ){
      fprintf(yyTraceFILE,"%s%s '%s', go to state %d\n",
         yyTracePrompt, zTag, yyTokenName[yypParser->yytos->major],
         yyNewState);
    }else{
      fprintf(yyTraceFILE,"%s%s '%s', pending reduce %d\n",
         yyTracePrompt, zTag, yyTokenName[yypParser->yytos->major],
         yyNewState - YY_MIN_REDUCE);
    }
  }
}
#else
# define yyTraceShift(X,Y,Z)
#endif

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  YYACTIONTYPE yyNewState,      /* The new state to shift in */
  YYCODETYPE yyMajor,           /* The major token to shift in */
  ImplParseTOKENTYPE yyMinor        /* The minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yytos++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
    yypParser->yyhwm++;
    assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack) );
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yytos>yypParser->yystackEnd ){
    yypParser->yytos--;
    yyStackOverflow(yypParser);
    return;
  }
#else
  if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz] ){
    if( yyGrowStack(yypParser) ){
      yypParser->yytos--;
      yyStackOverflow(yypParser);
      return;
    }
  }
#endif
  if( yyNewState > YY_MAX_SHIFT ){
    yyNewState += YY_MIN_REDUCE - YY_MIN_SHIFTREDUCE;
  }
  yytos = yypParser->yytos;
  yytos->stateno = yyNewState;
  yytos->major = yyMajor;
  yytos->minor.yy0 = yyMinor;
  yyTraceShift(yypParser, yyNewState, "Shift");
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;       /* Symbol on the left-hand side of the rule */
  signed char nrhs;     /* Negative of the number of RHS symbols in the rule */
} yyRuleInfo[] = {
  {   64,   -2 }, /* (0) package ::= package_opt END */
  {   65,    0 }, /* (1) package_opt ::= */
  {   65,   -2 }, /* (2) package_opt ::= package_opt function_def */
  {   65,   -2 }, /* (3) package_opt ::= package_opt var_def */
  {   65,   -2 }, /* (4) package_opt ::= package_opt var_decl */
  {   65,   -2 }, /* (5) package_opt ::= package_opt struct_def */
  {   69,   -2 }, /* (6) struct_def ::= struct_def_opt R_C_BRACKET */
  {   70,   -3 }, /* (7) struct_def_opt ::= ID L_C_BRACKET var_decl */
  {   70,   -2 }, /* (8) struct_def_opt ::= struct_def_opt var_decl */
  {   66,   -3 }, /* (9) function_def ::= ID function_type block_statement */
  {   68,   -3 }, /* (10) var_decl ::= ID COLON type */
  {   67,   -2 }, /* (11) var_def ::= var_decl literal */
  {   71,   -2 }, /* (12) function_type ::= function_type_opt R_R_BRACKET */
  {   71,   -2 }, /* (13) function_type ::= L_R_BRACKET R_R_BRACKET */
  {   75,   -2 }, /* (14) function_type_opt ::= L_R_BRACKET var_decl */
  {   75,   -3 }, /* (15) function_type_opt ::= function_type_opt COMMA var_decl */
  {   73,   -2 }, /* (16) type ::= type ASTERIX */
  {   73,   -5 }, /* (17) type ::= L_S_BRACKET type COMMA INTEGER R_S_BRACKET */
  {   73,   -1 }, /* (18) type ::= U8 */
  {   73,   -1 }, /* (19) type ::= U16 */
  {   73,   -1 }, /* (20) type ::= U32 */
  {   73,   -1 }, /* (21) type ::= U64 */
  {   73,   -1 }, /* (22) type ::= I8 */
  {   73,   -1 }, /* (23) type ::= I16 */
  {   73,   -1 }, /* (24) type ::= I32 */
  {   73,   -1 }, /* (25) type ::= I64 */
  {   73,   -1 }, /* (26) type ::= F32 */
  {   73,   -1 }, /* (27) type ::= F64 */
  {   73,   -1 }, /* (28) type ::= function_type */
  {   73,   -1 }, /* (29) type ::= struct_def */
  {   72,   -2 }, /* (30) block_statement ::= block_statement_opt R_C_BRACKET */
  {   76,   -1 }, /* (31) block_statement_opt ::= L_C_BRACKET */
  {   76,   -2 }, /* (32) block_statement_opt ::= block_statement_opt statement */
  {   77,   -1 }, /* (33) statement ::= SEMICOLON */
  {   77,   -1 }, /* (34) statement ::= var_decl */
  {   77,   -1 }, /* (35) statement ::= var_def */
  {   77,   -2 }, /* (36) statement ::= u_mnemonic operand */
  {   77,   -4 }, /* (37) statement ::= d_mnemonic operand COMMA operand */
  {   78,   -1 }, /* (38) u_mnemonic ::= PUSH */
  {   80,   -1 }, /* (39) d_mnemonic ::= MOV */
  {   80,   -1 }, /* (40) d_mnemonic ::= ADD */
  {   79,   -1 }, /* (41) operand ::= ref_exp */
  {   79,   -1 }, /* (42) operand ::= FLOAT */
  {   79,   -1 }, /* (43) operand ::= scalar_exp */
  {   79,   -3 }, /* (44) operand ::= L_S_BRACKET scalar_exp R_S_BRACKET */
  {   74,   -2 }, /* (45) literal ::= literal_opt R_C_BRACKET */
  {   83,   -2 }, /* (46) literal_opt ::= L_C_BRACKET exp */
  {   83,   -3 }, /* (47) literal_opt ::= literal_opt COMMA exp */
  {   84,   -1 }, /* (48) exp ::= scalar_exp */
  {   84,   -1 }, /* (49) exp ::= FLOAT */
  {   84,   -1 }, /* (50) exp ::= STRING */
  {   84,   -1 }, /* (51) exp ::= ref_exp */
  {   81,   -1 }, /* (52) ref_exp ::= ID */
  {   81,   -7 }, /* (53) ref_exp ::= CAST LESS_THAN type GREATER_THAN L_R_BRACKET ref_exp R_R_BRACKET */
  {   81,   -4 }, /* (54) ref_exp ::= ref_exp L_S_BRACKET scalar_exp R_S_BRACKET */
  {   81,   -3 }, /* (55) ref_exp ::= ref_exp DOT ID */
  {   81,   -3 }, /* (56) ref_exp ::= ref_exp ARROW ID */
  {   81,   -3 }, /* (57) ref_exp ::= ref_exp PLUS scalar_exp */
  {   81,   -3 }, /* (58) ref_exp ::= ref_exp MINUS scalar_exp */
  {   85,   -1 }, /* (59) scalar_exp_int ::= INTEGER */
  {   86,   -1 }, /* (60) multiplicative_exp ::= scalar_exp_int */
  {   86,   -3 }, /* (61) multiplicative_exp ::= multiplicative_exp ASTERIX scalar_exp */
  {   86,   -3 }, /* (62) multiplicative_exp ::= multiplicative_exp SLASH scalar_exp */
  {   86,   -3 }, /* (63) multiplicative_exp ::= multiplicative_exp PERCENT scalar_exp */
  {   87,   -1 }, /* (64) additive_exp ::= multiplicative_exp */
  {   87,   -3 }, /* (65) additive_exp ::= additive_exp PLUS multiplicative_exp */
  {   87,   -3 }, /* (66) additive_exp ::= additive_exp MINUS multiplicative_exp */
  {   88,   -1 }, /* (67) shift_exp ::= additive_exp */
  {   88,   -3 }, /* (68) shift_exp ::= shift_exp DOUBLE_LESS_THAN additive_exp */
  {   88,   -3 }, /* (69) shift_exp ::= shift_exp DOUBLE_GREATER_THAN additive_exp */
  {   89,   -1 }, /* (70) and_exp ::= shift_exp */
  {   89,   -3 }, /* (71) and_exp ::= and_exp AMPERSAND shift_exp */
  {   90,   -1 }, /* (72) exclusive_or_exp ::= and_exp */
  {   90,   -3 }, /* (73) exclusive_or_exp ::= exclusive_or_exp CIRCUMFLEX and_exp */
  {   91,   -1 }, /* (74) inclusive_or_exp ::= exclusive_or_exp */
  {   91,   -3 }, /* (75) inclusive_or_exp ::= inclusive_or_exp PIPE exclusive_or_exp */
  {   82,   -1 }, /* (76) scalar_exp ::= inclusive_or_exp */
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
**
** The yyLookahead and yyLookaheadToken parameters provide reduce actions
** access to the lookahead token (if any).  The yyLookahead will be YYNOCODE
** if the lookahead token has already been consumed.  As this procedure is
** only called from one place, optimizing compilers will in-line it, which
** means that the extra parameters have no performance impact.
*/
static YYACTIONTYPE yy_reduce(
  yyParser *yypParser,         /* The parser */
  unsigned int yyruleno,       /* Number of the rule by which to reduce */
  int yyLookahead,             /* Lookahead token, or YYNOCODE if none */
  ImplParseTOKENTYPE yyLookaheadToken  /* Value of the lookahead token */
  ImplParseCTX_PDECL                   /* %extra_context */
){
  int yygoto;                     /* The next state */
  YYACTIONTYPE yyact;             /* The next action */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  ImplParseARG_FETCH
  (void)yyLookahead;
  (void)yyLookaheadToken;
  yymsp = yypParser->yytos;
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    yysize = yyRuleInfo[yyruleno].nrhs;
    if( yysize ){
      fprintf(yyTraceFILE, "%sReduce %d [%s], go to state %d.\n",
        yyTracePrompt,
        yyruleno, yyRuleName[yyruleno], yymsp[yysize].stateno);
    }else{
      fprintf(yyTraceFILE, "%sReduce %d [%s].\n",
        yyTracePrompt, yyruleno, yyRuleName[yyruleno]);
    }
  }
#endif /* NDEBUG */

  /* Check that the stack is large enough to grow by a single entry
  ** if the RHS of the rule is empty.  This ensures that there is room
  ** enough on the stack to push the LHS value */
  if( yyRuleInfo[yyruleno].nrhs==0 ){
#ifdef YYTRACKMAXSTACKDEPTH
    if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
      yypParser->yyhwm++;
      assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack));
    }
#endif
#if YYSTACKDEPTH>0 
    if( yypParser->yytos>=yypParser->yystackEnd ){
      yyStackOverflow(yypParser);
      /* The call to yyStackOverflow() above pops the stack until it is
      ** empty, causing the main parser loop to exit.  So the return value
      ** is never used and does not matter. */
      return 0;
    }
#else
    if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz-1] ){
      if( yyGrowStack(yypParser) ){
        yyStackOverflow(yypParser);
        /* The call to yyStackOverflow() above pops the stack until it is
        ** empty, causing the main parser loop to exit.  So the return value
        ** is never used and does not matter. */
        return 0;
      }
      yymsp = yypParser->yytos;
    }
#endif
  }

  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
/********** Begin reduce actions **********************************************/
      default:
      /* (0) package ::= package_opt END */ yytestcase(yyruleno==0);
      /* (1) package_opt ::= */ yytestcase(yyruleno==1);
      /* (2) package_opt ::= package_opt function_def */ yytestcase(yyruleno==2);
      /* (3) package_opt ::= package_opt var_def */ yytestcase(yyruleno==3);
      /* (4) package_opt ::= package_opt var_decl */ yytestcase(yyruleno==4);
      /* (5) package_opt ::= package_opt struct_def */ yytestcase(yyruleno==5);
      /* (6) struct_def ::= struct_def_opt R_C_BRACKET */ yytestcase(yyruleno==6);
      /* (7) struct_def_opt ::= ID L_C_BRACKET var_decl */ yytestcase(yyruleno==7);
      /* (8) struct_def_opt ::= struct_def_opt var_decl */ yytestcase(yyruleno==8);
      /* (9) function_def ::= ID function_type block_statement */ yytestcase(yyruleno==9);
      /* (10) var_decl ::= ID COLON type */ yytestcase(yyruleno==10);
      /* (11) var_def ::= var_decl literal */ yytestcase(yyruleno==11);
      /* (12) function_type ::= function_type_opt R_R_BRACKET */ yytestcase(yyruleno==12);
      /* (13) function_type ::= L_R_BRACKET R_R_BRACKET */ yytestcase(yyruleno==13);
      /* (14) function_type_opt ::= L_R_BRACKET var_decl */ yytestcase(yyruleno==14);
      /* (15) function_type_opt ::= function_type_opt COMMA var_decl */ yytestcase(yyruleno==15);
      /* (16) type ::= type ASTERIX */ yytestcase(yyruleno==16);
      /* (17) type ::= L_S_BRACKET type COMMA INTEGER R_S_BRACKET */ yytestcase(yyruleno==17);
      /* (18) type ::= U8 */ yytestcase(yyruleno==18);
      /* (19) type ::= U16 */ yytestcase(yyruleno==19);
      /* (20) type ::= U32 */ yytestcase(yyruleno==20);
      /* (21) type ::= U64 */ yytestcase(yyruleno==21);
      /* (22) type ::= I8 */ yytestcase(yyruleno==22);
      /* (23) type ::= I16 */ yytestcase(yyruleno==23);
      /* (24) type ::= I32 */ yytestcase(yyruleno==24);
      /* (25) type ::= I64 */ yytestcase(yyruleno==25);
      /* (26) type ::= F32 */ yytestcase(yyruleno==26);
      /* (27) type ::= F64 */ yytestcase(yyruleno==27);
      /* (28) type ::= function_type (OPTIMIZED OUT) */ assert(yyruleno!=28);
      /* (29) type ::= struct_def (OPTIMIZED OUT) */ assert(yyruleno!=29);
      /* (30) block_statement ::= block_statement_opt R_C_BRACKET */ yytestcase(yyruleno==30);
      /* (31) block_statement_opt ::= L_C_BRACKET */ yytestcase(yyruleno==31);
      /* (32) block_statement_opt ::= block_statement_opt statement */ yytestcase(yyruleno==32);
      /* (33) statement ::= SEMICOLON */ yytestcase(yyruleno==33);
      /* (34) statement ::= var_decl */ yytestcase(yyruleno==34);
      /* (35) statement ::= var_def (OPTIMIZED OUT) */ assert(yyruleno!=35);
      /* (36) statement ::= u_mnemonic operand */ yytestcase(yyruleno==36);
      /* (37) statement ::= d_mnemonic operand COMMA operand */ yytestcase(yyruleno==37);
      /* (38) u_mnemonic ::= PUSH */ yytestcase(yyruleno==38);
      /* (39) d_mnemonic ::= MOV */ yytestcase(yyruleno==39);
      /* (40) d_mnemonic ::= ADD */ yytestcase(yyruleno==40);
      /* (41) operand ::= ref_exp */ yytestcase(yyruleno==41);
      /* (42) operand ::= FLOAT */ yytestcase(yyruleno==42);
      /* (43) operand ::= scalar_exp (OPTIMIZED OUT) */ assert(yyruleno!=43);
      /* (44) operand ::= L_S_BRACKET scalar_exp R_S_BRACKET */ yytestcase(yyruleno==44);
      /* (45) literal ::= literal_opt R_C_BRACKET */ yytestcase(yyruleno==45);
      /* (46) literal_opt ::= L_C_BRACKET exp */ yytestcase(yyruleno==46);
      /* (47) literal_opt ::= literal_opt COMMA exp */ yytestcase(yyruleno==47);
      /* (48) exp ::= scalar_exp (OPTIMIZED OUT) */ assert(yyruleno!=48);
      /* (49) exp ::= FLOAT */ yytestcase(yyruleno==49);
      /* (50) exp ::= STRING */ yytestcase(yyruleno==50);
      /* (51) exp ::= ref_exp */ yytestcase(yyruleno==51);
      /* (52) ref_exp ::= ID */ yytestcase(yyruleno==52);
      /* (53) ref_exp ::= CAST LESS_THAN type GREATER_THAN L_R_BRACKET ref_exp R_R_BRACKET */ yytestcase(yyruleno==53);
      /* (54) ref_exp ::= ref_exp L_S_BRACKET scalar_exp R_S_BRACKET */ yytestcase(yyruleno==54);
      /* (55) ref_exp ::= ref_exp DOT ID */ yytestcase(yyruleno==55);
      /* (56) ref_exp ::= ref_exp ARROW ID */ yytestcase(yyruleno==56);
      /* (57) ref_exp ::= ref_exp PLUS scalar_exp */ yytestcase(yyruleno==57);
      /* (58) ref_exp ::= ref_exp MINUS scalar_exp */ yytestcase(yyruleno==58);
      /* (59) scalar_exp_int ::= INTEGER */ yytestcase(yyruleno==59);
      /* (60) multiplicative_exp ::= scalar_exp_int (OPTIMIZED OUT) */ assert(yyruleno!=60);
      /* (61) multiplicative_exp ::= multiplicative_exp ASTERIX scalar_exp */ yytestcase(yyruleno==61);
      /* (62) multiplicative_exp ::= multiplicative_exp SLASH scalar_exp */ yytestcase(yyruleno==62);
      /* (63) multiplicative_exp ::= multiplicative_exp PERCENT scalar_exp */ yytestcase(yyruleno==63);
      /* (64) additive_exp ::= multiplicative_exp */ yytestcase(yyruleno==64);
      /* (65) additive_exp ::= additive_exp PLUS multiplicative_exp */ yytestcase(yyruleno==65);
      /* (66) additive_exp ::= additive_exp MINUS multiplicative_exp */ yytestcase(yyruleno==66);
      /* (67) shift_exp ::= additive_exp */ yytestcase(yyruleno==67);
      /* (68) shift_exp ::= shift_exp DOUBLE_LESS_THAN additive_exp */ yytestcase(yyruleno==68);
      /* (69) shift_exp ::= shift_exp DOUBLE_GREATER_THAN additive_exp */ yytestcase(yyruleno==69);
      /* (70) and_exp ::= shift_exp */ yytestcase(yyruleno==70);
      /* (71) and_exp ::= and_exp AMPERSAND shift_exp */ yytestcase(yyruleno==71);
      /* (72) exclusive_or_exp ::= and_exp */ yytestcase(yyruleno==72);
      /* (73) exclusive_or_exp ::= exclusive_or_exp CIRCUMFLEX and_exp */ yytestcase(yyruleno==73);
      /* (74) inclusive_or_exp ::= exclusive_or_exp */ yytestcase(yyruleno==74);
      /* (75) inclusive_or_exp ::= inclusive_or_exp PIPE exclusive_or_exp */ yytestcase(yyruleno==75);
      /* (76) scalar_exp ::= inclusive_or_exp */ yytestcase(yyruleno==76);
        break;
/********** End reduce actions ************************************************/
  };
  assert( yyruleno<sizeof(yyRuleInfo)/sizeof(yyRuleInfo[0]) );
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yyact = yy_find_reduce_action(yymsp[yysize].stateno,(YYCODETYPE)yygoto);

  /* There are no SHIFTREDUCE actions on nonterminals because the table
  ** generator has simplified them to pure REDUCE actions. */
  assert( !(yyact>YY_MAX_SHIFT && yyact<=YY_MAX_SHIFTREDUCE) );

  /* It is not possible for a REDUCE to be followed by an error */
  assert( yyact!=YY_ERROR_ACTION );

  yymsp += yysize+1;
  yypParser->yytos = yymsp;
  yymsp->stateno = (YYACTIONTYPE)yyact;
  yymsp->major = (YYCODETYPE)yygoto;
  yyTraceShift(yypParser, yyact, "... then shift");
  return yyact;
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  ImplParseARG_FETCH
  ImplParseCTX_FETCH
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
/************ Begin %parse_failure code ***************************************/
/************ End %parse_failure code *****************************************/
  ImplParseARG_STORE /* Suppress warning about unused %extra_argument variable */
  ImplParseCTX_STORE
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  ImplParseTOKENTYPE yyminor         /* The minor type of the error token */
){
  ImplParseARG_FETCH
  ImplParseCTX_FETCH
#define TOKEN yyminor
/************ Begin %syntax_error code ****************************************/
#line 63 "./parser/grammar.y"

    printf("syntax error\n");
#line 1289 "./parser/out/grammar.c"
/************ End %syntax_error code ******************************************/
  ImplParseARG_STORE /* Suppress warning about unused %extra_argument variable */
  ImplParseCTX_STORE
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  ImplParseARG_FETCH
  ImplParseCTX_FETCH
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
#ifndef YYNOERRORRECOVERY
  yypParser->yyerrcnt = -1;
#endif
  assert( yypParser->yytos==yypParser->yystack );
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
/*********** Begin %parse_accept code *****************************************/
/*********** End %parse_accept code *******************************************/
  ImplParseARG_STORE /* Suppress warning about unused %extra_argument variable */
  ImplParseCTX_STORE
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "ImplParseAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void ImplParse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  ImplParseTOKENTYPE yyminor       /* The value for the token */
  ImplParseARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  YYACTIONTYPE yyact;   /* The parser action. */
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  int yyendofinput;     /* True if we are at the end of input */
#endif
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser = (yyParser*)yyp;  /* The parser */
  ImplParseCTX_FETCH
  ImplParseARG_STORE

  assert( yypParser->yytos!=0 );
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  yyendofinput = (yymajor==0);
#endif

  yyact = yypParser->yytos->stateno;
#ifndef NDEBUG
  if( yyTraceFILE ){
    if( yyact < YY_MIN_REDUCE ){
      fprintf(yyTraceFILE,"%sInput '%s' in state %d\n",
              yyTracePrompt,yyTokenName[yymajor],yyact);
    }else{
      fprintf(yyTraceFILE,"%sInput '%s' with pending reduce %d\n",
              yyTracePrompt,yyTokenName[yymajor],yyact-YY_MIN_REDUCE);
    }
  }
#endif

  do{
    assert( yyact==yypParser->yytos->stateno );
    yyact = yy_find_shift_action((YYCODETYPE)yymajor,yyact);
    if( yyact >= YY_MIN_REDUCE ){
      yyact = yy_reduce(yypParser,yyact-YY_MIN_REDUCE,yymajor,
                        yyminor ImplParseCTX_PARAM);
    }else if( yyact <= YY_MAX_SHIFTREDUCE ){
      yy_shift(yypParser,yyact,(YYCODETYPE)yymajor,yyminor);
#ifndef YYNOERRORRECOVERY
      yypParser->yyerrcnt--;
#endif
      break;
    }else if( yyact==YY_ACCEPT_ACTION ){
      yypParser->yytos--;
      yy_accept(yypParser);
      return;
    }else{
      assert( yyact == YY_ERROR_ACTION );
      yyminorunion.yy0 = yyminor;
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminor);
      }
      yymx = yypParser->yytos->major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor, &yyminorunion);
        yymajor = YYNOCODE;
      }else{
        while( yypParser->yytos >= yypParser->yystack
            && yymx != YYERRORSYMBOL
            && (yyact = yy_find_reduce_action(
                        yypParser->yytos->stateno,
                        YYERRORSYMBOL)) >= YY_MIN_REDUCE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yytos < yypParser->yystack || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
#ifndef YYNOERRORRECOVERY
          yypParser->yyerrcnt = -1;
#endif
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          yy_shift(yypParser,yyact,YYERRORSYMBOL,yyminor);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
      if( yymajor==YYNOCODE ) break;
      yyact = yypParser->yytos->stateno;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor, yyminor);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      break;
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor, yyminor);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
#ifndef YYNOERRORRECOVERY
        yypParser->yyerrcnt = -1;
#endif
      }
      break;
#endif
    }
  }while( yypParser->yytos>yypParser->yystack );
#ifndef NDEBUG
  if( yyTraceFILE ){
    yyStackEntry *i;
    char cDiv = '[';
    fprintf(yyTraceFILE,"%sReturn. Stack=",yyTracePrompt);
    for(i=&yypParser->yystack[1]; i<=yypParser->yytos; i++){
      fprintf(yyTraceFILE,"%c%s", cDiv, yyTokenName[i->major]);
      cDiv = ' ';
    }
    fprintf(yyTraceFILE,"]\n");
  }
#endif
  return;
}

/*
** Return the fallback token corresponding to canonical token iToken, or
** 0 if iToken has no fallback.
*/
int ImplParseFallback(int iToken){
#ifdef YYFALLBACK
  if( iToken<(int)(sizeof(yyFallback)/sizeof(yyFallback[0])) ){
    return yyFallback[iToken];
  }
#else
  (void)iToken;
#endif
  return 0;
}
