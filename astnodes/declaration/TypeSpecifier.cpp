///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       TypeSpecifier.cpp
/// @brief      Definition of the TypeSpecifier AST node.
/// @author     Patrick Flick
///

#include "TypeSpecifier.h"

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void TypeSpecifier::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{

}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void TypeSpecifier::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{

}

// calls accept(visitor) for all children nodes of this AST node
void TypeSpecifier::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes

}

// implements the visitor pattern
void TypeSpecifier::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void TypeSpecifier::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void TypeSpecifier::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
TypeSpecifier::~TypeSpecifier()
{

}

///
/// @}
///