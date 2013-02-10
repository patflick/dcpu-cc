///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       ReturnStatement.cpp
/// @brief      Definition of the ReturnStatement AST node.
/// @author     Patrick Flick
///

#include "ReturnStatement.h"

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void ReturnStatement::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->expr != NULL)
        this->expr->acceptPreRecursive(visitor);

}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void ReturnStatement::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->expr != NULL)
        this->expr->acceptPostRecursive(visitor);

}

// calls accept(visitor) for all children nodes of this AST node
void ReturnStatement::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
    this->expr->accept(visitor);

}

// implements the visitor pattern
void ReturnStatement::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void ReturnStatement::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void ReturnStatement::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
ReturnStatement::~ReturnStatement()
{
    this->safe_delete(this->expr);

}

///
/// @}
///