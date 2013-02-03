///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       TypeConversionOperator.cpp
/// @brief      Definition of the TypeConversionOperator AST node.
/// @author     Patrick Flick
///

#include "TypeConversionOperator.h"

using namespace dtcc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void TypeConversionOperator::allChildrenAcceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    if (this->expr != NULL)
        this->expr->acceptPreRecursive(visitor);

}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void TypeConversionOperator::allChildrenAcceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    if (this->expr != NULL)
        this->expr->acceptPostRecursive(visitor);

}

// calls accept(visitor) for all children nodes of this AST node
void TypeConversionOperator::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    this->expr->accept(visitor);
}

// implements the visitor pattern
void TypeConversionOperator::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void TypeConversionOperator::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void TypeConversionOperator::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
TypeConversionOperator::~TypeConversionOperator()
{
    this->safe_delete(this->expr);
}

///
/// @}
///