///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       MethodCall.cpp
/// @brief      Definition of the MethodCall AST node.
/// @author     Patrick Flick
///

#include "MethodCall.h"

using namespace dtcc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void MethodCall::allChildrenAcceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    if (this->lhsExpr != NULL)
        this->lhsExpr->acceptPreRecursive(visitor);
    if (this->rhsExprs != NULL)
        for (Expressions::iterator i = this->rhsExprs->begin(); i != this->rhsExprs->end(); ++i)
            (*i)->acceptPreRecursive(visitor);
}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void MethodCall::allChildrenAcceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    if (this->lhsExpr != NULL)
        this->lhsExpr->acceptPostRecursive(visitor);
    if (this->rhsExprs != NULL)
        for (Expressions::iterator i = this->rhsExprs->begin(); i != this->rhsExprs->end(); ++i)
            (*i)->acceptPostRecursive(visitor);
}

// calls accept(visitor) for all children nodes of this AST node
void MethodCall::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    if (this->lhsExpr != NULL)
        this->lhsExpr->accept(visitor);
    if (this->rhsExprs != NULL)
    for (Expressions::iterator i = this->rhsExprs->begin(); i != this->rhsExprs->end(); ++i)
        (*i)->accept(visitor);
}

// implements the visitor pattern
void MethodCall::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void MethodCall::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void MethodCall::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
MethodCall::~MethodCall()
{
    if (this->rhsExprs != NULL)
        for (Expressions::iterator i = this->rhsExprs->begin(); i != this->rhsExprs->end(); ++i)
            this->safe_delete((*i));
    this->safe_delete(this->lhsExpr);
    this->safe_delete(this->rhsExprs);
}

///
/// @}
///