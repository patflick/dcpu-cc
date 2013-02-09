///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       ConditionalOperator.h
/// @brief      Declaration of the ConditionalOperator AST node.
/// @author     Patrick Flick
///

#include <astnodes/Node.h>

#ifndef __DCPU_CC_AST_NODES_CONDITIONALOPERATOR_H
#define __DCPU_CC_AST_NODES_CONDITIONALOPERATOR_H

// include needed nodes
#include <astnodes/expression/Expression.h>


namespace dtcc
{
    namespace astnodes
    {

        ///
        /// @class      ConditionalOperator
        /// @brief      The ConditionalOperator AST node.
        ///
        class ConditionalOperator : public Expression
        {
        private:
            ///
            /// @brief          Calls acceptPreRecursive(visitor) on all children nodes.
            /// @param visitor  The visitor to be accepted.
            ///
            void allChildrenAcceptPreRecursive(dtcc::visitor::Visitor & visitor);
            
            ///
            /// @brief          Calls acceptPostRecursive(visitor) on all children nodes.
            /// @param visitor  The visitor to be accepted.
            ///
            void allChildrenAcceptPostRecursive(dtcc::visitor::Visitor & visitor);
            
        public:
            Expression * condExpr;
            Expression * ifExpr;
            Expression * elseExpr;

            
        public:
            ///
            /// @brief      The constructor of the ConditionalOperator AST node.
            /// @param condExpr TODO: FILLOUT
            /// @param ifExpr TODO: FILLOUT
            /// @param elseExpr TODO: FILLOUT

            ///
            ConditionalOperator(Expression * condExpr, Expression * ifExpr, Expression * elseExpr) : condExpr(condExpr), ifExpr(ifExpr), elseExpr(elseExpr) {}
            
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
            /// @brief      The destructor of the ConditionalOperator AST node.
            ///
            virtual ~ConditionalOperator();
        };

    } // namespace dtcc
} // namespace astnode

#endif

///
/// @}
///