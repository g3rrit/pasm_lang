/* Generated by re2c 1.0.1 on Sun Dec  9 23:10:38 2018 */
#line 1 "./lexer/lexer.re"
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

    
#line 40 "./src/lexer/lexer.cc"
{
	YYCTYPE yych;
	yych = YYPEEK ();
	switch (yych) {
	case '\t':
	case '\r':
	case ' ':	goto yy3;
	case '\n':	goto yy5;
	case '!':	goto yy7;
	case '%':	goto yy9;
	case '&':	goto yy11;
	case '(':	goto yy13;
	case ')':	goto yy15;
	case '*':	goto yy17;
	case '+':	goto yy19;
	case ',':	goto yy21;
	case '-':	goto yy23;
	case '.':	goto yy25;
	case '/':	goto yy27;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy29;
	case ':':	goto yy32;
	case ';':	goto yy34;
	case '<':	goto yy36;
	case '>':	goto yy38;
	case '?':	goto yy40;
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'g':
	case 'h':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 's':
	case 't':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy42;
	case '[':	goto yy45;
	case ']':	goto yy47;
	case '^':	goto yy49;
	case 'a':	goto yy51;
	case 'f':	goto yy52;
	case 'i':	goto yy53;
	case 'r':	goto yy54;
	case 'u':	goto yy55;
	case '{':	goto yy56;
	case '|':	goto yy58;
	case '}':	goto yy60;
	case '~':	goto yy62;
	default:	goto yy2;
	}
yy2:
	YYRESTORE ();
	goto yy31;
yy3:
	YYSKIP ();
#line 39 "./lexer/lexer.re"
	{
                                                *current_token = token(OTHER);
                                                return *current_token;
                                            }
#line 147 "./src/lexer/lexer.cc"
yy5:
	YYSKIP ();
#line 43 "./lexer/lexer.re"
	{
                                                line_num++;
                                                *current_token = token(OTHER);
                                                return *current_token;
                                            }
#line 156 "./src/lexer/lexer.cc"
yy7:
	YYSKIP ();
#line 199 "./lexer/lexer.re"
	{
                                                *current_token = token(EXCLAMATIONMARK);
                                                return *current_token;
                                            }
#line 164 "./src/lexer/lexer.cc"
yy9:
	YYSKIP ();
#line 194 "./lexer/lexer.re"
	{
                                                *current_token = token(PERCENT);
                                                return *current_token;
                                            }
#line 172 "./src/lexer/lexer.cc"
yy11:
	YYSKIP ();
#line 114 "./lexer/lexer.re"
	{
                                                *current_token = token(AMPERSAND);
                                                return *current_token;
                                            }
#line 180 "./src/lexer/lexer.cc"
yy13:
	YYSKIP ();
#line 149 "./lexer/lexer.re"
	{
                                                *current_token = token(L_R_BRACKET);
                                                return *current_token;
                                            }
#line 188 "./src/lexer/lexer.cc"
yy15:
	YYSKIP ();
#line 154 "./lexer/lexer.re"
	{
                                                *current_token = token(R_R_BRACKET);
                                                return *current_token;
                                            }
#line 196 "./src/lexer/lexer.cc"
yy17:
	YYSKIP ();
#line 169 "./lexer/lexer.re"
	{
                                                *current_token = token(ASTERIX);
                                                return *current_token;
                                            }
#line 204 "./src/lexer/lexer.cc"
yy19:
	YYSKIP ();
#line 174 "./lexer/lexer.re"
	{
                                                *current_token = token(PLUS);
                                                return *current_token;
                                            }
#line 212 "./src/lexer/lexer.cc"
yy21:
	YYSKIP ();
#line 134 "./lexer/lexer.re"
	{
                                                *current_token = token(COMMA);
                                                return *current_token;
                                            }
#line 220 "./src/lexer/lexer.cc"
yy23:
	YYSKIP ();
#line 179 "./lexer/lexer.re"
	{
                                                *current_token = token(MINUS);
                                                return *current_token;
                                            }
#line 228 "./src/lexer/lexer.cc"
yy25:
	YYSKIP ();
#line 189 "./lexer/lexer.re"
	{
                                                *current_token = token(DOT);
                                                return *current_token;
                                            }
#line 236 "./src/lexer/lexer.cc"
yy27:
	YYSKIP ();
#line 184 "./lexer/lexer.re"
	{
                                                *current_token = token(SLASH);
                                                return *current_token;
                                            }
#line 244 "./src/lexer/lexer.cc"
yy29:
	YYSKIP ();
	YYBACKUP ();
	yych = YYPEEK ();
	switch (yych) {
	case '.':	goto yy64;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy29;
	default:	goto yy31;
	}
yy31:
#line 229 "./lexer/lexer.re"
	{
                                                *current_token = token(INTEGER);
                                                current_token->set_int_val(atoi(buffer));
                                                return *current_token;
                                            }
#line 270 "./src/lexer/lexer.cc"
yy32:
	YYSKIP ();
#line 124 "./lexer/lexer.re"
	{
                                                *current_token = token(COLON);
                                                return *current_token;
                                            }
#line 278 "./src/lexer/lexer.cc"
yy34:
	YYSKIP ();
#line 129 "./lexer/lexer.re"
	{
                                                *current_token = token(SEMICOLON);
                                                return *current_token;
                                            }
#line 286 "./src/lexer/lexer.cc"
yy36:
	YYSKIP ();
#line 209 "./lexer/lexer.re"
	{
                                                *current_token = token(LESS_THAN);
                                                return *current_token;
                                            }
#line 294 "./src/lexer/lexer.cc"
yy38:
	YYSKIP ();
#line 214 "./lexer/lexer.re"
	{
                                                *current_token = token(GREATER_THAN);
                                                return *current_token;
                                            }
#line 302 "./src/lexer/lexer.cc"
yy40:
	YYSKIP ();
#line 204 "./lexer/lexer.re"
	{
                                                *current_token = token(QUESTIONMARK);
                                                return *current_token;
                                            }
#line 310 "./src/lexer/lexer.cc"
yy42:
	YYSKIP ();
	yych = YYPEEK ();
yy43:
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy42;
	default:	goto yy44;
	}
