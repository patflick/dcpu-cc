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

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void ExplicitCastOperator::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->typeName != NULL)
        this->typeName->acceptPreRecursive(visitor);
    if (this->expr != NULL)
        this->expr->acceptPreRecursive(visitor);

}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void ExplicitCastOperator::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->typeName != NULL)
        this->typeName->acceptPostRecursive(visitor);
    if (this->expr != NULL)
        this->expr->acceptPostRecursive(visitor);

}

// calls accept(visitor) for all children nodes of this AST node
void ExplicitCastOperator::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
    this->typeName->accept(visitor);
    this->expr->accept(visitor);

}

// implements the visitor pattern
void ExplicitCastOperator::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void ExplicitCastOperator::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void ExplicitCastOperator::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
ExplicitCastOperator::~ExplicitCastOperator()
{
    this->safe_delete(this->typeName);
    this->safe_delete(this->expr);

}

///
/// @}
///