///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       TypeName.cpp
/// @brief      Definition of the TypeName AST node.
/// @author     Patrick Flick
///

#include "TypeName.h"

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void TypeName::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    // TODO do we have to visit decl specifiers?
//     if (this->declSpecifiers != NULL)
//         this->declSpecifiers->acceptPreRecursive(visitor);
    if (this->abstrDeclarator != NULL)
        this->abstrDeclarator->acceptPreRecursive(visitor);
}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void TypeName::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    // TODO do we have to visit decl specifiers?
//     if (this->declSpecifiers != NULL)
//         this->declSpecifiers->acceptPostRecursive(visitor);
    if (this->abstrDeclarator != NULL)
        this->abstrDeclarator->acceptPostRecursive(visitor);
}

// calls accept(visitor) for all children nodes of this AST node
void TypeName::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
    // TODO do we have to visit decl specifiers?
    // this->declSpecifiers->accept(visitor);
    if (this->abstrDeclarator != NULL)
        this->abstrDeclarator->accept(visitor);
}

// implements the visitor pattern
void TypeName::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void TypeName::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void TypeName::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
TypeName::~TypeName()
{
    this->safe_delete(this->declSpecifiers);
    this->safe_delete(this->abstrDeclarator);

}

///
/// @}
///