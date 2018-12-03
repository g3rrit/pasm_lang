/*
 * compile with:
 * re2c --input custom -o fstream.cc fstream.re
 * g++ -o fstream fstream.cc
 */

#include "lexer.h"

token& lex(std::ifstream &in, bool keep)
{
#define TOKEN_BUFFER_SIZE 128
    static token token_buffer[TOKEN_BUFFER_SIZE];
    static size_t token_buffer_pos = 0;
    static token* current_token = nullptr;

    current_token = &token_buffer[token_buffer_pos];

    if(keep) {
        token_buffer_pos++;
    }
    token_buffer_pos %= TOKEN_BUFFER_SIZE;

    std::streampos mar;
    size_t pos = 0;
    size_t line_num = 0;

#define BUFFER_SIZE 1024
    static char buffer[BUFFER_SIZE];
    bzero(buffer, BUFFER_SIZE);
#   define YYCTYPE     char
#   define YYPEEK()    in.peek(); {if(in.eof()) {*current_token = token(END); return *current_token;}}
#   define YYSKIP()    do { in.get(buffer[pos]); pos++; if (in.eof()) { *current_token = token(END); return *current_token; }} while(0)
#   define YYBACKUP()  mar = in.tellg()
#   define YYRESTORE() in.seekg(mar)

    /*!re2c
        re2c:yyfill:enable = 0;

        [ \t\r]                             {
                                                *current_token = token(OTHER);
                                                return *current_token;
                                            }
        [\n]                                {
                                                line_num++;
                                                *current_token = token(OTHER);
                                                return *current_token;
                                            }

        "use"                               {
                                                *current_token = token(USE);
                                                return *current_token;
                                            }

        "as"                                {
                                                *current_token = token(AS);
                                                return *current_token;
                                            }

        "ret"                               {
                                                *current_token = token(RET);
                                                return *current_token;
                                            }

        "u8"                                {
                                                *current_token = token(U8);
                                                return *current_token;
                                            }

        "u16"                               {
                                                *current_token = token(U16);
                                                return *current_token;
                                            }

        "u32"                               {
                                                *current_token = token(U32);
                                                return *current_token;
                                            }

        "u64"                               {
                                                *current_token = token(U64);
                                                return *current_token;
                                            }

        "i8"                                {
                                                *current_token = token(I8);
                                                return *current_token;
                                            }

        "i16"                               {
                                                *current_token = token(I16);
                                                return *current_token;
                                            }

        "i32"                               {
                                                *current_token = token(I32);
                                                return *current_token;
                                            }

        "i64"                               {
                                                *current_token = token(I64);
                                                return *current_token;
                                            }

        "f32"                               {
                                                *current_token = token(F32);
                                                return *current_token;
                                            }

        "f64"                               {
                                                *current_token = token(F64);
                                                return *current_token;
                                            }

        "void"                              {
                                                *current_token = token(VOID);
                                                return *current_token;
                                            }

        [&]                                 {
                                                *current_token = token(AMPERSAND);
                                                return *current_token;
                                            }

        [\x5e]                              {
                                                *current_token = token(CIRCUMFLEX);
                                                return *current_token;
                                            }

        [:]                                 {
                                                *current_token = token(COLON);
                                                return *current_token;
                                            }

        [;]                                 {
                                                *current_token = token(SEMICOLON);
                                                return *current_token;
                                            }

        [,]                                 {
                                                *current_token = token(COMMA);
                                                return *current_token;
                                            }

        [\x7b]                              {
                                                *current_token = token(L_C_BRACKET);
                                                return *current_token;
                                            }

        [\x7d]                              {
                                                *current_token = token(R_C_BRACKET);
                                                return *current_token;
                                            }

        [\x28]                              {
                                                *current_token = token(L_R_BRACKET);
                                                return *current_token;
                                            }

        [\x29]                              {
                                                *current_token = token(R_R_BRACKET);
                                                return *current_token;
                                            }

        [\x5b]                              {
                                                *current_token = token(L_S_BRACKET);
                                                return *current_token;
                                            }

        [\x5d]                              {
                                                *current_token = token(R_S_BRACKET);
                                                return *current_token;
                                            }

        [\x2a]                              {
                                                *current_token = token(ASTERIX);
                                                return *current_token;
                                            }

        [\x2b]                              {
                                                *current_token = token(PLUS);
                                                return *current_token;
                                            }

        [\x2d]                              {
                                                *current_token = token(MINUS);
                                                return *current_token;
                                            }

        [\x2f]                              {
                                                *current_token = token(SLASH);
                                                return *current_token;
                                            }

        [\x2e]                              {
                                                *current_token = token(DOT);
                                                return *current_token;
                                            }

        [%]                                 {
                                                *current_token = token(PERCENT);
                                                return *current_token;
                                            }

        [!]                                 {
                                                *current_token = token(EXCLAMATIONMARK);
                                                return *current_token;
                                            }

        [?]                                 {
                                                *current_token = token(QUESTIONMARK);
                                                return *current_token;
                                            }

        [<]                                 {
                                                *current_token = token(LESS_THAN);
                                                return *current_token;
                                            }

        [>]                                 {
                                                *current_token = token(GREATER_THAN);
                                                return *current_token;
                                            }

        [\x7c]                              {
                                                *current_token = token(PIPE);
                                                return *current_token;
                                            }

        [\x7e]                              {
                                                *current_token = token(TILDE);
                                                return *current_token;
                                            }

        [0-9]+		                        {
                                                *current_token = token(INTEGER);
                                                current_token->set_int_val(atoi(buffer));
                                                return *current_token;
                                            }

        [0-9]+[\x2e][0-9]+                  {
                                                *current_token = token(FLOAT);
                                                current_token->set_float_val(atof(buffer));
                                                return *current_token;
                                            }

        [a-zA-Z_][a-zA-Z0-9_]*              {
                                                *current_token = token(ID);
                                                current_token->set_str_val(buffer);
                                                return *current_token;
                                            }

    */
}
