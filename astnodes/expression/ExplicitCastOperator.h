///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       ExplicitCastOperator.h
/// @brief      Declaration of the ExplicitCastOperator AST node.
/// @author     Patrick Flick
///

#include <astnodes/Node.h>

#ifndef __DCPU_CC_AST_NODES_EXPLICITCASTOPERATOR_H
#define __DCPU_CC_AST_NODES_EXPLICITCASTOPERATOR_H

// include needed nodes
#include <astnodes/expression/Expression.h>
#include <astnodes/declaration/TypeName.h>


namespace dcpucc
{
    namespace astnodes
    {

        ///
        /// @class      ExplicitCastOperator
        /// @brief      The ExplicitCastOperator AST node.
        ///
        class ExplicitCastOperator : public Expression
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
            TypeName * typeName;
            Expression * expr;

            
        public:
            ///
            /// @brief      The constructor of the ExplicitCastOperator AST node.
            /// @param typeName TODO: FILLOUT
            /// @param expr TODO: FILLOUT

            ///
            ExplicitCastOperator(TypeName * typeName, Expression * expr) : typeName(typeName), expr(expr) {}
            
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
            /// @brief      The destructor of the ExplicitCastOperator AST node.
            ///
            virtual ~ExplicitCastOperator();
        };

    } // namespace dcpucc
} // namespace astnode

#endif

///
/// @}
///