yy44:
#line 241 "./lexer/lexer.re"
	{
                                                *current_token = token(ID);
                                                current_token->set_str_val(buffer);
                                                return *current_token;
                                            }
#line 388 "./src/lexer/lexer.cc"
yy45:
	YYSKIP ();
#line 159 "./lexer/lexer.re"
	{
                                                *current_token = token(L_S_BRACKET);
                                                return *current_token;
                                            }
#line 396 "./src/lexer/lexer.cc"
yy47:
	YYSKIP ();
#line 164 "./lexer/lexer.re"
	{
                                                *current_token = token(R_S_BRACKET);
                                                return *current_token;
                                            }
#line 404 "./src/lexer/lexer.cc"
yy49:
	YYSKIP ();
#line 119 "./lexer/lexer.re"
	{
                                                *current_token = token(CIRCUMFLEX);
                                                return *current_token;
                                            }
#line 412 "./src/lexer/lexer.cc"
yy51:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case 's':	goto yy65;
	default:	goto yy43;
	}
yy52:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '3':	goto yy67;
	case '6':	goto yy68;
	default:	goto yy43;
	}
yy53:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '1':	goto yy69;
	case '3':	goto yy70;
	case '6':	goto yy71;
	case '8':	goto yy72;
	default:	goto yy43;
	}
yy54:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case 'e':	goto yy74;
	default:	goto yy43;
	}
yy55:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '1':	goto yy75;
	case '3':	goto yy76;
	case '6':	goto yy77;
	case '8':	goto yy78;
	case 's':	goto yy80;
	default:	goto yy43;
	}
yy56:
	YYSKIP ();
#line 139 "./lexer/lexer.re"
	{
                                                *current_token = token(L_C_BRACKET);
                                                return *current_token;
                                            }
#line 463 "./src/lexer/lexer.cc"
yy58:
	YYSKIP ();
#line 219 "./lexer/lexer.re"
	{
                                                *current_token = token(PIPE);
                                                return *current_token;
                                            }
#line 471 "./src/lexer/lexer.cc"
yy60:
	YYSKIP ();
#line 144 "./lexer/lexer.re"
	{
                                                *current_token = token(R_C_BRACKET);
                                                return *current_token;
                                            }
#line 479 "./src/lexer/lexer.cc"
yy62:
	YYSKIP ();
#line 224 "./lexer/lexer.re"
	{
                                                *current_token = token(TILDE);
                                                return *current_token;
                                            }
#line 487 "./src/lexer/lexer.cc"
yy64:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy81;
	default:	goto yy2;
	}
