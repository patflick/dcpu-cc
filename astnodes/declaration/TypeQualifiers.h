///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       TypeQualifiers.h
/// @brief      Declaration of the TypeQualifiers AST node.
/// @author     Patrick Flick
///

#include <astnodes/Node.h>
#ifndef __DCPU_CC_AST_NODES_TYPEQUALIFIERS_H
#define __DCPU_CC_AST_NODES_TYPEQUALIFIERS_H

#include "TypeQualifier.h"
#include <vector>

namespace dcpucc
{
    namespace astnodes
    {
        ///
        /// @brief      The TypeQualifiers AST node.
        ///
        /// This is a std::vector of TypeQualifier.
        typedef std::vector<TypeQualifier*> TypeQualifiers;
    } // namespace dcpucc
} // namespace astnode

#endif

///
/// @}
///
