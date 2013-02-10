///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       EmptyStatement.cpp
/// @brief      Definition of the EmptyStatement AST node.
/// @author     Patrick Flick
///

#include "EmptyStatement.h"

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void EmptyStatement::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{

}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void EmptyStatement::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{

}

// calls accept(visitor) for all children nodes of this AST node
void EmptyStatement::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes

}

// implements the visitor pattern
void EmptyStatement::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void EmptyStatement::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void EmptyStatement::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
EmptyStatement::~EmptyStatement()
{

}

///
/// @}
///