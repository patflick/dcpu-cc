///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       CaseStatement.cpp
/// @brief      Definition of the CaseStatement AST node.
/// @author     Patrick Flick
///

#include "CaseStatement.h"

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void CaseStatement::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->constExpr != NULL)
        this->constExpr->acceptPreRecursive(visitor);
    if (this->statement != NULL)
        this->statement->acceptPreRecursive(visitor);

}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void CaseStatement::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->constExpr != NULL)
        this->constExpr->acceptPostRecursive(visitor);
    if (this->statement != NULL)
        this->statement->acceptPostRecursive(visitor);

}

// calls accept(visitor) for all children nodes of this AST node
void CaseStatement::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
    this->constExpr->accept(visitor);
    this->statement->accept(visitor);

}

// implements the visitor pattern
void CaseStatement::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void CaseStatement::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void CaseStatement::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
CaseStatement::~CaseStatement()
{
    this->safe_delete(this->constExpr);
    this->safe_delete(this->statement);

}

///
/// @}
///