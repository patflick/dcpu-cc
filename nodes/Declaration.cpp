///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       Declaration.cpp
/// @brief      Definition of the Declaration AST node.
/// @author     Patrick Flick
///

#include "Declaration.h"

using namespace dtcc::astnodes;

// calls accept(visitor) for all children nodes of this AST node
void Declaration::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // TODO do we have to visit declspecifiers??
    // this->declSpecifiers->accept(visitor);
    if (this->declarators != NULL)
        for (Declarators::iterator i = this->declarators->begin(); i != this->declarators->end(); ++i)
            (*i)->accept(visitor);
    if (this->singleDeclarator != NULL)
        this->singleDeclarator->accept(visitor);

}

// implements the visitor pattern
void Declaration::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void Declaration::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void Declaration::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
Declaration::~Declaration()
{
    delete this->declSpecifiers;
    delete this->declarators;

}

///
/// @}
///