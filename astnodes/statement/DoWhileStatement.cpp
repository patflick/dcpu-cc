///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       DoWhileStatement.cpp
/// @brief      Definition of the DoWhileStatement AST node.
/// @author     Patrick Flick
///

#include "DoWhileStatement.h"

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void DoWhileStatement::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->statement != NULL)
        this->statement->acceptPreRecursive(visitor);
    if (this->condExpr != NULL)
        this->condExpr->acceptPreRecursive(visitor);

}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void DoWhileStatement::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->statement != NULL)
        this->statement->acceptPostRecursive(visitor);
    if (this->condExpr != NULL)
        this->condExpr->acceptPostRecursive(visitor);

}

// calls accept(visitor) for all children nodes of this AST node
void DoWhileStatement::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
    this->statement->accept(visitor);
    this->condExpr->accept(visitor);

}

// implements the visitor pattern
void DoWhileStatement::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void DoWhileStatement::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void DoWhileStatement::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
DoWhileStatement::~DoWhileStatement()
{
    this->safe_delete(this->statement);
    this->safe_delete(this->condExpr);

}

///
/// @}
///