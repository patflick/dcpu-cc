///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       CharacterLiteral.cpp
/// @brief      Definition of the CharacterLiteral AST node.
/// @author     Patrick Flick
///

#include "CharacterLiteral.h"

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void CharacterLiteral::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void CharacterLiteral::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
}

// calls accept(visitor) for all children nodes of this AST node
void CharacterLiteral::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
}

// implements the visitor pattern
void CharacterLiteral::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void CharacterLiteral::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void CharacterLiteral::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
CharacterLiteral::~CharacterLiteral()
{
}

///
/// @}
///