/**

    File:           parser.y

    Project:        DCPU-16 Tools
    Component:      LibDCPU-ci-lang-c

    Authors:        Patrick Flick

    Description:    Defines parser for the compiler.
                    Taken from the official ANSI-C grammar.
                    Source: http://www.lysator.liu.se/c/ANSI-C-grammar-y.html

**/

%{

// include all nodes

// Turn on verbose error messages.
#define YYERROR_VERBOSE

// Defines the root node.
//NDeclarations* program;

// YY-stuff.
extern int yylex();
extern int yycolumn;
extern char * yytext;
// only within toolchain:
//extern bstring yyfilename;
void yyerror(const char *str);

%}

%token IDENTIFIER CONSTANT STRING_LITERAL SIZEOF
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME

%token TYPEDEF EXTERN STATIC AUTO REGISTER
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%start translation_unit


%%

primary_expression
        : IDENTIFIER
        {
            $$ = new Identifier(*$1);
        }
        | CONSTANT
        {
            $$ = new Constant($1);
        }
        | STRING_LITERAL
        {
            $$ = new StringLiteral(*$1);
        }
        | '(' expression ')'
        {
            $$ = $2;
        }
        ;

postfix_expression
        : primary_expression
        {
            $$ = $1;
        }
        | postfix_expression '[' expression ']'
        {
            $$ = new ArrayAccessOperator($1, $3);
        }
        | postfix_expression '(' ')'
        {
            $$ = new MethodCall($1, new Expressions());
        }
        | postfix_expression '(' argument_expression_list ')'
        {
            $$ = new MethodCall($1, $3);
        }
/* TODO structs and enums
        | postfix_expression '.' IDENTIFIER
        | postfix_expression PTR_OP IDENTIFIER
*/
        | postfix_expression INC_OP
        {
            $$ = new PostIncDec($2, $1);
        }
        | postfix_expression DEC_OP
        {
            $$ = new PostIncDec($2, $1);
        }
        ;

argument_expression_list
        : assignment_expression
        {
            $$ = new Expressions();
            $$->push_back($1);
        }
        | argument_expression_list ',' assignment_expression
        {
            $1->push_back($3);
            $$ = $1;
        }
        ;

unary_expression
        : postfix_expression
        {
            $$ = $1;
        }
        | INC_OP unary_expression
        {
            $$ = new PreIncDec($1, $2);
        }
        | DEC_OP unary_expression
        {
            $$ = new PreIncDec($1, $2);
        }
        | unary_operator cast_expression
        {
            $$ = new UnaryOperator($1, $2);
        }
        | SIZEOF unary_expression
        {
            $$ = new SizeOfOperator($2);
        }
        | SIZEOF '(' type_name ')'
        {
            $$ = new SizeOfOperator($3);
        }
        ;

unary_operator
        : '&'
        | '*'
        | '+'
        | '-'
        | '~'
        | '!'
        ;

cast_expression
        : unary_expression
        {
            $$ = $1;
        }
        | '(' type_name ')' cast_expression
        {
            $$ = new ExplicitCastOperator($2, $4);
        }
        ;

multiplicative_expression
        : cast_expression
        {
            $$ = $1;
        }
        | multiplicative_expression '*' cast_expression
        {
            $$ = new BinaryOperator($1, $2, $3);
        }
        | multiplicative_expression '/' cast_expression
        {
            $$ = new BinaryOperator($1, $2, $3);
        }
        | multiplicative_expression '%' cast_expression
        {
            $$ = new BinaryOperator($1, $2, $3);
        }
        ;

additive_expression
        : multiplicative_expression
        {
            $$ = $1;
        }
        | additive_expression '+' multiplicative_expression
        {
            $$ = new BinaryOperator($1, $2, $3);
        }
        | additive_expression '-' multiplicative_expression
        {
            $$ = new BinaryOperator($1, $2, $3);
        }
        ;

shift_expression
        : additive_expression
        {
            $$ = $1;
        }
        | shift_expression LEFT_OP additive_expression
        {
            $$ = new BinaryOperator($1, $2, $3);
        }
        | shift_expression RIGHT_OP additive_expression
        {
            $$ = new BinaryOperator($1, $2, $3);
        }
        ;

