///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       IfStatement.h
/// @brief      Declaration of the IfStatement AST node.
/// @author     Patrick Flick
///

#include <astnodes/Node.h>

#ifndef __DCPU_CC_AST_NODES_IFSTATEMENT_H
#define __DCPU_CC_AST_NODES_IFSTATEMENT_H

// include needed nodes
#include "Statement.h"
#include "LabelStatement.h"
#include <astnodes/expression/Expression.h>


namespace dcpucc
{
    namespace astnodes
    {

        ///
        /// @class      IfStatement
        /// @brief      The IfStatement AST node.
        ///
        class IfStatement : public Statement
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
            Expression * condExpr;
            Statement * ifStmt;
            Statement * elseStmt;

            LabelStatement* elselbl;
            LabelStatement* endlbl;
            
        public:
            ///
            /// @brief      The constructor of the IfStatement AST node.
            /// @param condExpr TODO: FILLOUT
            /// @param ifStmt TODO: FILLOUT
            /// @param elseStmt TODO: FILLOUT

            ///
            IfStatement(Expression * condExpr, Statement * ifStmt, Statement * elseStmt)
                : condExpr(condExpr), ifStmt(ifStmt), elseStmt(elseStmt),
                elselbl(NULL), endlbl(NULL) {}
            
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
            /// @brief      The destructor of the IfStatement AST node.
            ///
            virtual ~IfStatement();
        };

    } // namespace dcpucc
} // namespace astnode

#endif

///
/// @}
///