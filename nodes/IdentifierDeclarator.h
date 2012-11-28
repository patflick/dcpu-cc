///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       IdentifierDeclarator.h
/// @brief      Declaration of the IdentifierDeclarator AST node.
/// @author     Patrick Flick
///

#include "Node.h"

#ifndef __DCPU_CC_AST_NODES_IDENTIFIERDECLARATOR_H
#define __DCPU_CC_AST_NODES_IDENTIFIERDECLARATOR_H

// include needed nodes
#include "Declarator.h"
#include <string>

namespace dtcc
{
    namespace astnodes
    {

        ///
        /// @class      IdentifierDeclarator
        /// @brief      The IdentifierDeclarator AST node.
        ///
        class IdentifierDeclarator : public Declarator
        {
        public:
            std::string name;
        
        private:
            ///
            /// @brief          Calls accept(visitor) on all children nodes.
            /// @param visitor  The visitor to be accepted.
            ///
            void allChildrenAccept(dtcc::visitor::Visitor & visitor);
            
        public:
            ///
            /// @brief      The constructor of the IdentifierDeclarator AST node.

            ///
            IdentifierDeclarator(std::string& name) : name(name)  {}
            
            ///
            /// @brief          The accept method of the Visitor pattern.
            /// @sa             http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param visitor  The visitor to be accepted.
            ///
            /// This is a non recursive version of accept, which calls
            /// only visit(this) and then returns.
            void accept(dtcc::visitor::Visitor & visitor);
            
            ///
            /// @brief          The accept method of the Visitor pattern.
            /// @sa             http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param visitor  The visitor to be accepted.
            ///
            /// This is a post recursive version of accept, meaning that
            /// it first calls visit(this) and then accept(visitor) for
            /// all its children nodes.
            void acceptPostRecursive(dtcc::visitor::Visitor & visitor);
            
            ///
            /// @brief          The accept method of the Visitor pattern.
            /// @sa             http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param visitor  The visitor to be accepted.
            ///
            /// This is a pre recursive version of accept, meaning that
            /// it first calls accept(visitor) for
            /// all its children nodes and only then visit(this).
            void acceptPreRecursive(dtcc::visitor::Visitor & visitor);
            
            ///
            /// @brief      The destructor of the IdentifierDeclarator AST node.
            ///
            ~IdentifierDeclarator();
        };

    } // namespace dtcc
} // namespace astnode

#endif

///
/// @}
///