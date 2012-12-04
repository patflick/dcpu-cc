%{
#include <stdio.h>
#include <cstdlib>
// only within toolchain
//#include <lexfix.h>

#include <string>
#include <nodes/allnodes.h>
#include <set>
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
extern std::set<std::string> activeTypedef;
%}



D                       [0-9]
O                       [0-7]
A                       [a-zA-Z_]
H                       [a-fA-F0-9]
E                       [Ee][+-]?{D}+
F                       (f|F)
L                       (l|L)
U                       (u|U)


%x IN_CHAR
%x IN_STRING

%%
"/*"                    { comment(); }

"auto"                  { count(); return yylval.token = AUTO; }
"break"                 { count(); return(BREAK); }
"case"                  { count(); return(CASE); }
"char"                  { count(); return yylval.token = CHAR; }
"const"                 { count(); return yylval.token = CONST; }
"continue"              { count(); return(CONTINUE); }
"default"               { count(); return(DEFAULT); }
"do"                    { count(); return(DO); }
"double"                { count(); return yylval.token = DOUBLE; }
"else"                  { count(); return(ELSE); }
"enum"                  { count(); return(ENUM); }
"extern"                { count(); return yylval.token = EXTERN; }
"float"                 { count(); return yylval.token = FLOAT; }
"for"                   { count(); return(FOR); }
"goto"                  { count(); return(GOTO); }
"if"                    { count(); return(IF); }
"int"                   { count(); return yylval.token = INT; }
"long"                  { count(); return yylval.token = LONG; }
"register"              { count(); return yylval.token = REGISTER; }
"return"                { count(); return(RETURN); }
"short"                 { count(); return yylval.token = SHORT; }
"signed"                { count(); return yylval.token = SIGNED; }
"sizeof"                { count(); return(SIZEOF); }
"static"                { count(); return yylval.token = STATIC; }
"struct"                { count(); return yylval.token = STRUCT; }
"switch"                { count(); return(SWITCH); }
"typedef"               { count(); return yylval.token = TYPEDEF; }
"union"                 { count(); return yylval.token = UNION; }
"unsigned"              { count(); return yylval.token = UNSIGNED; }
"void"                  { count(); return yylval.token = VOID; }
"volatile"              { count(); return yylval.token = VOLATILE; }
"while"                 { count(); return(WHILE); }

    /* Identifier or possibly typedef */
{A}({A}|{D})*           { count(); return(check_type()); }


    /* numerical constants/literals */
    
    /* hex int */
0[xX]{H}+               { count(); yylval.intLiteral = strtoul(yytext, NULL, 16); return(INT_LITERAL); }
0[xX]{H}+{U}            { count(); yylval.intLiteral = strtoul(yytext, NULL, 16); return(UINT_LITERAL); }
0[xX]{H}+{L}            { count(); yylval.intLiteral = strtoul(yytext, NULL, 16); return(LONG_LITERAL); }
0[xX]{H}+({U}{L}|{L}{U})    { count(); yylval.intLiteral = strtoul(yytext, NULL, 16); return(ULONG_LITERAL); }
    /* octal int */
0{O}+                   { count(); yylval.intLiteral = strtoul(yytext, NULL, 8); return(INT_LITERAL); }
0{O}+{U}                { count(); yylval.intLiteral = strtoul(yytext, NULL, 8); return(UINT_LITERAL); }
0{O}+{L}                { count(); yylval.intLiteral = strtoul(yytext, NULL, 8); return(LONG_LITERAL); }
0{O}+({U}{L}|{L}{U})    { count(); yylval.intLiteral = strtoul(yytext, NULL, 8); return(ULONG_LITERAL); }
    /* decimal int */
{D}+                    { count(); yylval.intLiteral = strtoul(yytext, NULL, 10); return(INT_LITERAL); }
{D}+{U}                 { count(); yylval.intLiteral = strtoul(yytext, NULL, 10); return(UINT_LITERAL); }
{D}+{L}                 { count(); yylval.intLiteral = strtoul(yytext, NULL, 10); return(LONG_LITERAL); }
{D}+({U}{L}|{L}{U})     { count(); yylval.intLiteral = strtoul(yytext, NULL, 10); return(ULONG_LITERAL); }
    /* binary int */
0b[0-1]+                { count(); yylval.intLiteral = strtoul(yytext, NULL, 2); return(INT_LITERAL); }
0b[0-1]+{U}             { count(); yylval.intLiteral = strtoul(yytext, NULL, 2); return(UINT_LITERAL); }
0b[0-1]+{L}             { count(); yylval.intLiteral = strtoul(yytext, NULL, 2); return(LONG_LITERAL); }
0b[0-1]+({U}{L}|{L}{U}) { count(); yylval.intLiteral = strtoul(yytext, NULL, 2); return(ULONG_LITERAL); }
    /* float */
{D}+{E}{F}              { count(); yylval.floatLiteral = strtod(yytext, NULL); return(FLOAT_LITERAL); }
{D}*"."{D}+({E})?{F}    { count(); yylval.floatLiteral = strtod(yytext, NULL); return(FLOAT_LITERAL); }
{D}+"."{D}*({E})?{F}    { count(); yylval.floatLiteral = strtod(yytext, NULL); return(FLOAT_LITERAL); }
    /* double */
{D}+{E}                 { count(); yylval.floatLiteral = strtod(yytext, NULL); return(DOUBLE_LITERAL); }
{D}*"."{D}+({E})?       { count(); yylval.floatLiteral = strtod(yytext, NULL); return(DOUBLE_LITERAL); }
{D}+"."{D}*({E})?       { count(); yylval.floatLiteral = strtod(yytext, NULL); return(DOUBLE_LITERAL); }
    /* long double */
{D}+{E}{L}              { count(); yylval.floatLiteral = strtod(yytext, NULL); return(LDOUBLE_LITERAL); }
{D}*"."{D}+({E})?{L}    { count(); yylval.floatLiteral = strtod(yytext, NULL); return(LDOUBLE_LITERAL); }
{D}+"."{D}*({E})?{L}    { count(); yylval.floatLiteral = strtod(yytext, NULL); return(LDOUBLE_LITERAL); }


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

// the set that holds the type names that have already been declared by typedefs
std::set<std::string> activeTypedef;

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


int yycolumn = 0;

void count()
{
        int i;

        for (i = 0; yytext[i] != '\0'; i++)
                if (yytext[i] == '\n')
                        yycolumn = 0;
                else if (yytext[i] == '\t')
                        yycolumn += 8 - (yycolumn % 8);
                else
                        yycolumn++;

        ECHO;
}


int check_type()
{
/*
* pseudo code --- this is what it should check
*
*       if (yytext == type_name)
*               return(TYPE_NAME);
*
*       return(IDENTIFIER);
*/

    yylval.string = new std::string(yytext);

    if (activeTypedef.find(std::string(yytext)) != activeTypedef.end())
    {
        // we've got ourselves a typedef here
        return(TYPE_NAME);
    }
    else
        return(IDENTIFIER);
}