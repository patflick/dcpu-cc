///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       ConditionalOperator.cpp
/// @brief      Definition of the ConditionalOperator AST node.
/// @author     Patrick Flick
///

#include "ConditionalOperator.h"

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void ConditionalOperator::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->condExpr != NULL)
        this->condExpr->acceptPreRecursive(visitor);
    if (this->ifExpr != NULL)
        this->ifExpr->acceptPreRecursive(visitor);
    if (this->elseExpr != NULL)
        this->elseExpr->acceptPreRecursive(visitor);

}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void ConditionalOperator::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->condExpr != NULL)
        this->condExpr->acceptPostRecursive(visitor);
    if (this->ifExpr != NULL)
        this->ifExpr->acceptPostRecursive(visitor);
    if (this->elseExpr != NULL)
        this->elseExpr->acceptPostRecursive(visitor);

}

// calls accept(visitor) for all children nodes of this AST node
void ConditionalOperator::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
    this->condExpr->accept(visitor);
    this->ifExpr->accept(visitor);
    this->elseExpr->accept(visitor);

}

// implements the visitor pattern
void ConditionalOperator::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void ConditionalOperator::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void ConditionalOperator::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
ConditionalOperator::~ConditionalOperator()
{
    this->safe_delete(this->condExpr);
    this->safe_delete(this->ifExpr);
    this->safe_delete(this->elseExpr);

}

///
/// @}
///