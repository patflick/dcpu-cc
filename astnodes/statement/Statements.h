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

#include <astnodes/Node.h>
#include "Statement.h"
#include <vector>

namespace dcpucc
{
    namespace astnodes
    {
        ///
        /// @brief      The Statements AST node.
        ///
        /// This is a std::vector of Statement.
        typedef std::vector<Statement*> Statements;
    } // namespace dcpucc
} // namespace astnode

#endif

///
/// @}
///
