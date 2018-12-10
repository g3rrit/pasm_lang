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
#include <assert.h>
/************ Begin %include sections from the grammar ************************/
#line 1 "./parser/grammar.y"

#include "exp.h"
#include "token_types.h"
#include "cassert"
#include "lexer.h"
#include "util.h"

using namespace tree;
#line 38 "./parser/out/grammar.c"
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
#define YYNOCODE 96
#define YYACTIONTYPE unsigned short int
#define ImplParseTOKENTYPE token*
typedef union {
  int yyinit;
  ImplParseTOKENTYPE yy0;
  float_token* yy17;
  infix_scalar_exp* yy42;
  exp* yy52;
  int_token* yy70;
  string_token* yy150;
  id_token* yy180;
  ref_exp* yy184;
  scalar_exp* yy189;
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
#define YYNSTATE             66
#define YYNRULE              81
#define YYNTOKEN             64
#define YY_MAX_SHIFT         65
#define YY_MIN_SHIFTREDUCE   127
#define YY_MAX_SHIFTREDUCE   207
#define YY_ERROR_ACTION      208
#define YY_ACCEPT_ACTION     209
#define YY_NO_ACTION         210
#define YY_MIN_REDUCE        211
#define YY_MAX_REDUCE        291
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
#define YY_ACTTAB_COUNT (311)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   267,  274,  264,  265,  261,   39,  275,   42,   50,   49,
 /*    10 */    63,   62,   60,  263,  267,  274,  264,  265,  262,   39,
 /*    20 */   275,   42,   50,   49,   63,   62,   60,  263,  267,  274,
 /*    30 */   257,  209,   18,   38,  275,   42,   50,   49,   63,   62,
 /*    40 */    60,  258,  267,  274,  257,   23,   24,   38,  275,   42,
 /*    50 */    50,   49,   63,   62,   60,  258,  274,  248,   22,   21,
 /*    60 */   133,  275,   42,   50,   49,   63,   59,  267,  274,  257,
 /*    70 */   168,   52,   38,  275,   42,   50,   49,   63,   62,   60,
 /*    80 */   258,  160,  171,   65,    2,  145,  146,  147,  148,  149,
 /*    90 */   150,  151,  152,  153,  154,  274,  247,  168,  176,  157,
 /*   100 */   275,   42,   50,   49,   63,   62,   60,   53,  274,  168,
 /*   110 */   165,  166,  167,  275,   42,   46,   14,  267,   27,   30,
 /*   120 */     1,  274,   37,   45,   34,  168,  275,   42,   50,   49,
 /*   130 */    63,   62,   60,  273,  274,  143,  158,   58,  168,  275,
 /*   140 */    42,   50,   49,   63,   62,   60,  272,  274,   55,  271,
 /*   150 */   143,  274,  275,   40,  246,   29,  275,   42,   50,   49,
 /*   160 */    63,   62,   60,  278,  243,    5,  274,    4,   58,   54,
 /*   170 */     3,  275,   42,   50,   49,   63,   62,   60,  277,  171,
 /*   180 */   170,  169,  274,  270,  175,  144,  225,  275,   42,   50,
 /*   190 */    49,   63,   62,   60,  276,  274,   57,   26,  143,   15,
 /*   200 */   275,   42,   50,   49,   63,   62,   60,   64,   57,  168,
 /*   210 */    32,   19,   13,  211,   16,  240,   28,  239,  274,   44,
 /*   220 */    25,   45,   57,  275,   41,  168,  140,  240,   28,  239,
 /*   230 */    16,   56,  168,   45,  171,  170,  213,  214,   33,  216,
 /*   240 */    28,  240,   28,  239,  274,   43,   20,   45,   15,  275,
 /*   250 */    42,   50,   49,   61,  274,   58,    7,    8,   58,  275,
 /*   260 */    42,   50,   47,  210,   12,  210,   32,  184,   36,   35,
 /*   270 */    27,    6,  274,  219,    7,    8,  226,  275,   42,   48,
 /*   280 */   168,  222,   12,   10,    9,   16,   36,   35,   51,   11,
 /*   290 */   220,   58,   31,  185,   17,  210,  210,  210,  210,  210,
 /*   300 */   210,  210,  210,  210,  210,  210,  210,  210,  210,  218,
 /*   310 */   139,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    64,   65,   66,   67,   68,   69,   70,   71,   72,   73,
 /*    10 */    74,   75,   76,   77,   64,   65,   66,   67,   68,   69,
 /*    20 */    70,   71,   72,   73,   74,   75,   76,   77,   64,   65,
 /*    30 */    66,   78,   79,   69,   70,   71,   72,   73,   74,   75,
 /*    40 */    76,   77,   64,   65,   66,   40,   41,   69,   70,   71,
 /*    50 */    72,   73,   74,   75,   76,   77,   65,   93,   36,   37,
 /*    60 */    47,   70,   71,   72,   73,   74,   75,   64,   65,   66,
 /*    70 */    57,   93,   69,   70,   71,   72,   73,   74,   75,   76,
 /*    80 */    77,   29,   11,    2,   33,   17,   18,   19,   20,   21,
 /*    90 */    22,   23,   24,   25,   26,   65,   93,   57,   47,   47,
 /*   100 */    70,   71,   72,   73,   74,   75,   76,   77,   65,   57,
 /*   110 */    58,   59,   60,   70,   71,   72,   48,   64,   50,   85,
 /*   120 */    46,   65,   69,   89,   33,   57,   70,   71,   72,   73,
 /*   130 */    74,   75,   76,   77,   65,   44,   46,   64,   57,   70,
 /*   140 */    71,   72,   73,   74,   75,   76,   77,   65,   65,   64,
 /*   150 */    44,   65,   70,   71,   81,   82,   70,   71,   72,   73,
 /*   160 */    74,   75,   76,   77,   91,   92,   65,   94,   64,   63,
 /*   170 */    33,   70,   71,   72,   73,   74,   75,   76,   77,   11,
 /*   180 */    12,   13,   65,   64,   49,   49,   82,   70,   71,   72,
 /*   190 */    73,   74,   75,   76,   77,   65,   64,   50,   44,   28,
 /*   200 */    70,   71,   72,   73,   74,   75,   76,   77,   64,   57,
 /*   210 */    46,   35,   34,    0,   62,   83,   84,   85,   65,   87,
 /*   220 */    64,   89,   64,   70,   71,   57,   51,   83,   84,   85,
 /*   230 */    62,   87,   57,   89,   11,   12,   80,   81,   82,   83,
 /*   240 */    84,   83,   84,   85,   65,   87,   45,   89,   28,   70,
 /*   250 */    71,   72,   73,   74,   65,   64,   40,   41,   64,   70,
 /*   260 */    71,   72,   73,   96,   48,   96,   46,   51,   52,   53,
 /*   270 */    50,   48,   65,   82,   40,   41,   82,   70,   71,   72,
 /*   280 */    57,   88,   48,   38,   39,   62,   52,   53,   95,   44,
 /*   290 */    86,   64,   33,   49,   90,   96,   96,   96,   96,   96,
 /*   300 */    96,   96,   96,   96,   96,   96,   96,   96,   96,   82,
 /*   310 */    51,   96,   96,   96,   96,   96,   96,   96,   96,   96,
 /*   320 */    96,   96,   96,   96,   96,   96,   96,   96,   96,   96,
 /*   330 */    96,   96,   96,   96,   96,   96,   96,   96,   96,   96,
 /*   340 */    96,   96,   96,   96,   96,   96,   96,   96,   96,   96,
 /*   350 */    96,   96,   96,   96,   96,   96,   96,   96,
};
#define YY_SHIFT_COUNT    (65)
#define YY_SHIFT_MIN      (0)
#define YY_SHIFT_MAX      (259)
static const unsigned short int yy_shift_ofst[] = {
 /*     0 */   311,  168,  168,  223,  223,  223,   71,   71,   71,   71,
 /*    10 */    71,   71,   71,   71,   68,   68,   68,   52,   81,   71,
 /*    20 */    71,   71,   71,   71,   71,  220,  152,  175,   13,   74,
 /*    30 */    90,   40,   40,   74,   71,   40,   40,  216,  234,  234,
 /*    40 */   245,  245,  245,  106,   91,  259,    5,   22,    5,   22,
 /*    50 */     5,   51,  137,  135,  147,  136,  154,  164,  171,  176,
 /*    60 */   178,  201,  176,  201,  244,  213,
};
#define YY_REDUCE_COUNT (36)
#define YY_REDUCE_MIN   (-64)
#define YY_REDUCE_MAX   (227)
static const short yy_reduce_ofst[] = {
 /*     0 */   -47,  -64,  -50,  -36,  -22,    3,   30,   56,   69,   86,
 /*    10 */   101,  117,  130,   -9,  132,  144,  158,   73,  156,  179,
 /*    20 */   189,   43,  207,   82,  153,   34,   53,  104,  191,  193,
 /*    30 */   204,  194,  227,  193,   83,   85,  119,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   212,  208,  208,  208,  208,  208,  208,  208,  208,  208,
 /*    10 */   208,  208,  208,  208,  208,  208,  208,  208,  208,  208,
 /*    20 */   208,  208,  208,  208,  208,  208,  208,  208,  208,  245,
 /*    30 */   208,  208,  208,  215,  208,  208,  208,  208,  256,  266,
 /*    40 */   281,  280,  279,  208,  208,  208,  284,  286,  283,  285,
 /*    50 */   282,  208,  208,  208,  208,  208,  221,  208,  208,  290,
 /*    60 */   291,  288,  289,  287,  208,  208,
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
  /*    1 */ "T_WHITESPACE",
  /*    2 */ "T_END",
  /*    3 */ "T_OTHER",
  /*    4 */ "T_TAB",
  /*    5 */ "T_NEW_LINE",
  /*    6 */ "T_CARRIAGE_RETURN",
  /*    7 */ "T_CHAR",
  /*    8 */ "T_MULTICHAR",
  /*    9 */ "T_LINE_COMMENT",
  /*   10 */ "T_MULTILINE_COMMENT",
  /*   11 */ "T_INTEGER",
  /*   12 */ "T_FLOAT",
  /*   13 */ "T_STRING",
  /*   14 */ "T_USE",
  /*   15 */ "T_AS",
  /*   16 */ "T_RET",
  /*   17 */ "T_U8",
  /*   18 */ "T_U16",
  /*   19 */ "T_U32",
  /*   20 */ "T_U64",
  /*   21 */ "T_I8",
  /*   22 */ "T_I16",
  /*   23 */ "T_I32",
  /*   24 */ "T_I64",
  /*   25 */ "T_F32",
  /*   26 */ "T_F64",
  /*   27 */ "T_EXCALAMATIONMARK_EQUALS",
  /*   28 */ "T_COLON",
  /*   29 */ "T_SEMICOLON",
  /*   30 */ "T_EXCLAMATIONMARK",
  /*   31 */ "T_QUESTIONMARK",
  /*   32 */ "T_EXP",
  /*   33 */ "T_COMMA",
  /*   34 */ "T_PIPE",
  /*   35 */ "T_CIRCUMFLEX",
  /*   36 */ "T_DOUBLE_LESS_THAN",
  /*   37 */ "T_DOUBLE_GREATER_THAN",
  /*   38 */ "T_SLASH",
  /*   39 */ "T_PERCENT",
  /*   40 */ "T_MINUS",
  /*   41 */ "T_PLUS",
  /*   42 */ "T_EXCLAMATION_MARK",
  /*   43 */ "T_TILDE",
  /*   44 */ "T_ASTERIX",
  /*   45 */ "T_AMPERSAND",
  /*   46 */ "T_L_C_BRACKET",
  /*   47 */ "T_R_C_BRACKET",
  /*   48 */ "T_L_S_BRACKET",
  /*   49 */ "T_R_S_BRACKET",
  /*   50 */ "T_L_R_BRACKET",
  /*   51 */ "T_R_R_BRACKET",
  /*   52 */ "T_DOT",
  /*   53 */ "T_ARROW",
  /*   54 */ "T_DOUBLE_COLON",
  /*   55 */ "T_POINTER_TYPE",
  /*   56 */ "T_VOID",
  /*   57 */ "T_ID",
  /*   58 */ "T_PUSH",
  /*   59 */ "T_MOV",
  /*   60 */ "T_ADD",
  /*   61 */ "EXP",
  /*   62 */ "T_LESS_THAN",
  /*   63 */ "T_GREATER_THAN",
  /*   64 */ "id",
  /*   65 */ "integer",
  /*   66 */ "float",
  /*   67 */ "string",
  /*   68 */ "exp",
  /*   69 */ "ref_exp",
  /*   70 */ "scalar_exp_int",
  /*   71 */ "multiplicative_exp",
  /*   72 */ "additive_exp",
  /*   73 */ "shift_exp",
  /*   74 */ "and_exp",
  /*   75 */ "exclusive_or_exp",
  /*   76 */ "inclusive_or_exp",
  /*   77 */ "scalar_exp",
  /*   78 */ "package",
  /*   79 */ "package_opt",
  /*   80 */ "function_def",
  /*   81 */ "var_def",
  /*   82 */ "var_decl",
  /*   83 */ "struct_def",
  /*   84 */ "struct_def_opt",
  /*   85 */ "function_type",
  /*   86 */ "block_statement",
  /*   87 */ "type",
  /*   88 */ "literal",
  /*   89 */ "function_type_opt",
  /*   90 */ "block_statement_opt",
  /*   91 */ "statement",
  /*   92 */ "u_mnemonic",
  /*   93 */ "operand",
  /*   94 */ "d_mnemonic",
  /*   95 */ "literal_opt",
};
#endif /* defined(YYCOVERAGE) || !defined(NDEBUG) */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "package ::= package_opt T_END",
 /*   1 */ "package_opt ::=",
 /*   2 */ "package_opt ::= package_opt function_def",
 /*   3 */ "package_opt ::= package_opt var_def",
 /*   4 */ "package_opt ::= package_opt var_decl",
 /*   5 */ "package_opt ::= package_opt struct_def",
 /*   6 */ "struct_def ::= struct_def_opt T_R_C_BRACKET",
 /*   7 */ "struct_def_opt ::= id T_L_C_BRACKET var_decl",
 /*   8 */ "struct_def_opt ::= struct_def_opt var_decl",
 /*   9 */ "function_def ::= id function_type block_statement",
 /*  10 */ "var_decl ::= id T_COLON type",
 /*  11 */ "var_def ::= var_decl literal",
 /*  12 */ "function_type ::= function_type_opt T_R_R_BRACKET",
 /*  13 */ "function_type ::= T_L_R_BRACKET T_R_R_BRACKET",
 /*  14 */ "function_type_opt ::= T_L_R_BRACKET var_decl",
 /*  15 */ "function_type_opt ::= function_type_opt T_COMMA var_decl",
 /*  16 */ "type ::= type T_ASTERIX",
 /*  17 */ "type ::= T_L_S_BRACKET type T_COMMA integer T_R_S_BRACKET",
 /*  18 */ "type ::= T_U8",
 /*  19 */ "type ::= T_U16",
 /*  20 */ "type ::= T_U32",
 /*  21 */ "type ::= T_U64",
 /*  22 */ "type ::= T_I8",
 /*  23 */ "type ::= T_I16",
 /*  24 */ "type ::= T_I32",
 /*  25 */ "type ::= T_I64",
 /*  26 */ "type ::= T_F32",
 /*  27 */ "type ::= T_F64",
 /*  28 */ "type ::= function_type",
 /*  29 */ "type ::= struct_def",
 /*  30 */ "block_statement ::= block_statement_opt T_R_C_BRACKET",
 /*  31 */ "block_statement_opt ::= T_L_C_BRACKET",
 /*  32 */ "block_statement_opt ::= block_statement_opt statement",
 /*  33 */ "statement ::= T_SEMICOLON",
 /*  34 */ "statement ::= var_decl",
 /*  35 */ "statement ::= var_def",
 /*  36 */ "statement ::= u_mnemonic operand",
 /*  37 */ "statement ::= d_mnemonic operand T_COMMA operand",
 /*  38 */ "u_mnemonic ::= T_PUSH",
 /*  39 */ "d_mnemonic ::= T_MOV",
 /*  40 */ "d_mnemonic ::= T_ADD",
 /*  41 */ "id ::= T_ID",
 /*  42 */ "string ::= T_STRING",
 /*  43 */ "float ::= T_FLOAT",
 /*  44 */ "integer ::= T_INTEGER",
 /*  45 */ "operand ::= ref_exp",
 /*  46 */ "operand ::= float",
 /*  47 */ "operand ::= scalar_exp",
 /*  48 */ "operand ::= T_L_S_BRACKET scalar_exp T_R_S_BRACKET",
 /*  49 */ "literal ::= literal_opt T_R_C_BRACKET",
 /*  50 */ "literal_opt ::= T_L_C_BRACKET exp",
 /*  51 */ "literal_opt ::= literal_opt T_COMMA exp",
 /*  52 */ "exp ::= scalar_exp",
 /*  53 */ "exp ::= float",
 /*  54 */ "exp ::= string",
 /*  55 */ "exp ::= ref_exp",
 /*  56 */ "ref_exp ::= id",
 /*  57 */ "ref_exp ::= T_LESS_THAN type T_GREATER_THAN T_L_R_BRACKET ref_exp T_R_R_BRACKET",
 /*  58 */ "ref_exp ::= ref_exp T_L_S_BRACKET scalar_exp T_R_S_BRACKET",
 /*  59 */ "ref_exp ::= ref_exp T_DOT id",
 /*  60 */ "ref_exp ::= ref_exp T_ARROW id",
 /*  61 */ "ref_exp ::= ref_exp T_PLUS scalar_exp",
 /*  62 */ "ref_exp ::= ref_exp T_MINUS scalar_exp",
 /*  63 */ "scalar_exp_int ::= integer",
 /*  64 */ "multiplicative_exp ::= scalar_exp_int",
 /*  65 */ "multiplicative_exp ::= multiplicative_exp T_ASTERIX scalar_exp",
 /*  66 */ "multiplicative_exp ::= multiplicative_exp T_SLASH scalar_exp",
 /*  67 */ "multiplicative_exp ::= multiplicative_exp T_PERCENT scalar_exp",
 /*  68 */ "additive_exp ::= multiplicative_exp",
 /*  69 */ "additive_exp ::= additive_exp T_PLUS multiplicative_exp",
 /*  70 */ "additive_exp ::= additive_exp T_MINUS multiplicative_exp",
 /*  71 */ "shift_exp ::= additive_exp",
 /*  72 */ "shift_exp ::= shift_exp T_DOUBLE_LESS_THAN additive_exp",
 /*  73 */ "shift_exp ::= shift_exp T_DOUBLE_GREATER_THAN additive_exp",
 /*  74 */ "and_exp ::= shift_exp",
 /*  75 */ "and_exp ::= and_exp T_AMPERSAND shift_exp",
 /*  76 */ "exclusive_or_exp ::= and_exp",
 /*  77 */ "exclusive_or_exp ::= exclusive_or_exp T_CIRCUMFLEX and_exp",
 /*  78 */ "inclusive_or_exp ::= exclusive_or_exp",
 /*  79 */ "inclusive_or_exp ::= inclusive_or_exp T_PIPE exclusive_or_exp",
 /*  80 */ "scalar_exp ::= inclusive_or_exp",
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

