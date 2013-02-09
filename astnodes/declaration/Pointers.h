///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       Pointers.h
/// @brief      Declaration of the Pointers AST node.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_AST_NODES_POINTERS_H
#define __DCPU_CC_AST_NODES_POINTERS_H

#include <astnodes/Node.h>
#include "Pointer.h"
#include <vector>

namespace dtcc
{
    namespace astnodes
    {
        ///
        /// @brief      The Pointers AST node.
        ///
        /// This is a std::vector of Pointer.
        typedef std::vector<Pointer*> Pointers;
    } // namespace dtcc
} // namespace astnode

#endif

///
/// @}
///
