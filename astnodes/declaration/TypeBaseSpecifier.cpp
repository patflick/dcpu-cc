///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       TypeBaseSpecifier.cpp
/// @brief      Definition of the TypeBaseSpecifier AST node.
/// @author     Patrick Flick
///

#include "TypeBaseSpecifier.h"

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void TypeBaseSpecifier::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    // nothing to do here
}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void TypeBaseSpecifier::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    // nothing to do here
}

// calls accept(visitor) for all children nodes of this AST node
void TypeBaseSpecifier::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
    // nothing to do here
}

// implements the visitor pattern
void TypeBaseSpecifier::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void TypeBaseSpecifier::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void TypeBaseSpecifier::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
TypeBaseSpecifier::~TypeBaseSpecifier()
{
}

///
/// @}
///