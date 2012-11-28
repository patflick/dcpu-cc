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

using namespace dtcc::astnodes;

// calls accept(visitor) for all children nodes of this AST node
void EmptyStatement::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
}

// implements the visitor pattern
void EmptyStatement::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void EmptyStatement::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void EmptyStatement::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
EmptyStatement::~EmptyStatement()
{

}

///
/// @}
///