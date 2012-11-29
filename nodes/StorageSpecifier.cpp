///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       StorageSpecifier.cpp
/// @brief      Definition of the StorageSpecifier AST node.
/// @author     Patrick Flick
///

#include "StorageSpecifier.h"

using namespace dtcc::astnodes;

// calls accept(visitor) for all children nodes of this AST node
void StorageSpecifier::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // nothing to do here
}

// implements the visitor pattern
void StorageSpecifier::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void StorageSpecifier::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void StorageSpecifier::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
StorageSpecifier::~StorageSpecifier()
{
}

///
/// @}
///