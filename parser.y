%{
/**

    File:           parser.y

    Project:        DCPU-16 Tools
    Component:      LibDCPU-ci-lang-c

    Authors:        Patrick Flick

    Description:    Defines parser for the compiler.
                    Taken from the official ANSI-C grammar.
                    Source: http://www.lysator.liu.se/c/ANSI-C-grammar-y.html

**/

#include <string>
// include all nodes
#include <astnodes/allnodes.h>

using namespace dcpucc::astnodes;

// Turn on verbose error messages.
#define YYERROR_VERBOSE

// Defines the root node.
Program* program;

// YY-stuff.
extern int yylex();
extern int yycolumn;
extern char * yytext;
// only within toolchain:
//extern bstring yyfilename;
void yyerror(const char *str);
void checkForTypedefs(Declaration * declaration);

%}

%union {
    FunctionDefinition* function;
    ExternalDeclaration* extDecl;
    Declaration* declaration;
    Declarations* declarations;
    ParameterDeclarations* paramdeclarations;
    Statement* stmt;
    ExpressionStatement* exprStmt;
    BlockStatement* blkStmt;
    Statements* stmts;
    Expression* expr;
    Identifier* id;
    Expressions* exprs;
    ChainExpressions* chainexprs;
    Declarator* declarator;
    Declarators* declarators;
    DeclarationSpecifiers* declspecs;
    TypeName* typeName;
    TypeQualifier* typequal;
    TypeQualifiers* typequals;
    TypeSpecifier* typespec;
    StorageSpecifier* storspec;
    ExternalDeclarations* extDecls;
    Pointers* pointers;
    Enumerator* enumerator;
    Enumerators* enumerators;
    std::string* string;
    long intLiteral;
    double floatLiteral;
    int token;
}


/* special tokens */
%token <token> LINE_FILE
%token <token> ERROR

/* constants */
%token <intLiteral> INT_LITERAL UINT_LITERAL LONG_LITERAL ULONG_LITERAL
%token <floatLiteral> FLOAT_LITERAL DOUBLE_LITERAL LDOUBLE_LITERAL
%token <string> STRING_LITERAL CHARACTER_LITERAL IDENTIFIER TYPE_NAME ASSEMBLY

%token <token> SIZEOF
%token <token> PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token <token> AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token <token> SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token <token> XOR_ASSIGN OR_ASSIGN

/* built in functions */
%token <token> BUILDIN_VA_START

%token <token> TYPEDEF EXTERN STATIC AUTO REGISTER
%token <token> CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token <token> STRUCT UNION ENUM ELLIPSIS

%token <token> CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

/* simple operators (single character) */
%token <token> BRACE_OPEN BRACE_CLOSE CURVED_OPEN CURVED_CLOSE SQUARE_OPEN SQUARE_CLOSE
%token <token> COMMA COLON ASSIGN_EQUAL DOT BIN_AND_OP NOT_OP BIN_INV_OP
%token <token> SUB_OP ADD_OP MUL_OP DIV_OP MOD_OP LT_OP GT_OP BIN_XOR_OP
%token <token> BIN_OR_OP TERNARY_IF SEMICOLON

/* Define types of grammar rules */
%type <program> program
%type <function> function_definition
%type <extDecl> external_declaration
%type <extDecls> translation_unit
%type <declaration> parameter_declaration declaration struct_declaration
%type <declarations> declaration_list struct_declaration_list
%type <paramdeclarations> parameter_list parameter_type_list
%type <stmt> statement labeled_statement jump_statement iteration_statement selection_statement expression_statement asm_statement
%type <exprStmt> cond_expression_statement
%type <blkStmt> compound_statement
%type <stmts> statement_list
%type <id> ident
%type <expr> primary_expression postfix_expression unary_expression cast_expression multiplicative_expression additive_expression shift_expression relational_expression equality_expression and_expression exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression conditional_expression assignment_expression constant_expression
%type <exprs> argument_expression_list initializer_list initializer
%type <chainexprs> expression
%type <declarator> init_declarator direct_declarator declarator direct_abstract_declarator abstract_declarator struct_declarator
%type <declarators> init_declarator_list struct_declarator_list
%type <declspecs> specifier_qualifier_list declaration_specifiers
%type <typeName> type_name
%type <typequal> type_qualifier
%type <typequals> type_qualifier_list
%type <typespec> type_specifier struct_or_union_specifier enum_specifier
%type <storspec> storage_class_specifier
%type <pointers> pointer
%type <token> unary_operator assignment_operator struct_or_union
%type <enumerator> enumerator
%type <enumerators> enumerator_list


