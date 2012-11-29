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

using namespace dtcc::astnodes;

// calls accept(visitor) for all children nodes of this AST node
void TypeName::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // TODO do we have to visit decl specifiers?
    // this->declSpecifiers->accept(visitor);
    this->abstrDeclarator->accept(visitor);

}

// implements the visitor pattern
void TypeName::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void TypeName::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void TypeName::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
TypeName::~TypeName()
{
    delete this->declSpecifiers;
    delete this->abstrDeclarator;

}

///
/// @}
///