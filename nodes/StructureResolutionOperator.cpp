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

using namespace dtcc::astnodes;

// calls accept(visitor) for all children nodes of this AST node
void StructureResolutionOperator::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
    this->lhsExpr->accept(visitor);
}

// implements the visitor pattern
void StructureResolutionOperator::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void StructureResolutionOperator::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void StructureResolutionOperator::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
StructureResolutionOperator::~StructureResolutionOperator()
{
    delete this->lhsExpr;
}

///
/// @}
///