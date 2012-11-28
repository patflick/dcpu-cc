%{
#include <stdio.h>
// only within toolchain
//#include <lexfix.h>

#include <string>
#include <nodes/allnodes.h>
using namespace dtcc::astnodes;

#include "parser.hpp"

// only within toolchain
/*
extern "C"
{
    #include <rparse.h>
}
*/

void count();
bool comment();
int check_type();
extern int string_return;
%}



D                       [0-9]
L                       [a-zA-Z_]
H                       [a-fA-F0-9]
E                       [Ee][+-]?{D}+
FS                      (f|F|l|L)
IS                      (u|U|l|L)*


%x IN_CHAR
%x IN_STRING

%%
"/*"                    { comment(); }

"auto"                  { count(); return(AUTO); }
"break"                 { count(); return(BREAK); }
"case"                  { count(); return(CASE); }
"char"                  { count(); return(CHAR); }
"const"                 { count(); return(CONST); }
"continue"              { count(); return(CONTINUE); }
"default"               { count(); return(DEFAULT); }
"do"                    { count(); return(DO); }
"double"                { count(); return(DOUBLE); }
"else"                  { count(); return(ELSE); }
"enum"                  { count(); return(ENUM); }
"extern"                { count(); return(EXTERN); }
"float"                 { count(); return(FLOAT); }
"for"                   { count(); return(FOR); }
"goto"                  { count(); return(GOTO); }
"if"                    { count(); return(IF); }
"int"                   { count(); return(INT); }
"long"                  { count(); return(LONG); }
"register"              { count(); return(REGISTER); }
"return"                { count(); return(RETURN); }
"short"                 { count(); return(SHORT); }
"signed"                { count(); return(SIGNED); }
"sizeof"                { count(); return(SIZEOF); }
"static"                { count(); return(STATIC); }
"struct"                { count(); return(STRUCT); }
"switch"                { count(); return(SWITCH); }
"typedef"               { count(); return(TYPEDEF); }
"union"                 { count(); return(UNION); }
"unsigned"              { count(); return(UNSIGNED); }
"void"                  { count(); return(VOID); }
"volatile"              { count(); return(VOLATILE); }
"while"                 { count(); return(WHILE); }

{L}({L}|{D})*           { count(); return(check_type()); }

0[xX]{H}+{IS}?          { count(); return(CONSTANT); }
0{D}+{IS}?              { count(); return(CONSTANT); }
{D}+{IS}?               { count(); return(CONSTANT); }
L?'(\\.|[^\\'])+'       { count(); return(CONSTANT); }

{D}+{E}{FS}?            { count(); return(CONSTANT); }
{D}*"."{D}+({E})?{FS}?  { count(); return(CONSTANT); }
{D}+"."{D}*({E})?{FS}?  { count(); return(CONSTANT); }


    /* String and character analysis */

\'                                      { count(); yylval.string = new std::string(); BEGIN(IN_CHAR); }
\"                                      { count(); yylval.string = new std::string(); BEGIN(IN_STRING); }
<IN_CHAR>\'                             { count(); BEGIN(string_return); return CHARACTER_LITERAL; }
<IN_STRING>\"                           { count(); BEGIN(string_return); return STRING_LITERAL; }
<IN_STRING,IN_CHAR>\\a                  { count(); *yylval.string += '\a'; }
<IN_STRING,IN_CHAR>\\b                  { count(); *yylval.string += '\b'; }
<IN_STRING,IN_CHAR>\\f                  { count(); *yylval.string += '\f'; }
<IN_STRING,IN_CHAR>\\n                  { count(); *yylval.string += '\n'; }
<IN_STRING,IN_CHAR>\\r                  { count(); *yylval.string += '\r'; }
<IN_STRING,IN_CHAR>\\t                  { count(); *yylval.string += '\t'; }
<IN_STRING,IN_CHAR>\\v                  { count(); *yylval.string += '\v'; }
<IN_STRING,IN_CHAR>\\\'                 { count(); *yylval.string += '\''; }
<IN_STRING,IN_CHAR>\\\"                 { count(); *yylval.string += '\"'; }
<IN_STRING,IN_CHAR>\\\\                 { count(); *yylval.string += '\\'; }
<IN_STRING,IN_CHAR>\\\?                 { count(); *yylval.string += '\?'; }
<IN_STRING,IN_CHAR>\\[0-7]{1,3}         { count(); *yylval.string += (char)strtoul(yytext + 1, NULL, 8); }
<IN_STRING,IN_CHAR>\\x[a-fA-F0-9]{2}    { count(); *yylval.string += (char)strtoul(yytext + 2, NULL, 16); }
<IN_STRING,IN_CHAR>\\[0-9]+             { count(); return ERROR; }
<IN_STRING,IN_CHAR>\\(.|\n)             { count(); *yylval.string += yytext[1]; }
<IN_STRING>[^\\\n\"]+                   { count(); *yylval.string += yytext; }
<IN_CHAR>[^\\\n\']+                     { count(); *yylval.string += yytext; }


L?\"(\\.|[^\\"])*\"     { count(); return(STRING_LITERAL); }

