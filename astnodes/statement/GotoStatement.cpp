///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       GotoStatement.cpp
/// @brief      Definition of the GotoStatement AST node.
/// @author     Patrick Flick
///

#include "GotoStatement.h"

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void GotoStatement::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    // nothing to do
}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void GotoStatement::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    // nothing to do
}

// calls accept(visitor) for all children nodes of this AST node
void GotoStatement::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
    // nothing to do
}

// implements the visitor pattern
void GotoStatement::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void GotoStatement::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void GotoStatement::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
GotoStatement::~GotoStatement()
{
}

///
/// @}
///