%{
#include <stdio.h>
#include <cstdlib>
// only within toolchain
//#include <lexfix.h>

#include <string>
#include <astnodes/allnodes.h>
#include <set>
#include <Compiler.h>
using namespace dcpucc::astnodes;

#include "parser.hpp"

void count();
bool comment();
bool comment_line();
int check_type();
std::string* yyfilename = new std::string("<fixmefile>");
std::vector<std::string> yylines;
std::string yycurline;
int yylineno_offset;
extern int string_return;
extern std::set<std::string> activeTypedef;
extern dcpucc::Compiler* compiler;
bool handle_lineinfo();

#define YY_INPUT(buf,result,max_size) \
{ \
    size_t chars_read = 0;\
    size_t size_to_read = max_size;\
    if (!compiler->getInput(buf, chars_read, size_to_read))\
    { \
        result = YY_NULL;\
    } else { \
        result = chars_read;\
    }\
}


%}

%option yylineno
%option nounput

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
%x AT_ASM
%x IN_ASM_BLOCK
%x IN_ASM_COMMENT
%x IN_ASM_STRING
%x IN_ASM_CHAR
%x IN_COMMENT
%x IN_COMMENT_LINE

%%

\#                      { count(); if(!handle_lineinfo()) return ERROR; }

"//"                    { count(); BEGIN(IN_COMMENT_LINE); }
<IN_COMMENT_LINE>\n     { count(); BEGIN(INITIAL); }
<IN_COMMENT_LINE>.      { count(); }
"/*"                    { count(); BEGIN(IN_COMMENT); }
<IN_COMMENT>"*/"        { count(); BEGIN(INITIAL); }
<IN_COMMENT>.           { count(); }


    /* C keywords */
"auto"                  { count(); return yylval.token = AUTO; }
"break"                 { count(); return yylval.token = BREAK; }
"case"                  { count(); return yylval.token = CASE; }
"char"                  { count(); return yylval.token = CHAR; }
"const"                 { count(); return yylval.token = CONST; }
"continue"              { count(); return yylval.token = CONTINUE; }
"default"               { count(); return yylval.token = DEFAULT; }
"do"                    { count(); return yylval.token = DO; }
"double"                { count(); return yylval.token = DOUBLE; }
"else"                  { count(); return yylval.token = ELSE; }
"enum"                  { count(); return yylval.token = ENUM; }
"extern"                { count(); return yylval.token = EXTERN; }
"float"                 { count(); return yylval.token = FLOAT; }
"for"                   { count(); return yylval.token = FOR; }
"goto"                  { count(); return yylval.token = GOTO; }
"if"                    { count(); return yylval.token = IF; }
"int"                   { count(); return yylval.token = INT; }
"long"                  { count(); return yylval.token = LONG; }
"register"              { count(); return yylval.token = REGISTER; }
"return"                { count(); return yylval.token = RETURN; }
"short"                 { count(); return yylval.token = SHORT; }
"signed"                { count(); return yylval.token = SIGNED; }
"sizeof"                { count(); return yylval.token = SIZEOF; }
"static"                { count(); return yylval.token = STATIC; }
"struct"                { count(); return yylval.token = STRUCT; }
"switch"                { count(); return yylval.token = SWITCH; }
"typedef"               { count(); return yylval.token = TYPEDEF; }
"union"                 { count(); return yylval.token = UNION; }
"unsigned"              { count(); return yylval.token = UNSIGNED; }
"void"                  { count(); return yylval.token = VOID; }
"volatile"              { count(); return yylval.token = VOLATILE; }
"while"                 { count(); return yylval.token = WHILE; }


    /* Build-In functions */
"__builtin_va_start"    { count(); return BUILDIN_VA_START; }


    /* Inline assembly */
"__asm"                 { count(); BEGIN(AT_ASM); }
<AT_ASM>\{              { count(); BEGIN(IN_ASM_BLOCK); yylval.string = new std::string(); }
<AT_ASM>\n              { count(); }
<AT_ASM>[ \t]+          /* ignore whitespace */;
<AT_ASM>[^\{]           { count(); return ERROR; }

<IN_ASM_BLOCK>;         { count(); BEGIN(IN_ASM_COMMENT); *yylval.string += yytext; }
<IN_ASM_BLOCK>\'        { count(); BEGIN(IN_ASM_CHAR); *yylval.string += yytext; }
<IN_ASM_BLOCK>\"        { count(); BEGIN(IN_ASM_STRING); *yylval.string += yytext; }
<IN_ASM_BLOCK>\}        { count(); BEGIN(INITIAL); return ASSEMBLY; }
<IN_ASM_BLOCK>\n         { count();  *yylval.string += yytext; }
<IN_ASM_BLOCK>.         { count();  *yylval.string += yytext; }

    /* comments in ASM block */
<IN_ASM_COMMENT>\n      { count();  BEGIN(IN_ASM_BLOCK); *yylval.string += "\n"; }
<IN_ASM_COMMENT>.       { count();  *yylval.string += yytext; }

    /* character literals in ASM blocks */
<IN_ASM_CHAR>\'         { count(); BEGIN(IN_ASM_BLOCK); *yylval.string += yytext; }
<IN_ASM_CHAR>\\\'       { count(); *yylval.string += "\\'"; }
<IN_ASM_CHAR>.          { count(); *yylval.string += yytext; }

    /* string literals in ASM blocks */
<IN_ASM_STRING>\"      { count(); BEGIN(IN_ASM_BLOCK); *yylval.string += yytext; }
<IN_ASM_STRING>\\\"    { count(); *yylval.string += "\\\""; }
<IN_ASM_STRING>.       { count(); *yylval.string += yytext; }


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


