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

using namespace dtcc::astnodes;

// calls accept(visitor) for all children nodes of this AST node
void WhileStatement::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
}

// implements the visitor pattern
void WhileStatement::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void WhileStatement::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void WhileStatement::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
WhileStatement::~WhileStatement()
{
    delete this->condExpr;
    delete this->statement;

}

///
/// @}
///