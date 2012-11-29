#include <iostream>

#include <visitor/PrintAstVisitor.h>

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

extern "C"
{
    #include <unistd.h>
    #include <stdlib.h>
}

extern int yyparse();
extern FILE* yyin, *yyout;
extern dtcc::astnodes::Program* program;

int main(int argc, char **argv) {
    std::cout << "Compiling program:" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    // Parse C.
    yyout = stderr;
    yyin = fopen("test.c", "r");
    if (yyin == NULL)
    {
        printf("fuck\n");
        return 1;
    }
    
    yyparse();
    
    if (yyin != stdin)
        fclose(yyin);
    
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Resulting AST:" << std::endl;
    
    if (program == NULL)
    {
        std::cerr << "An error occurred while parsing." << std::endl;
        return 1;
    }
    
    dtcc::visitor::PrintAstVisitor* printVisitor = new dtcc::visitor::PrintAstVisitor();
    
    program->accept(*printVisitor);
    
    delete(program);
    
    return 0;
}
