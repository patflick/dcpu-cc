///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       Enumerator.cpp
/// @brief      Definition of the Enumerator AST node.
/// @author     Patrick Flick
///

#include "Enumerator.h"

using namespace dtcc::astnodes;

// calls accept(visitor) for all children nodes of this AST node
void Enumerator::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
    if (this->expr != NULL)
        this->expr->accept(visitor);
}

// implements the visitor pattern
void Enumerator::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void Enumerator::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void Enumerator::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
Enumerator::~Enumerator()
{
    delete this->expr;

}

///
/// @}
///