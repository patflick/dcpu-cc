///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       FunctionDefinition.cpp
/// @brief      Definition of the FunctionDefinition AST node.
/// @author     Patrick Flick
///

#include "FunctionDefinition.h"

using namespace dtcc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void FunctionDefinition::allChildrenAcceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    // TODO do we have to visit DeclarationSpecifiers??
    //if (this->declSpecifiers != NULL)
    //    this->declSpecifiers->acceptPreRecursive(visitor);
    if (this->declarator != NULL)
        this->declarator->acceptPreRecursive(visitor);
    if (this->block != NULL)
        this->block->acceptPreRecursive(visitor);

}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void FunctionDefinition::allChildrenAcceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    // TODO do we have to visit DeclarationSpecifiers??
    //if (this->declSpecifiers != NULL)
    //    this->declSpecifiers->acceptPostRecursive(visitor);
    if (this->declarator != NULL)
        this->declarator->acceptPostRecursive(visitor);
    if (this->block != NULL)
        this->block->acceptPostRecursive(visitor);

}

// calls accept(visitor) for all children nodes of this AST node
void FunctionDefinition::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // TODO do we have to visit DeclarationSpecifiers??
    // this->declSpecifiers->accept(visitor);
    if (this->declarator != NULL)
        this->declarator->accept(visitor);
    if (this->block != NULL)
        this->block->accept(visitor);
}

// implements the visitor pattern
void FunctionDefinition::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void FunctionDefinition::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void FunctionDefinition::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
FunctionDefinition::~FunctionDefinition()
{
    this->safe_delete(this->declSpecifiers);
    this->safe_delete(this->declarator);
    this->safe_delete(this->block);
}

///
/// @}
///