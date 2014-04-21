///
/// @addtogroup LibDCPU-CI-Lang-C/Compiler
/// @{
///
///
/// @file       Compiler.h
/// @brief      Implements the main wrapper for the compiler.
/// @author     Patrick Flick
///

#ifndef DTCC_COMPILER_H
#define DTCC_COMPILER_H

#include <cstdlib>
#include <list>
#include <string>

#include <visitor/SemanticCheckVisitor.h>
#include <codegen/DirectCodeGenVisitor.h>

#define DTCC_COMPILER_INPUT_STRING 1
#define DTCC_COMPILER_INPUT_STREAM 2

namespace dcpucc
{
    /// @brief The wrapper class for the compiler.
    /// @author Patrick Flick
    /// @class Compiler
    /// Declares the interface for the DCPU compiler.
    /// This should be the only way the library is accessed from
    /// third-party projects.
    class Compiler
    {
    private:
        int input_type;
        std::string input_str;
        unsigned int input_str_ctr;
        std::string m_asmOutput;
        
    public:
        /// @brief The default contructor.
        Compiler();
        
        /// @brief Input function for the lexer.
        /// DO NOT call from the outside.
        /// For internal usage only.
        bool getInput(char*, size_t&, size_t);
        
        /// @brief Compiles the input stream.
        /// @param input The input stream to be compiled.
        /// When called the compiler tries to compile the given
        /// input. On success the result can be gotten with getAssembler().
        /// If errors occur during compilation, no output is generated.
        /// The error state should be checked with hasErrors() before
        /// calling getAssembler().
        void compile(std::istream& input);
        
        /// @brief Compiles the input string.
        /// @param input The input string to be compiled.
        /// When called the compiler tries to compile the given
        /// input. On success the result can be gotten with getAssembler().
        /// If errors occur during compilation, no output is generated.
        /// The error state should be checked with hasErrors() before
        /// calling getAssembler().
        void compile(std::string& input);
        
        /// @brief Returns whether errors occurred while compiling.
        /// After calling compile(...), this method will return whether
        /// errors occurred during compilation.
        bool hasErrors();
        
        /// @brief Returns whether warnings occurred while compiling.
        /// After calling compile(...), this method will return whether
        /// warnings occurred during compilation.
        bool hasWarnings();
        
        /// @brief Returns warnings that occurred during compilation.
        /// After calling compile(...), this method will return a list
        /// of warning messages, that were added during compilation.
        std::list<std::string> getWarnings();
        
        /// @brief Returns errors that occurred during compilation.
        /// After calling compile(...), this method will return a list
        /// of error messages, that were added during compilation.
        std::list<std::string> getErrors();
        
        /// @brief Returns errors and warnings that occurred during compilation.
        /// After calling compile(...), this method will return a list
        /// of error and warning messages, that were added during compilation.
        std::list<std::string> getWarningsAndErrors();
        
        /// @brief Prints all errors to stderr.
        /// After calling compile(...), this method will print all errors
        /// and warnings that occurred during compilation to stderr.
        void printErrors();
        
        /// @brief Returns generated assembler.
        /// After calling compile(...), and when the compilation was successful
        /// (i.e. hasErrors() returns false), this method returns the compiled
        /// code in DCPU16 assembler as std::string.
        std::string getAssembler();
        
        /// The destructor of the Compiler class.
        virtual ~Compiler();
    };

} // namespace dcpucc


#endif // COMPILER_H


///
/// @}
///
