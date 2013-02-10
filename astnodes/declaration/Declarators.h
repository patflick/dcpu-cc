///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       Declarators.h
/// @brief      Declaration of the Declarators AST node.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_AST_NODES_DECLARATORS_H
#define __DCPU_CC_AST_NODES_DECLARATORS_H

#include <astnodes/Node.h>
#include "Declarator.h"
#include <vector>

namespace dcpucc
{
    namespace astnodes
    {
        ///
        /// @brief      The Declarators AST node.
        ///
        /// This is a std::vector of Declarator.
        typedef std::vector<Declarator*> Declarators;
    } // namespace dcpucc
} // namespace astnode

#endif

///
/// @}
///
