///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       Declaration.h
/// @brief      Declaration of the Declaration AST node.
/// @author     Patrick Flick
///

#include <astnodes/Node.h>

#ifndef __DCPU_CC_AST_NODES_DECLARATION_H
#define __DCPU_CC_AST_NODES_DECLARATION_H

// include needed nodes
#include "ExternalDeclaration.h"
#include "DeclarationSpecifiers.h"
#include "Declarators.h"
#include <cstdlib>

#include <types/Type.h>

namespace dcpucc
{
    namespace astnodes
    {
        

        enum StorSpec_t {STORAGE_DEFAULT, STORAGE_TYPEDEF, STORAGE_EXTERN, STORAGE_STATIC, STORAGE_AUTO, STORAGE_REGISTER};
        
        ///
        /// @class      Declaration
        /// @brief      The Declaration AST node.
        ///
        class Declaration : public ExternalDeclaration
        {
        private:
            ///
            /// @brief          Calls acceptPreRecursive(visitor) on all children nodes.
            /// @param visitor  The visitor to be accepted.
            ///
            void allChildrenAcceptPreRecursive(dcpucc::visitor::Visitor & visitor);
            
            ///
            /// @brief          Calls acceptPostRecursive(visitor) on all children nodes.
            /// @param visitor  The visitor to be accepted.
            ///
            void allChildrenAcceptPostRecursive(dcpucc::visitor::Visitor & visitor);
            
        public:
            DeclarationSpecifiers * declSpecifiers;
            Declarators * declarators;
            Declarator * singleDeclarator;
            
            bool isParamDecl;
            enum StorSpec_t storageSpecifier;

            types::Type* type;
            
        public:
            ///
            /// @brief      The constructor of the Declaration AST node.
            /// @param declSpecifiers TODO: FILLOUT
            /// @param declarators TODO: FILLOUT
            Declaration(DeclarationSpecifiers * declSpecifiers, Declarators * declarators) :
            declSpecifiers(declSpecifiers), declarators(declarators), singleDeclarator(NULL), isParamDecl(false) {}
            
            ///
            /// @brief      The constructor of the Declaration AST node.
            /// @param declSpecifiers TODO: FILLOUT
            /// @param declarator TODO: FILLOUT
            Declaration(DeclarationSpecifiers * declSpecifiers, Declarator * declarator) :
            declSpecifiers(declSpecifiers), declarators(NULL), singleDeclarator(declarator), isParamDecl(true) {}
            
            
            ///
            /// @brief          The accept method of the Visitor pattern.
            /// @sa             http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param visitor  The visitor to be accepted.
            ///
            /// This is a non recursive version of accept, which calls
            /// only visit(this) and then returns.
            void accept(dcpucc::visitor::Visitor & visitor);
            
            ///
            /// @brief          The accept method of the Visitor pattern.
            /// @sa             http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param visitor  The visitor to be accepted.
            ///
            /// This is a post recursive version of accept, meaning that
            /// it first calls visit(this) and then accept(visitor) for
            /// all its children nodes.
            void acceptPostRecursive(dcpucc::visitor::Visitor & visitor);
            
            ///
            /// @brief          The accept method of the Visitor pattern.
            /// @sa             http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param visitor  The visitor to be accepted.
            ///
            /// This is a pre recursive version of accept, meaning that
            /// it first calls accept(visitor) for
            /// all its children nodes and only then visit(this).
            void acceptPreRecursive(dcpucc::visitor::Visitor & visitor);
            
            ///
            /// @brief          Calls accept(visitor) on all children nodes.
            /// @param visitor  The visitor to be accepted.
            ///
            void allChildrenAccept(dcpucc::visitor::Visitor & visitor);
            
            ///
            /// @brief      The destructor of the Declaration AST node.
            ///
            virtual ~Declaration();
        };

    } // namespace dcpucc
} // namespace astnode

#endif

///
/// @}
///