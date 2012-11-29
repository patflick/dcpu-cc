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

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void StructUnionSpecifier::allChildrenAcceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    if (this->declarations != NULL)
        for (Declarations::iterator i = this->declarations->begin(); i != this->declarations->end(); ++i)
            (*i)->acceptPreRecursive(visitor);
}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void StructUnionSpecifier::allChildrenAcceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    if (this->declarations != NULL)
        for (Declarations::iterator i = this->declarations->begin(); i != this->declarations->end(); ++i)
            (*i)->acceptPostRecursive(visitor);
}

// calls accept(visitor) for all children nodes of this AST node
void StructUnionSpecifier::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
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
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void StructUnionSpecifier::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
StructUnionSpecifier::~StructUnionSpecifier()
{
    if (this->declarations != NULL)
        for (Declarations::iterator i = this->declarations->begin(); i != this->declarations->end(); ++i)
            this->safe_delete(*i);
    this->safe_delete(this->declarations);
}

///
/// @}
///