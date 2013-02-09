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

using namespace dtcc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void CharacterLiteral::allChildrenAcceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void CharacterLiteral::allChildrenAcceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
}

// calls accept(visitor) for all children nodes of this AST node
void CharacterLiteral::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
}

// implements the visitor pattern
void CharacterLiteral::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void CharacterLiteral::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void CharacterLiteral::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
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