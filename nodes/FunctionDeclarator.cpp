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

// calls accept(visitor) for all children nodes of this AST node
void FunctionDeclarator::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
    this->baseDeclarator->accept(visitor);
    if (parameterList != NULL)
        for (Declarations::iterator i = parameterList->declarations.begin(); i != parameterList->declarations.end(); ++i)
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
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void FunctionDeclarator::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
FunctionDeclarator::~FunctionDeclarator()
{
    delete this->baseDeclarator;
    delete this->parameterList;

}

///
/// @}
///