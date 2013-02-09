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

using namespace dtcc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void LabelStatement::allChildrenAcceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    if (this->statement != NULL)
        this->statement->acceptPreRecursive(visitor);
}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void LabelStatement::allChildrenAcceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    if (this->statement != NULL)
        this->statement->acceptPostRecursive(visitor);
}

// calls accept(visitor) for all children nodes of this AST node
void LabelStatement::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    if (this->statement != NULL)
        this->statement->accept(visitor);
}

// implements the visitor pattern
void LabelStatement::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void LabelStatement::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void LabelStatement::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
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