"..."                   { count(); return yylval.token = ELLIPSIS; }
">>="                   { count(); return yylval.token = RIGHT_ASSIGN; }
"<<="                   { count(); return yylval.token = LEFT_ASSIGN; }
"+="                    { count(); return yylval.token = ADD_ASSIGN; }
"-="                    { count(); return yylval.token = SUB_ASSIGN; }
"*="                    { count(); return yylval.token = MUL_ASSIGN; }
"/="                    { count(); return yylval.token = DIV_ASSIGN; }
"%="                    { count(); return yylval.token = MOD_ASSIGN; }
"&="                    { count(); return yylval.token = AND_ASSIGN; }
"^="                    { count(); return yylval.token = XOR_ASSIGN; }
"|="                    { count(); return yylval.token = OR_ASSIGN; }
">>"                    { count(); return yylval.token = RIGHT_OP; }
"<<"                    { count(); return yylval.token = LEFT_OP; }
"++"                    { count(); return yylval.token = INC_OP; }
"--"                    { count(); return yylval.token = DEC_OP; }
"->"                    { count(); return yylval.token = PTR_OP; }
"&&"                    { count(); return yylval.token = AND_OP; }
"||"                    { count(); return yylval.token = OR_OP; }
"<="                    { count(); return yylval.token = LE_OP; }
">="                    { count(); return yylval.token = GE_OP; }
"=="                    { count(); return yylval.token = EQ_OP; }
"!="                    { count(); return yylval.token = NE_OP; }
";"                     { count(); return yylval.token = SEMICOLON; }
("{"|"<%")              { count(); return yylval.token = BRACE_OPEN; }
("}"|"%>")              { count(); return yylval.token = BRACE_CLOSE; }
","                     { count(); return yylval.token = COMMA; }
":"                     { count(); return yylval.token = COLON; }
"="                     { count(); return yylval.token = ASSIGN_EQUAL; }
"("                     { count(); return yylval.token = CURVED_OPEN; }
")"                     { count(); return yylval.token = CURVED_CLOSE; }
("["|"<:")              { count(); return yylval.token = SQUARE_OPEN; }
("]"|":>")              { count(); return yylval.token = SQUARE_CLOSE; }
"."                     { count(); return yylval.token = DOT; }
"&"                     { count(); return yylval.token = BIN_AND_OP; }
"!"                     { count(); return yylval.token = NOT_OP; }
"~"                     { count(); return yylval.token = BIN_INV_OP; }
"-"                     { count(); return yylval.token = SUB_OP; }
"+"                     { count(); return yylval.token = ADD_OP; }
"*"                     { count(); return yylval.token = MUL_OP; }
"/"                     { count(); return yylval.token = DIV_OP; }
"%"                     { count(); return yylval.token = MOD_OP; }
"<"                     { count(); return yylval.token = LT_OP; }
">"                     { count(); return yylval.token = GT_OP; }
"^"                     { count(); return yylval.token = BIN_XOR_OP; }
"|"                     { count(); return yylval.token = BIN_OR_OP; }
"?"                     { count(); return yylval.token = TERNARY_IF; }

[ \t\v\n\f]             { count(); }
    /* ignore bad characters, and don't print them to stdout */
.                       { count(); }
<*>.|\n                 { count(); }

%%

// state variable
int string_return = INITIAL;

// the set that holds the type names that have already been declared by typedefs
std::set<std::string> activeTypedef;

int yywrap()
{
        return(1);
}


bool handle_lineinfo()
{
    std::string line;
    char c;
    while ((c = yyinput()) != '\n' && c != 0 && c != EOF)
    {
        line += c;
    }
    yylines.push_back(std::string(""));

    std::istringstream iss(line);
    int lineno;
    if (!(iss >> std::ws >> lineno >> std::ws )) { return false; } // error

    std::string filename( (std::istreambuf_iterator<char>( iss )),
                            (std::istreambuf_iterator<char>()) );
    
    yyfilename = new std::string(filename);
    yylineno_offset = lineno - yylineno;

    return true;
}

int yycolumn = 0;

void count()
{
    int i;

    for (i = 0; yytext[i] != '\0'; i++)
    {
        
        if (yytext[i] == '\n')
        {
            yycolumn = 0;
            yylines.push_back(yycurline);
            yycurline = std::string("");
        }
        else if (yytext[i] == '\t')
        {
            yycurline += yytext[i];
            yycolumn += 8 - (yycolumn % 8);
        }
        else
        {
            yycurline += yytext[i];
            yycolumn++;
        }
    }
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
