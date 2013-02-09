///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       ContinueStatement.cpp
/// @brief      Definition of the ContinueStatement AST node.
/// @author     Patrick Flick
///

#include "ContinueStatement.h"

using namespace dtcc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void ContinueStatement::allChildrenAcceptPreRecursive(dtcc::visitor::Visitor & visitor)
{

}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void ContinueStatement::allChildrenAcceptPostRecursive(dtcc::visitor::Visitor & visitor)
{

}

// calls accept(visitor) for all children nodes of this AST node
void ContinueStatement::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes

}

// implements the visitor pattern
void ContinueStatement::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void ContinueStatement::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void ContinueStatement::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
ContinueStatement::~ContinueStatement()
{

}

///
/// @}
///