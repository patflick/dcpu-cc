///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       StructUnionSpecifier.cpp
/// @brief      Definition of the StructUnionSpecifier AST node.
/// @author     Patrick Flick
///

#include "StructUnionSpecifier.h"

using namespace dtcc::astnodes;

// calls accept(visitor) for all children nodes of this AST node
void StructUnionSpecifier::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
    if (this->declarations != NULL)
        for (Declarations::iterator i = this->declarations->begin(); i != this->declarations->end(); ++i)
            (*i)->accept(visitor);
}

// implements the visitor pattern
void StructUnionSpecifier::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void StructUnionSpecifier::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void StructUnionSpecifier::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
StructUnionSpecifier::~StructUnionSpecifier()
{
    delete this->declarations;
}

///
/// @}
///