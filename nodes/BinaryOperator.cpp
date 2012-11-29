///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       BinaryOperator.cpp
/// @brief      Definition of the BinaryOperator AST node.
/// @author     Patrick Flick
///

#include "BinaryOperator.h"

using namespace dtcc::astnodes;

// calls accept(visitor) for all children nodes of this AST node
void BinaryOperator::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    this->lhsExrp->accept(visitor);
    this->rhsExpr->accept(visitor);
}

// implements the visitor pattern
void BinaryOperator::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void BinaryOperator::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void BinaryOperator::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
BinaryOperator::~BinaryOperator()
{
    delete this->lhsExrp;
    delete this->rhsExpr;

}

///
/// @}
///