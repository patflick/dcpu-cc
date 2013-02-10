///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       ChainExpressions.cpp
/// @brief      Definition of the ChainExpressions AST node.
/// @author     Patrick Flick
///

#include "ChainExpressions.h"

using namespace dcpucc::astnodes;

// calls acceptPreRecursive(visitor) for all children nodes of this AST node
void ChainExpressions::allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->exprs != NULL)
        for (Expressions::iterator i = this->exprs->begin(); i != this->exprs->end(); ++i)
            (*i)->acceptPreRecursive(visitor);
}

// calls acceptPostRecursive(visitor) for all children nodes of this AST node
void ChainExpressions::allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    if (this->exprs != NULL)
        for (Expressions::iterator i = this->exprs->begin(); i != this->exprs->end(); ++i)
            (*i)->acceptPostRecursive(visitor);
}

// calls accept(visitor) for all children nodes of this AST node
void ChainExpressions::allChildrenAccept(dcpucc::visitor::Visitor & visitor)
{
    if (this->exprs != NULL)
        for (Expressions::iterator i = this->exprs->begin(); i != this->exprs->end(); ++i)
            (*i)->accept(visitor);
}

// implements the visitor pattern
void ChainExpressions::accept(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void ChainExpressions::acceptPostRecursive(dcpucc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAcceptPostRecursive(visitor);
}

// implements the pre recursive visitor pattern
void ChainExpressions::acceptPreRecursive(dcpucc::visitor::Visitor & visitor)
{
    this->allChildrenAcceptPreRecursive(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
ChainExpressions::~ChainExpressions()
{
    if (this->exprs != NULL)
        for (Expressions::iterator i = this->exprs->begin(); i != this->exprs->end(); ++i)
            this->safe_delete((*i));
    this->safe_delete(this->exprs);
}

///
/// @}
///