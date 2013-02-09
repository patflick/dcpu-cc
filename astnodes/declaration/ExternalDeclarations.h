///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       ExternalDeclarations.h
/// @brief      Declaration of the ExternalDeclarations AST node.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_AST_NODES_EXTERNALDECLARATIONS_H
#define __DCPU_CC_AST_NODES_EXTERNALDECLARATIONS_H

#include <astnodes/Node.h>
#include "ExternalDeclaration.h"
#include <vector>

namespace dtcc
{
    namespace astnodes
    {
        ///
        /// @brief      The ExternalDeclarations AST node.
        ///
        /// This is a std::vector of ExternalDeclaration.
        typedef std::vector<ExternalDeclaration*> ExternalDeclarations;
    } // namespace dtcc
} // namespace astnode

#endif

///
/// @}
///
