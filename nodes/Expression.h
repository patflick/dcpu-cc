///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       Expression.h
/// @brief      Declaration of the Expression AST node.
/// @author     Patrick Flick
///

#include "Node.h"

#ifndef __DCPU_CC_AST_NODES_EXPRESSION_H
#define __DCPU_CC_AST_NODES_EXPRESSION_H

// include needed nodes
#include "Node.h"
#include <types/Type.h>


namespace dtcc
{
    namespace astnodes
    {

        ///
        /// @class      Expression
        /// @brief      The Expression AST node.
        ///
        class Expression : public Node
        {
            
        public:
            /// Each expression has a type associated with it
            types::Type* exprType;
            
        public:
            ///
            /// @brief      The constructor of the Expression AST node.
            ///
            Expression() : exprType(NULL) {}
            
            ///
            /// @brief          The accept method of the Visitor pattern.
            /// @sa             http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param visitor  The visitor to be accepted.
            ///
            /// This is a non recursive version of accept, which calls
            /// only visit(this) and then returns.
            virtual void accept(dtcc::visitor::Visitor & visitor) = 0;
            
            ///
            /// @brief          The accept method of the Visitor pattern.
            /// @sa             http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param visitor  The visitor to be accepted.
            ///
            /// This is a post recursive version of accept, meaning that
            /// it first calls visit(this) and then accept(visitor) for
            /// all its children nodes.
            virtual void acceptPostRecursive(dtcc::visitor::Visitor & visitor) = 0;
            
            ///
            /// @brief          The accept method of the Visitor pattern.
            /// @sa             http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param visitor  The visitor to be accepted.
            ///
            /// This is a pre recursive version of accept, meaning that
            /// it first calls accept(visitor) for
            /// all its children nodes and only then visit(this).
            virtual void acceptPreRecursive(dtcc::visitor::Visitor & visitor) = 0;
            
            ///
            /// @brief          Calls accept(visitor) on all children nodes.
            /// @param visitor  The visitor to be accepted.
            ///
            virtual void allChildrenAccept(dtcc::visitor::Visitor & visitor) = 0;
            
            ///
            /// @brief      The destructor of the Expression AST node.
            ///
            virtual ~Expression();
        };

    } // namespace dtcc
} // namespace astnode

#endif

///
/// @}
///