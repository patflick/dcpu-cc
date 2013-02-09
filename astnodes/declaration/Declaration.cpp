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

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void Declaration::allChildrenAcceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    // TODO do we have to visit declspecifiers??
        // this->declSpecifiers->acceptPreRecursive(visitor);
    if (this->declarators != NULL)
        for (Declarators::iterator i = this->declarators->begin(); i != this->declarators->end(); ++i)
            (*i)->acceptPreRecursive(visitor);
    if (this->singleDeclarator != NULL)
        this->singleDeclarator->acceptPreRecursive(visitor);
}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void Declaration::allChildrenAcceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    // TODO do we have to visit declspecifiers??
    // this->declSpecifiers->acceptPostRecursive(visitor);
    if (this->declarators != NULL)
        for (Declarators::iterator i = this->declarators->begin(); i != this->declarators->end(); ++i)
            (*i)->acceptPostRecursive(visitor);
    if (this->singleDeclarator != NULL)
        this->singleDeclarator->acceptPostRecursive(visitor);
}

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
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void Declaration::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
Declaration::~Declaration()
{
    if (this->declarators != NULL)
        for (Declarators::iterator i = this->declarators->begin(); i != this->declarators->end(); ++i)
            this->safe_delete((*i));
    this->safe_delete(this->declSpecifiers);
    this->safe_delete(this->declarators);
    this->safe_delete(this->singleDeclarator);
}

///
/// @}
///