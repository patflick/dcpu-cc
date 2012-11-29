///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       NoIdentifierDeclarator.cpp
/// @brief      Definition of the NoIdentifierDeclarator AST node.
/// @author     Patrick Flick
///

#include "NoIdentifierDeclarator.h"

using namespace dtcc::astnodes;

// calls accept(visitor) for all children nodes of this AST node
void NoIdentifierDeclarator::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes

}

// implements the visitor pattern
void NoIdentifierDeclarator::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void NoIdentifierDeclarator::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void NoIdentifierDeclarator::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
NoIdentifierDeclarator::~NoIdentifierDeclarator()
{

}

///
/// @}
///