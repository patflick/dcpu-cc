///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       MethodCall.h
/// @brief      Declaration of the MethodCall AST node.
/// @author     Patrick Flick
///

#include <astnodes/Node.h>

#ifndef __DCPU_CC_AST_NODES_METHODCALL_H
#define __DCPU_CC_AST_NODES_METHODCALL_H

// include needed nodes
#include <astnodes/expression/Expression.h>
#include "Expressions.h"

namespace dcpucc
{
    namespace astnodes
    {

        ///
        /// @class      MethodCall
        /// @brief      The MethodCall AST node.
        ///
        class MethodCall : public Expression
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
            Expression * lhsExpr;
            Expressions * rhsExprs;
            unsigned int varArgsSize;
            types::Type* returnType;
            
        public:
            ///
            /// @brief      The constructor of the MethodCall AST node.
            /// @param lhsExpr TODO: FILLOUT
            /// @param rhsExprs TODO: FILLOUT

            ///
            MethodCall(Expression * lhsExpr, Expressions * rhsExprs) : lhsExpr(lhsExpr), rhsExprs(rhsExprs), varArgsSize(0), returnType(NULL) {}
            
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
            /// @brief      The destructor of the MethodCall AST node.
            ///
            virtual ~MethodCall();
        };

    } // namespace dcpucc
} // namespace astnode

#endif

///
/// @}
///