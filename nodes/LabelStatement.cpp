///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       LabelStatement.cpp
/// @brief      Definition of the LabelStatement AST node.
/// @author     Patrick Flick
///

#include "LabelStatement.h"

using namespace dtcc::astnodes;

// calls accept(visitor) for all children nodes of this AST node
void LabelStatement::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
}

// implements the visitor pattern
void LabelStatement::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void LabelStatement::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void LabelStatement::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
LabelStatement::~LabelStatement()
{
    delete this->statement;

}

///
/// @}
///