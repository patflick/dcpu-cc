///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       AddressOfOperator.cpp
/// @brief      Definition of the AddressOfOperator AST node.
/// @author     Patrick Flick
///

#include "AddressOfOperator.h"

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void AddressOfOperator::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->expr != NULL)
        this->expr->acceptPreRecursive(visitor);
}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void AddressOfOperator::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->expr != NULL)
        this->expr->acceptPostRecursive(visitor);
}

// calls accept(visitor) for all children nodes of this AST node
void AddressOfOperator::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
    if (this->expr != NULL)
        this->expr->accept(visitor);
}

// implements the visitor pattern
void AddressOfOperator::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void AddressOfOperator::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void AddressOfOperator::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
AddressOfOperator::~AddressOfOperator()
{
    this->safe_delete(this->expr);
}

///
/// @}
///