///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       StructUnionSpecifier.h
/// @brief      Declaration of the StructUnionSpecifier AST node.
/// @author     Patrick Flick
///

#include "Node.h"

#ifndef __DCPU_CC_AST_NODES_STRUCTUNIONSPECIFIER_H
#define __DCPU_CC_AST_NODES_STRUCTUNIONSPECIFIER_H

// include needed nodes
#include "TypeSpecifier.h"
#include "Declarations.h"
#include <string>

namespace dtcc
{
    namespace astnodes
    {

        ///
        /// @class      StructUnionSpecifier
        /// @brief      The StructUnionSpecifier AST node.
        ///
        class StructUnionSpecifier : public TypeSpecifier
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
            int token;
            Declarations * declarations;
            std::string& name;
            bool hasName;

            
        public:
            ///
            /// @brief      The constructor of the StructUnionSpecifier AST node.
            /// @param token TODO: FILLOUT
            /// @param declarations TODO: FILLOUT
            /// @param name TODO: FILLOUT
            ///
            StructUnionSpecifier(int token, Declarations * declarations, std::string& name) : token(token), declarations(declarations), name(name), hasName(true) {}
            
            ///
            /// @brief      The constructor of the StructUnionSpecifier AST node.
            /// @param token TODO: FILLOUT
            /// @param declarations TODO: FILLOUT
            /// @param name TODO: FILLOUT
            ///
            StructUnionSpecifier(int token, Declarations * declarations) : token(token), declarations(declarations), name(*(new std::string(""))), hasName(false) {}
            
            
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
            /// @brief      The destructor of the StructUnionSpecifier AST node.
            ///
            ~StructUnionSpecifier();
        };

    } // namespace dtcc
} // namespace astnode

#endif

///
/// @}
///