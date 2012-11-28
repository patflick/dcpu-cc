///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       Statement.cpp
/// @brief      Definition of the Statement AST node.
/// @author     Patrick Flick
///

#include "Statement.h"

using namespace dtcc::astnodes;

// calls accept(visitor) for all children nodes of this AST node
void Statement::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
}

// implements the visitor pattern
void Statement::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void Statement::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void Statement::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
Statement::~Statement()
{

}

///
/// @}
///