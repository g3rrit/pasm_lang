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

#include "exp.h"
#include "token_types.h"
#include "cassert"
#include "lexer.h"
#include "util.h"

using namespace tree;
#line 37 "./parser/out/grammar.c"
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
#define YYNOCODE 95
#define YYACTIONTYPE unsigned short int
#define ImplParseTOKENTYPE token*
typedef union {
  int yyinit;
  ImplParseTOKENTYPE yy0;
  string_token* yy22;
  infix_scalar_exp* yy54;
  int_token* yy74;
  exp* yy86;
  float_token* yy97;
  id_token* yy104;
  ref_exp* yy128;
  scalar_exp* yy149;
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
#define YYNTOKEN             63
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
#define YY_ACTTAB_COUNT (323)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   267,  274,  264,  265,  261,   39,  275,   42,   50,   49,
 /*    10 */    63,   62,   60,  263,  267,  274,  264,  265,  262,   39,
 /*    20 */   275,   42,   50,   49,   63,   62,   60,  263,  267,  274,
 /*    30 */   257,  209,   18,   38,  275,   42,   50,   49,   63,   62,
 /*    40 */    60,  258,  267,  274,  257,   23,   24,   38,  275,   42,
 /*    50 */    50,   49,   63,   62,   60,  258,  274,  248,   22,   21,
 /*    60 */   133,  275,   42,   50,   49,   63,   59,  267,  274,  257,
 /*    70 */   168,   52,   38,  275,   42,   50,   49,   63,   62,   60,
 /*    80 */   258,  160,   65,    2,  171,  145,  146,  147,  148,  149,
 /*    90 */   150,  151,  152,  153,  154,  274,  247,  176,  168,  157,
 /*   100 */   275,   42,   50,   49,   63,   62,   60,   53,  274,  168,
 /*   110 */   165,  166,  167,  275,   42,   46,   14,   15,   27,   30,
 /*   120 */    10,    9,  274,   45,    1,  168,   11,  275,   42,   50,
 /*   130 */    49,   63,   62,   60,  273,   32,  274,  168,   55,   27,
 /*   140 */   158,  275,   42,   50,   49,   63,   62,   60,  272,  168,
 /*   150 */   274,   58,    3,   16,  271,  275,   42,   50,   49,   63,
 /*   160 */    62,   60,  278,  267,  143,  274,  270,  175,   37,  225,
 /*   170 */   275,   42,   50,   49,   63,   62,   60,  277,  274,   58,
 /*   180 */   144,  274,   54,  275,   42,   48,  275,   42,   50,   49,
 /*   190 */    63,   62,   60,  276,  274,   57,   26,  219,   34,  275,
 /*   200 */    42,   50,   49,   63,   62,   60,   64,   57,  220,  143,
 /*   210 */    32,  140,   17,  143,  240,   28,  239,  168,   44,   57,
 /*   220 */    45,   15,   19,   31,  222,   20,  240,   28,  239,   58,
 /*   230 */    56,   51,   45,   13,   25,  185,  211,  210,  240,   28,
 /*   240 */   239,  139,   43,  274,   45,  210,  246,   29,  275,   40,
 /*   250 */   213,  214,   33,  216,   28,  274,  243,    5,   58,    4,
 /*   260 */   275,   42,   50,   49,   61,  210,  210,    7,    8,  171,
 /*   270 */   170,  169,  171,  170,  210,   12,  226,  210,  184,   36,
 /*   280 */    35,  274,   58,    7,    8,  210,  275,   42,   50,   47,
 /*   290 */   210,   12,  274,  210,  210,   36,   35,  275,   41,  210,
 /*   300 */   218,  210,  210,  210,  210,  210,  210,  210,  210,    6,
 /*   310 */   210,  210,  210,  210,  210,  168,  210,  210,  168,   16,
 /*   320 */   210,  210,   16,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    63,   64,   65,   66,   67,   68,   69,   70,   71,   72,
 /*    10 */    73,   74,   75,   76,   63,   64,   65,   66,   67,   68,
 /*    20 */    69,   70,   71,   72,   73,   74,   75,   76,   63,   64,
 /*    30 */    65,   77,   78,   68,   69,   70,   71,   72,   73,   74,
 /*    40 */    75,   76,   63,   64,   65,   40,   41,   68,   69,   70,
 /*    50 */    71,   72,   73,   74,   75,   76,   64,   92,   36,   37,
 /*    60 */    47,   69,   70,   71,   72,   73,   74,   63,   64,   65,
 /*    70 */    57,   92,   68,   69,   70,   71,   72,   73,   74,   75,
 /*    80 */    76,   29,    2,   33,   11,   17,   18,   19,   20,   21,
 /*    90 */    22,   23,   24,   25,   26,   64,   92,   47,   57,   47,
 /*   100 */    69,   70,   71,   72,   73,   74,   75,   76,   64,   57,
 /*   110 */    58,   59,   60,   69,   70,   71,   48,   28,   50,   84,
 /*   120 */    38,   39,   64,   88,   46,   57,   44,   69,   70,   71,
 /*   130 */    72,   73,   74,   75,   76,   46,   64,   57,   64,   50,
 /*   140 */    46,   69,   70,   71,   72,   73,   74,   75,   76,   57,
 /*   150 */    64,   63,   33,   61,   63,   69,   70,   71,   72,   73,
 /*   160 */    74,   75,   76,   63,   44,   64,   63,   49,   68,   81,
 /*   170 */    69,   70,   71,   72,   73,   74,   75,   76,   64,   63,
 /*   180 */    49,   64,   62,   69,   70,   71,   69,   70,   71,   72,
 /*   190 */    73,   74,   75,   76,   64,   63,   50,   81,   33,   69,
 /*   200 */    70,   71,   72,   73,   74,   75,   76,   63,   85,   44,
 /*   210 */    46,   51,   89,   44,   82,   83,   84,   57,   86,   63,
 /*   220 */    88,   28,   35,   33,   87,   45,   82,   83,   84,   63,
 /*   230 */    86,   94,   88,   34,   63,   49,    0,   95,   82,   83,
 /*   240 */    84,   51,   86,   64,   88,   95,   80,   81,   69,   70,
 /*   250 */    79,   80,   81,   82,   83,   64,   90,   91,   63,   93,
 /*   260 */    69,   70,   71,   72,   73,   95,   95,   40,   41,   11,
 /*   270 */    12,   13,   11,   12,   95,   48,   81,   95,   51,   52,
 /*   280 */    53,   64,   63,   40,   41,   95,   69,   70,   71,   72,
 /*   290 */    95,   48,   64,   95,   95,   52,   53,   69,   70,   95,
 /*   300 */    81,   95,   95,   95,   95,   95,   95,   95,   95,   48,
 /*   310 */    95,   95,   95,   95,   95,   57,   95,   95,   57,   61,
 /*   320 */    95,   95,   61,   95,   95,   95,   95,   95,   95,   95,
 /*   330 */    95,   95,   95,   95,   95,   95,   95,   95,   95,   95,
 /*   340 */    95,   95,   95,   95,   95,   95,   95,
};
#define YY_SHIFT_COUNT    (65)
#define YY_SHIFT_MIN      (0)
#define YY_SHIFT_MAX      (261)
static const unsigned short int yy_shift_ofst[] = {
 /*     0 */   323,  258,  258,  261,  261,  261,   73,   73,   73,   73,
 /*    10 */    73,   73,   73,   73,   68,   68,   68,   52,   80,   73,
 /*    20 */    73,   73,   73,   73,   73,   89,   92,  160,   13,   78,
 /*    30 */    94,   41,   41,   78,   73,   41,   41,  227,  243,  243,
 /*    40 */    82,   82,   82,  120,  165,  190,    5,   22,    5,   22,
 /*    50 */     5,   50,  119,  118,  146,  131,  169,  164,  193,  187,
 /*    60 */   199,  180,  187,  180,  186,  236,
};
#define YY_REDUCE_COUNT (36)
#define YY_REDUCE_MIN   (-63)
#define YY_REDUCE_MAX   (228)
static const short yy_reduce_ofst[] = {
 /*     0 */   -46,  -63,  -49,  -35,  -21,    4,   31,   58,   72,   86,
 /*    10 */   101,  117,  130,   -8,  132,  144,  156,  166,  171,  191,
 /*    20 */   217,   44,  114,  179,  228,   35,  100,   88,  116,  137,
 /*    30 */   123,  195,  219,  137,   74,   91,  103,
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
  /*   61 */ "LESS_THAN",
  /*   62 */ "GREATER_THAN",
  /*   63 */ "id",
  /*   64 */ "integer",
  /*   65 */ "float",
  /*   66 */ "string",
  /*   67 */ "exp",
  /*   68 */ "ref_exp",
  /*   69 */ "scalar_exp_int",
  /*   70 */ "multiplicative_exp",
  /*   71 */ "additive_exp",
  /*   72 */ "shift_exp",
  /*   73 */ "and_exp",
  /*   74 */ "exclusive_or_exp",
  /*   75 */ "inclusive_or_exp",
  /*   76 */ "scalar_exp",
  /*   77 */ "package",
  /*   78 */ "package_opt",
  /*   79 */ "function_def",
  /*   80 */ "var_def",
  /*   81 */ "var_decl",
  /*   82 */ "struct_def",
  /*   83 */ "struct_def_opt",
  /*   84 */ "function_type",
  /*   85 */ "block_statement",
  /*   86 */ "type",
  /*   87 */ "literal",
  /*   88 */ "function_type_opt",
  /*   89 */ "block_statement_opt",
  /*   90 */ "statement",
  /*   91 */ "u_mnemonic",
  /*   92 */ "operand",
  /*   93 */ "d_mnemonic",
  /*   94 */ "literal_opt",
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
 /*   7 */ "struct_def_opt ::= id L_C_BRACKET var_decl",
 /*   8 */ "struct_def_opt ::= struct_def_opt var_decl",
 /*   9 */ "function_def ::= id function_type block_statement",
 /*  10 */ "var_decl ::= id COLON type",
 /*  11 */ "var_def ::= var_decl literal",
 /*  12 */ "function_type ::= function_type_opt R_R_BRACKET",
 /*  13 */ "function_type ::= L_R_BRACKET R_R_BRACKET",
 /*  14 */ "function_type_opt ::= L_R_BRACKET var_decl",
 /*  15 */ "function_type_opt ::= function_type_opt COMMA var_decl",
 /*  16 */ "type ::= type ASTERIX",
 /*  17 */ "type ::= L_S_BRACKET type COMMA integer R_S_BRACKET",
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
 /*  41 */ "id ::= ID",
 /*  42 */ "string ::= STRING",
 /*  43 */ "float ::= FLOAT",
 /*  44 */ "integer ::= INTEGER",
 /*  45 */ "operand ::= ref_exp",
 /*  46 */ "operand ::= float",
 /*  47 */ "operand ::= scalar_exp",
 /*  48 */ "operand ::= L_S_BRACKET scalar_exp R_S_BRACKET",
 /*  49 */ "literal ::= literal_opt R_C_BRACKET",
 /*  50 */ "literal_opt ::= L_C_BRACKET exp",
 /*  51 */ "literal_opt ::= literal_opt COMMA exp",
 /*  52 */ "exp ::= scalar_exp",
 /*  53 */ "exp ::= float",
 /*  54 */ "exp ::= string",
 /*  55 */ "exp ::= ref_exp",
 /*  56 */ "ref_exp ::= id",
 /*  57 */ "ref_exp ::= LESS_THAN type GREATER_THAN L_R_BRACKET ref_exp R_R_BRACKET",
 /*  58 */ "ref_exp ::= ref_exp L_S_BRACKET scalar_exp R_S_BRACKET",
 /*  59 */ "ref_exp ::= ref_exp DOT id",
 /*  60 */ "ref_exp ::= ref_exp ARROW id",
 /*  61 */ "ref_exp ::= ref_exp PLUS scalar_exp",
 /*  62 */ "ref_exp ::= ref_exp MINUS scalar_exp",
 /*  63 */ "scalar_exp_int ::= integer",
 /*  64 */ "multiplicative_exp ::= scalar_exp_int",
 /*  65 */ "multiplicative_exp ::= multiplicative_exp ASTERIX scalar_exp",
 /*  66 */ "multiplicative_exp ::= multiplicative_exp SLASH scalar_exp",
 /*  67 */ "multiplicative_exp ::= multiplicative_exp PERCENT scalar_exp",
 /*  68 */ "additive_exp ::= multiplicative_exp",
 /*  69 */ "additive_exp ::= additive_exp PLUS multiplicative_exp",
 /*  70 */ "additive_exp ::= additive_exp MINUS multiplicative_exp",
 /*  71 */ "shift_exp ::= additive_exp",
 /*  72 */ "shift_exp ::= shift_exp DOUBLE_LESS_THAN additive_exp",
 /*  73 */ "shift_exp ::= shift_exp DOUBLE_GREATER_THAN additive_exp",
 /*  74 */ "and_exp ::= shift_exp",
 /*  75 */ "and_exp ::= and_exp AMPERSAND shift_exp",
 /*  76 */ "exclusive_or_exp ::= and_exp",
 /*  77 */ "exclusive_or_exp ::= exclusive_or_exp CIRCUMFLEX and_exp",
 /*  78 */ "inclusive_or_exp ::= exclusive_or_exp",
 /*  79 */ "inclusive_or_exp ::= inclusive_or_exp PIPE exclusive_or_exp",
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

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;       /* Symbol on the left-hand side of the rule */
  signed char nrhs;     /* Negative of the number of RHS symbols in the rule */
} yyRuleInfo[] = {
  {   77,   -2 }, /* (0) package ::= package_opt END */
  {   78,    0 }, /* (1) package_opt ::= */
  {   78,   -2 }, /* (2) package_opt ::= package_opt function_def */
  {   78,   -2 }, /* (3) package_opt ::= package_opt var_def */
  {   78,   -2 }, /* (4) package_opt ::= package_opt var_decl */
  {   78,   -2 }, /* (5) package_opt ::= package_opt struct_def */
  {   82,   -2 }, /* (6) struct_def ::= struct_def_opt R_C_BRACKET */
  {   83,   -3 }, /* (7) struct_def_opt ::= id L_C_BRACKET var_decl */
  {   83,   -2 }, /* (8) struct_def_opt ::= struct_def_opt var_decl */
  {   79,   -3 }, /* (9) function_def ::= id function_type block_statement */
  {   81,   -3 }, /* (10) var_decl ::= id COLON type */
  {   80,   -2 }, /* (11) var_def ::= var_decl literal */
  {   84,   -2 }, /* (12) function_type ::= function_type_opt R_R_BRACKET */
  {   84,   -2 }, /* (13) function_type ::= L_R_BRACKET R_R_BRACKET */
  {   88,   -2 }, /* (14) function_type_opt ::= L_R_BRACKET var_decl */
  {   88,   -3 }, /* (15) function_type_opt ::= function_type_opt COMMA var_decl */
  {   86,   -2 }, /* (16) type ::= type ASTERIX */
  {   86,   -5 }, /* (17) type ::= L_S_BRACKET type COMMA integer R_S_BRACKET */
  {   86,   -1 }, /* (18) type ::= U8 */
  {   86,   -1 }, /* (19) type ::= U16 */
  {   86,   -1 }, /* (20) type ::= U32 */
  {   86,   -1 }, /* (21) type ::= U64 */
  {   86,   -1 }, /* (22) type ::= I8 */
  {   86,   -1 }, /* (23) type ::= I16 */
  {   86,   -1 }, /* (24) type ::= I32 */
  {   86,   -1 }, /* (25) type ::= I64 */
  {   86,   -1 }, /* (26) type ::= F32 */
  {   86,   -1 }, /* (27) type ::= F64 */
  {   86,   -1 }, /* (28) type ::= function_type */
  {   86,   -1 }, /* (29) type ::= struct_def */
  {   85,   -2 }, /* (30) block_statement ::= block_statement_opt R_C_BRACKET */
  {   89,   -1 }, /* (31) block_statement_opt ::= L_C_BRACKET */
  {   89,   -2 }, /* (32) block_statement_opt ::= block_statement_opt statement */
  {   90,   -1 }, /* (33) statement ::= SEMICOLON */
  {   90,   -1 }, /* (34) statement ::= var_decl */
  {   90,   -1 }, /* (35) statement ::= var_def */
  {   90,   -2 }, /* (36) statement ::= u_mnemonic operand */
  {   90,   -4 }, /* (37) statement ::= d_mnemonic operand COMMA operand */
  {   91,   -1 }, /* (38) u_mnemonic ::= PUSH */
  {   93,   -1 }, /* (39) d_mnemonic ::= MOV */
  {   93,   -1 }, /* (40) d_mnemonic ::= ADD */
  {   63,   -1 }, /* (41) id ::= ID */
  {   66,   -1 }, /* (42) string ::= STRING */
  {   65,   -1 }, /* (43) float ::= FLOAT */
  {   64,   -1 }, /* (44) integer ::= INTEGER */
  {   92,   -1 }, /* (45) operand ::= ref_exp */
  {   92,   -1 }, /* (46) operand ::= float */
  {   92,   -1 }, /* (47) operand ::= scalar_exp */
  {   92,   -3 }, /* (48) operand ::= L_S_BRACKET scalar_exp R_S_BRACKET */
  {   87,   -2 }, /* (49) literal ::= literal_opt R_C_BRACKET */
  {   94,   -2 }, /* (50) literal_opt ::= L_C_BRACKET exp */
  {   94,   -3 }, /* (51) literal_opt ::= literal_opt COMMA exp */
  {   67,   -1 }, /* (52) exp ::= scalar_exp */
  {   67,   -1 }, /* (53) exp ::= float */
  {   67,   -1 }, /* (54) exp ::= string */
  {   67,   -1 }, /* (55) exp ::= ref_exp */
  {   68,   -1 }, /* (56) ref_exp ::= id */
  {   68,   -6 }, /* (57) ref_exp ::= LESS_THAN type GREATER_THAN L_R_BRACKET ref_exp R_R_BRACKET */
  {   68,   -4 }, /* (58) ref_exp ::= ref_exp L_S_BRACKET scalar_exp R_S_BRACKET */
  {   68,   -3 }, /* (59) ref_exp ::= ref_exp DOT id */
  {   68,   -3 }, /* (60) ref_exp ::= ref_exp ARROW id */
  {   68,   -3 }, /* (61) ref_exp ::= ref_exp PLUS scalar_exp */
  {   68,   -3 }, /* (62) ref_exp ::= ref_exp MINUS scalar_exp */
  {   69,   -1 }, /* (63) scalar_exp_int ::= integer */
  {   70,   -1 }, /* (64) multiplicative_exp ::= scalar_exp_int */
  {   70,   -3 }, /* (65) multiplicative_exp ::= multiplicative_exp ASTERIX scalar_exp */
  {   70,   -3 }, /* (66) multiplicative_exp ::= multiplicative_exp SLASH scalar_exp */
  {   70,   -3 }, /* (67) multiplicative_exp ::= multiplicative_exp PERCENT scalar_exp */
  {   71,   -1 }, /* (68) additive_exp ::= multiplicative_exp */
  {   71,   -3 }, /* (69) additive_exp ::= additive_exp PLUS multiplicative_exp */
  {   71,   -3 }, /* (70) additive_exp ::= additive_exp MINUS multiplicative_exp */
  {   72,   -1 }, /* (71) shift_exp ::= additive_exp */
  {   72,   -3 }, /* (72) shift_exp ::= shift_exp DOUBLE_LESS_THAN additive_exp */
  {   72,   -3 }, /* (73) shift_exp ::= shift_exp DOUBLE_GREATER_THAN additive_exp */
  {   73,   -1 }, /* (74) and_exp ::= shift_exp */
  {   73,   -3 }, /* (75) and_exp ::= and_exp AMPERSAND shift_exp */
  {   74,   -1 }, /* (76) exclusive_or_exp ::= and_exp */
  {   74,   -3 }, /* (77) exclusive_or_exp ::= exclusive_or_exp CIRCUMFLEX and_exp */
  {   75,   -1 }, /* (78) inclusive_or_exp ::= exclusive_or_exp */
  {   75,   -3 }, /* (79) inclusive_or_exp ::= inclusive_or_exp PIPE exclusive_or_exp */
  {   76,   -1 }, /* (80) scalar_exp ::= inclusive_or_exp */
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
        YYMINORTYPE yylhsminor;
      case 0: /* package ::= package_opt END */
#line 91 "./parser/grammar.y"
{
    log_debug("package ::= package_opt  END");
}
#line 1188 "./parser/out/grammar.c"
        break;
      case 1: /* package_opt ::= */
#line 95 "./parser/grammar.y"
{
    log_debug("package_opt ::= /* empty */");
}
#line 1195 "./parser/out/grammar.c"
        break;
      case 2: /* package_opt ::= package_opt function_def */
#line 98 "./parser/grammar.y"
{
    log_debug("package_opt ::= package_opt function_def");
}
#line 1202 "./parser/out/grammar.c"
        break;
      case 3: /* package_opt ::= package_opt var_def */
#line 101 "./parser/grammar.y"
{
    log_debug("package_opt ::= package_opt var_def");
}
#line 1209 "./parser/out/grammar.c"
        break;
      case 4: /* package_opt ::= package_opt var_decl */
#line 104 "./parser/grammar.y"
{
    log_debug("package_opt ::= package_opt var_decl");
}
#line 1216 "./parser/out/grammar.c"
        break;
      case 5: /* package_opt ::= package_opt struct_def */
#line 107 "./parser/grammar.y"
{
    log_debug("package_opt ::= package_opt struct_def");
}
#line 1223 "./parser/out/grammar.c"
        break;
      case 6: /* struct_def ::= struct_def_opt R_C_BRACKET */
#line 115 "./parser/grammar.y"
{
    log_debug("struct_def ::= struct_def_opt R_C_BRACKET");
}
#line 1230 "./parser/out/grammar.c"
        break;
      case 7: /* struct_def_opt ::= id L_C_BRACKET var_decl */
#line 118 "./parser/grammar.y"
{
    log_debug("struct_def_opt ::= id L_C_BRACKET var_decl");
}
#line 1237 "./parser/out/grammar.c"
        break;
      case 8: /* struct_def_opt ::= struct_def_opt var_decl */
#line 121 "./parser/grammar.y"
{
    log_debug("struct_def_opt ::= struct_def_opt var_decl");
}
#line 1244 "./parser/out/grammar.c"
        break;
      case 9: /* function_def ::= id function_type block_statement */
#line 129 "./parser/grammar.y"
{
    log_debug("function_def ::= id function_type block_statement");
}
#line 1251 "./parser/out/grammar.c"
        break;
      case 10: /* var_decl ::= id COLON type */
#line 139 "./parser/grammar.y"
{
    log_debug("var_decl ::= id COLON type");
}
#line 1258 "./parser/out/grammar.c"
        break;
      case 11: /* var_def ::= var_decl literal */
#line 143 "./parser/grammar.y"
{
    log_debug("var_def ::= var_decl literal");
}
#line 1265 "./parser/out/grammar.c"
        break;
      case 12: /* function_type ::= function_type_opt R_R_BRACKET */
#line 153 "./parser/grammar.y"
{
    log_debug("function_type ::= function_type_opt R_R_BRACKET");
}
#line 1272 "./parser/out/grammar.c"
        break;
      case 13: /* function_type ::= L_R_BRACKET R_R_BRACKET */
#line 156 "./parser/grammar.y"
{
    log_debug("function_type ::= L_R_BRACKET R_R_BRACKET");
}
#line 1279 "./parser/out/grammar.c"
        break;
      case 14: /* function_type_opt ::= L_R_BRACKET var_decl */
#line 160 "./parser/grammar.y"
{
    log_debug("function_type_opt ::= L_R_BRACKET var_decl");
}
#line 1286 "./parser/out/grammar.c"
        break;
      case 15: /* function_type_opt ::= function_type_opt COMMA var_decl */
#line 163 "./parser/grammar.y"
{
    log_debug("function_type_opt ::= function_type_opt COMMA var_decl");
}
#line 1293 "./parser/out/grammar.c"
        break;
      case 16: /* type ::= type ASTERIX */
#line 169 "./parser/grammar.y"
{
    log_debug("type ::= type ASTERIX . [POINTER_TYP");
}
#line 1300 "./parser/out/grammar.c"
        break;
      case 17: /* type ::= L_S_BRACKET type COMMA integer R_S_BRACKET */
#line 172 "./parser/grammar.y"
{
    log_debug("type ::= L_S_BRACKET type COMMA integer R_S_BRACKET");
}
#line 1307 "./parser/out/grammar.c"
        break;
      case 18: /* type ::= U8 */
#line 175 "./parser/grammar.y"
{
    log_debug("type ::= U8");
}
#line 1314 "./parser/out/grammar.c"
        break;
      case 19: /* type ::= U16 */
#line 178 "./parser/grammar.y"
{
    log_debug("type ::= U16");
}
#line 1321 "./parser/out/grammar.c"
        break;
      case 20: /* type ::= U32 */
#line 181 "./parser/grammar.y"
{
    log_debug("type ::= U32");
}
#line 1328 "./parser/out/grammar.c"
        break;
      case 21: /* type ::= U64 */
#line 184 "./parser/grammar.y"
{
    log_debug("type ::= U64");
}
#line 1335 "./parser/out/grammar.c"
        break;
      case 22: /* type ::= I8 */
#line 187 "./parser/grammar.y"
{
    log_debug("type ::= I8");
}
#line 1342 "./parser/out/grammar.c"
        break;
      case 23: /* type ::= I16 */
#line 190 "./parser/grammar.y"
{
    log_debug("type ::= I16");
}
#line 1349 "./parser/out/grammar.c"
        break;
      case 24: /* type ::= I32 */
#line 193 "./parser/grammar.y"
{
    log_debug("type ::= I32");
}
#line 1356 "./parser/out/grammar.c"
        break;
      case 25: /* type ::= I64 */
#line 196 "./parser/grammar.y"
{
    log_debug("type ::= I64");
}
#line 1363 "./parser/out/grammar.c"
        break;
      case 26: /* type ::= F32 */
#line 199 "./parser/grammar.y"
{
    log_debug("type ::= F32");
}
#line 1370 "./parser/out/grammar.c"
        break;
      case 27: /* type ::= F64 */
#line 202 "./parser/grammar.y"
{
    log_debug("type ::= F64");
}
#line 1377 "./parser/out/grammar.c"
        break;
      case 28: /* type ::= function_type */
#line 205 "./parser/grammar.y"
{
    log_debug("type ::= function_type");
}
#line 1384 "./parser/out/grammar.c"
        break;
      case 29: /* type ::= struct_def */
#line 208 "./parser/grammar.y"
{
    log_debug("type ::= struct_def");
}
#line 1391 "./parser/out/grammar.c"
        break;
      case 30: /* block_statement ::= block_statement_opt R_C_BRACKET */
#line 216 "./parser/grammar.y"
{
    log_debug("block_statement ::= block_statement_opt R_C_BRACKET");
}
#line 1398 "./parser/out/grammar.c"
        break;
      case 31: /* block_statement_opt ::= L_C_BRACKET */
#line 220 "./parser/grammar.y"
{
    log_debug("block_statement_opt ::= L_C_BRACKET");
}
#line 1405 "./parser/out/grammar.c"
        break;
      case 32: /* block_statement_opt ::= block_statement_opt statement */
#line 223 "./parser/grammar.y"
{
    log_debug("block_statement_opt ::= block_statement_opt statement");
}
#line 1412 "./parser/out/grammar.c"
        break;
      case 33: /* statement ::= SEMICOLON */
#line 227 "./parser/grammar.y"
{
    log_debug("statement ::= SEMICOLON");
}
#line 1419 "./parser/out/grammar.c"
        break;
      case 34: /* statement ::= var_decl */
#line 230 "./parser/grammar.y"
{
    log_debug("statement ::= var_decl");
}
#line 1426 "./parser/out/grammar.c"
        break;
      case 35: /* statement ::= var_def */
#line 233 "./parser/grammar.y"
{
    log_debug("statement ::= var_def");
}
#line 1433 "./parser/out/grammar.c"
        break;
      case 36: /* statement ::= u_mnemonic operand */
#line 236 "./parser/grammar.y"
{
    log_debug("statement ::= u_mnemonic operand");
}
#line 1440 "./parser/out/grammar.c"
        break;
      case 37: /* statement ::= d_mnemonic operand COMMA operand */
#line 239 "./parser/grammar.y"
{
    log_debug("statement ::= d_mnemonic operand COMMA operand");
}
#line 1447 "./parser/out/grammar.c"
        break;
      case 38: /* u_mnemonic ::= PUSH */
#line 243 "./parser/grammar.y"
{
    log_debug("u_mnemonic ::= PUSH");
}
#line 1454 "./parser/out/grammar.c"
        break;
      case 39: /* d_mnemonic ::= MOV */
#line 247 "./parser/grammar.y"
{
    log_debug("d_mnemonic ::= MOV");
}
#line 1461 "./parser/out/grammar.c"
        break;
      case 40: /* d_mnemonic ::= ADD */
#line 250 "./parser/grammar.y"
{
    log_debug("d_mnemonic ::= ADD");
}
#line 1468 "./parser/out/grammar.c"
        break;
      case 41: /* id ::= ID */
#line 261 "./parser/grammar.y"
{
    log_debug("id ::= ID");
    yylhsminor.yy104 = static_cast<id_token*>(*yymsp[0].minor.yy0);
}
#line 1476 "./parser/out/grammar.c"
  yymsp[0].minor.yy104 = yylhsminor.yy104;
        break;
      case 42: /* string ::= STRING */
#line 265 "./parser/grammar.y"
{
    log_debug("string ::= STRING");
    yylhsminor.yy22 = static_cast<string_token*>(*yymsp[0].minor.yy0);
}
#line 1485 "./parser/out/grammar.c"
  yymsp[0].minor.yy22 = yylhsminor.yy22;
        break;
      case 43: /* float ::= FLOAT */
#line 269 "./parser/grammar.y"
{
    log_debug("float ::= FLOAT");
    yylhsminor.yy97 = static_cast<float_token*>(*yymsp[0].minor.yy0);
}
#line 1494 "./parser/out/grammar.c"
  yymsp[0].minor.yy97 = yylhsminor.yy97;
        break;
      case 44: /* integer ::= INTEGER */
#line 273 "./parser/grammar.y"
{
    log_debug("integer ::= INTEGER");
    yylhsminor.yy74 = static_cast<int_token*>(*yymsp[0].minor.yy0);
}
#line 1503 "./parser/out/grammar.c"
  yymsp[0].minor.yy74 = yylhsminor.yy74;
        break;
      case 45: /* operand ::= ref_exp */
#line 280 "./parser/grammar.y"
{
    log_debug("operand ::= ref_exp");
}
#line 1511 "./parser/out/grammar.c"
        break;
      case 46: /* operand ::= float */
#line 283 "./parser/grammar.y"
{
    log_debug("operand ::= float");
}
#line 1518 "./parser/out/grammar.c"
        break;
      case 47: /* operand ::= scalar_exp */
#line 286 "./parser/grammar.y"
{
    log_debug("operand ::= scalar_exp");
}
#line 1525 "./parser/out/grammar.c"
        break;
      case 48: /* operand ::= L_S_BRACKET scalar_exp R_S_BRACKET */
#line 289 "./parser/grammar.y"
{
    log_debug("operand ::= L_S_BRACKET scalar_exp R_S_BRACKET");
}
#line 1532 "./parser/out/grammar.c"
        break;
      case 49: /* literal ::= literal_opt R_C_BRACKET */
#line 295 "./parser/grammar.y"
{
    log_debug("literal ::= literal_opt R_C_BRACKET");
}
#line 1539 "./parser/out/grammar.c"
        break;
      case 50: /* literal_opt ::= L_C_BRACKET exp */
#line 299 "./parser/grammar.y"
{
    log_debug("literal_opt ::= L_C_BRACKET exp");
}
#line 1546 "./parser/out/grammar.c"
        break;
      case 51: /* literal_opt ::= literal_opt COMMA exp */
#line 302 "./parser/grammar.y"
{
    log_debug("literal_opt ::= literal_opt COMMA exp");
}
#line 1553 "./parser/out/grammar.c"
        break;
      case 52: /* exp ::= scalar_exp */
#line 308 "./parser/grammar.y"
{
    log_debug("exp ::= scalar_exp");
    yylhsminor.yy86 = yymsp[0].minor.yy54;
}
#line 1561 "./parser/out/grammar.c"
  yymsp[0].minor.yy86 = yylhsminor.yy86;
        break;
      case 53: /* exp ::= float */
#line 312 "./parser/grammar.y"
{
    log_debug("exp ::= float");
    yylhsminor.yy86 = new float_exp(yymsp[0].minor.yy97);
}
#line 1570 "./parser/out/grammar.c"
  yymsp[0].minor.yy86 = yylhsminor.yy86;
        break;
      case 54: /* exp ::= string */
#line 316 "./parser/grammar.y"
{
    log_debug("exp ::= string");
    yylhsminor.yy86 = new string_exp(yymsp[0].minor.yy22);
}
#line 1579 "./parser/out/grammar.c"
  yymsp[0].minor.yy86 = yylhsminor.yy86;
        break;
      case 55: /* exp ::= ref_exp */
#line 320 "./parser/grammar.y"
{
    log_debug("exp ::= ref_exp");
    yylhsminor.yy86 = yymsp[0].minor.yy128;
}
#line 1588 "./parser/out/grammar.c"
  yymsp[0].minor.yy86 = yylhsminor.yy86;
        break;
      case 56: /* ref_exp ::= id */
#line 327 "./parser/grammar.y"
{
    log_debug("ref_exp ::= id");
    yylhsminor.yy128 = new id_exp(yymsp[0].minor.yy104);
}
#line 1597 "./parser/out/grammar.c"
  yymsp[0].minor.yy128 = yylhsminor.yy128;
        break;
      case 57: /* ref_exp ::= LESS_THAN type GREATER_THAN L_R_BRACKET ref_exp R_R_BRACKET */
#line 331 "./parser/grammar.y"
{
    log_debug("ref_exp ::= CAST LESS_THAN type GREATER_THAN L_R_BRACKET ref_exp R_R_BRACKET");
    yymsp[-5].minor.yy128 = new cast_exp(yymsp[-1].minor.yy128, yymsp[-4].minor.yy0);
}
#line 1606 "./parser/out/grammar.c"
        break;
      case 58: /* ref_exp ::= ref_exp L_S_BRACKET scalar_exp R_S_BRACKET */
#line 335 "./parser/grammar.y"
{
    log_debug("ref_exp ::= ref_exp L_S_BRACKET scalar_exp R_S_BRACKET");
    yylhsminor.yy128 = new acc_exp(yymsp[-3].minor.yy128, yymsp[-1].minor.yy54);
}
#line 1614 "./parser/out/grammar.c"
  yymsp[-3].minor.yy128 = yylhsminor.yy128;
        break;
      case 59: /* ref_exp ::= ref_exp DOT id */
#line 339 "./parser/grammar.y"
{
    log_debug("ref_exp ::= ref_exp DOT id");
    yylhsminor.yy128 = new ref_acc_exp(yymsp[-2].minor.yy128, yymsp[0].minor.yy104, ref_acc_exp::REF_OP::DOT);
}
#line 1623 "./parser/out/grammar.c"
  yymsp[-2].minor.yy128 = yylhsminor.yy128;
        break;
      case 60: /* ref_exp ::= ref_exp ARROW id */
#line 343 "./parser/grammar.y"
{
    log_debug("ref_exp ::= ref_exp ARROW id");
    yylhsminor.yy128 = new ref_acc_exp(yymsp[-2].minor.yy128, yymsp[0].minor.yy104, ref_acc_exp::REF_OP::ARROW);
}
#line 1632 "./parser/out/grammar.c"
  yymsp[-2].minor.yy128 = yylhsminor.yy128;
        break;
      case 61: /* ref_exp ::= ref_exp PLUS scalar_exp */
#line 347 "./parser/grammar.y"
{
    log_debug("ref_exp ::= ref_exp PLUS scalar_exp");
    yylhsminor.yy128 = new ref_off_exp(yymsp[-2].minor.yy128, yymsp[0].minor.yy54, ref_off_exp::REF_OP::PLUS);
}
#line 1641 "./parser/out/grammar.c"
  yymsp[-2].minor.yy128 = yylhsminor.yy128;
        break;
      case 62: /* ref_exp ::= ref_exp MINUS scalar_exp */
#line 351 "./parser/grammar.y"
{
    log_debug("ref_exp ::= ref_exp MINUS scalar_exp");
    yylhsminor.yy128 = new ref_off_exp(yymsp[-2].minor.yy128, yymsp[0].minor.yy54, ref_off_exp::REF_OP::MINUS);
}
#line 1650 "./parser/out/grammar.c"
  yymsp[-2].minor.yy128 = yylhsminor.yy128;
        break;
      case 63: /* scalar_exp_int ::= integer */
#line 358 "./parser/grammar.y"
{
    log_debug("scalar_exp_int ::= integer");
    yylhsminor.yy149 = new int_exp(yymsp[0].minor.yy74);
}
#line 1659 "./parser/out/grammar.c"
  yymsp[0].minor.yy149 = yylhsminor.yy149;
        break;
      case 64: /* multiplicative_exp ::= scalar_exp_int */
#line 363 "./parser/grammar.y"
{
    log_debug("multiplicative_exp ::= scalar_exp_int");
    yylhsminor.yy54 = yymsp[0].minor.yy149;
}
#line 1668 "./parser/out/grammar.c"
  yymsp[0].minor.yy54 = yylhsminor.yy54;
        break;
      case 65: /* multiplicative_exp ::= multiplicative_exp ASTERIX scalar_exp */
#line 367 "./parser/grammar.y"
{
    log_debug("multiplicative_exp ::= multiplicative_exp ASTERIX scalar_ex");
    yylhsminor.yy54 = new infix_scalar_exp(yymsp[-2].minor.yy54, yymsp[0].minor.yy54, infix_scalar_exp::INFIX_OP::TIMES);
}
#line 1677 "./parser/out/grammar.c"
  yymsp[-2].minor.yy54 = yylhsminor.yy54;
        break;
      case 66: /* multiplicative_exp ::= multiplicative_exp SLASH scalar_exp */
#line 371 "./parser/grammar.y"
{
    log_debug("multiplicative_exp ::= multiplicative_exp SLASH scalar_exp");
    yylhsminor.yy54 =new infix_scalar_exp(yymsp[-2].minor.yy54, yymsp[0].minor.yy54, infix_scalar_exp::INFIX_OP::DIV);
}
#line 1686 "./parser/out/grammar.c"
  yymsp[-2].minor.yy54 = yylhsminor.yy54;
        break;
      case 67: /* multiplicative_exp ::= multiplicative_exp PERCENT scalar_exp */
#line 375 "./parser/grammar.y"
{
    log_debug("multiplicative_exp ::= multiplicative_exp PERCENT scalar_exp");
    yylhsminor.yy54 = new infix_scalar_exp(yymsp[-2].minor.yy54, yymsp[0].minor.yy54, infix_scalar_exp::INFIX_OP::MOD);
}
#line 1695 "./parser/out/grammar.c"
  yymsp[-2].minor.yy54 = yylhsminor.yy54;
        break;
      case 68: /* additive_exp ::= multiplicative_exp */
#line 380 "./parser/grammar.y"
{
    log_debug("additive_exp ::= multiplicative_exp");
    yylhsminor.yy54 = yymsp[0].minor.yy54;
}
#line 1704 "./parser/out/grammar.c"
  yymsp[0].minor.yy54 = yylhsminor.yy54;
        break;
      case 69: /* additive_exp ::= additive_exp PLUS multiplicative_exp */
#line 384 "./parser/grammar.y"
{
    log_debug("additive_exp ::= additive_exp PLUS multiplicative_exp");
    yylhsminor.yy54 = new infix_scalar_exp(yymsp[-2].minor.yy54, yymsp[0].minor.yy54, infix_scalar_exp::INFIX_OP::PLUS);
}
#line 1713 "./parser/out/grammar.c"
  yymsp[-2].minor.yy54 = yylhsminor.yy54;
        break;
      case 70: /* additive_exp ::= additive_exp MINUS multiplicative_exp */
#line 388 "./parser/grammar.y"
{
    log_debug("additive_exp ::= additive_exp MINUS multiplicative_exp");
    yylhsminor.yy54 = new infix_scalar_exp(yymsp[-2].minor.yy54, yymsp[0].minor.yy54, infix_scalar_exp::INFIX_OP::MINUS);
}
#line 1722 "./parser/out/grammar.c"
  yymsp[-2].minor.yy54 = yylhsminor.yy54;
        break;
      case 71: /* shift_exp ::= additive_exp */
#line 393 "./parser/grammar.y"
{
    log_debug("shift_exp ::= additive_exp");
    yylhsminor.yy54 = yymsp[0].minor.yy54;
}
#line 1731 "./parser/out/grammar.c"
  yymsp[0].minor.yy54 = yylhsminor.yy54;
        break;
      case 72: /* shift_exp ::= shift_exp DOUBLE_LESS_THAN additive_exp */
#line 397 "./parser/grammar.y"
{
    log_debug("shift_exp ::= shift_exp DOUBLE_LESS_THAN additive_exp");
    yylhsminor.yy54 = new infix_scalar_exp(yymsp[-2].minor.yy54, yymsp[0].minor.yy54, infix_scalar_exp::INFIX_OP::SHIFT_LEFT);
}
#line 1740 "./parser/out/grammar.c"
  yymsp[-2].minor.yy54 = yylhsminor.yy54;
        break;
      case 73: /* shift_exp ::= shift_exp DOUBLE_GREATER_THAN additive_exp */
#line 401 "./parser/grammar.y"
{
    log_debug("shift_exp ::= shift_exp DOUBLE_GREATER_THAN additive_exp");
    yylhsminor.yy54 = new infix_scalar_exp(yymsp[-2].minor.yy54, yymsp[0].minor.yy54, infix_scalar_exp::INFIX_OP::SHIFT_RIGHT);
}
#line 1749 "./parser/out/grammar.c"
  yymsp[-2].minor.yy54 = yylhsminor.yy54;
        break;
      case 74: /* and_exp ::= shift_exp */
#line 406 "./parser/grammar.y"
{
    log_debug("and_exp ::= shift_exp");
    yylhsminor.yy54 = yymsp[0].minor.yy54;
}
#line 1758 "./parser/out/grammar.c"
  yymsp[0].minor.yy54 = yylhsminor.yy54;
        break;
      case 75: /* and_exp ::= and_exp AMPERSAND shift_exp */
#line 410 "./parser/grammar.y"
{
    log_debug("and_exp ::= and_exp AMPERSAND shift_exp");
    yylhsminor.yy54 = new infix_scalar_exp(yymsp[-2].minor.yy54, yymsp[0].minor.yy54, infix_scalar_exp::INFIX_OP::AND);
}
#line 1767 "./parser/out/grammar.c"
  yymsp[-2].minor.yy54 = yylhsminor.yy54;
        break;
      case 76: /* exclusive_or_exp ::= and_exp */
#line 415 "./parser/grammar.y"
{
    log_debug("exclusive_or_exp ::= and_exp");
    yylhsminor.yy54 = yymsp[0].minor.yy54;
}
#line 1776 "./parser/out/grammar.c"
  yymsp[0].minor.yy54 = yylhsminor.yy54;
        break;
      case 77: /* exclusive_or_exp ::= exclusive_or_exp CIRCUMFLEX and_exp */
#line 419 "./parser/grammar.y"
{
    log_debug("exclusive_or_exp ::= exclusive_or_exp CIRCUMFLEX and_exp");
    yylhsminor.yy54 = new infix_scalar_exp(yymsp[-2].minor.yy54, yymsp[0].minor.yy54, infix_scalar_exp::INFIX_OP::NOR);
}
#line 1785 "./parser/out/grammar.c"
  yymsp[-2].minor.yy54 = yylhsminor.yy54;
        break;
      case 78: /* inclusive_or_exp ::= exclusive_or_exp */
#line 424 "./parser/grammar.y"
{
    log_debug("inclusive_or_exp ::= exclusive_or_exp");
    yylhsminor.yy54 = yymsp[0].minor.yy54;
}
#line 1794 "./parser/out/grammar.c"
  yymsp[0].minor.yy54 = yylhsminor.yy54;
        break;
      case 79: /* inclusive_or_exp ::= inclusive_or_exp PIPE exclusive_or_exp */
#line 428 "./parser/grammar.y"
{
    log_debug("inclusive_or_exp ::= inclusive_or_exp PIPE exclusive_or_exp");
    yylhsminor.yy54 = new infix_scalar_exp(yymsp[-2].minor.yy54, yymsp[0].minor.yy54, infix_scalar_exp::INFIX_OP::OR);
}
#line 1803 "./parser/out/grammar.c"
  yymsp[-2].minor.yy54 = yylhsminor.yy54;
        break;
      case 80: /* scalar_exp ::= inclusive_or_exp */
#line 433 "./parser/grammar.y"
{
    log_debug("scalar_exp ::= inclusive_or_exp");
    yylhsminor.yy54 = yymsp[0].minor.yy54;
}
#line 1812 "./parser/out/grammar.c"
  yymsp[0].minor.yy54 = yylhsminor.yy54;
        break;
      default:
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
#line 83 "./parser/grammar.y"

    printf("syntax error\n");
#line 1878 "./parser/out/grammar.c"
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
