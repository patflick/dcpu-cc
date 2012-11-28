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

using namespace dtcc::astnodes;

// calls accept(visitor) for all children nodes of this AST node
void TypeNameSpecifier::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
}

// implements the visitor pattern
void TypeNameSpecifier::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void TypeNameSpecifier::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void TypeNameSpecifier::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
TypeNameSpecifier::~TypeNameSpecifier()
{

}

///
/// @}
///