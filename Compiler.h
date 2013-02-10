


#ifndef COMPILER_H
#define COMPILER_H

#include <visitor/SemanticCheckVisitor.h>
#include <codegen/DirectCodeGenVisitor.h>

#include <list>
#include <string>

using namespace dtcc;

namespace dtcc
{

    class Compiler
    {
    private:
        
        
        
    public:
        Compiler();
        
        Compiler(const Compiler& other);
        
        /// @brief Input function for the lexer.
        void getInput(char*, int&, int);
        
        void compile(std::string input);
        
        bool hasErrors();
        std::list<std::string> getErrors();
        void printErrors();
        
        std::string getAssembler();
        
        virtual ~Compiler();
        
        
    };

} // namespace dtcc

Compiler* compiler = NULL;


#endif // COMPILER_H
