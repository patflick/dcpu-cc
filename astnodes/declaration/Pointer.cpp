///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       Pointer.cpp
/// @brief      Definition of the Pointer AST node.
/// @author     Patrick Flick
///

#include "Pointer.h"

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void Pointer::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    // TODO do we need to visit type qualifiers??
//     if (this->typeQualifiers != NULL)
//         this->typeQualifiers->acceptPreRecursive(visitor);

}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void Pointer::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    // TODO do we need to visit type qualifiers??
//     if (this->typeQualifiers != NULL)
//         this->typeQualifiers->acceptPostRecursive(visitor);

}

// calls accept(visitor) for all children nodes of this AST node
void Pointer::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
    // TODO do we need to visit type qualifiers??
    //this->typeQualifiers->accept(visitor);

}

// implements the visitor pattern
void Pointer::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void Pointer::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void Pointer::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
Pointer::~Pointer()
{
    this->safe_delete(this->typeQualifiers);

}

///
/// @}
///