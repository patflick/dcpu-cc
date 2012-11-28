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

// calls accept(visitor) for all children nodes of this AST node
void MethodCall::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
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
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void MethodCall::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
MethodCall::~MethodCall()
{
    delete this->lhsExpr;
    delete this->rhsExprs;

}

///
/// @}
///