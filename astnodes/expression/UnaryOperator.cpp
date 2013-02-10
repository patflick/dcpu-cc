///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       UnaryOperator.cpp
/// @brief      Definition of the UnaryOperator AST node.
/// @author     Patrick Flick
///

#include "UnaryOperator.h"

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void UnaryOperator::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->expr != NULL)
        this->expr->acceptPreRecursive(visitor);
}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void UnaryOperator::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->expr != NULL)
        this->expr->acceptPostRecursive(visitor);
}

// calls accept(visitor) for all children nodes of this AST node
void UnaryOperator::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
    if (this->expr != NULL)
        this->expr->accept(visitor);
}

// implements the visitor pattern
void UnaryOperator::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void UnaryOperator::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void UnaryOperator::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
UnaryOperator::~UnaryOperator()
{
    this->safe_delete(this->expr);
}

///
/// @}
///