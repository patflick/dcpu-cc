///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       Statements.h
/// @brief      Declaration of the Statements AST node.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_AST_NODES_STATEMENTS_H
#define __DCPU_CC_AST_NODES_STATEMENTS_H

#include "Node.h"
#include "Statement.h"
#include <vector>

namespace dtcc
{
    namespace astnodes
    {
        ///
        /// @brief      The Statements AST node.
        ///
        /// This is a std::vector of Statement.
        typedef std::vector<Statement*> Statements;
    } // namespace dtcc
} // namespace astnode

#endif

///
/// @}
///