relational_expression
        : shift_expression
        {
            $$ = $1;
        }
        | relational_expression '<' shift_expression
        {
            $$ = new BinaryOperator($1, $2, $3);
        }
        | relational_expression '>' shift_expression
        {
            $$ = new BinaryOperator($1, $2, $3);
        }
        | relational_expression LE_OP shift_expression
        {
            $$ = new BinaryOperator($1, $2, $3);
        }
        | relational_expression GE_OP shift_expression
        {
            $$ = new BinaryOperator($1, $2, $3);
        }
        ;

equality_expression
        : relational_expression
        {
            $$ = $1;
        }
        | equality_expression EQ_OP relational_expression
        {
            $$ = new BinaryOperator($1, $2, $3);
        }
        | equality_expression NE_OP relational_expression
        {
            $$ = new BinaryOperator($1, $2, $3);
        }
        ;

and_expression
        : equality_expression
        {
            $$ = $1;
        }
        | and_expression '&' equality_expression
        {
            $$ = new BinaryOperator($1, $2, $3);
        }
        ;

exclusive_or_expression
        : and_expression
        {
            $$ = $1;
        }
        | exclusive_or_expression '^' and_expression
        {
            $$ = new BinaryOperator($1, $2, $3);
        }
        ;

inclusive_or_expression
        : exclusive_or_expression
        {
            $$ = $1;
        }
        | inclusive_or_expression '|' exclusive_or_expression
        {
            $$ = new BinaryOperator($1, $2, $3);
        }
        ;

logical_and_expression
        : inclusive_or_expression
        {
            $$ = $1;
        }
        | logical_and_expression AND_OP inclusive_or_expression
        {
            $$ = new BinaryOperator($1, $2, $3);
        }
        ;

logical_or_expression
        : logical_and_expression
        {
            $$ = $1;
        }
        | logical_or_expression OR_OP logical_and_expression
        {
            $$ = new BinaryOperator($1, $2, $3);
        }
        ;

conditional_expression
        : logical_or_expression
        {
            $$ = $1;
        }
        | logical_or_expression '?' expression ':' conditional_expression
        {
            $$ = new ConditionalOperator($1, $3, $5);
        }
        ;

assignment_expression
        : conditional_expression
        {
            $$ = $1;
        }
        | unary_expression assignment_operator assignment_expression
        {
            $$ = new AssignmentOperator($1, $2, $3);
        }
        ;

assignment_operator
        : '='
        | MUL_ASSIGN
        | DIV_ASSIGN
        | MOD_ASSIGN
        | ADD_ASSIGN
        | SUB_ASSIGN
        | LEFT_ASSIGN
        | RIGHT_ASSIGN
        | AND_ASSIGN
        | XOR_ASSIGN
        | OR_ASSIGN
        ;

expression
        : assignment_expression
        {
            $$ = new Expressions();
            $$->push_back($1);
        }
        | expression ',' assignment_expression
        {
            $1->push_back($3);
            $$ = $1;
        }
        ;

constant_expression
        : conditional_expression
        {
            $$ = $1;
        }
        ;

declaration
        : declaration_specifiers ';'
        {
            $$ = new Declaration($1, NULL);
        }
        | declaration_specifiers init_declarator_list ';'
        {
            $$ = new Declaration($1, $2);
        }
        ;

declaration_specifiers
        : storage_class_specifier
        {
            $$ = new DeclarationSpecifiers();
            $$->addStorageSpecifier($1);
        }
        | storage_class_specifier declaration_specifiers
        {
            $2->addStorageSpecifier($1);
            $$ = $2;
        }
        | type_specifier
        {
            $$ = new DeclarationSpecifiers();
            $$->addTypeSpecifier($1);
        }
        | type_specifier declaration_specifiers
        {
            $2->addTypeSpecifier($1);
            $$ = $2;
        }
        | type_qualifier
        {
            $$ = new DeclarationSpecifiers();
            $$->addTypeQualifier($1);
        }
        | type_qualifier declaration_specifiers
        {
            $2->addTypeQualifier($1);
            $$ = $2;
        }
        ;

init_declarator_list
        : init_declarator
        {
            $$ = new Declarators();
            $$->push_back($1);
        }
        | init_declarator_list ',' init_declarator
        {
            $1->push_back($3);
            $$ = $1;
        }
        ;

