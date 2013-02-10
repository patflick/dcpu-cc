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

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void Enumerator::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->expr != NULL)
        this->expr->acceptPreRecursive(visitor);
}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void Enumerator::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->expr != NULL)
        this->expr->acceptPostRecursive(visitor);
}

// calls accept(visitor) for all children nodes of this AST node
void Enumerator::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
    if (this->expr != NULL)
        this->expr->accept(visitor);
}

// implements the visitor pattern
void Enumerator::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void Enumerator::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void Enumerator::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
Enumerator::~Enumerator()
{
    this->safe_delete(this->expr);
}

///
/// @}
///