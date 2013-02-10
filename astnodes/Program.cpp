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

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void Program::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->decls != NULL)
        for (ExternalDeclarations::iterator i = this->decls->begin(); i != this->decls->end(); ++i)
            (*i)->acceptPreRecursive(visitor);
}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void Program::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->decls != NULL)
        for (ExternalDeclarations::iterator i = this->decls->begin(); i != this->decls->end(); ++i)
            (*i)->acceptPostRecursive(visitor);
}

// calls accept(visitor) for all children nodes of this AST node
void Program::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
    if (this->decls != NULL)
        for (ExternalDeclarations::iterator i = this->decls->begin(); i != this->decls->end(); ++i)
            (*i)->accept(visitor);
}

// implements the visitor pattern
void Program::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void Program::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void Program::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
Program::~Program()
{
    if (this->decls != NULL)
        for (ExternalDeclarations::iterator i = this->decls->begin(); i != this->decls->end(); ++i)
            this->safe_delete((*i));
    this->safe_delete(this->decls);
}

///
/// @}
///