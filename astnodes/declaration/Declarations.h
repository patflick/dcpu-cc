///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       Declarations.h
/// @brief      Declaration of the Declarations AST node.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_AST_NODES_DECLARATIONS_H
#define __DCPU_CC_AST_NODES_DECLARATIONS_H

#include <astnodes/Node.h>
#include "Declaration.h"
#include <vector>

namespace dcpucc
{
    namespace astnodes
    {
        ///
        /// @brief      The Declarations AST node.
        ///
        /// This is a std::vector of Declaration.
        typedef std::vector<Declaration*> Declarations;
    } // namespace dcpucc
} // namespace astnode

#endif

///
/// @}
///