init_declarator
        : declarator
        {
            $$ = $1;
        }
        | declarator '=' initializer
        {
            $$ = $1;
            $$->setInitializer($3);
        }
        ;

storage_class_specifier
        : TYPEDEF
        {
            $$ = new StorageSpecifier($1);
        }
        | EXTERN
        {
            $$ = new StorageSpecifier($1);
        }
        | STATIC
        {
            $$ = new StorageSpecifier($1);
        }
        | AUTO
        {
            $$ = new StorageSpecifier($1);
        }
        | REGISTER
        {
            $$ = new StorageSpecifier($1);
        }
        ;

type_specifier
        : VOID
        {
            $$ = new TypeBaseSpecifier($1);
        }
        | CHAR
        {
            $$ = new TypeBaseSpecifier($1);
        }
        | SHORT
        {
            $$ = new TypeBaseSpecifier($1);
        }
        | INT
        {
            $$ = new TypeBaseSpecifier($1);
        }
        | LONG
        {
            $$ = new TypeBaseSpecifier($1);
        }
        | FLOAT
        {
            $$ = new TypeBaseSpecifier($1);
        }
        | DOUBLE
        {
            $$ = new TypeBaseSpecifier($1);
        }
        | SIGNED
        {
            $$ = new TypeBaseSpecifier($1);
        }
        | UNSIGNED
        {
            $$ = new TypeBaseSpecifier($1);
        }
/*
        // TODO structs and enums
        | struct_or_union_specifier
        | enum_specifier
*/
        | TYPE_NAME
        {
            $$ = new TypeNameSpecifier($1);
        }
        ;

/*
struct_or_union_specifier
        : struct_or_union IDENTIFIER '{' struct_declaration_list '}'
        | struct_or_union '{' struct_declaration_list '}'
        | struct_or_union IDENTIFIER
        ;

struct_or_union
        : STRUCT
        | UNION
        ;

struct_declaration_list
        : struct_declaration
        | struct_declaration_list struct_declaration
        ;

struct_declaration
        : specifier_qualifier_list struct_declarator_list ';'
        ;
*/


specifier_qualifier_list
        : type_specifier
        {
            $$ = new DeclarationSpecifiers();
            $$->addTypeSpecifier($1);
        }
        | type_specifier specifier_qualifier_list
        {
            $2->addTypeSpecifier($1);
            $$ = $2;
        }
        | type_qualifier
        {
            $$ = new DeclarationSpecifiers();
            $$->addTypeQualifier($1);
        }
        | type_qualifier specifier_qualifier_list
        {
            $2->addTypeQualifier($1);
            $$ = $2;
        }
        ;
/*
struct_declarator_list
        : struct_declarator
        | struct_declarator_list ',' struct_declarator
        ;

struct_declarator
        : declarator
        | ':' constant_expression
        | declarator ':' constant_expression
        ;
*/


// TODO support enums
/*
enum_specifier
        : ENUM '{' enumerator_list '}'
        | ENUM IDENTIFIER '{' enumerator_list '}'
        | ENUM IDENTIFIER
        ;

enumerator_list
        : enumerator
        | enumerator_list ',' enumerator
        ;

enumerator
        : IDENTIFIER
        | IDENTIFIER '=' constant_expression
        ;
*/


type_qualifier
        : CONST
        {
            $$ = new TypeQualifier($1);
        }
        | VOLATILE
        {
            $$ = new TypeQualifier($1);
        }
        ;

declarator
        : pointer direct_declarator
        {
            $$ = $2;
            $$->setPointers($1);
        }
        | direct_declarator
        {
            $$ = $1;
        }
        ;

direct_declarator
        : IDENTIFIER
        {
            $$ = new IdentifierDeclarator(*$1);
        }
        | '(' declarator ')'
        {
            $$ = $2;
        }
        | direct_declarator '[' constant_expression ']'
        {
            $$ = new ArrayDeclarator($1,$3);
        }
        | direct_declarator '[' ']'
        {
            $$ = new ArrayDeclarator($1,NULL);
        }
        | direct_declarator '(' parameter_type_list ')'
        {
            $$ = new FunctionDeclarator($1, $3);
        }
        // we dont support untyped parameters
        /*
        | direct_declarator '(' identifier_list ')'
        */
        | direct_declarator '(' ')'
        {
            $$ = new FunctionDeclarator($1, NULL);
        }
        ;

