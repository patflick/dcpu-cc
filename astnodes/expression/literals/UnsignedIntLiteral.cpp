///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       UnsignedIntLiteral.cpp
/// @brief      Definition of the UnsignedIntLiteral AST node.
/// @author     Patrick Flick
///

#include "UnsignedIntLiteral.h"

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void UnsignedIntLiteral::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    // nothing to do here
}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void UnsignedIntLiteral::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    // nothing to do here
}

// calls accept(visitor) for all children nodes of this AST node
void UnsignedIntLiteral::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
    // nothing to do here
}

// implements the visitor pattern
void UnsignedIntLiteral::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void UnsignedIntLiteral::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void UnsignedIntLiteral::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
UnsignedIntLiteral::~UnsignedIntLiteral()
{
    // nothing to do here
}

///
/// @}
///