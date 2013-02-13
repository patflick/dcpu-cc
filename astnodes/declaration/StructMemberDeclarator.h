///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       StructMemberDeclarator.h
/// @brief      Declaration of the StructMemberDeclarator AST node.
/// @author     Patrick Flick
///

#include <astnodes/Node.h>

#ifndef __DCPU_CC_AST_NODES_STRUCTMEMBERDECLARATOR_H
#define __DCPU_CC_AST_NODES_STRUCTMEMBERDECLARATOR_H

// include needed nodes
#include "Declarator.h"
#include <astnodes/expression/Expression.h>


namespace dcpucc
{
    namespace astnodes
    {

        ///
        /// @class      StructMemberDeclarator
        /// @brief      The StructMemberDeclarator AST node.
        ///
        class StructMemberDeclarator : public Declarator
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
            Declarator * baseDeclarator;
            Expression * constExpr;
            bool isBitField;
            unsigned int bitFieldSize;

            
        public:
            ///
            /// @brief      The constructor of the StructMemberDeclarator AST node.
            /// @param baseDeclarator TODO: FILLOUT
            /// @param constExpr TODO: FILLOUT
            ///
            StructMemberDeclarator(Declarator * baseDeclarator, Expression * constExpr)
                : baseDeclarator(baseDeclarator), constExpr(constExpr), isBitField(false), bitFieldSize(0) {}
            
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
            /// @brief      The destructor of the StructMemberDeclarator AST node.
            ///
            virtual ~StructMemberDeclarator();
        };

    } // namespace dcpucc
} // namespace astnode

#endif

///
/// @}
///