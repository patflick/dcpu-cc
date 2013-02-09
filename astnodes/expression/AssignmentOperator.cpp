///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       AssignmentOperator.cpp
/// @brief      Definition of the AssignmentOperator AST node.
/// @author     Patrick Flick
///

#include "AssignmentOperator.h"

using namespace dtcc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void AssignmentOperator::allChildrenAcceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    if (this->lhsExrp != NULL)
        this->lhsExrp->acceptPreRecursive(visitor);
    if (this->rhsExpr != NULL)
        this->rhsExpr->acceptPreRecursive(visitor);
}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void AssignmentOperator::allChildrenAcceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    if (this->lhsExrp != NULL)
        this->lhsExrp->acceptPostRecursive(visitor);
    if (this->rhsExpr != NULL)
        this->rhsExpr->acceptPostRecursive(visitor);
}

// calls accept(visitor) for all children nodes of this AST node
void AssignmentOperator::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    if (this->lhsExrp != NULL)
        this->lhsExrp->accept(visitor);
    if (this->rhsExpr != NULL)
        this->rhsExpr->accept(visitor);
}

// implements the visitor pattern
void AssignmentOperator::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void AssignmentOperator::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void AssignmentOperator::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
AssignmentOperator::~AssignmentOperator()
{
    this->safe_delete(this->lhsExrp);
    this->safe_delete(this->rhsExpr);
}

///
/// @}
///