pointer
        : '*'
        {
            $$ = new Pointers();
            $$->push_back(new Pointer(new TypeQualifiers()));
        }
        | '*' type_qualifier_list
        {
            $$ = new Pointers();
            $$->push_back(new Pointer($2));
        }
        | '*' pointer
        {
            $2->push_back(new Pointer(new TypeQualifiers()));
            $$ = $2;
        }
        | '*' type_qualifier_list pointer
        {
            $3->push_back(new Pointer($2));
            $$ = $3;
        }
        ;

type_qualifier_list
        : type_qualifier
        {
            $$ = new TypeQualifiers();
            $$->push_back($1);
        }
        | type_qualifier_list type_qualifier
        {
            $1->push_back($2);
            $$ = $1;
        }
        ;


parameter_type_list
        : parameter_list
        {
            $$ = $1;
        }
        | parameter_list ',' ELLIPSIS
        {
            $1->setVarArg(true);
            $$ = $1;
        }
        ;

parameter_list
        : parameter_declaration
        {
            $$ = new ParameterDeclarations();
            $$->push_back($1);
        }
        | parameter_list ',' parameter_declaration
        {
            $1->push_back($3);
            $$ = $1;
        }
        ;

parameter_declaration
        : declaration_specifiers declarator
        {
            $$ = new Declaration($1, $2);
        }
        | declaration_specifiers abstract_declarator
        {
            $$ = new Declaration($1, $2);
        }
        | declaration_specifiers
        {
            $$ = new Declaration($1, new NoIdentifierDeclarator());
        }
        ;

/*
// we dont support untyped parameters
identifier_list
        : IDENTIFIER
        | identifier_list ',' IDENTIFIER
        ;
*/


type_name
        : specifier_qualifier_list
        {
            $$ = new TypeName($1, NULL);
        }
        | specifier_qualifier_list abstract_declarator
        {
            $$ = new TypeName($1, $2);
        }
        ;

abstract_declarator
        : pointer
        {
            $$ = new NoIdentifierDeclarator();
            $$->setPointers($1);
        }
        | direct_abstract_declarator
        {
            $$ = $1;
        }
        | pointer direct_abstract_declarator
        {
            $$ = $2;
            $$->setPointers($1);
        }
        ;

direct_abstract_declarator
        : '(' abstract_declarator ')'
        {
            $$ = $2;
        }
        | '[' ']'
        {
            $$ = new ArrayDeclarator(new NoIdentifierDeclarator());
        }
        | '[' constant_expression ']'
        {
            $$ = new ArrayDeclarator(new NoIdentifierDeclarator(), $2);
        }
        | direct_abstract_declarator '[' ']'
        {
            $$ = new ArrayDeclarator($1);
        }
        | direct_abstract_declarator '[' constant_expression ']'
        {
            $$ = new ArrayDeclarator($1, $3);
        }
        | '(' ')'
        {
            $$ = new FunctionDeclarator(new NoIdentifierDeclarator(), new ParameterDeclarations());
        }
        | '(' parameter_type_list ')'
        {
            $$ = new FunctionDeclarator(new NoIdentifierDeclarator(), $2);
        }
        | direct_abstract_declarator '(' ')'
        {
            $$ = new FunctionDeclarator($1, new ParameterDeclarations());
        }
        | direct_abstract_declarator '(' parameter_type_list ')'
        {
            $$ = new FunctionDeclarator($1, $3);
        }
        ;

initializer
        : assignment_expression
        {
            $$ = new Expressions();
            $$->push_back($1);
        }
        | '{' initializer_list '}'
        {
            $$ = $2;
        }
        | '{' initializer_list ',' '}'
        {
            $$ = $2;
        }
        ;

initializer_list
        : initializer
        {
            $$ = $1;
        }
        | initializer_list ',' initializer
        {
            for(Expressions::iterator i = $3->begin(); i != $3->end(); ++i)
            {
                $1->push_back(*i);
            }
            delete $1;
            $$ = $1;
        }
        ;

// TODO TODO
/* FIXME TODO further up from here
   TODO TODO TODO TODO
*/

