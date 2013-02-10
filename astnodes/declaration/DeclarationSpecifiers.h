///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       DeclarationSpecifiers.h
/// @brief      Declaration of the DeclarationSpecifiers Lists.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_AST_NODES_DECLARATIONSPECIFIERS_H
#define __DCPU_CC_AST_NODES_DECLARATIONSPECIFIERS_H

#include <astnodes/Node.h>
#include "StorageSpecifier.h"
#include "TypeSpecifier.h"
#include "TypeQualifier.h"
#include <vector>

namespace dcpucc
{
    namespace astnodes
    {
        ///
        /// @class      DeclarationSpecifiers
        /// @brief      The DeclarationSpecifiers Lists.
        ///
        /// Wraps lists (vectors) for storage specifiers, type specifiers
        /// and type qualifiers.
        class DeclarationSpecifiers
        {
        public:
            std::vector<StorageSpecifier*> storageSpecifiers;
            std::vector<TypeSpecifier*> typeSpecifiers;
            std::vector<TypeQualifier*> typeQualifiers;
            
        public:
            DeclarationSpecifiers() :
                storageSpecifiers(std::vector<StorageSpecifier*>()),
                typeSpecifiers(std::vector<TypeSpecifier*>()),
                typeQualifiers(std::vector<TypeQualifier*>()) {}
            ~DeclarationSpecifiers() {}
        };
        
    } // namespace dcpucc
} // namespace astnode

#endif

///
/// @}
///
