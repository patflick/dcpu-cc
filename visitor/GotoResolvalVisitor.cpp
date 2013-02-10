///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Visitor
/// @{
///

///
/// @file       GotoResolvalVisitor.cpp
/// @brief      Definitions of the GotoResolvalVisitor class.
/// @author     Patrick Flick
///

// import parser tokens
#define YYSTYPE int
#include <parser.hpp>

#include "GotoResolvalVisitor.h"
#include <iostream>
#include <string>

using namespace dcpucc;
using namespace dcpucc::visitor;


void GotoResolvalVisitor::visit(astnodes::GotoStatement * gotoStatement)
{
    // check if there is a matching label
    if (semCheck->m_funcLabels.find(gotoStatement->identifier) == semCheck->m_funcLabels.end())
    {
        semCheck->addError(gotoStatement, ERR_CC_GOTO_NO_LABEL, gotoStatement->identifier);
        return;
    }
    
    // assign matching label
    gotoStatement->lbl = semCheck->m_funcLabels[gotoStatement->identifier];
}


///
/// @}
///
