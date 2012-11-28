///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       ArrayAccessOperator.cpp
/// @brief      Definition of the ArrayAccessOperator AST node.
/// @author     Patrick Flick
///

#include "ArrayAccessOperator.h"

using namespace dtcc::astnodes;

// calls accept(visitor) for all children nodes of this AST node
void ArrayAccessOperator::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
}

// implements the visitor pattern
void ArrayAccessOperator::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void ArrayAccessOperator::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void ArrayAccessOperator::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
ArrayAccessOperator::~ArrayAccessOperator()
{
    delete this->lhsExpr;
    delete this->rhsExpr;

}

///
/// @}
///