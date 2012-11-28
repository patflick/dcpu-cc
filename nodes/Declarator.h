///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       Declarator.h
/// @brief      Declaration of the Declarator AST node.
/// @author     Patrick Flick
///

#include "Node.h"

#ifndef __DCPU_CC_AST_NODES_DECLARATOR_H
#define __DCPU_CC_AST_NODES_DECLARATOR_H

// include needed nodes
#include "Node.h"
#include "Expressions.h"
#include "Pointers.h"
#include <cstdlib>

namespace dtcc
{
    namespace astnodes
    {

        ///
        /// @class      Declarator
        /// @brief      The Declarator AST node.
        ///
        class Declarator : public Node
        {
        public:
            Expressions* initializers;
            Pointers* pointers;
        
        private:
            ///
            /// @brief          Calls accept(visitor) on all children nodes.
            /// @param visitor  The visitor to be accepted.
            ///
            void allChildrenAccept(dtcc::visitor::Visitor & visitor);
            
        public:
            ///
            /// @brief      The constructor of the Declarator AST node.
            ///
            Declarator() : initializers(NULL) {}
            
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
            /// @brief      The destructor of the Declarator AST node.
            ///
            ~Declarator();
        };

    } // namespace dtcc
} // namespace astnode

#endif

///
/// @}
///