/*
 * Solving the shift/reduce conflict because of dangling `else` in
 * if statement, source:
 * http://stackoverflow.com/questions/1737460/how-to-find-shift-reduce-conflict-in-this-yacc-file
 */
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

/* Start point of parsing */
%start program


%%

ident
        : IDENTIFIER
        {
            $$ = new Identifier(*$1);
        }
        ;

primary_expression
        : ident
        {
            $$ = $1;
        }
        | STRING_LITERAL
        {
            $$ = new StringLiteral(*$1);
        }
        | CHARACTER_LITERAL
        {
            $$ = new CharacterLiteral(*$1);
        }
        | INT_LITERAL
        {
            $$ = new SignedIntLiteral($1);
        }
        | UINT_LITERAL
        {
            $$ = new UnsignedIntLiteral($1);
        }
        | LONG_LITERAL
        {
            $$ = new SignedLongLiteral($1);
        }
        | ULONG_LITERAL
        {
            $$ = new UnsignedLongLiteral($1);
        }
        | FLOAT_LITERAL
        {
            $$ = new FloatLiteral($1);
        }
        | DOUBLE_LITERAL
        {
            $$ = new DoubleLiteral($1);
        }
        | LDOUBLE_LITERAL
        {
            $$ = new LongDoubleLiteral($1);
        }
        | CURVED_OPEN expression CURVED_CLOSE
        {
            $$ = $2;
        }
        ;

postfix_expression
        : primary_expression
        {
            $$ = $1;
        }
        | postfix_expression SQUARE_OPEN expression SQUARE_CLOSE
        {
            $$ = new ArrayAccessOperator($1, $3);
        }
        | postfix_expression CURVED_OPEN CURVED_CLOSE
        {
            $$ = new MethodCall($1, new Expressions());
        }
        | postfix_expression CURVED_OPEN argument_expression_list CURVED_CLOSE
        {
            $$ = new MethodCall($1, $3);
        }
        | postfix_expression DOT IDENTIFIER
        {
            $$ = new StructureResolutionOperator($1, *$3, false);
        }
        | postfix_expression PTR_OP IDENTIFIER
        {
            $$ = new StructureResolutionOperator($1, *$3, true);
        }
        | postfix_expression INC_OP
        {
            $$ = new PostIncDec($2, $1);
        }
        | postfix_expression DEC_OP
        {
            $$ = new PostIncDec($2, $1);
        }
        | BUILDIN_VA_START CURVED_OPEN ident COMMA ident CURVED_CLOSE
        {
            $$ = new BuiltInVaStart($3, $5);
        }
        ;

argument_expression_list
        : assignment_expression
        {
            $$ = new Expressions();
            $$->push_back($1);
        }
        | argument_expression_list COMMA assignment_expression
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
        | BIN_AND_OP unary_expression
        {
            $$ = new AddressOfOperator($2);
        }
        | MUL_OP unary_expression
        {
            $$ = new DerefOperator($2);
        }
        | SIZEOF unary_expression
        {
            $$ = new SizeOfOperator($2);
        }
        | SIZEOF CURVED_OPEN type_name CURVED_CLOSE
        {
            $$ = new SizeOfOperator($3);
        }
        ;

