///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       ParameterDeclarations.h
/// @brief      Declaration of the ParameterDeclarations AST node.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_AST_NODES_TYPEQUALIFIERS_H
#define __DCPU_CC_AST_NODES_TYPEQUALIFIERS_H

#include "Node.h"
#include "Declaration.h"
#include <vector>

namespace dtcc
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
            ParameterDeclarations() : varArgs(false), declarations(std::vector<Declaration*>()) {}
            ~ParameterDeclarations() {}
        };
        
    } // namespace dtcc
} // namespace astnode

#endif

///
/// @}
///
