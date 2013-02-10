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

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void PreIncDec::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->expr != NULL)
        this->expr->acceptPreRecursive(visitor);
}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void PreIncDec::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->expr != NULL)
        this->expr->acceptPostRecursive(visitor);
}

// calls accept(visitor) for all children nodes of this AST node
void PreIncDec::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
    if (this->expr != NULL)
        this->expr->accept(visitor);
}

// implements the visitor pattern
void PreIncDec::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void PreIncDec::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void PreIncDec::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
PreIncDec::~PreIncDec()
{
    this->safe_delete(this->expr);
}

///
/// @}
///