///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       TypeQualifier.cpp
/// @brief      Definition of the TypeQualifier AST node.
/// @author     Patrick Flick
///

#include "TypeQualifier.h"

using namespace dtcc::astnodes;

// calls accept(visitor) for all children nodes of this AST node
void TypeQualifier::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
}

// implements the visitor pattern
void TypeQualifier::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void TypeQualifier::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void TypeQualifier::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
TypeQualifier::~TypeQualifier()
{
}

///
/// @}
///