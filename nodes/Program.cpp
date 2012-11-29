///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       Program.cpp
/// @brief      Definition of the Program AST node.
/// @author     Patrick Flick
///

#include "Program.h"

using namespace dtcc::astnodes;

// calls accept(visitor) for all children nodes of this AST node
void Program::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    for (ExternalDeclarations::iterator i = this->decls->begin(); i != this->decls->end(); ++i)
        (*i)->accept(visitor);

}

// implements the visitor pattern
void Program::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void Program::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void Program::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
Program::~Program()
{
    delete this->decls;

}

///
/// @}
///