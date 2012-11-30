///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Visitor
/// @{
///

///
/// @file       CheckTypedefVisitor.cpp
/// @brief      Definitions of the CheckTypedefVisitor class.
/// @author     Patrick Flick
///

// import parser tokens
#define YYSTYPE int
#include <parser.hpp>

#include "CheckTypedefVisitor.h"
#include <iostream>
#include <string>

using namespace dtcc::visitor;


void CheckTypedefVisitor::visit(astnodes::Declaration * declaration)
{
    // this visitor is called with acceptPreRecursive,
    // which means the child nodes have already been visited and the
    // typeNameList list is filled with all identifiers.
    // i.e. we are doing Post-Processing here.
    
    for (std::vector<astnodes::StorageSpecifier*>::iterator i = declaration->declSpecifiers->storageSpecifiers.begin(); i != declaration->declSpecifiers->storageSpecifiers.end(); ++i)
    {
        if ((*i)->token == TYPEDEF)
        {
            this->isTypedef = true;
        }
    }
}

void CheckTypedefVisitor::visit(astnodes::FunctionDeclarator * functionDeclarator)
{
    // ignore the parameters list of a function declarator (those add
    // their name to the list as well):
    // - clear list
    // - visit the base declarator of the functiond declarator again
    this->typeNameList.clear();
    functionDeclarator->baseDeclarator->acceptPreRecursive(*this);
}


void CheckTypedefVisitor::visit(astnodes::IdentifierDeclarator * identifierDeclarator)
{
    this->typeNameList.push_back(identifierDeclarator->name);
}


///
/// @}
///
