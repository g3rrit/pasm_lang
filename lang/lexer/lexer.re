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
#   define YYPEEK()    in.peek(); {if(in.eof()) {*current_token = token(T_END); return *current_token;}}
#   define YYSKIP()    do { in.get(buffer[pos]); pos++; if (in.eof()) { *current_token = token(T_END); return *current_token; }} while(0)
#   define YYBACKUP()  mar = in.tellg()
#   define YYRESTORE() in.seekg(mar)

    /*!re2c
        re2c:yyfill:enable = 0;

        [ \t\r]                             {
                                                *current_token = token(T_OTHER);
                                                return *current_token;
                                            }
        [\n]                                {
                                                line_num++;
                                                *current_token = token(T_OTHER);
                                                return *current_token;
                                            }

        "use"                               {
                                                *current_token = token(T_USE);
                                                return *current_token;
                                            }

        "as"                                {
                                                *current_token = token(T_AS);
                                                return *current_token;
                                            }

        "ret"                               {
                                                *current_token = token(T_RET);
                                                return *current_token;
                                            }

        "u8"                                {
                                                *current_token = token(T_U8);
                                                return *current_token;
                                            }

        "u16"                               {
                                                *current_token = token(T_U16);
                                                return *current_token;
                                            }

        "u32"                               {
                                                *current_token = token(T_U32);
                                                return *current_token;
                                            }

        "u64"                               {
                                                *current_token = token(T_U64);
                                                return *current_token;
                                            }

        "i8"                                {
                                                *current_token = token(T_I8);
                                                return *current_token;
                                            }

        "i16"                               {
                                                *current_token = token(T_I16);
                                                return *current_token;
                                            }

        "i32"                               {
                                                *current_token = token(T_I32);
                                                return *current_token;
                                            }

        "i64"                               {
                                                *current_token = token(T_I64);
                                                return *current_token;
                                            }

        "f32"                               {
                                                *current_token = token(T_F32);
                                                return *current_token;
                                            }

        "f64"                               {
                                                *current_token = token(T_F64);
                                                return *current_token;
                                            }

        [&]                                 {
                                                *current_token = token(T_AMPERSAND);
                                                return *current_token;
                                            }

        [\x5e]                              {
                                                *current_token = token(T_CIRCUMFLEX);
                                                return *current_token;
                                            }

        [:]                                 {
                                                *current_token = token(T_COLON);
                                                return *current_token;
                                            }

        [;]                                 {
                                                *current_token = token(T_SEMICOLON);
                                                return *current_token;
                                            }

        [,]                                 {
                                                *current_token = token(T_COMMA);
                                                return *current_token;
                                            }

        [\x7b]                              {
                                                *current_token = token(T_L_C_BRACKET);
                                                return *current_token;
                                            }

        [\x7d]                              {
                                                *current_token = token(T_R_C_BRACKET);
                                                return *current_token;
                                            }

        [\x28]                              {
                                                *current_token = token(T_L_R_BRACKET);
                                                return *current_token;
                                            }

        [\x29]                              {
                                                *current_token = token(T_R_R_BRACKET);
                                                return *current_token;
                                            }

        [\x5b]                              {
                                                *current_token = token(T_L_S_BRACKET);
                                                return *current_token;
                                            }

        [\x5d]                              {
                                                *current_token = token(T_R_S_BRACKET);
                                                return *current_token;
                                            }

        [\x2a]                              {
                                                *current_token = token(T_ASTERIX);
                                                return *current_token;
                                            }

        [\x2b]                              {
                                                *current_token = token(T_PLUS);
                                                return *current_token;
                                            }

        [\x2d]                              {
                                                *current_token = token(T_MINUS);
                                                return *current_token;
                                            }

        [\x2f]                              {
                                                *current_token = token(T_SLASH);
                                                return *current_token;
                                            }

        [\x2e]                              {
                                                *current_token = token(T_DOT);
                                                return *current_token;
                                            }

        [%]                                 {
                                                *current_token = token(T_PERCENT);
                                                return *current_token;
                                            }

        [!]                                 {
                                                *current_token = token(T_EXCLAMATIONMARK);
                                                return *current_token;
                                            }

        [?]                                 {
                                                *current_token = token(T_QUESTIONMARK);
                                                return *current_token;
                                            }

        [<]                                 {
                                                *current_token = token(T_LESS_THAN);
                                                return *current_token;
                                            }

        [>]                                 {
                                                *current_token = token(T_GREATER_THAN);
                                                return *current_token;
                                            }

        [\x7c]                              {
                                                *current_token = token(T_PIPE);
                                                return *current_token;
                                            }

        [\x7e]                              {
                                                *current_token = token(T_TILDE);
                                                return *current_token;
                                            }

        [0-9]+		                        {
                                                *current_token = token(T_INTEGER);
                                                current_token->set_int_val(atoi(buffer));
                                                return *current_token;
                                            }

        [0-9]+[\x2e][0-9]+                  {
                                                *current_token = token(T_FLOAT);
                                                current_token->set_float_val(atof(buffer));
                                                return *current_token;
                                            }

        [a-zA-Z_][a-zA-Z0-9_]*              {
                                                *current_token = token(T_ID);
                                                current_token->set_str_val(buffer);
                                                return *current_token;
                                            }

    */
}
