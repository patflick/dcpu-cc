///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       ArrayDeclarator.cpp
/// @brief      Definition of the ArrayDeclarator AST node.
/// @author     Patrick Flick
///

#include "ArrayDeclarator.h"

using namespace dtcc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void ArrayDeclarator::allChildrenAcceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    if (this->baseDeclarator != NULL)
        this->baseDeclarator->acceptPreRecursive(visitor);
    if (this->constExpr != NULL)
        this->constExpr->acceptPreRecursive(visitor);

}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void ArrayDeclarator::allChildrenAcceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    if (this->baseDeclarator != NULL)
        this->baseDeclarator->acceptPostRecursive(visitor);
    if (this->constExpr != NULL)
        this->constExpr->acceptPostRecursive(visitor);

}

// calls accept(visitor) for all children nodes of this AST node
void ArrayDeclarator::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
    this->baseDeclarator->accept(visitor);
    this->constExpr->accept(visitor);

}

// implements the visitor pattern
void ArrayDeclarator::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void ArrayDeclarator::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void ArrayDeclarator::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
ArrayDeclarator::~ArrayDeclarator()
{
    this->safe_delete(this->baseDeclarator);
    this->safe_delete(this->constExpr);

}

///
/// @}
///