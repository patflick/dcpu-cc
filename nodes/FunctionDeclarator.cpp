///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       FunctionDeclarator.cpp
/// @brief      Definition of the FunctionDeclarator AST node.
/// @author     Patrick Flick
///

#include "FunctionDeclarator.h"

using namespace dtcc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void FunctionDeclarator::allChildrenAcceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    if (this->pointers != NULL)
        for (Pointers::iterator i = this->pointers->begin(); i != this->pointers->end(); ++i)
            (*i)->acceptPreRecursive(visitor);
    if (this->baseDeclarator != NULL)
        this->baseDeclarator->acceptPreRecursive(visitor);
    if (parameterList != NULL)
        for (Declarations::iterator i = parameterList->declarations.begin(); i != parameterList->declarations.end(); ++i)
            (*i)->acceptPreRecursive(visitor);
    if (this->initializers != NULL)
        for (Expressions::iterator i = this->initializers->begin(); i != this->initializers->end(); ++i)
            (*i)->acceptPreRecursive(visitor);
}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void FunctionDeclarator::allChildrenAcceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    if (this->pointers != NULL)
        for (Pointers::iterator i = this->pointers->begin(); i != this->pointers->end(); ++i)
            (*i)->acceptPostRecursive(visitor);
    if (this->baseDeclarator != NULL)
        this->baseDeclarator->acceptPostRecursive(visitor);
    if (parameterList != NULL)
        for (Declarations::iterator i = parameterList->declarations.begin(); i != parameterList->declarations.end(); ++i)
            (*i)->acceptPostRecursive(visitor);
    if (this->initializers != NULL)
        for (Expressions::iterator i = this->initializers->begin(); i != this->initializers->end(); ++i)
            (*i)->acceptPostRecursive(visitor);
}

// calls accept(visitor) for all children nodes of this AST node
void FunctionDeclarator::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    if (this->pointers != NULL)
        for (Pointers::iterator i = this->pointers->begin(); i != this->pointers->end(); ++i)
            (*i)->accept(visitor);
    if (this->baseDeclarator != NULL)
        this->baseDeclarator->accept(visitor);
    if (parameterList != NULL)
        for (Declarations::iterator i = parameterList->declarations.begin(); i != parameterList->declarations.end(); ++i)
            (*i)->accept(visitor);
    if (this->initializers != NULL)
        for (Expressions::iterator i = this->initializers->begin(); i != this->initializers->end(); ++i)
            (*i)->accept(visitor);
}

// implements the visitor pattern
void FunctionDeclarator::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void FunctionDeclarator::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void FunctionDeclarator::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
FunctionDeclarator::~FunctionDeclarator()
{
    if (parameterList != NULL)
        for (Declarations::iterator i = parameterList->declarations.begin(); i != parameterList->declarations.end(); ++i)
            this->safe_delete((*i));
    this->safe_delete(this->baseDeclarator);
    this->safe_delete(this->parameterList);

}

///
/// @}
///