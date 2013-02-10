///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       StructureResolutionOperator.cpp
/// @brief      Definition of the StructureResolutionOperator AST node.
/// @author     Patrick Flick
///

#include "StructureResolutionOperator.h"

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void StructureResolutionOperator::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->lhsExpr != NULL)
        this->lhsExpr->acceptPreRecursive(visitor);
}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void StructureResolutionOperator::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->lhsExpr != NULL)
        this->lhsExpr->acceptPostRecursive(visitor);
}

// calls accept(visitor) for all children nodes of this AST node
void StructureResolutionOperator::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
    if (this->lhsExpr != NULL)
        this->lhsExpr->accept(visitor);
}

// implements the visitor pattern
void StructureResolutionOperator::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void StructureResolutionOperator::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void StructureResolutionOperator::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
StructureResolutionOperator::~StructureResolutionOperator()
{
    this->safe_delete(this->lhsExpr);
}

///
/// @}
///