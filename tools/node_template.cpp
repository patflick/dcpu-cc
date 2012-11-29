///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       %ClassName%.cpp
/// @brief      Definition of the %ClassName% AST node.
/// @author     Patrick Flick
///

#include "%ClassName%.h"

using namespace dtcc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void %ClassName%::allChildrenAcceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
%ChildrenPreVisitor%
}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void %ClassName%::allChildrenAcceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
%ChildrenPostVisitor%
}

// calls accept(visitor) for all children nodes of this AST node
void %ClassName%::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
%ChildrenVisitor%
}

// implements the visitor pattern
void %ClassName%::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void %ClassName%::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void %ClassName%::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
%ClassName%::~%ClassName%()
{
%deleteClassMembers%
}

///
/// @}
///