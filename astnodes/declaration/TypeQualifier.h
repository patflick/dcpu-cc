///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       TypeQualifier.h
/// @brief      Declaration of the TypeQualifier AST node.
/// @author     Patrick Flick
///

#include <astnodes/Node.h>

#ifndef __DCPU_CC_AST_NODES_TYPEQUALIFIER_H
#define __DCPU_CC_AST_NODES_TYPEQUALIFIER_H

// include needed nodes
#include <astnodes/Node.h>


namespace dcpucc
{
    namespace astnodes
    {

        ///
        /// @class      TypeQualifier
        /// @brief      The TypeQualifier AST node.
        ///
        class TypeQualifier : public Node
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
            int token;

            
        public:
            ///
            /// @brief      The constructor of the TypeQualifier AST node.
            /// @param token TODO: FILLOUT

            ///
            TypeQualifier(int token) : token(token) {}
            
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
            /// @brief      The destructor of the TypeQualifier AST node.
            ///
            virtual ~TypeQualifier();
        };

    } // namespace dcpucc
} // namespace astnode

#endif

///
/// @}
///