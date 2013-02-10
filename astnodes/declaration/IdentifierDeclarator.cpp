///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       IdentifierDeclarator.cpp
/// @brief      Definition of the IdentifierDeclarator AST node.
/// @author     Patrick Flick
///

#include "IdentifierDeclarator.h"

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void IdentifierDeclarator::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->pointers != NULL)
        for (Pointers::iterator i = this->pointers->begin(); i != this->pointers->end(); ++i)
            (*i)->acceptPreRecursive(visitor);
    if (this->initializers != NULL)
        for (Expressions::iterator i = this->initializers->begin(); i != this->initializers->end(); ++i)
            (*i)->acceptPreRecursive(visitor);
}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void IdentifierDeclarator::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->pointers != NULL)
        for (Pointers::iterator i = this->pointers->begin(); i != this->pointers->end(); ++i)
            (*i)->acceptPostRecursive(visitor);
    if (this->initializers != NULL)
        for (Expressions::iterator i = this->initializers->begin(); i != this->initializers->end(); ++i)
            (*i)->acceptPostRecursive(visitor);
}

// calls accept(visitor) for all children nodes of this AST node
void IdentifierDeclarator::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
    if (this->pointers != NULL)
        for (Pointers::iterator i = this->pointers->begin(); i != this->pointers->end(); ++i)
            (*i)->accept(visitor);
    if (this->initializers != NULL)
        for (Expressions::iterator i = this->initializers->begin(); i != this->initializers->end(); ++i)
            (*i)->accept(visitor);
}

// implements the visitor pattern
void IdentifierDeclarator::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void IdentifierDeclarator::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void IdentifierDeclarator::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
IdentifierDeclarator::~IdentifierDeclarator()
{
}

///
/// @}
///