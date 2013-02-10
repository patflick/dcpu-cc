///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       Enumerator.h
/// @brief      Declaration of the Enumerator AST node.
/// @author     Patrick Flick
///

#include <astnodes/Node.h>
#ifndef __DCPU_CC_AST_NODES_ENUMERATOR_H
#define __DCPU_CC_AST_NODES_ENUMERATOR_H

// include needed nodes
#include <astnodes/Node.h>
#include <astnodes/expression/Expression.h>
#include <string>

namespace dcpucc
{
    namespace astnodes
    {

        ///
        /// @class      Enumerator
        /// @brief      The Enumerator AST node.
        ///
        class Enumerator : public Node
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
            std::string& name;
            Expression * expr;

            
        public:
            ///
            /// @brief      The constructor of the Enumerator AST node.
            /// @param name TODO: FILLOUT
            /// @param expr TODO: FILLOUT

            ///
            Enumerator(std::string& name, Expression * expr) : name(name), expr(expr) {}
            
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
            /// @brief      The destructor of the Enumerator AST node.
            ///
            virtual ~Enumerator();
        };

    } // namespace dcpucc
} // namespace astnode

#endif

///
/// @}
///