statement
        : labeled_statement
        {
            $$ = $1;
        }
        | compound_statement
        {
            $$ = $1;
        }
        | expression_statement
        {
            $$ = $1;
        }
        | selection_statement
        {
            $$ = $1;
        }
        | iteration_statement
        {
            $$ = $1;
        }
        | jump_statement
        {
            $$ = $1;
        }
        ;

labeled_statement
        : IDENTIFIER ':' statement
        {
            $$ = new LabelStatement(*$1, $3);
        }
        | CASE constant_expression ':' statement
        {
            $$ = new CaseStatement($1, $3);
        }
        | DEFAULT ':' statement
        {
            $$ = new DefaultStatement($3);
        }
        ;

compound_statement
        : '{' '}'
        {
            $$ = new BlockStatement();
        }
        | '{' statement_list '}'
        {
            $$ = new BlockStatement(NULL, $2);
        }
        | '{' declaration_list '}'
        {
            $$ = new BlockStatement($2, NULL);
        }
        | '{' declaration_list statement_list '}'
        {
            $$ = new BlockStatement($2, $3);
        }
        ;

declaration_list
        : declaration
        {
            $$ = new Declarations();
            $$->push_back($1);
        }
        | declaration_list declaration
        {
            $1->push_back($2);
            $$ = $1;
        }
        ;

statement_list
        : statement
        {
            $$ = new Statements();
            $$->push_back($1);
        }
        | statement_list statement
        {
            $1->push_back($2);
            $$ = $1;
        }
        ;

expression_statement
        : ';'
        {
            $$ = new EmptyStatement();
        }
        | expression ';'
        {
            $$ = new ExpressionStatement($1);
        }
        ;

selection_statement
        : IF '(' expression ')' statement
        {
            $$ = new IfStatement($3, $5, NULL);
        }
        | IF '(' expression ')' statement ELSE statement
        {
            $$ = new IfStatement($3, $5, $7);
        }
        | SWITCH '(' expression ')' statement
        {
            $$ = new SwitchStatement($3, $5);
        }
        ;

iteration_statement
        : WHILE '(' expression ')' statement
        {
            $$ = new WhileStatement($3, $5);
        }
        | DO statement WHILE '(' expression ')' ';'
        {
            $$ = new DoWhileStatement($2, $5);
        }
        | FOR '(' expression_statement expression_statement ')' statement
        {
            $$ = new ForStatement($3, $4, NULL, $6);
        }
        | FOR '(' expression_statement expression_statement expression ')' statement
        {
            $$ = new ForStatement($3, $4, $5, $7);
        }
        ;

jump_statement
        : GOTO IDENTIFIER ';'
        {
            $$ = new GotoStatement(*$2);
        }
        | CONTINUE ';'
        {
            $$ = new ContinueStatement();
        }
        | BREAK ';'
        {
            $$ = new BreakStatement();
        }
        | RETURN ';'
        {
            $$ = new ReturnStatement(NULL);
        }
        | RETURN expression ';'
        {
            $$ = new ReturnStatement($2);
        }
        ;

translation_unit
        : external_declaration
        {
            $$ = new Declarations();
            $$->push_back($1);
        }
        | translation_unit external_declaration
        {
            $1->push_back($2);
            $$ = $1;
        }
        ;

external_declaration
        : function_definition
        {
            $$ = $1;
        }
        | declaration
        {
            $$ = $1;
        }
        ;

function_definition
        : declaration_specifiers declarator compound_statement
        {
            $$ = new FunctionDefinition($1, $2, $3);
        }
        // the following are deactivated, because they are for legacy C code
        // with no return type or no type in parameter lists, e.g.:
        //  foo(bar,baz) int bar; int baz; { /* function body */}

        //| declaration_specifiers declarator declaration_list compound_statement
        //| declarator declaration_list compound_statement
        //| declarator compound_statement
        ;

%%

#include <cstdio>
#include "lexer.hpp"
#include <cassert>

void yyerror(const char *str)
{
    fflush(stdout);
    printf("\n%*s\n%*s\n", yycolumn, "^", yycolumn, str);
/*
    if (yyfilename == NULL)
        fprintf(stderr, "error at line %i of '%s': %s\n", yylineno, "<unknown>", str);
    else
        fprintf(stderr, "error at line %i of '%s': %s\n", yylineno, yyfilename->data, str);
*/
}
extern int yycolumn;
extern char * yytext;
