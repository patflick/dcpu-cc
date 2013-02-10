///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       Declarator.cpp
/// @brief      Definition of the Declarator AST node.
/// @author     Patrick Flick
///

#include "Declarator.h"

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void Declarator::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->pointers != NULL)
        for (Pointers::iterator i = this->pointers->begin(); i != this->pointers->end(); ++i)
            (*i)->acceptPreRecursive(visitor);
    if (this->initializers != NULL)
        for (Expressions::iterator i = this->initializers->begin(); i != this->initializers->end(); ++i)
            (*i)->acceptPreRecursive(visitor);
}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void Declarator::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->pointers != NULL)
        for (Pointers::iterator i = this->pointers->begin(); i != this->pointers->end(); ++i)
            (*i)->acceptPostRecursive(visitor);
    if (this->initializers != NULL)
        for (Expressions::iterator i = this->initializers->begin(); i != this->initializers->end(); ++i)
            (*i)->acceptPostRecursive(visitor);
}

void Declarator::setInitializer(Expressions* inits)
{
    this->initializers = inits;
}

void Declarator::setPointers(Pointers* pointers)
{
    this->pointers = pointers;
}

// calls accept(visitor) for all children nodes of this AST node
void Declarator::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
    if (this->pointers != NULL)
        for (Pointers::iterator i = this->pointers->begin(); i != this->pointers->end(); ++i)
            (*i)->accept(visitor);
    if (this->initializers != NULL)
        for (Expressions::iterator i = this->initializers->begin(); i != this->initializers->end(); ++i)
            (*i)->accept(visitor);
}

// implements the visitor pattern
void Declarator::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void Declarator::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void Declarator::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
Declarator::~Declarator()
{
    if (this->pointers != NULL)
        delete this->pointers;
}

///
/// @}
///