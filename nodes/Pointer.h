///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       Pointer.h
/// @brief      Declaration of the Pointer AST node.
/// @author     Patrick Flick
///

#include "Node.h"

#ifndef __DCPU_CC_AST_NODES_POINTER_H
#define __DCPU_CC_AST_NODES_POINTER_H

// include needed nodes
#include "Node.h"
#include "TypeQualifiers.h"


namespace dtcc
{
    namespace astnodes
    {

        ///
        /// @class      Pointer
        /// @brief      The Pointer AST node.
        ///
        class Pointer : public Node
        {
        public:
            TypeQualifiers * typeQualifiers;

        
        private:
            ///
            /// @brief          Calls accept(visitor) on all children nodes.
            /// @param visitor  The visitor to be accepted.
            ///
            void allChildrenAccept(dtcc::visitor::Visitor & visitor);
            
        public:
            ///
            /// @brief      The constructor of the Pointer AST node.
            /// @param typeQualifiers TODO: FILLOUT

            ///
            Pointer(TypeQualifiers * typeQualifiers) : typeQualifiers(typeQualifiers) {}
            
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
            /// @brief      The destructor of the Pointer AST node.
            ///
            ~Pointer();
        };

    } // namespace dtcc
} // namespace astnode

#endif

///
/// @}
///