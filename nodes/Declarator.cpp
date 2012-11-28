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

using namespace dtcc::astnodes;

void Declarator::setInitializer(Expressions* inits)
{
    this->initializers = inits;
}

void Declarator::setPointers(Pointers* pointers)
{
    this->pointers = pointers;
}


// calls accept(visitor) for all children nodes of this AST node
void Declarator::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
}

// implements the visitor pattern
void Declarator::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void Declarator::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void Declarator::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
Declarator::~Declarator()
{
    if (this->initializers != NULL)
        delete this->initializers;
    if (this->pointers != NULL)
        delete this->pointers;
}

///
/// @}
///