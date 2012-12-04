///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       SignedLongLiteral.cpp
/// @brief      Definition of the SignedLongLiteral AST node.
/// @author     Patrick Flick
///

#include "SignedLongLiteral.h"

using namespace dtcc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void SignedLongLiteral::allChildrenAcceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    // nothing to do here
}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void SignedLongLiteral::allChildrenAcceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    // nothing to do here
}

// calls accept(visitor) for all children nodes of this AST node
void SignedLongLiteral::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // nothing to do here
}

// implements the visitor pattern
void SignedLongLiteral::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void SignedLongLiteral::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void SignedLongLiteral::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
SignedLongLiteral::~SignedLongLiteral()
{
    // nothing to do here
}

///
/// @}
///