/* For rule J, yyRuleInfoLhs[J] contains the symbol on the left-hand side
** of that rule */
static const YYCODETYPE yyRuleInfoLhs[] = {
  {   78,   -2 }, /* (0) package ::= package_opt T_END */
  {   79,    0 }, /* (1) package_opt ::= */
  {   79,   -2 }, /* (2) package_opt ::= package_opt function_def */
  {   79,   -2 }, /* (3) package_opt ::= package_opt var_def */
  {   79,   -2 }, /* (4) package_opt ::= package_opt var_decl */
  {   79,   -2 }, /* (5) package_opt ::= package_opt struct_def */
  {   83,   -2 }, /* (6) struct_def ::= struct_def_opt T_R_C_BRACKET */
  {   84,   -3 }, /* (7) struct_def_opt ::= id T_L_C_BRACKET var_decl */
  {   84,   -2 }, /* (8) struct_def_opt ::= struct_def_opt var_decl */
  {   80,   -3 }, /* (9) function_def ::= id function_type block_statement */
  {   82,   -3 }, /* (10) var_decl ::= id T_COLON type */
  {   81,   -2 }, /* (11) var_def ::= var_decl literal */
  {   85,   -2 }, /* (12) function_type ::= function_type_opt T_R_R_BRACKET */
  {   85,   -2 }, /* (13) function_type ::= T_L_R_BRACKET T_R_R_BRACKET */
  {   89,   -2 }, /* (14) function_type_opt ::= T_L_R_BRACKET var_decl */
  {   89,   -3 }, /* (15) function_type_opt ::= function_type_opt T_COMMA var_decl */
  {   87,   -2 }, /* (16) type ::= type T_ASTERIX */
  {   87,   -5 }, /* (17) type ::= T_L_S_BRACKET type T_COMMA integer T_R_S_BRACKET */
  {   87,   -1 }, /* (18) type ::= T_U8 */
  {   87,   -1 }, /* (19) type ::= T_U16 */
  {   87,   -1 }, /* (20) type ::= T_U32 */
  {   87,   -1 }, /* (21) type ::= T_U64 */
  {   87,   -1 }, /* (22) type ::= T_I8 */
  {   87,   -1 }, /* (23) type ::= T_I16 */
  {   87,   -1 }, /* (24) type ::= T_I32 */
  {   87,   -1 }, /* (25) type ::= T_I64 */
  {   87,   -1 }, /* (26) type ::= T_F32 */
  {   87,   -1 }, /* (27) type ::= T_F64 */
  {   87,   -1 }, /* (28) type ::= function_type */
  {   87,   -1 }, /* (29) type ::= struct_def */
  {   86,   -2 }, /* (30) block_statement ::= block_statement_opt T_R_C_BRACKET */
  {   90,   -1 }, /* (31) block_statement_opt ::= T_L_C_BRACKET */
  {   90,   -2 }, /* (32) block_statement_opt ::= block_statement_opt statement */
  {   91,   -1 }, /* (33) statement ::= T_SEMICOLON */
  {   91,   -1 }, /* (34) statement ::= var_decl */
  {   91,   -1 }, /* (35) statement ::= var_def */
  {   91,   -2 }, /* (36) statement ::= u_mnemonic operand */
  {   91,   -4 }, /* (37) statement ::= d_mnemonic operand T_COMMA operand */
  {   92,   -1 }, /* (38) u_mnemonic ::= T_PUSH */
  {   94,   -1 }, /* (39) d_mnemonic ::= T_MOV */
  {   94,   -1 }, /* (40) d_mnemonic ::= T_ADD */
  {   64,   -1 }, /* (41) id ::= T_ID */
  {   67,   -1 }, /* (42) string ::= T_STRING */
  {   66,   -1 }, /* (43) float ::= T_FLOAT */
  {   65,   -1 }, /* (44) integer ::= T_INTEGER */
  {   93,   -1 }, /* (45) operand ::= ref_exp */
  {   93,   -1 }, /* (46) operand ::= float */
  {   93,   -1 }, /* (47) operand ::= scalar_exp */
  {   93,   -3 }, /* (48) operand ::= T_L_S_BRACKET scalar_exp T_R_S_BRACKET */
  {   88,   -2 }, /* (49) literal ::= literal_opt T_R_C_BRACKET */
  {   95,   -2 }, /* (50) literal_opt ::= T_L_C_BRACKET exp */
  {   95,   -3 }, /* (51) literal_opt ::= literal_opt T_COMMA exp */
  {   68,   -1 }, /* (52) exp ::= scalar_exp */
  {   68,   -1 }, /* (53) exp ::= float */
  {   68,   -1 }, /* (54) exp ::= string */
  {   68,   -1 }, /* (55) exp ::= ref_exp */
  {   69,   -1 }, /* (56) ref_exp ::= id */
  {   69,   -6 }, /* (57) ref_exp ::= T_LESS_THAN type T_GREATER_THAN T_L_R_BRACKET ref_exp T_R_R_BRACKET */
  {   69,   -4 }, /* (58) ref_exp ::= ref_exp T_L_S_BRACKET scalar_exp T_R_S_BRACKET */
  {   69,   -3 }, /* (59) ref_exp ::= ref_exp T_DOT id */
  {   69,   -3 }, /* (60) ref_exp ::= ref_exp T_ARROW id */
  {   69,   -3 }, /* (61) ref_exp ::= ref_exp T_PLUS scalar_exp */
  {   69,   -3 }, /* (62) ref_exp ::= ref_exp T_MINUS scalar_exp */
  {   70,   -1 }, /* (63) scalar_exp_int ::= integer */
  {   71,   -1 }, /* (64) multiplicative_exp ::= scalar_exp_int */
  {   71,   -3 }, /* (65) multiplicative_exp ::= multiplicative_exp T_ASTERIX scalar_exp */
  {   71,   -3 }, /* (66) multiplicative_exp ::= multiplicative_exp T_SLASH scalar_exp */
  {   71,   -3 }, /* (67) multiplicative_exp ::= multiplicative_exp T_PERCENT scalar_exp */
  {   72,   -1 }, /* (68) additive_exp ::= multiplicative_exp */
  {   72,   -3 }, /* (69) additive_exp ::= additive_exp T_PLUS multiplicative_exp */
  {   72,   -3 }, /* (70) additive_exp ::= additive_exp T_MINUS multiplicative_exp */
  {   73,   -1 }, /* (71) shift_exp ::= additive_exp */
  {   73,   -3 }, /* (72) shift_exp ::= shift_exp T_DOUBLE_LESS_THAN additive_exp */
  {   73,   -3 }, /* (73) shift_exp ::= shift_exp T_DOUBLE_GREATER_THAN additive_exp */
  {   74,   -1 }, /* (74) and_exp ::= shift_exp */
  {   74,   -3 }, /* (75) and_exp ::= and_exp T_AMPERSAND shift_exp */
  {   75,   -1 }, /* (76) exclusive_or_exp ::= and_exp */
  {   75,   -3 }, /* (77) exclusive_or_exp ::= exclusive_or_exp T_CIRCUMFLEX and_exp */
  {   76,   -1 }, /* (78) inclusive_or_exp ::= exclusive_or_exp */
  {   76,   -3 }, /* (79) inclusive_or_exp ::= inclusive_or_exp T_PIPE exclusive_or_exp */
  {   77,   -1 }, /* (80) scalar_exp ::= inclusive_or_exp */
};

