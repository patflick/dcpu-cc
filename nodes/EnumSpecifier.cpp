///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       EnumSpecifier.cpp
/// @brief      Definition of the EnumSpecifier AST node.
/// @author     Patrick Flick
///

#include "EnumSpecifier.h"

using namespace dtcc::astnodes;

// calls accept(visitor) for all children nodes of this AST node
void EnumSpecifier::allChildrenAccept(dtcc::visitor::Visitor & visitor)
{
    if (this->enums != NULL)
        for(Enumerators::iterator i = this->enums->begin(); i != this->enums->end(); ++i)
            (*i)->accept(visitor);
}

// implements the visitor pattern
void EnumSpecifier::accept(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
}

// implements the post recursive visitor pattern
void EnumSpecifier::acceptPostRecursive(dtcc::visitor::Visitor & visitor)
{
    visitor.visit(this);
    this->allChildrenAccept(visitor);
}

// implements the pre recursive visitor pattern
void EnumSpecifier::acceptPreRecursive(dtcc::visitor::Visitor & visitor)
{
    this->allChildrenAccept(visitor);
    visitor.visit(this);
}

// implements the destructor, which deletes all children
EnumSpecifier::~EnumSpecifier()
{
    delete this->enums;

}

///
/// @}
///