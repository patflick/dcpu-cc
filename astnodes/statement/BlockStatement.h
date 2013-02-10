///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       BlockStatement.h
/// @brief      Declaration of the BlockStatement AST node.
/// @author     Patrick Flick
///

#include <astnodes/Node.h>

#ifndef __DCPU_CC_AST_NODES_BLOCKSTATEMENT_H
#define __DCPU_CC_AST_NODES_BLOCKSTATEMENT_H

// include needed nodes
#include "Statement.h"
#include <astnodes/declaration/Declaration.h>
#include "Statements.h"

// each block has it's own scope
#include <symboltable/SymbolTableScope.h>

namespace dcpucc
{
    namespace astnodes
    {

        ///
        /// @class      BlockStatement
        /// @brief      The BlockStatement AST node.
        ///
        class BlockStatement : public Statement
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
            Declarations * declarations;
            Statements * statements;

            symboltable::SymbolTableScope* scope;
            
        public:
            ///
            /// @brief      The constructor of the BlockStatement AST node.
            /// @param declarations TODO: FILLOUT
            /// @param statements TODO: FILLOUT

            ///
            BlockStatement(Declarations * declarations, Statements * statements) : declarations(declarations), statements(statements) , scope(NULL) {}
            
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
            /// @brief      The destructor of the BlockStatement AST node.
            ///
            virtual ~BlockStatement();
        };

    } // namespace dcpucc
} // namespace astnode

#endif

///
/// @}
///