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

// calls accept(visitor) for all children nodes of this AST node
void AssignmentOperator::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    this->lhsExrp->accept(visitor);
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
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void AssignmentOperator::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
AssignmentOperator::~AssignmentOperator()
{
    delete this->lhsExrp;
    delete this->rhsExpr;

}

///
/// @}
///