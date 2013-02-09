///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       Enumerators.h
/// @brief      Declaration of the Enumerators AST node.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_AST_NODES_ENUMERATORS_H
#define __DCPU_CC_AST_NODES_ENUMERATORS_H

#include <astnodes/Node.h>
#include "Enumerator.h"
#include <vector>

namespace dtcc
{
    namespace astnodes
    {
        ///
        /// @brief      The Enumerators AST node.
        ///
        /// This is a std::vector of Enumerator.
        typedef std::vector<Enumerator*> Enumerators;
    } // namespace dtcc
} // namespace astnode

#endif

///
/// @}
///
