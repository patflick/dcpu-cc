///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       IfStatement.cpp
/// @brief      Definition of the IfStatement AST node.
/// @author     Patrick Flick
///

#include "IfStatement.h"

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void IfStatement::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->condExpr != NULL)
        this->condExpr->acceptPreRecursive(visitor);
    if (this->ifStmt != NULL)
        this->ifStmt->acceptPreRecursive(visitor);
    if (this->elseStmt != NULL)
        this->elseStmt->acceptPreRecursive(visitor);

}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void IfStatement::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->condExpr != NULL)
        this->condExpr->acceptPostRecursive(visitor);
    if (this->ifStmt != NULL)
        this->ifStmt->acceptPostRecursive(visitor);
    if (this->elseStmt != NULL)
        this->elseStmt->acceptPostRecursive(visitor);

}

// calls accept(visitor) for all children nodes of this AST node
void IfStatement::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
    this->condExpr->accept(visitor);
    this->ifStmt->accept(visitor);
    this->elseStmt->accept(visitor);

}

// implements the visitor pattern
void IfStatement::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void IfStatement::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void IfStatement::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
IfStatement::~IfStatement()
{
    this->safe_delete(this->condExpr);
    this->safe_delete(this->ifStmt);
    this->safe_delete(this->elseStmt);

}

///
/// @}
///