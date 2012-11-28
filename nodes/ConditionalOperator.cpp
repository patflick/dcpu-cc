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

using namespace dtcc::astnodes;

// calls accept(visitor) for all children nodes of this AST node
void ConditionalOperator::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
}

// implements the visitor pattern
void ConditionalOperator::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void ConditionalOperator::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void ConditionalOperator::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
ConditionalOperator::~ConditionalOperator()
{
    delete this->condExpr;
    delete this->ifExpr;
    delete this->elseExpr;

}

///
/// @}
///