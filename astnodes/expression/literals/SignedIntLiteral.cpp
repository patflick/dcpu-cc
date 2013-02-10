///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       SignedIntLiteral.cpp
/// @brief      Definition of the SignedIntLiteral AST node.
/// @author     Patrick Flick
///

#include "SignedIntLiteral.h"

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void SignedIntLiteral::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void SignedIntLiteral::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
}

// calls accept(visitor) for all children nodes of this AST node
void SignedIntLiteral::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
}

// implements the visitor pattern
void SignedIntLiteral::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void SignedIntLiteral::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void SignedIntLiteral::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
SignedIntLiteral::~SignedIntLiteral()
{
}

///
/// @}
///