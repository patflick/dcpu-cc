///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       WhileStatement.cpp
/// @brief      Definition of the WhileStatement AST node.
/// @author     Patrick Flick
///

#include "WhileStatement.h"

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void WhileStatement::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->condExpr != NULL)
        this->condExpr->acceptPreRecursive(visitor);
    if (this->statement != NULL)
        this->statement->acceptPreRecursive(visitor);

}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void WhileStatement::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->condExpr != NULL)
        this->condExpr->acceptPostRecursive(visitor);
    if (this->statement != NULL)
        this->statement->acceptPostRecursive(visitor);

}

// calls accept(visitor) for all children nodes of this AST node
void WhileStatement::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
    this->condExpr->accept(visitor);
    this->statement->accept(visitor);

}

// implements the visitor pattern
void WhileStatement::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void WhileStatement::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void WhileStatement::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
WhileStatement::~WhileStatement()
{
    this->safe_delete(this->condExpr);
    this->safe_delete(this->statement);

}

///
/// @}
///