///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       ParameterDeclarations.h
/// @brief      Declaration of the ParameterDeclarations AST node.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_AST_NODES_PARAMETERDECLARATIONS_H
#define __DCPU_CC_AST_NODES_PARAMETERDECLARATIONS_H

#include <astnodes/Node.h>
#include "Declaration.h"
#include <vector>

namespace dcpucc
{
    namespace astnodes
    {
        ///
        /// @class      ParameterDeclarations
        /// @brief      The ParameterDeclarations AST node.
        ///
        class ParameterDeclarations
        {
        public:
            std::vector<Declaration*> declarations;
            bool varArgs;
            
        public:
            ParameterDeclarations() : declarations(std::vector<Declaration*>()), varArgs(false) {}
            ~ParameterDeclarations() {}
        };
        
    } // namespace dcpucc
} // namespace astnode

#endif

///
/// @}
///
