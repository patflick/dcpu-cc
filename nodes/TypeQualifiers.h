///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       TypeQualifiers.h
/// @brief      Declaration of the TypeQualifiers AST node.
/// @author     Patrick Flick
///

#include "Node.h"
#ifndef __DCPU_CC_AST_NODES_TYPEQUALIFIERS_H
#define __DCPU_CC_AST_NODES_TYPEQUALIFIERS_H

#include "TypeQualifier.h"
#include <vector>

namespace dtcc
{
    namespace astnodes
    {
        ///
        /// @brief      The TypeQualifiers AST node.
        ///
        /// This is a std::vector of TypeQualifier.
        typedef std::vector<TypeQualifier*> TypeQualifiers;
    } // namespace dtcc
} // namespace astnode

#endif

///
/// @}
///