unary_operator
        : ADD_OP
        | SUB_OP
        | BIN_INV_OP
        | NOT_OP
        ;

cast_expression
        : unary_expression
        {
            $$ = $1;
        }
        | CURVED_OPEN type_name CURVED_CLOSE cast_expression
        {
            $$ = new ExplicitCastOperator($2, $4);
        }
        ;

multiplicative_expression
        : cast_expression
        {
            $$ = $1;
        }
        | multiplicative_expression MUL_OP cast_expression
        {
            $$ = new BinaryOperator($1, $2, $3);
        }
        | multiplicative_expression DIV_OP cast_expression
        {
            $$ = new BinaryOperator($1, $2, $3);
        }
        | multiplicative_expression MOD_OP cast_expression
        {
            $$ = new BinaryOperator($1, $2, $3);
        }
        ;

additive_expression
        : multiplicative_expression
        {
            $$ = $1;
        }
        | additive_expression ADD_OP multiplicative_expression
        {
            $$ = new BinaryOperator($1, $2, $3);
        }
        | additive_expression SUB_OP multiplicative_expression
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
        | relational_expression LT_OP shift_expression
        {
            $$ = new BinaryOperator($1, $2, $3);
        }
        | relational_expression GT_OP shift_expression
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
        | and_expression BIN_AND_OP equality_expression
        {
            $$ = new BinaryOperator($1, $2, $3);
        }
        ;

exclusive_or_expression
        : and_expression
        {
            $$ = $1;
        }
        | exclusive_or_expression BIN_XOR_OP and_expression
        {
            $$ = new BinaryOperator($1, $2, $3);
        }
        ;

