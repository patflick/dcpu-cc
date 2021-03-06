///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       SwitchStatement.h
/// @brief      Declaration of the SwitchStatement AST node.
/// @author     Patrick Flick
///

#include <astnodes/Node.h>

#ifndef __DCPU_CC_AST_NODES_SWITCHSTATEMENT_H
#define __DCPU_CC_AST_NODES_SWITCHSTATEMENT_H

// include needed nodes
#include "Statement.h"
#include <astnodes/expression/Expression.h>
#include "CaseStatement.h"
#include <map>


namespace dcpucc
{
    namespace astnodes
    {

        ///
        /// @class      SwitchStatement
        /// @brief      The SwitchStatement AST node.
        ///
        class SwitchStatement : public Statement
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
            Expression * expr;
            Statement * statement;
            types::Type* promotedType;
            
            LabelStatement* defaultLbl;
            LabelStatement* endLbl;
            
            /// the map that holds for each constant the case statement
            /// this is filled during semantic analysis
            std::map<long, CaseStatement*> cases;

            
        public:
            ///
            /// @brief      The constructor of the SwitchStatement AST node.
            /// @param expr TODO: FILLOUT
            /// @param statement TODO: FILLOUT

            ///
            SwitchStatement(Expression * expr, Statement * statement) : expr(expr), statement(statement), promotedType(NULL), defaultLbl(NULL), endLbl(NULL), cases(std::map<long, CaseStatement*>()) {}
            
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
            /// @brief      The destructor of the SwitchStatement AST node.
            ///
            virtual ~SwitchStatement();
        };

    } // namespace dcpucc
} // namespace astnode

#endif

///
/// @}
///