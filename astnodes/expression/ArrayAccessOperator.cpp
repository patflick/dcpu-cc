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

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void ArrayAccessOperator::allChildrenAcceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    if (this->lhsExpr != NULL)
        this->lhsExpr->acceptPreRecursive(visitor);
    if (this->rhsExpr != NULL)
        this->rhsExpr->acceptPreRecursive(visitor);

}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void ArrayAccessOperator::allChildrenAcceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    if (this->lhsExpr != NULL)
        this->lhsExpr->acceptPostRecursive(visitor);
    if (this->rhsExpr != NULL)
        this->rhsExpr->acceptPostRecursive(visitor);

}

// calls accept(visitor) for all children nodes of this AST node
void ArrayAccessOperator::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    this->lhsExpr->accept(visitor);
    this->rhsExpr->accept(visitor);
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
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void ArrayAccessOperator::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
ArrayAccessOperator::~ArrayAccessOperator()
{
    this->safe_delete(this->lhsExpr);
    this->safe_delete(this->rhsExpr);

}

///
/// @}
///