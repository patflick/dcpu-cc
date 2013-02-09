///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       WhileStatement.h
/// @brief      Declaration of the WhileStatement AST node.
/// @author     Patrick Flick
///

#include <astnodes/Node.h>

#ifndef __DCPU_CC_AST_NODES_WHILESTATEMENT_H
#define __DCPU_CC_AST_NODES_WHILESTATEMENT_H

// include needed nodes
#include "Statement.h"
#include <astnodes/expression/Expression.h>
#include "LabelStatement.h"


namespace dtcc
{
    namespace astnodes
    {

        ///
        /// @class      WhileStatement
        /// @brief      The WhileStatement AST node.
        ///
        class WhileStatement : public Statement
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
            Statement * statement;

            LabelStatement* startLbl;
            LabelStatement* endLbl;
            
        public:
            ///
            /// @brief      The constructor of the WhileStatement AST node.
            /// @param condExpr TODO: FILLOUT
            /// @param statement TODO: FILLOUT

            ///
            WhileStatement(Expression * condExpr, Statement * statement) : condExpr(condExpr), statement(statement) {}
            
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
            /// @brief      The destructor of the WhileStatement AST node.
            ///
            virtual ~WhileStatement();
        };

    } // namespace dtcc
} // namespace astnode

#endif

///
/// @}
///