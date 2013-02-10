///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       TypeNameSpecifier.cpp
/// @brief      Definition of the TypeNameSpecifier AST node.
/// @author     Patrick Flick
///

#include "TypeNameSpecifier.h"

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void TypeNameSpecifier::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    // nothing to do here
}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void TypeNameSpecifier::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    // nothing to do here
}

// calls accept(visitor) for all children nodes of this AST node
void TypeNameSpecifier::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
    // nothing to do here
}

// implements the visitor pattern
void TypeNameSpecifier::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void TypeNameSpecifier::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void TypeNameSpecifier::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
TypeNameSpecifier::~TypeNameSpecifier()
{
}

///
/// @}
///