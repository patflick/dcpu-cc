///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       Declarator.h
/// @brief      Declaration of the Declarator AST node.
/// @author     Patrick Flick
///

#include <astnodes/Node.h>

#ifndef __DCPU_CC_AST_NODES_DECLARATOR_H
#define __DCPU_CC_AST_NODES_DECLARATOR_H

// include needed nodes
#include <astnodes/Node.h>
#include <astnodes/expression/Expressions.h>
#include "Pointers.h"
#include <cstdlib>

namespace dcpucc
{
    namespace astnodes
    {

        ///
        /// @class      Declarator
        /// @brief      The Declarator AST node.
        ///
        class Declarator : public Node
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
            Expressions* initializers;
            Pointers* pointers;

            
        public:
            ///
            /// @brief      The constructor of the Declarator AST node.
            ///
            Declarator() : initializers(NULL), pointers(NULL) {}
            
            ///
            /// @brief          Sets initializer expressions to this declarator.
            /// @param inits    The initialization expressions.
            void setInitializer(Expressions* inits);
            
            ///
            /// @brief              Sets pointers of this declarator.
            /// @param pointers    The pointers to be set.
            void setPointers(Pointers* pointers);
            
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
            /// @brief      The destructor of the Declarator AST node.
            ///
            virtual ~Declarator();
        };

    } // namespace dcpucc
} // namespace astnode

#endif

///
/// @}
///