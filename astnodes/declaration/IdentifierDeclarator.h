///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       IdentifierDeclarator.h
/// @brief      Declaration of the IdentifierDeclarator AST node.
/// @author     Patrick Flick
///

#include <astnodes/Node.h>

#ifndef __DCPU_CC_AST_NODES_IDENTIFIERDECLARATOR_H
#define __DCPU_CC_AST_NODES_IDENTIFIERDECLARATOR_H

// include needed nodes
#include "Declarator.h"
#include <symboltable/TypePosition.h>

#include <string>


namespace dcpucc
{
    namespace astnodes
    {
        /// Defines possible output values for the identifier declarator.
        enum VariableOutput_t {VAROUT_NOTHING, VAROUT_STATIC, VAROUT_GLOBAL, VAROUT_EXTERN};
        
        ///
        /// @class      IdentifierDeclarator
        /// @brief      The IdentifierDeclarator AST node.
        ///
        class IdentifierDeclarator : public Declarator
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
            std::string& name;
            bool isVariableDeclaration;
            VariableOutput_t varoutput;
            symboltable::TypePosition typePos;
            types::Type* variableType;

        public:
            ///
            /// @brief      The constructor of the IdentifierDeclarator AST node.
            ///
            IdentifierDeclarator(std::string& name) : name(name), isVariableDeclaration(false), variableType(NULL)  {}
            
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
            /// @brief      The destructor of the IdentifierDeclarator AST node.
            ///
            virtual ~IdentifierDeclarator();
        };

    } // namespace dcpucc
} // namespace astnode

#endif

///
/// @}
///