///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       PreIncDec.cpp
/// @brief      Definition of the PreIncDec AST node.
/// @author     Patrick Flick
///

#include "PreIncDec.h"

using namespace dtcc::astnodes;

// calls accept(visitor) for all children nodes of this AST node
void PreIncDec::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
}

// implements the visitor pattern
void PreIncDec::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void PreIncDec::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void PreIncDec::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
PreIncDec::~PreIncDec()
{
    delete this->expr;

}

///
/// @}
///