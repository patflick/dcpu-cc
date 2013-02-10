


#ifndef COMPILER_H
#define COMPILER_H

#include <visitor/SemanticCheckVisitor.h>
#include <codegen/DirectCodeGenVisitor.h>

#include <list>
#include <string>

using namespace dtcc;

#define DTCC_COMPILER_INPUT_STRING 1
#define DTCC_COMPILER_INPUT_STREAM 2

namespace dtcc
{

    class Compiler
    {
    private:
        int input_type;
        std::string input_str;
        unsigned int input_str_ctr;
        std::string m_asmOutput;
        
    public:
        Compiler();
        
        /// @brief Input function for the lexer.
        bool getInput(char*, int&, int);
        
        void compile(std::istream& input);
        void compile(std::string& input);
        
        bool hasErrors();
        bool hasWarnings();
        std::list<std::string> getWarnings();
        std::list<std::string> getErrors();
        std::list<std::string> getWarningsAndErrors();
        void printErrors();
        
        std::string getAssembler();
        
        virtual ~Compiler();
    };

} // namespace dtcc


#endif // COMPILER_H
