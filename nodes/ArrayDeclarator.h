///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       ArrayDeclarator.h
/// @brief      Declaration of the ArrayDeclarator AST node.
/// @author     Patrick Flick
///

#include "Node.h"

#ifndef __DCPU_CC_AST_NODES_ARRAYDECLARATOR_H
#define __DCPU_CC_AST_NODES_ARRAYDECLARATOR_H

// include needed nodes
#include "Declarator.h"
#include "Expression.h"


namespace dtcc
{
    namespace astnodes
    {

        ///
        /// @class      ArrayDeclarator
        /// @brief      The ArrayDeclarator AST node.
        ///
        class ArrayDeclarator : public Declarator
        {
        public:
            Declarator * baseDeclarator;
            Expression * constExpr;

            
        public:
            ///
            /// @brief      The constructor of the ArrayDeclarator AST node.
            /// @param baseDeclarator TODO: FILLOUT
            /// @param constExpr TODO: FILLOUT

            ///
            ArrayDeclarator(Declarator * baseDeclarator, Expression * constExpr) : baseDeclarator(baseDeclarator), constExpr(constExpr) {}
            
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
            /// @brief          Calls accept(visitor) on all children nodes.
            /// @param visitor  The visitor to be accepted.
            ///
            void allChildrenAccept(dtcc::visitor::Visitor & visitor);
            
            ///
            /// @brief      The destructor of the ArrayDeclarator AST node.
            ///
            ~ArrayDeclarator();
        };

    } // namespace dtcc
} // namespace astnode

#endif

///
/// @}
///