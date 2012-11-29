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

using namespace dtcc::astnodes;

// calls accept(visitor) for all children nodes of this AST node
void DoWhileStatement::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
    this->statement->accept(visitor);
    this->condExpr->accept(visitor);

}

// implements the visitor pattern
void DoWhileStatement::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void DoWhileStatement::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void DoWhileStatement::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
DoWhileStatement::~DoWhileStatement()
{
    delete this->statement;
    delete this->condExpr;

}

///
/// @}
///