/* For rule J, yyRuleInfoNRhs[J] contains the negative of the number
** of symbols on the right-hand side of that rule. */
static const signed char yyRuleInfoNRhs[] = {
        YYMINORTYPE yylhsminor;
      case 0: /* package ::= package_opt T_END */
#line 91 "./parser/grammar.y"
{
    log_debug("package ::= package_opt  END");
}
#line 1106 "./parser/out/grammar.c"
        break;
      case 1: /* package_opt ::= */
#line 95 "./parser/grammar.y"
{
    log_debug("package_opt ::= /* empty */");
}
#line 1113 "./parser/out/grammar.c"
        break;
      case 2: /* package_opt ::= package_opt function_def */
#line 98 "./parser/grammar.y"
{
    log_debug("package_opt ::= package_opt function_def");
}
#line 1120 "./parser/out/grammar.c"
        break;
      case 3: /* package_opt ::= package_opt var_def */
#line 101 "./parser/grammar.y"
{
    log_debug("package_opt ::= package_opt var_def");
}
#line 1127 "./parser/out/grammar.c"
        break;
      case 4: /* package_opt ::= package_opt var_decl */
#line 104 "./parser/grammar.y"
{
    log_debug("package_opt ::= package_opt var_decl");
}
#line 1134 "./parser/out/grammar.c"
        break;
      case 5: /* package_opt ::= package_opt struct_def */
#line 107 "./parser/grammar.y"
{
    log_debug("package_opt ::= package_opt struct_def");
}
#line 1141 "./parser/out/grammar.c"
        break;
      case 6: /* struct_def ::= struct_def_opt T_R_C_BRACKET */
#line 115 "./parser/grammar.y"
{
    log_debug("struct_def ::= struct_def_opt R_C_BRACKET");
}
#line 1148 "./parser/out/grammar.c"
        break;
      case 7: /* struct_def_opt ::= id T_L_C_BRACKET var_decl */
#line 118 "./parser/grammar.y"
{
    log_debug("struct_def_opt ::= id L_C_BRACKET var_decl");
}
#line 1155 "./parser/out/grammar.c"
        break;
      case 8: /* struct_def_opt ::= struct_def_opt var_decl */
#line 121 "./parser/grammar.y"
{
    log_debug("struct_def_opt ::= struct_def_opt var_decl");
}
#line 1162 "./parser/out/grammar.c"
        break;
      case 9: /* function_def ::= id function_type block_statement */
#line 129 "./parser/grammar.y"
{
    log_debug("function_def ::= id function_type block_statement");
}
#line 1169 "./parser/out/grammar.c"
        break;
      case 10: /* var_decl ::= id T_COLON type */
#line 139 "./parser/grammar.y"
{
    log_debug("var_decl ::= id COLON type");
}
#line 1176 "./parser/out/grammar.c"
        break;
      case 11: /* var_def ::= var_decl literal */
#line 143 "./parser/grammar.y"
{
    log_debug("var_def ::= var_decl literal");
}
#line 1183 "./parser/out/grammar.c"
        break;
      case 12: /* function_type ::= function_type_opt T_R_R_BRACKET */
#line 153 "./parser/grammar.y"
{
    log_debug("function_type ::= function_type_opt R_R_BRACKET");
}
#line 1190 "./parser/out/grammar.c"
        break;
      case 13: /* function_type ::= T_L_R_BRACKET T_R_R_BRACKET */
#line 156 "./parser/grammar.y"
{
    log_debug("function_type ::= L_R_BRACKET R_R_BRACKET");
}
#line 1197 "./parser/out/grammar.c"
        break;
      case 14: /* function_type_opt ::= T_L_R_BRACKET var_decl */
#line 160 "./parser/grammar.y"
{
    log_debug("function_type_opt ::= L_R_BRACKET var_decl");
}
#line 1204 "./parser/out/grammar.c"
        break;
      case 15: /* function_type_opt ::= function_type_opt T_COMMA var_decl */
#line 163 "./parser/grammar.y"
{
    log_debug("function_type_opt ::= function_type_opt COMMA var_decl");
}
#line 1211 "./parser/out/grammar.c"
        break;
      case 16: /* type ::= type T_ASTERIX */
#line 169 "./parser/grammar.y"
{
    log_debug("type ::= type ASTERIX . [POINTER_TYP");
}
#line 1218 "./parser/out/grammar.c"
        break;
      case 17: /* type ::= T_L_S_BRACKET type T_COMMA integer T_R_S_BRACKET */
#line 172 "./parser/grammar.y"
{
    log_debug("type ::= L_S_BRACKET type COMMA integer R_S_BRACKET");
}
#line 1225 "./parser/out/grammar.c"
        break;
      case 18: /* type ::= T_U8 */
#line 175 "./parser/grammar.y"
{
    log_debug("type ::= U8");
}
#line 1232 "./parser/out/grammar.c"
        break;
      case 19: /* type ::= T_U16 */
#line 178 "./parser/grammar.y"
{
    log_debug("type ::= U16");
}
#line 1239 "./parser/out/grammar.c"
        break;
      case 20: /* type ::= T_U32 */
#line 181 "./parser/grammar.y"
{
    log_debug("type ::= U32");
}
#line 1246 "./parser/out/grammar.c"
        break;
      case 21: /* type ::= T_U64 */
#line 184 "./parser/grammar.y"
{
    log_debug("type ::= U64");
}
#line 1253 "./parser/out/grammar.c"
        break;
      case 22: /* type ::= T_I8 */
#line 187 "./parser/grammar.y"
{
    log_debug("type ::= I8");
}
#line 1260 "./parser/out/grammar.c"
        break;
      case 23: /* type ::= T_I16 */
#line 190 "./parser/grammar.y"
{
    log_debug("type ::= I16");
}
#line 1267 "./parser/out/grammar.c"
        break;
      case 24: /* type ::= T_I32 */
#line 193 "./parser/grammar.y"
{
    log_debug("type ::= I32");
}
#line 1274 "./parser/out/grammar.c"
        break;
      case 25: /* type ::= T_I64 */
#line 196 "./parser/grammar.y"
{
    log_debug("type ::= I64");
}
#line 1281 "./parser/out/grammar.c"
        break;
      case 26: /* type ::= T_F32 */
#line 199 "./parser/grammar.y"
{
    log_debug("type ::= F32");
}
#line 1288 "./parser/out/grammar.c"
        break;
      case 27: /* type ::= T_F64 */
#line 202 "./parser/grammar.y"
{
    log_debug("type ::= F64");
}
#line 1295 "./parser/out/grammar.c"
        break;
      case 28: /* type ::= function_type */
#line 205 "./parser/grammar.y"
{
    log_debug("type ::= function_type");
}
#line 1302 "./parser/out/grammar.c"
        break;
      case 29: /* type ::= struct_def */
#line 208 "./parser/grammar.y"
{
    log_debug("type ::= struct_def");
}
#line 1309 "./parser/out/grammar.c"
        break;
      case 30: /* block_statement ::= block_statement_opt T_R_C_BRACKET */
#line 216 "./parser/grammar.y"
{
    log_debug("block_statement ::= block_statement_opt R_C_BRACKET");
}
#line 1316 "./parser/out/grammar.c"
        break;
      case 31: /* block_statement_opt ::= T_L_C_BRACKET */
#line 220 "./parser/grammar.y"
{
    log_debug("block_statement_opt ::= L_C_BRACKET");
}
#line 1323 "./parser/out/grammar.c"
        break;
      case 32: /* block_statement_opt ::= block_statement_opt statement */
#line 223 "./parser/grammar.y"
{
    log_debug("block_statement_opt ::= block_statement_opt statement");
}
#line 1330 "./parser/out/grammar.c"
        break;
      case 33: /* statement ::= T_SEMICOLON */
#line 227 "./parser/grammar.y"
{
    log_debug("statement ::= SEMICOLON");
}
#line 1337 "./parser/out/grammar.c"
        break;
      case 34: /* statement ::= var_decl */
#line 230 "./parser/grammar.y"
{
    log_debug("statement ::= var_decl");
}
#line 1344 "./parser/out/grammar.c"
        break;
      case 35: /* statement ::= var_def */
#line 233 "./parser/grammar.y"
{
    log_debug("statement ::= var_def");
}
#line 1351 "./parser/out/grammar.c"
        break;
      case 36: /* statement ::= u_mnemonic operand */
#line 236 "./parser/grammar.y"
{
    log_debug("statement ::= u_mnemonic operand");
}
#line 1358 "./parser/out/grammar.c"
        break;
      case 37: /* statement ::= d_mnemonic operand T_COMMA operand */
#line 239 "./parser/grammar.y"
{
    log_debug("statement ::= d_mnemonic operand COMMA operand");
}
#line 1365 "./parser/out/grammar.c"
        break;
      case 38: /* u_mnemonic ::= T_PUSH */
#line 243 "./parser/grammar.y"
{
    log_debug("u_mnemonic ::= PUSH");
}
#line 1372 "./parser/out/grammar.c"
        break;
      case 39: /* d_mnemonic ::= T_MOV */
#line 247 "./parser/grammar.y"
{
    log_debug("d_mnemonic ::= MOV");
}
#line 1379 "./parser/out/grammar.c"
        break;
      case 40: /* d_mnemonic ::= T_ADD */
#line 250 "./parser/grammar.y"
{
    log_debug("d_mnemonic ::= ADD");
}
#line 1386 "./parser/out/grammar.c"
        break;
      case 41: /* id ::= T_ID */
#line 261 "./parser/grammar.y"
{
    log_debug("id ::= ID");
    yylhsminor.yy180 = static_cast<id_token*>(*yymsp[0].minor.yy0);
}
#line 1394 "./parser/out/grammar.c"
  yymsp[0].minor.yy180 = yylhsminor.yy180;
        break;
      case 42: /* string ::= T_STRING */
#line 265 "./parser/grammar.y"
{
    log_debug("string ::= STRING");
    yylhsminor.yy150 = static_cast<string_token*>(*yymsp[0].minor.yy0);
}
#line 1403 "./parser/out/grammar.c"
  yymsp[0].minor.yy150 = yylhsminor.yy150;
        break;
      case 43: /* float ::= T_FLOAT */
#line 269 "./parser/grammar.y"
{
    log_debug("float ::= FLOAT");
    yylhsminor.yy17 = static_cast<float_token*>(*yymsp[0].minor.yy0);
}
#line 1412 "./parser/out/grammar.c"
  yymsp[0].minor.yy17 = yylhsminor.yy17;
        break;
      case 44: /* integer ::= T_INTEGER */
#line 273 "./parser/grammar.y"
{
    log_debug("integer ::= INTEGER");
    yylhsminor.yy70 = static_cast<int_token*>(*yymsp[0].minor.yy0);
}
#line 1421 "./parser/out/grammar.c"
  yymsp[0].minor.yy70 = yylhsminor.yy70;
        break;
      case 45: /* operand ::= ref_exp */
#line 280 "./parser/grammar.y"
{
    log_debug("operand ::= ref_exp");
}
#line 1429 "./parser/out/grammar.c"
        break;
      case 46: /* operand ::= float */
#line 283 "./parser/grammar.y"
{
    log_debug("operand ::= float");
}
#line 1436 "./parser/out/grammar.c"
        break;
      case 47: /* operand ::= scalar_exp */
#line 286 "./parser/grammar.y"
{
    log_debug("operand ::= scalar_exp");
}
#line 1443 "./parser/out/grammar.c"
        break;
      case 48: /* operand ::= T_L_S_BRACKET scalar_exp T_R_S_BRACKET */
#line 289 "./parser/grammar.y"
{
    log_debug("operand ::= L_S_BRACKET scalar_exp R_S_BRACKET");
}
#line 1450 "./parser/out/grammar.c"
        break;
      case 49: /* literal ::= literal_opt T_R_C_BRACKET */
#line 295 "./parser/grammar.y"
{
    log_debug("literal ::= literal_opt R_C_BRACKET");
}
#line 1457 "./parser/out/grammar.c"
        break;
      case 50: /* literal_opt ::= T_L_C_BRACKET exp */
#line 299 "./parser/grammar.y"
{
    log_debug("literal_opt ::= L_C_BRACKET exp");
}
#line 1464 "./parser/out/grammar.c"
        break;
      case 51: /* literal_opt ::= literal_opt T_COMMA exp */
#line 302 "./parser/grammar.y"
{
    log_debug("literal_opt ::= literal_opt COMMA exp");
}
#line 1471 "./parser/out/grammar.c"
        break;
      case 52: /* exp ::= scalar_exp */
#line 308 "./parser/grammar.y"
{
    log_debug("exp ::= scalar_exp");
    yylhsminor.yy52 = yymsp[0].minor.yy42;
}
#line 1479 "./parser/out/grammar.c"
  yymsp[0].minor.yy52 = yylhsminor.yy52;
        break;
      case 53: /* exp ::= float */
#line 312 "./parser/grammar.y"
{
    log_debug("exp ::= float");
    yylhsminor.yy52 = new float_exp(yymsp[0].minor.yy17);
}
#line 1488 "./parser/out/grammar.c"
  yymsp[0].minor.yy52 = yylhsminor.yy52;
        break;
      case 54: /* exp ::= string */
#line 316 "./parser/grammar.y"
{
    log_debug("exp ::= string");
    yylhsminor.yy52 = new string_exp(yymsp[0].minor.yy150);
}
#line 1497 "./parser/out/grammar.c"
  yymsp[0].minor.yy52 = yylhsminor.yy52;
        break;
      case 55: /* exp ::= ref_exp */
#line 320 "./parser/grammar.y"
{
    log_debug("exp ::= ref_exp");
    yylhsminor.yy52 = yymsp[0].minor.yy184;
}
#line 1506 "./parser/out/grammar.c"
  yymsp[0].minor.yy52 = yylhsminor.yy52;
        break;
      case 56: /* ref_exp ::= id */
#line 327 "./parser/grammar.y"
{
    log_debug("ref_exp ::= id");
    yylhsminor.yy184 = new id_exp(yymsp[0].minor.yy180);
}
#line 1515 "./parser/out/grammar.c"
  yymsp[0].minor.yy184 = yylhsminor.yy184;
        break;
      case 57: /* ref_exp ::= T_LESS_THAN type T_GREATER_THAN T_L_R_BRACKET ref_exp T_R_R_BRACKET */
#line 331 "./parser/grammar.y"
{
    log_debug("ref_exp ::= CAST LESS_THAN type GREATER_THAN L_R_BRACKET ref_exp R_R_BRACKET");
    yymsp[-5].minor.yy184 = new cast_exp(yymsp[-1].minor.yy184, yymsp[-4].minor.yy0);
}
#line 1524 "./parser/out/grammar.c"
        break;
      case 58: /* ref_exp ::= ref_exp T_L_S_BRACKET scalar_exp T_R_S_BRACKET */
#line 335 "./parser/grammar.y"
{
    log_debug("ref_exp ::= ref_exp L_S_BRACKET scalar_exp R_S_BRACKET");
    yylhsminor.yy184 = new acc_exp(yymsp[-3].minor.yy184, yymsp[-1].minor.yy42);
}
#line 1532 "./parser/out/grammar.c"
  yymsp[-3].minor.yy184 = yylhsminor.yy184;
        break;
      case 59: /* ref_exp ::= ref_exp T_DOT id */
#line 339 "./parser/grammar.y"
{
    log_debug("ref_exp ::= ref_exp DOT id");
    yylhsminor.yy184 = new ref_acc_exp(yymsp[-2].minor.yy184, yymsp[0].minor.yy180, ref_acc_exp::REF_OP::DOT);
}
#line 1541 "./parser/out/grammar.c"
  yymsp[-2].minor.yy184 = yylhsminor.yy184;
        break;
      case 60: /* ref_exp ::= ref_exp T_ARROW id */
#line 343 "./parser/grammar.y"
{
    log_debug("ref_exp ::= ref_exp ARROW id");
    yylhsminor.yy184 = new ref_acc_exp(yymsp[-2].minor.yy184, yymsp[0].minor.yy180, ref_acc_exp::REF_OP::ARROW);
}
#line 1550 "./parser/out/grammar.c"
  yymsp[-2].minor.yy184 = yylhsminor.yy184;
        break;
      case 61: /* ref_exp ::= ref_exp T_PLUS scalar_exp */
#line 347 "./parser/grammar.y"
{
    log_debug("ref_exp ::= ref_exp PLUS scalar_exp");
    yylhsminor.yy184 = new ref_off_exp(yymsp[-2].minor.yy184, yymsp[0].minor.yy42, ref_off_exp::REF_OP::PLUS);
}
#line 1559 "./parser/out/grammar.c"
  yymsp[-2].minor.yy184 = yylhsminor.yy184;
        break;
      case 62: /* ref_exp ::= ref_exp T_MINUS scalar_exp */
#line 351 "./parser/grammar.y"
{
    log_debug("ref_exp ::= ref_exp MINUS scalar_exp");
    yylhsminor.yy184 = new ref_off_exp(yymsp[-2].minor.yy184, yymsp[0].minor.yy42, ref_off_exp::REF_OP::MINUS);
}
#line 1568 "./parser/out/grammar.c"
  yymsp[-2].minor.yy184 = yylhsminor.yy184;
        break;
      case 63: /* scalar_exp_int ::= integer */
#line 358 "./parser/grammar.y"
{
    log_debug("scalar_exp_int ::= integer");
    yylhsminor.yy189 = new int_exp(yymsp[0].minor.yy70);
}
#line 1577 "./parser/out/grammar.c"
  yymsp[0].minor.yy189 = yylhsminor.yy189;
        break;
      case 64: /* multiplicative_exp ::= scalar_exp_int */
#line 363 "./parser/grammar.y"
{
    log_debug("multiplicative_exp ::= scalar_exp_int");
    yylhsminor.yy42 = yymsp[0].minor.yy189;
}
#line 1586 "./parser/out/grammar.c"
  yymsp[0].minor.yy42 = yylhsminor.yy42;
        break;
      case 65: /* multiplicative_exp ::= multiplicative_exp T_ASTERIX scalar_exp */
#line 367 "./parser/grammar.y"
{
    log_debug("multiplicative_exp ::= multiplicative_exp ASTERIX scalar_ex");
    yylhsminor.yy42 = new infix_scalar_exp(yymsp[-2].minor.yy42, yymsp[0].minor.yy42, infix_scalar_exp::INFIX_OP::TIMES);
}
#line 1595 "./parser/out/grammar.c"
  yymsp[-2].minor.yy42 = yylhsminor.yy42;
        break;
      case 66: /* multiplicative_exp ::= multiplicative_exp T_SLASH scalar_exp */
#line 371 "./parser/grammar.y"
{
    log_debug("multiplicative_exp ::= multiplicative_exp SLASH scalar_exp");
    yylhsminor.yy42 =new infix_scalar_exp(yymsp[-2].minor.yy42, yymsp[0].minor.yy42, infix_scalar_exp::INFIX_OP::DIV);
}
#line 1604 "./parser/out/grammar.c"
  yymsp[-2].minor.yy42 = yylhsminor.yy42;
        break;
      case 67: /* multiplicative_exp ::= multiplicative_exp T_PERCENT scalar_exp */
#line 375 "./parser/grammar.y"
{
    log_debug("multiplicative_exp ::= multiplicative_exp PERCENT scalar_exp");
    yylhsminor.yy42 = new infix_scalar_exp(yymsp[-2].minor.yy42, yymsp[0].minor.yy42, infix_scalar_exp::INFIX_OP::MOD);
}
#line 1613 "./parser/out/grammar.c"
  yymsp[-2].minor.yy42 = yylhsminor.yy42;
        break;
      case 68: /* additive_exp ::= multiplicative_exp */
#line 380 "./parser/grammar.y"
{
    log_debug("additive_exp ::= multiplicative_exp");
    yylhsminor.yy42 = yymsp[0].minor.yy42;
}
#line 1622 "./parser/out/grammar.c"
  yymsp[0].minor.yy42 = yylhsminor.yy42;
        break;
      case 69: /* additive_exp ::= additive_exp T_PLUS multiplicative_exp */
#line 384 "./parser/grammar.y"
{
    log_debug("additive_exp ::= additive_exp PLUS multiplicative_exp");
    yylhsminor.yy42 = new infix_scalar_exp(yymsp[-2].minor.yy42, yymsp[0].minor.yy42, infix_scalar_exp::INFIX_OP::PLUS);
}
#line 1631 "./parser/out/grammar.c"
  yymsp[-2].minor.yy42 = yylhsminor.yy42;
        break;
      case 70: /* additive_exp ::= additive_exp T_MINUS multiplicative_exp */
#line 388 "./parser/grammar.y"
{
    log_debug("additive_exp ::= additive_exp MINUS multiplicative_exp");
    yylhsminor.yy42 = new infix_scalar_exp(yymsp[-2].minor.yy42, yymsp[0].minor.yy42, infix_scalar_exp::INFIX_OP::MINUS);
}
#line 1640 "./parser/out/grammar.c"
  yymsp[-2].minor.yy42 = yylhsminor.yy42;
        break;
      case 71: /* shift_exp ::= additive_exp */
#line 393 "./parser/grammar.y"
{
    log_debug("shift_exp ::= additive_exp");
    yylhsminor.yy42 = yymsp[0].minor.yy42;
}
#line 1649 "./parser/out/grammar.c"
  yymsp[0].minor.yy42 = yylhsminor.yy42;
        break;
      case 72: /* shift_exp ::= shift_exp T_DOUBLE_LESS_THAN additive_exp */
#line 397 "./parser/grammar.y"
{
    log_debug("shift_exp ::= shift_exp DOUBLE_LESS_THAN additive_exp");
    yylhsminor.yy42 = new infix_scalar_exp(yymsp[-2].minor.yy42, yymsp[0].minor.yy42, infix_scalar_exp::INFIX_OP::SHIFT_LEFT);
}
#line 1658 "./parser/out/grammar.c"
  yymsp[-2].minor.yy42 = yylhsminor.yy42;
        break;
      case 73: /* shift_exp ::= shift_exp T_DOUBLE_GREATER_THAN additive_exp */
#line 401 "./parser/grammar.y"
{
    log_debug("shift_exp ::= shift_exp DOUBLE_GREATER_THAN additive_exp");
    yylhsminor.yy42 = new infix_scalar_exp(yymsp[-2].minor.yy42, yymsp[0].minor.yy42, infix_scalar_exp::INFIX_OP::SHIFT_RIGHT);
}
#line 1667 "./parser/out/grammar.c"
  yymsp[-2].minor.yy42 = yylhsminor.yy42;
        break;
      case 74: /* and_exp ::= shift_exp */
#line 406 "./parser/grammar.y"
{
    log_debug("and_exp ::= shift_exp");
    yylhsminor.yy42 = yymsp[0].minor.yy42;
}
#line 1676 "./parser/out/grammar.c"
  yymsp[0].minor.yy42 = yylhsminor.yy42;
        break;
      case 75: /* and_exp ::= and_exp T_AMPERSAND shift_exp */
#line 410 "./parser/grammar.y"
{
    log_debug("and_exp ::= and_exp T_AMPERSAND shift_exp");
    yylhsminor.yy42 = new infix_scalar_exp(yymsp[-2].minor.yy42, yymsp[0].minor.yy42, infix_scalar_exp::INFIX_OP::AND);
}
#line 1685 "./parser/out/grammar.c"
  yymsp[-2].minor.yy42 = yylhsminor.yy42;
        break;
      case 76: /* exclusive_or_exp ::= and_exp */
#line 415 "./parser/grammar.y"
{
    log_debug("exclusive_or_exp ::= and_exp");
    yylhsminor.yy42 = yymsp[0].minor.yy42;
}
#line 1694 "./parser/out/grammar.c"
  yymsp[0].minor.yy42 = yylhsminor.yy42;
        break;
      case 77: /* exclusive_or_exp ::= exclusive_or_exp T_CIRCUMFLEX and_exp */
#line 419 "./parser/grammar.y"
{
    log_debug("exclusive_or_exp ::= exclusive_or_exp CIRCUMFLEX and_exp");
    yylhsminor.yy42 = new infix_scalar_exp(yymsp[-2].minor.yy42, yymsp[0].minor.yy42, infix_scalar_exp::INFIX_OP::NOR);
}
#line 1703 "./parser/out/grammar.c"
  yymsp[-2].minor.yy42 = yylhsminor.yy42;
        break;
      case 78: /* inclusive_or_exp ::= exclusive_or_exp */
#line 424 "./parser/grammar.y"
{
    log_debug("inclusive_or_exp ::= exclusive_or_exp");
    yylhsminor.yy42 = yymsp[0].minor.yy42;
}
#line 1712 "./parser/out/grammar.c"
  yymsp[0].minor.yy42 = yylhsminor.yy42;
        break;
      case 79: /* inclusive_or_exp ::= inclusive_or_exp T_PIPE exclusive_or_exp */
#line 428 "./parser/grammar.y"
{
    log_debug("inclusive_or_exp ::= inclusive_or_exp PIPE exclusive_or_exp");
    yylhsminor.yy42 = new infix_scalar_exp(yymsp[-2].minor.yy42, yymsp[0].minor.yy42, infix_scalar_exp::INFIX_OP::OR);
}
#line 1721 "./parser/out/grammar.c"
  yymsp[-2].minor.yy42 = yylhsminor.yy42;
        break;
      case 80: /* scalar_exp ::= inclusive_or_exp */
#line 433 "./parser/grammar.y"
{
    log_debug("scalar_exp ::= inclusive_or_exp");
    yylhsminor.yy42 = yymsp[0].minor.yy42;
}
#line 1730 "./parser/out/grammar.c"
  yymsp[0].minor.yy42 = yylhsminor.yy42;
        break;
      default:
        break;
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
    yysize = yyRuleInfoNRhs[yyruleno];
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
  if( yyRuleInfoNRhs[yyruleno]==0 ){
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
/********** End reduce actions ************************************************/
  };
  assert( yyruleno<sizeof(yyRuleInfoLhs)/sizeof(yyRuleInfoLhs[0]) );
  yygoto = yyRuleInfoLhs[yyruleno];
  yysize = yyRuleInfoNRhs[yyruleno];
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
#line 83 "./parser/grammar.y"

    printf("syntax error\n");
#line 1863 "./parser/out/grammar.c"
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
