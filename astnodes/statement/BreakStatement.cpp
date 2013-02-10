///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       BreakStatement.cpp
/// @brief      Definition of the BreakStatement AST node.
/// @author     Patrick Flick
///

#include "BreakStatement.h"

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void BreakStatement::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{

}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void BreakStatement::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{

}

// calls accept(visitor) for all children nodes of this AST node
void BreakStatement::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes

}

// implements the visitor pattern
void BreakStatement::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void BreakStatement::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void BreakStatement::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
BreakStatement::~BreakStatement()
{

}

///
/// @}
///