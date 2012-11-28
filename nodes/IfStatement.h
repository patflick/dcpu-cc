///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       IfStatement.h
/// @brief      Declaration of the IfStatement AST node.
/// @author     Patrick Flick
///

#include "Node.h"

#ifndef __DCPU_CC_AST_NODES_IFSTATEMENT_H
#define __DCPU_CC_AST_NODES_IFSTATEMENT_H

// include needed nodes
#include "Statement.h"
#include "Expression.h"


namespace dtcc
{
    namespace astnodes
    {

        ///
        /// @class      IfStatement
        /// @brief      The IfStatement AST node.
        ///
        class IfStatement : public Statement
        {
        public:
            Expression * condExpr;
            Statement * ifStmt;
            Statement * elseStmt;

        
        private:
            ///
            /// @brief          Calls accept(visitor) on all children nodes.
            /// @param visitor  The visitor to be accepted.
            ///
            void allChildrenAccept(dtcc::visitor::Visitor & visitor);
            
        public:
            ///
            /// @brief      The constructor of the IfStatement AST node.
            /// @param condExpr TODO: FILLOUT
            /// @param ifStmt TODO: FILLOUT
            /// @param elseStmt TODO: FILLOUT

            ///
            IfStatement(Expression * condExpr, Statement * ifStmt, Statement * elseStmt) : condExpr(condExpr), ifStmt(ifStmt), elseStmt(elseStmt) {}
            
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
            /// @brief      The destructor of the IfStatement AST node.
            ///
            ~IfStatement();
        };

    } // namespace dtcc
} // namespace astnode

#endif

///
/// @}
///