yy65:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy42;
	default:	goto yy66;
	}
yy66:
#line 54 "./lexer/lexer.re"
	{
                                                *current_token = token(AS);
                                                return *current_token;
                                            }
#line 579 "./src/lexer/lexer.cc"
yy67:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '2':	goto yy84;
	default:	goto yy43;
	}
yy68:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '4':	goto yy86;
	default:	goto yy43;
	}
yy69:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '6':	goto yy88;
	default:	goto yy43;
	}
yy70:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '2':	goto yy90;
	default:	goto yy43;
	}
yy71:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '4':	goto yy92;
	default:	goto yy43;
	}
yy72:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy42;
	default:	goto yy73;
	}
yy73:
#line 84 "./lexer/lexer.re"
	{
                                                *current_token = token(I8);
                                                return *current_token;
                                            }
#line 690 "./src/lexer/lexer.cc"
yy74:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case 't':	goto yy94;
	default:	goto yy43;
	}
yy75:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '6':	goto yy96;
	default:	goto yy43;
	}
yy76:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '2':	goto yy98;
	default:	goto yy43;
	}
yy77:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '4':	goto yy100;
	default:	goto yy43;
	}
yy78:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy42;
	default:	goto yy79;
	}
yy79:
#line 64 "./lexer/lexer.re"
	{
                                                *current_token = token(U8);
                                                return *current_token;
                                            }
#line 794 "./src/lexer/lexer.cc"
yy80:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case 'e':	goto yy102;
	default:	goto yy43;
	}
yy81:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy81;
	default:	goto yy83;
	}
yy83:
#line 235 "./lexer/lexer.re"
	{
                                                *current_token = token(FLOAT);
                                                current_token->set_float_val(atof(buffer));
                                                return *current_token;
                                            }
#line 825 "./src/lexer/lexer.cc"
yy84:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy42;
	default:	goto yy85;
	}
yy85:
#line 104 "./lexer/lexer.re"
	{
                                                *current_token = token(F32);
                                                return *current_token;
                                            }
#line 901 "./src/lexer/lexer.cc"
yy86:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy42;
	default:	goto yy87;
	}
yy87:
#line 109 "./lexer/lexer.re"
	{
                                                *current_token = token(F64);
                                                return *current_token;
                                            }
#line 977 "./src/lexer/lexer.cc"
yy88:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy42;
	default:	goto yy89;
	}
yy89:
#line 89 "./lexer/lexer.re"
	{
                                                *current_token = token(I16);
                                                return *current_token;
                                            }
#line 1053 "./src/lexer/lexer.cc"
yy90:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy42;
	default:	goto yy91;
	}
yy91:
#line 94 "./lexer/lexer.re"
	{
                                                *current_token = token(I32);
                                                return *current_token;
                                            }
#line 1129 "./src/lexer/lexer.cc"
yy92:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy42;
	default:	goto yy93;
	}
yy93:
#line 99 "./lexer/lexer.re"
	{
                                                *current_token = token(I64);
                                                return *current_token;
                                            }
#line 1205 "./src/lexer/lexer.cc"
yy94:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy42;
	default:	goto yy95;
	}
yy95:
#line 59 "./lexer/lexer.re"
	{
                                                *current_token = token(RET);
                                                return *current_token;
                                            }
#line 1281 "./src/lexer/lexer.cc"
yy96:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy42;
	default:	goto yy97;
	}
yy97:
#line 69 "./lexer/lexer.re"
	{
                                                *current_token = token(U16);
                                                return *current_token;
                                            }
#line 1357 "./src/lexer/lexer.cc"
yy98:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy42;
	default:	goto yy99;
	}
yy99:
#line 74 "./lexer/lexer.re"
	{
                                                *current_token = token(U32);
                                                return *current_token;
                                            }
#line 1433 "./src/lexer/lexer.cc"
yy100:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy42;
	default:	goto yy101;
	}
yy101:
#line 79 "./lexer/lexer.re"
	{
                                                *current_token = token(U64);
                                                return *current_token;
                                            }
#line 1509 "./src/lexer/lexer.cc"
yy102:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':	goto yy42;
	default:	goto yy103;
	}
yy103:
#line 49 "./lexer/lexer.re"
	{
                                                *current_token = token(USE);
                                                return *current_token;
                                            }
#line 1585 "./src/lexer/lexer.cc"
}
#line 247 "./lexer/lexer.re"

}