"..."                   { count(); return(ELLIPSIS); }
">>="                   { count(); return(RIGHT_ASSIGN); }
"<<="                   { count(); return(LEFT_ASSIGN); }
"+="                    { count(); return(ADD_ASSIGN); }
"-="                    { count(); return(SUB_ASSIGN); }
"*="                    { count(); return(MUL_ASSIGN); }
"/="                    { count(); return(DIV_ASSIGN); }
"%="                    { count(); return(MOD_ASSIGN); }
"&="                    { count(); return(AND_ASSIGN); }
"^="                    { count(); return(XOR_ASSIGN); }
"|="                    { count(); return(OR_ASSIGN); }
">>"                    { count(); return(RIGHT_OP); }
"<<"                    { count(); return(LEFT_OP); }
"++"                    { count(); return(INC_OP); }
"--"                    { count(); return(DEC_OP); }
"->"                    { count(); return(PTR_OP); }
"&&"                    { count(); return(AND_OP); }
"||"                    { count(); return(OR_OP); }
"<="                    { count(); return(LE_OP); }
">="                    { count(); return(GE_OP); }
"=="                    { count(); return(EQ_OP); }
"!="                    { count(); return(NE_OP); }
";"                     { count(); return(SEMICOLON); }
("{"|"<%")              { count(); return(BRACE_OPEN); }
("}"|"%>")              { count(); return(BRACE_CLOSE); }
","                     { count(); return(COMMA); }
":"                     { count(); return(COLON); }
"="                     { count(); return(ASSIGN_EQUAL); }
"("                     { count(); return(CURVED_OPEN); }
")"                     { count(); return(CURVED_CLOSE); }
("["|"<:")              { count(); return(SQUARE_OPEN); }
("]"|":>")              { count(); return(SQUARE_CLOSE); }
"."                     { count(); return(DOT); }
"&"                     { count(); return(BIN_AND_OP); }
"!"                     { count(); return(NOT_OP); }
"~"                     { count(); return(BIN_INV_OP); }
"-"                     { count(); return(SUB_OP); }
"+"                     { count(); return(ADD_OP); }
"*"                     { count(); return(MUL_OP); }
"/"                     { count(); return(DIV_OP); }
"%"                     { count(); return(MOD_OP); }
"<"                     { count(); return(LT_OP); }
">"                     { count(); return(GT_OP); }
"^"                     { count(); return(BIN_XOR_OP); }
"|"                     { count(); return(BIN_OR_OP); }
"?"                     { count(); return(TERNARY_IF); }

[ \t\v\n\f]             { count(); }
.                       { /* ignore bad characters */ }

%%

// state variable
int string_return = INITIAL;


int yywrap()
{
        return(1);
}


bool comment()
{
    char c;

loop:
    while ((c = yyinput()) != '*' && c != 0 && c != EOF) ;

star_loop:
    if ((c = yyinput()) != '/' && c != 0 && c != EOF)
        if (c == '*')
            goto star_loop;
        else
            goto loop;
    
    if (c == EOF)
        return false;
    return true;
}

bool comment_line()
{
    char c;

    while ((c = yyinput()) != '\n' && c != 0 && c != EOF) ;
    
    if (c == EOF)
        return false;
    return true;
}


int column = 0;

void count()
{
        int i;

        for (i = 0; yytext[i] != '\0'; i++)
                if (yytext[i] == '\n')
                        column = 0;
                else if (yytext[i] == '\t')
                        column += 8 - (column % 8);
                else
                        column++;

        ECHO;
}


int check_type()
{
    yylval.string = new std::string(yytext);
/*
* pseudo code --- this is what it should check
*
*       if (yytext == type_name)
*               return(TYPE_NAME);
*
*       return(IDENTIFIER);
*/

/*
*       it actually will only return IDENTIFIER
*/

    return(IDENTIFIER);
}