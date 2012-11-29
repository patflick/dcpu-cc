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

using namespace dtcc::astnodes;

// calls accept(visitor) for all children nodes of this AST node
void UnaryOperator::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{

    this->expr->accept(visitor);
}

// implements the visitor pattern
void UnaryOperator::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void UnaryOperator::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void UnaryOperator::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
UnaryOperator::~UnaryOperator()
{
    delete this->expr;

}

///
/// @}
///