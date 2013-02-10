///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       LabelStatement.cpp
/// @brief      Definition of the LabelStatement AST node.
/// @author     Patrick Flick
///

#include "LabelStatement.h"

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void LabelStatement::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->statement != NULL)
        this->statement->acceptPreRecursive(visitor);
}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void LabelStatement::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->statement != NULL)
        this->statement->acceptPostRecursive(visitor);
}

// calls accept(visitor) for all children nodes of this AST node
void LabelStatement::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
    if (this->statement != NULL)
        this->statement->accept(visitor);
}

// implements the visitor pattern
void LabelStatement::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void LabelStatement::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void LabelStatement::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
LabelStatement::~LabelStatement()
{
    this->safe_delete(this->statement);
}

///
/// @}
///