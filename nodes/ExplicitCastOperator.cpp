///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       ExplicitCastOperator.cpp
/// @brief      Definition of the ExplicitCastOperator AST node.
/// @author     Patrick Flick
///

#include "ExplicitCastOperator.h"

using namespace dtcc::astnodes;

// calls accept(visitor) for all children nodes of this AST node
void ExplicitCastOperator::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
    this->typeName->accept(visitor);
    this->expr->accept(visitor);

}

// implements the visitor pattern
void ExplicitCastOperator::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void ExplicitCastOperator::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void ExplicitCastOperator::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
ExplicitCastOperator::~ExplicitCastOperator()
{
    delete this->typeName;
    delete this->expr;

}

///
/// @}
///