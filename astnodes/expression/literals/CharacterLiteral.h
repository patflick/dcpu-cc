///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       CharacterLiteral.h
/// @brief      Declaration of the CharacterLiteral AST node.
/// @author     Patrick Flick
///

#include <astnodes/Node.h>

#ifndef __DCPU_CC_AST_NODES_CHARACTERLITERAL_H
#define __DCPU_CC_AST_NODES_CHARACTERLITERAL_H

// include needed nodes
#include <astnodes/expression/Expression.h>
#include <string>

namespace dtcc
{
    namespace astnodes
    {

        ///
        /// @class      CharacterLiteral
        /// @brief      The CharacterLiteral AST node.
        ///
        class CharacterLiteral : public Expression
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
            std::string& str;

            
        public:
            ///
            /// @brief      The constructor of the CharacterLiteral AST node.
            /// @param str TODO: FILLOUT

            ///
            CharacterLiteral(std::string& str) : str(str) {}
            
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
            /// @brief      The destructor of the CharacterLiteral AST node.
            ///
            virtual ~CharacterLiteral();
        };

    } // namespace dtcc
} // namespace astnode

#endif

///
/// @}
///