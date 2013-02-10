/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2013  <copyright holder> <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "Compiler.h"
#include <visitor/SemanticCheckVisitor.h>
#include <errors/ErrorList.h>

// declare the parser and lexer variables
extern int yyparse();
extern FILE* yyin, *yyout;
extern dcpucc::astnodes::Program* program;

using namespace dcpucc;

// global variables that are used by the parser and semantic check
// visitor to add error messages
Compiler* compiler = NULL;
errors::ErrorList errorlist;

int input_type;
std::string input_str;
unsigned int input_str_ctr;
std::string m_asmOutput;

Compiler::Compiler()
: input_type(DTCC_COMPILER_INPUT_STRING), input_str(std::string("")),
input_str_ctr(0), m_asmOutput(std::string(""))
{

}



/// @brief Input function for the lexer.
bool Compiler::getInput(char* buf, int& result, int max_size)
{
    if (this->input_type == DTCC_COMPILER_INPUT_STRING)
    {
        if (this->input_str_ctr < this->input_str.size())
        {
            buf[0] = this->input_str[this->input_str_ctr++];
            result = 1;
            return true;
        }
        else
        {
            return false;
        }
    }
    // TODO implement other cases
    return false;
}


void Compiler::compile(std::istream& input)
{
    // read stream into string
    std::string str( (std::istreambuf_iterator<char>( input )),
                   (std::istreambuf_iterator<char>()) );
    this->compile(str);
}


void Compiler::compile(std::string& input)
{
    // set input string, and its options
    this->input_type = DTCC_COMPILER_INPUT_STRING;
    this->input_str = input;
    this->input_str_ctr = 0;
    
    // set compiler, so the lexer can use the getInput method to get input
    compiler = this;
    
    // create errorlist
    errorlist = errors::ErrorList();
    
    // disable yy output
    yyout = NULL;
    yyin = NULL;
    // parse C AST
    yyparse();
    
    if (program == NULL)
    {
        // errors have been added
        return;
    }
    
    // load assembler information
    Assembler::loadAll();
    
    // Do semantic checks
    dcpucc::visitor::SemanticCheckVisitor* semCheck = new dcpucc::visitor::SemanticCheckVisitor();
    program->accept(*semCheck);
    
    if (errorlist.hasErrors())
    {
        // don't generate code in this case
        return;
    }
    
    // generate code
    dcpucc::codegen::DirectCodeGenVisitor* codegen = new dcpucc::codegen::DirectCodeGenVisitor();
    program->accept(*codegen);
    
    // get output
    this->m_asmOutput = codegen->getAssembly();
    
    // cleanup
    delete program;
    program = NULL;
}

bool Compiler::hasErrors()
{
    return errorlist.hasErrors();
}

bool Compiler::hasWarnings()
{
    return errorlist.hasWarnings();
}

std::list<std::string> Compiler::getWarnings()
{
    return errorlist.getWarnings();
}

std::list<std::string> Compiler::getErrors()
{
    return errorlist.getErrors();
}

std::list<std::string> Compiler::getWarningsAndErrors()
{
    return errorlist.getWarningsAndErrors();
}

void Compiler::printErrors()
{
    errorlist.printall();
}

std::string Compiler::getAssembler()
{
    return this->m_asmOutput;
}

Compiler::~Compiler()
{

}

