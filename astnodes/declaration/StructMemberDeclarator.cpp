///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       StructMemberDeclarator.cpp
/// @brief      Definition of the StructMemberDeclarator AST node.
/// @author     Patrick Flick
///

#include "StructMemberDeclarator.h"

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void StructMemberDeclarator::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->pointers != NULL)
        for (Pointers::iterator i = this->pointers->begin(); i != this->pointers->end(); ++i)
            (*i)->acceptPreRecursive(visitor);
    if (this->baseDeclarator != NULL)
        this->baseDeclarator->acceptPreRecursive(visitor);
    if (this->constExpr != NULL)
        this->constExpr->acceptPreRecursive(visitor);
}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void StructMemberDeclarator::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->pointers != NULL)
        for (Pointers::iterator i = this->pointers->begin(); i != this->pointers->end(); ++i)
            (*i)->acceptPostRecursive(visitor);
    if (this->baseDeclarator != NULL)
        this->baseDeclarator->acceptPostRecursive(visitor);
    if (this->constExpr != NULL)
        this->constExpr->acceptPostRecursive(visitor);
}

// calls accept(visitor) for all children nodes of this AST node
void StructMemberDeclarator::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
    if (this->pointers != NULL)
        for (Pointers::iterator i = this->pointers->begin(); i != this->pointers->end(); ++i)
            (*i)->accept(visitor);
    if (this->baseDeclarator != NULL)
        this->baseDeclarator->accept(visitor);
    if (this->constExpr != NULL)
        this->constExpr->accept(visitor);
}

// implements the visitor pattern
void StructMemberDeclarator::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void StructMemberDeclarator::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void StructMemberDeclarator::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
StructMemberDeclarator::~StructMemberDeclarator()
{
    this->safe_delete(this->baseDeclarator);
    this->safe_delete(this->constExpr);

}

///
/// @}
///