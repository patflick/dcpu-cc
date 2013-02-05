#include <iostream>

#include <visitor/PrintAstVisitor.h>
#include <visitor/SemanticCheckVisitor.h>
#include <errors/InternalCompilerException.h>
#include <codegen/DirectCodeGenVisitor.h>

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
    if ( argc < 2)
    {
        std::cout << "Usage dtcc2 <filename>" << std::endl;
        return 1;
    }
    
    char * filename = argv[1];
    
    std::cout << "Compiling program:" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    

    // Parse C.
    yyout = stderr;
    yyin = fopen(filename, "r");
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
    dtcc::visitor::SemanticCheckVisitor* semCheck = new dtcc::visitor::SemanticCheckVisitor();
    
    
    //program->accept(*printVisitor);
    try{
        program->accept(*semCheck);
    } catch (dtcc::errors::InternalCompilerException*  e)
    {
        std::cout << "INTERNAL COMPILER EXCEPTION: " << e->getMessage() << std::endl;
    }
    
    if (semCheck->hasErrors())
    {
        semCheck->printErrorsAndWarnings();
    }
    else
    {
        std::cout << "No Semantic errors, trying Code generation... " << std::endl;
        // try to compile
        Assembler::loadAll();
        dtcc::codegen::DirectCodeGenVisitor* codegen = new dtcc::codegen::DirectCodeGenVisitor();
        //try{
            program->accept(*codegen);
            
            std::string code = codegen->getAssembly();
            std::cout << code;
            /*
        }
        catch (dtcc::errors::InternalCompilerException*  e)
        {
            std::cout << "INTERNAL COMPILER EXCEPTION: " << e->getMessage() << std::endl;
        }
        */
    }
    
    
    delete(program);
    
    return 0;
}
