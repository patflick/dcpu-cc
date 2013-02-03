///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       AddressOfOperator.h
/// @brief      Declaration of the AddressOfOperator AST node.
/// @author     Patrick Flick
///

#include "Node.h"

#ifndef __DCPU_CC_AST_NODES_ADDRESSOFOPERATOR_H
#define __DCPU_CC_AST_NODES_ADDRESSOFOPERATOR_H

// include needed nodes
#include "Expression.h"


namespace dtcc
{
    namespace astnodes
    {

        ///
        /// @class      AddressOfOperator
        /// @brief      The AddressOfOperator AST node.
        ///
        class AddressOfOperator : public Expression
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
            Expression * expr;
            
            bool LtoR;

            
        public:
            ///
            /// @brief      The constructor of the AddressOfOperator AST node.
            /// @param optoken TODO: FILLOUT
            /// @param expr TODO: FILLOUT

            ///
            AddressOfOperator(Expression * expr) : expr(expr), LtoR(false) {}
            
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
            /// @brief      The destructor of the AddressOfOperator AST node.
            ///
            virtual ~AddressOfOperator();
        };

    } // namespace dtcc
} // namespace astnode

#endif

///
/// @}
///