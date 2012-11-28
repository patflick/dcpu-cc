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

// calls accept(visitor) for all children nodes of this AST node
void FunctionDefinition::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
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
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void FunctionDefinition::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
FunctionDefinition::~FunctionDefinition()
{
    delete this->declSpecifiers;
    delete this->declarator;
    delete this->block;

}

///
/// @}
///