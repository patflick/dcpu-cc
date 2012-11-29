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

using namespace dtcc::astnodes;

// calls accept(visitor) for all children nodes of this AST node
void ForStatement::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
    this->initExpr->accept(visitor);
    this->condExpr->accept(visitor);
    this->loopExpr->accept(visitor);
    this->statement->accept(visitor);

}

// implements the visitor pattern
void ForStatement::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void ForStatement::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void ForStatement::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
ForStatement::~ForStatement()
{
    delete this->initExpr;
    delete this->condExpr;
    delete this->loopExpr;
    delete this->statement;

}

///
/// @}
///