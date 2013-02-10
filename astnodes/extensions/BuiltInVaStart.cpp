///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       BuiltInVaStart.cpp
/// @brief      Definition of the BuiltInVaStart AST node.
/// @author     Patrick Flick
///

#include "BuiltInVaStart.h"

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void BuiltInVaStart::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->vaListID != NULL)
        this->vaListID->acceptPreRecursive(visitor);
    if (this->paramNID != NULL)
        this->paramNID->acceptPreRecursive(visitor);

}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void BuiltInVaStart::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->vaListID != NULL)
        this->vaListID->acceptPostRecursive(visitor);
    if (this->paramNID != NULL)
        this->paramNID->acceptPostRecursive(visitor);

}

// calls accept(visitor) for all children nodes of this AST node
void BuiltInVaStart::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
    // TODO implement this to call .accept(visitor) for all children nodes
    this->vaListID->accept(visitor);
    this->paramNID->accept(visitor);

}

// implements the visitor pattern
void BuiltInVaStart::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void BuiltInVaStart::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void BuiltInVaStart::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
BuiltInVaStart::~BuiltInVaStart()
{
    this->safe_delete(this->vaListID);
    this->safe_delete(this->paramNID);

}

///
/// @}
///