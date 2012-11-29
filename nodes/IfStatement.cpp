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

using namespace dtcc::astnodes;

// calls accept(visitor) for all children nodes of this AST node
void IfStatement::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
    this->condExpr->accept(visitor);
    this->ifStmt->accept(visitor);
    this->elseStmt->accept(visitor);

}

// implements the visitor pattern
void IfStatement::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void IfStatement::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void IfStatement::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
IfStatement::~IfStatement()
{
    delete this->condExpr;
    delete this->ifStmt;
    delete this->elseStmt;

}

///
/// @}
///