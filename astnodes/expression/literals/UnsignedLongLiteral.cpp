///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       UnsignedLongLiteral.cpp
/// @brief      Definition of the UnsignedLongLiteral AST node.
/// @author     Patrick Flick
///

#include "UnsignedLongLiteral.h"

using namespace dtcc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void UnsignedLongLiteral::allChildrenAcceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    // nothing to do here
}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void UnsignedLongLiteral::allChildrenAcceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    // nothing to do here
}

// calls accept(visitor) for all children nodes of this AST node
void UnsignedLongLiteral::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // nothing to do here
}

// implements the visitor pattern
void UnsignedLongLiteral::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void UnsignedLongLiteral::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void UnsignedLongLiteral::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
UnsignedLongLiteral::~UnsignedLongLiteral()
{
    // nothing to do here
}

///
/// @}
///