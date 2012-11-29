///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       BlockStatement.cpp
/// @brief      Definition of the BlockStatement AST node.
/// @author     Patrick Flick
///

#include "BlockStatement.h"

using namespace dtcc::astnodes;

// calls accept(visitor) for all children nodes of this AST node
void BlockStatement::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    // call accept for all children
    if (this->declarations != NULL)
        for (Declarations::iterator i = this->declarations->begin(); i != this->declarations->end(); ++i)
            (*i)->accept(visitor);
    if (this->statements != NULL)
        for (Statements::iterator i = this->statements->begin(); i != this->statements->end(); ++i)
            (*i)->accept(visitor);
}

// implements the visitor pattern
void BlockStatement::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void BlockStatement::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void BlockStatement::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
BlockStatement::~BlockStatement()
{
    delete this->declarations;
    delete this->statements;

}

///
/// @}
///