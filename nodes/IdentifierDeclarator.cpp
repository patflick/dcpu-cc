///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       IdentifierDeclarator.cpp
/// @brief      Definition of the IdentifierDeclarator AST node.
/// @author     Patrick Flick
///

#include "IdentifierDeclarator.h"

using namespace dtcc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void IdentifierDeclarator::allChildrenAcceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    // nothing to do
}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void IdentifierDeclarator::allChildrenAcceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    // nothing to do
}

// calls accept(visitor) for all children nodes of this AST node
void IdentifierDeclarator::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // nothing to do
}

// implements the visitor pattern
void IdentifierDeclarator::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void IdentifierDeclarator::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void IdentifierDeclarator::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
IdentifierDeclarator::~IdentifierDeclarator()
{
}

///
/// @}
///