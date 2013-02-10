///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       ExternalDeclaration.h
/// @brief      Declaration of the ExternalDeclaration AST node.
/// @author     Patrick Flick
///

#include <astnodes/Node.h>

#ifndef __DCPU_CC_AST_NODES_EXTERNALDECLARATION_H
#define __DCPU_CC_AST_NODES_EXTERNALDECLARATION_H

// include needed nodes
#include <astnodes/Node.h>


namespace dcpucc
{
    namespace astnodes
    {

        ///
        /// @class      ExternalDeclaration
        /// @brief      The ExternalDeclaration AST node.
        ///
        class ExternalDeclaration : public Node
        {
            
        public:
            
            ///
            /// @brief          The accept method of the Visitor pattern.
            /// @sa             http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param visitor  The visitor to be accepted.
            ///
            /// This is a non recursive version of accept, which calls
            /// only visit(this) and then returns.
            virtual void accept(dcpucc::visitor::Visitor & visitor) = 0;
            
            ///
            /// @brief          The accept method of the Visitor pattern.
            /// @sa             http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param visitor  The visitor to be accepted.
            ///
            /// This is a post recursive version of accept, meaning that
            /// it first calls visit(this) and then accept(visitor) for
            /// all its children nodes.
            virtual void acceptPostRecursive(dcpucc::visitor::Visitor & visitor) = 0;
            
            ///
            /// @brief          The accept method of the Visitor pattern.
            /// @sa             http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param visitor  The visitor to be accepted.
            ///
            /// This is a pre recursive version of accept, meaning that
            /// it first calls accept(visitor) for
            /// all its children nodes and only then visit(this).
            virtual void acceptPreRecursive(dcpucc::visitor::Visitor & visitor) = 0;
            
            ///
            /// @brief          Calls accept(visitor) on all children nodes.
            /// @param visitor  The visitor to be accepted.
            ///
            virtual void allChildrenAccept(dcpucc::visitor::Visitor & visitor) = 0;
            
            ///
            /// @brief      The destructor of the CaseStatement AST node.
            ///
            virtual ~ExternalDeclaration() {};
        };

    } // namespace dcpucc
} // namespace astnode

#endif

///
/// @}
///