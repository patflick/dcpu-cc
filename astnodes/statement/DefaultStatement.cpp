///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       DefaultStatement.cpp
/// @brief      Definition of the DefaultStatement AST node.
/// @author     Patrick Flick
///

#include "DefaultStatement.h"

using namespace dtcc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void DefaultStatement::allChildrenAcceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    if (this->statement != NULL)
        this->statement->acceptPreRecursive(visitor);

}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void DefaultStatement::allChildrenAcceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    if (this->statement != NULL)
        this->statement->acceptPostRecursive(visitor);

}

// calls accept(visitor) for all children nodes of this AST node
void DefaultStatement::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
    this->statement->accept(visitor);

}

// implements the visitor pattern
void DefaultStatement::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void DefaultStatement::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void DefaultStatement::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
DefaultStatement::~DefaultStatement()
{
    this->safe_delete(this->statement);

}

///
/// @}
///