///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       %ClassName%.h
/// @brief      Declaration of the %ClassName% AST node.
/// @author     Patrick Flick
///

#include "Node.h"

#ifndef __DCPU_CC_AST_NODES_%CLASSNAME%_H
#define __DCPU_CC_AST_NODES_%CLASSNAME%_H

// include needed nodes
%nodes_include%

namespace dtcc
{
    namespace astnodes
    {

        ///
        /// @class      %ClassName%
        /// @brief      The %ClassName% AST node.
        ///
        class %ClassName% : public %SuperClassName%
        {
        public:
%ClassMembers%
            
        public:
            ///
            /// @brief      The constructor of the %ClassName% AST node.
%DoxygenConstructorParams%
            ///
            %ClassName%(%Params%) %ParamInit% {}
            
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
            /// @brief      The destructor of the %ClassName% AST node.
            ///
            ~%ClassName%();
        };

    } // namespace dtcc
} // namespace astnode

#endif

///
/// @}
///