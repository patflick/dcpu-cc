///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       Constant.cpp
/// @brief      Definition of the Constant AST node.
/// @author     Patrick Flick
///

#include "Constant.h"

using namespace dtcc::astnodes;

// calls accept(visitor) for all children nodes of this AST node
void Constant::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // nothing to do here
}

// implements the visitor pattern
void Constant::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void Constant::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void Constant::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
Constant::~Constant()
{

}

///
/// @}
///