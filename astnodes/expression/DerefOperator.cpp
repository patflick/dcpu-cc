///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       DerefOperator.cpp
/// @brief      Definition of the DerefOperator AST node.
/// @author     Patrick Flick
///

#include "DerefOperator.h"

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void DerefOperator::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->expr != NULL)
        this->expr->acceptPreRecursive(visitor);
}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void DerefOperator::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->expr != NULL)
        this->expr->acceptPostRecursive(visitor);
}

// calls accept(visitor) for all children nodes of this AST node
void DerefOperator::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
    if (this->expr != NULL)
        this->expr->accept(visitor);
}

// implements the visitor pattern
void DerefOperator::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void DerefOperator::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void DerefOperator::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
DerefOperator::~DerefOperator()
{
    this->safe_delete(this->expr);
}

///
/// @}
///