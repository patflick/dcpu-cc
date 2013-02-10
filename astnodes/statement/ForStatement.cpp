///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       ForStatement.cpp
/// @brief      Definition of the ForStatement AST node.
/// @author     Patrick Flick
///

#include "ForStatement.h"

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void ForStatement::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->initExpr != NULL)
        this->initExpr->acceptPreRecursive(visitor);
    if (this->condExpr != NULL)
        this->condExpr->acceptPreRecursive(visitor);
    if (this->loopExpr != NULL)
        this->loopExpr->acceptPreRecursive(visitor);
    if (this->statement != NULL)
        this->statement->acceptPreRecursive(visitor);

}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void ForStatement::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->initExpr != NULL)
        this->initExpr->acceptPostRecursive(visitor);
    if (this->condExpr != NULL)
        this->condExpr->acceptPostRecursive(visitor);
    if (this->loopExpr != NULL)
        this->loopExpr->acceptPostRecursive(visitor);
    if (this->statement != NULL)
        this->statement->acceptPostRecursive(visitor);

}

// calls accept(visitor) for all children nodes of this AST node
void ForStatement::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
    this->initExpr->accept(visitor);
    this->condExpr->accept(visitor);
    this->loopExpr->accept(visitor);
    this->statement->accept(visitor);

}

// implements the visitor pattern
void ForStatement::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void ForStatement::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void ForStatement::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
ForStatement::~ForStatement()
{
    this->safe_delete(this->initExpr);
    this->safe_delete(this->condExpr);
    this->safe_delete(this->loopExpr);
    this->safe_delete(this->statement);

}

///
/// @}
///