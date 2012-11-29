///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       PostIncDec.cpp
/// @brief      Definition of the PostIncDec AST node.
/// @author     Patrick Flick
///

#include "PostIncDec.h"

using namespace dtcc::astnodes;

// calls accept(visitor) for all children nodes of this AST node
void PostIncDec::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    this->expr->accept(visitor);
}

// implements the visitor pattern
void PostIncDec::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void PostIncDec::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void PostIncDec::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
PostIncDec::~PostIncDec()
{
    delete this->expr;

}

///
/// @}
///