inclusive_or_expression
        : exclusive_or_expression
        {
            $$ = $1;
        }
        | inclusive_or_expression BIN_OR_OP exclusive_or_expression
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
        | logical_or_expression TERNARY_IF expression COLON conditional_expression
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
        : ASSIGN_EQUAL
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
            $$ = new ChainExpressions();
            $$->exprs->push_back($1);
        }
        | expression COMMA assignment_expression
        {
            $1->exprs->push_back($3);
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
        : declaration_specifiers SEMICOLON
        {
            $$ = new Declaration($1, new Declarators());
        }
        | declaration_specifiers init_declarator_list SEMICOLON
        {
            $$ = new Declaration($1, $2);
        }
        ;

declaration_specifiers
        : storage_class_specifier
        {
            $$ = new DeclarationSpecifiers();
            $$->storageSpecifiers.push_back($1);
        }
        | storage_class_specifier declaration_specifiers
        {
            $2->storageSpecifiers.push_back($1);
            $$ = $2;
        }
        | type_specifier
        {
            $$ = new DeclarationSpecifiers();
            $$->typeSpecifiers.push_back($1);
        }
        | type_specifier declaration_specifiers
        {
            $2->typeSpecifiers.push_back($1);
            $$ = $2;
        }
        | type_qualifier
        {
            $$ = new DeclarationSpecifiers();
            $$->typeQualifiers.push_back($1);
        }
        | type_qualifier declaration_specifiers
        {
            $2->typeQualifiers.push_back($1);
            $$ = $2;
        }
        ;

init_declarator_list
        : init_declarator
        {
            $$ = new Declarators();
            $$->push_back($1);
        }
        | init_declarator_list COMMA init_declarator
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
        | declarator ASSIGN_EQUAL initializer
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
        | struct_or_union_specifier
        {
            $$ = $1;
        }
        | enum_specifier
        {
            $$ = $1;
        }
        | TYPE_NAME
        {
            $$ = new TypeNameSpecifier(*$1);
        }
        ;


struct_or_union_specifier
        : struct_or_union IDENTIFIER BRACE_OPEN struct_declaration_list BRACE_CLOSE
        {
            $$ = new StructUnionSpecifier($1, $4, *$2);
        }
        | struct_or_union BRACE_OPEN struct_declaration_list BRACE_CLOSE
        {
            // anonymous struct
            $$ = new StructUnionSpecifier($1, $3);
        }
        | struct_or_union IDENTIFIER
        {
            $$ = new StructUnionSpecifier($1, NULL, *$2);
        }
        ;

struct_or_union
        : STRUCT
        | UNION
        ;

struct_declaration_list
        : struct_declaration
        {
            $$ = new Declarations();
            $$->push_back($1);
        }
        | struct_declaration_list struct_declaration
        {
            $1->push_back($2);
            $$ = $1;
        }
        ;

struct_declaration
        : specifier_qualifier_list struct_declarator_list SEMICOLON
        {
            $$ = new Declaration($1, $2);
        }
        ;



specifier_qualifier_list
        : type_specifier
        {
            $$ = new DeclarationSpecifiers();
            $$->typeSpecifiers.push_back($1);
        }
        | type_specifier specifier_qualifier_list
        {
            $2->typeSpecifiers.push_back($1);
            $$ = $2;
        }
        | type_qualifier
        {
            $$ = new DeclarationSpecifiers();
            $$->typeQualifiers.push_back($1);
        }
        | type_qualifier specifier_qualifier_list
        {
            $2->typeQualifiers.push_back($1);
            $$ = $2;
        }
        ;

struct_declarator_list
        : struct_declarator
        {
            $$ = new Declarators();
            $$->push_back($1);
        }
        | struct_declarator_list COMMA struct_declarator
        {
            $1->push_back($3);
            $$ = $1;
        }
        ;

struct_declarator
        : declarator
        {
            $$ = $1;
        }
/* No support for bit fields (well, at least not yet)
        | COLON constant_expression
        | declarator COLON constant_expression
*/
        ;


enum_specifier
        : ENUM BRACE_OPEN enumerator_list BRACE_CLOSE
        {
            $$ = new EnumSpecifier($3);
        }
        | ENUM IDENTIFIER BRACE_OPEN enumerator_list BRACE_CLOSE
        {
            $$ = new EnumSpecifier($4, *$2);
        }
        | ENUM IDENTIFIER
        {
            $$ = new EnumSpecifier(NULL, *$2);
        }
        ;

enumerator_list
        : enumerator
        {
            $$ = new Enumerators();
            $$->push_back($1);
        }
        | enumerator_list COMMA enumerator
        {
            $1->push_back($3);
            $$ = $1;
        }
        ;

enumerator
        : IDENTIFIER
        {
            $$ = new Enumerator(*$1, NULL);
        }
        | IDENTIFIER ASSIGN_EQUAL constant_expression
        {
            $$ = new Enumerator(*$1, $3);
        }
        ;



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
        | CURVED_OPEN declarator CURVED_CLOSE
        {
            $$ = $2;
        }
        | direct_declarator SQUARE_OPEN constant_expression SQUARE_CLOSE
        {
            $$ = new ArrayDeclarator($1,$3);
        }
        | direct_declarator SQUARE_OPEN SQUARE_CLOSE
        {
            $$ = new ArrayDeclarator($1,NULL);
        }
        | direct_declarator CURVED_OPEN parameter_type_list CURVED_CLOSE
        {
            $$ = new FunctionDeclarator($1, $3);
        }
        // we dont support untyped parameters
        /*
        | direct_declarator CURVED_OPEN identifier_list CURVED_CLOSE
        */
        | direct_declarator CURVED_OPEN CURVED_CLOSE
        {
            $$ = new FunctionDeclarator($1, new ParameterDeclarations());
        }
        ;

pointer
        : MUL_OP
        {
            $$ = new Pointers();
            $$->push_back(new Pointer(new TypeQualifiers()));
        }
        | MUL_OP type_qualifier_list
        {
            $$ = new Pointers();
            $$->push_back(new Pointer($2));
        }
        | MUL_OP pointer
        {
            $2->push_back(new Pointer(new TypeQualifiers()));
            $$ = $2;
        }
        | MUL_OP type_qualifier_list pointer
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
        | parameter_list COMMA ELLIPSIS
        {
            $1->varArgs = true;
            $$ = $1;
        }
        ;

parameter_list
        : parameter_declaration
        {
            $$ = new ParameterDeclarations();
            $$->declarations.push_back($1);
        }
        | parameter_list COMMA parameter_declaration
        {
            $1->declarations.push_back($3);
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
        | identifier_list COMMA IDENTIFIER
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
        : CURVED_OPEN abstract_declarator CURVED_CLOSE
        {
            $$ = $2;
        }
        | SQUARE_OPEN SQUARE_CLOSE
        {
            $$ = new ArrayDeclarator(new NoIdentifierDeclarator(), NULL);
        }
        | SQUARE_OPEN constant_expression SQUARE_CLOSE
        {
            $$ = new ArrayDeclarator(new NoIdentifierDeclarator(), $2);
        }
        | direct_abstract_declarator SQUARE_OPEN SQUARE_CLOSE
        {
            $$ = new ArrayDeclarator($1, NULL);
        }
        | direct_abstract_declarator SQUARE_OPEN constant_expression SQUARE_CLOSE
        {
            $$ = new ArrayDeclarator($1, $3);
        }
        | CURVED_OPEN CURVED_CLOSE
        {
            $$ = new FunctionDeclarator(new NoIdentifierDeclarator(), new ParameterDeclarations());
        }
        | CURVED_OPEN parameter_type_list CURVED_CLOSE
        {
            $$ = new FunctionDeclarator(new NoIdentifierDeclarator(), $2);
        }
        | direct_abstract_declarator CURVED_OPEN CURVED_CLOSE
        {
            $$ = new FunctionDeclarator($1, new ParameterDeclarations());
        }
        | direct_abstract_declarator CURVED_OPEN parameter_type_list CURVED_CLOSE
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
        | BRACE_OPEN initializer_list BRACE_CLOSE
        {
            $$ = $2;
        }
        | BRACE_OPEN initializer_list COMMA BRACE_CLOSE
        {
            $$ = $2;
        }
        ;

initializer_list
        : initializer
        {
            $$ = $1;
        }
        | initializer_list COMMA initializer
        {
            for(Expressions::iterator i = $3->begin(); i != $3->end(); ++i)
            {
                $1->push_back(*i);
            }
            delete $3;
            $$ = $1;
        }
        ;

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
        | asm_statement
        {
            $$ = $1;
        }
        ;

asm_statement:
        ASSEMBLY
        {
            $$ = new AssemblyStatement(*$1);
        }
        ;

labeled_statement
        : IDENTIFIER COLON statement
        {
            $$ = new LabelStatement(*$1, $3);
        }
        | CASE constant_expression COLON statement
        {
            $$ = new CaseStatement($2, $4);
        }
        | DEFAULT COLON statement
        {
            $$ = new DefaultStatement($3);
        }
        ;

compound_statement
        : BRACE_OPEN BRACE_CLOSE
        {
            $$ = new BlockStatement(NULL, NULL);
        }
        | BRACE_OPEN statement_list BRACE_CLOSE
        {
            $$ = new BlockStatement(NULL, $2);
        }
        | BRACE_OPEN declaration_list BRACE_CLOSE
        {
            $$ = new BlockStatement($2, NULL);
        }
        | BRACE_OPEN declaration_list statement_list BRACE_CLOSE
        {
            $$ = new BlockStatement($2, $3);
        }
        ;

declaration_list
        : declaration
        {
            // check for typedefs here to be added to the lexers list
            checkForTypedefs($1);
            // proceed normally
            $$ = new Declarations();
            $$->push_back($1);
        }
        | declaration_list declaration
        {
            // check for typedefs here to be added to the lexers list
            checkForTypedefs($2);
            // proceed normally
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
        : SEMICOLON
        {
            $$ = new EmptyStatement();
        }
        | expression SEMICOLON
        {
            $$ = new ExpressionStatement($1);
        }
        ;

cond_expression_statement
        : SEMICOLON
        {
            $$ = new ExpressionStatement(new SignedIntLiteral(1l));
        }
        | expression SEMICOLON
        {
            $$ = new ExpressionStatement($1);
        }
        ;

selection_statement
        // LOWER_THAN_ELSE gives this expression lower precedence thatn the 
        // one with the else part. This way the shift/reduce conflict is solved
        // source: http://stackoverflow.com/questions/1737460/how-to-find-shift-reduce-conflict-in-this-yacc-file
        : IF CURVED_OPEN expression CURVED_CLOSE statement %prec LOWER_THAN_ELSE
        {
            $$ = new IfStatement($3, $5, NULL);
        }
        | IF CURVED_OPEN expression CURVED_CLOSE statement ELSE statement
        {
            $$ = new IfStatement($3, $5, $7);
        }
        | SWITCH CURVED_OPEN expression CURVED_CLOSE statement
        {
            $$ = new SwitchStatement($3, $5);
        }
        ;

iteration_statement
        : WHILE CURVED_OPEN expression CURVED_CLOSE statement
        {
            $$ = new WhileStatement($3, $5);
        }
        | DO statement WHILE CURVED_OPEN expression CURVED_CLOSE SEMICOLON
        {
            $$ = new DoWhileStatement($2, $5);
        }
        | FOR CURVED_OPEN expression_statement cond_expression_statement CURVED_CLOSE statement
        {
            $$ = new ForStatement($3, $4, NULL, $6);
        }
        | FOR CURVED_OPEN expression_statement cond_expression_statement expression CURVED_CLOSE statement
        {
            $$ = new ForStatement($3, $4, $5, $7);
        }
        ;

jump_statement
        : GOTO IDENTIFIER SEMICOLON
        {
            $$ = new GotoStatement(*$2);
        }
        | CONTINUE SEMICOLON
        {
            $$ = new ContinueStatement();
        }
        | BREAK SEMICOLON
        {
            $$ = new BreakStatement();
        }
        | RETURN SEMICOLON
        {
            $$ = new ReturnStatement(NULL);
        }
        | RETURN expression SEMICOLON
        {
            $$ = new ReturnStatement($2);
        }
        ;

translation_unit
        : external_declaration
        {
            $$ = new ExternalDeclarations();
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
            // check for typedefs here to be added to the lexers list
            checkForTypedefs($1);
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

program
        : translation_unit
        {
            program = new Program($1);
        }
        ;

%%

#include <cstdio>
#include "lexer.hpp"
#include <cassert>
#include <visitor/CheckTypedefVisitor.h>
#include <set>
#include <errors/ErrorList.h>


extern int yycolumn;
extern char * yytext;
extern std::set<std::string> activeTypedef;
extern errors::ErrorList errorlist;
extern std::vector<std::string> yylines;
extern std::string yycurline;

void checkForTypedefs(Declaration * declaration)
{
    // create the CheckTypeDefVisitor and let it do its job
    dcpucc::visitor::CheckTypedefVisitor typedefChecker;
    declaration->acceptPreRecursive(typedefChecker);

    if (typedefChecker.isTypedef)
        for (std::vector<std::string>::iterator i = typedefChecker.typeNameList.begin(); i != typedefChecker.typeNameList.end(); ++i)
            // add typedef names into set shared with the lexer
            activeTypedef.insert(*i);
}

void yyerror(const char *str)
{
    std::string file;
    if (yyfilename == NULL)
        file = "<unknown>";
    else
        file = std::string(*yyfilename);
    errorlist.addError(yylineno, yycolumn, file, std::string(str));
    // add current line to lines
    yylines.push_back(yycurline);
}

