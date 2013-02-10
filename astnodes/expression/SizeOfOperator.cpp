///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       SizeOfOperator.cpp
/// @brief      Definition of the SizeOfOperator AST node.
/// @author     Patrick Flick
///

#include "SizeOfOperator.h"

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void SizeOfOperator::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->typeName != NULL)
        this->typeName->acceptPreRecursive(visitor);
    if (this->expr != NULL)
        this->expr->acceptPreRecursive(visitor);
}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void SizeOfOperator::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->typeName != NULL)
        this->typeName->acceptPostRecursive(visitor);
    if (this->expr != NULL)
        this->expr->acceptPostRecursive(visitor);

}

// calls accept(visitor) for all children nodes of this AST node
void SizeOfOperator::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
    if (this->typeName != NULL)
        this->typeName->accept(visitor);
    if (this->expr != NULL)
        this->expr->accept(visitor);

}

// implements the visitor pattern
void SizeOfOperator::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void SizeOfOperator::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void SizeOfOperator::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
SizeOfOperator::~SizeOfOperator()
{
    this->safe_delete(this->typeName);

}

///
/// @}
///