///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///
    
///
/// @file       Node.h
/// @brief      Declaration of the Node AST node.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_AST_NODES_NODE_H
#define __DCPU_CC_AST_NODES_NODE_H

#include <cstdlib>

namespace dtcc
{
    // forward-declare visitor
    namespace visitor
    {
        class Visitor;
    }
    
    
    namespace astnodes
    {
        
        ///
        /// @class      Node
        /// @brief      The Node AST node.
        ///
        class Node
        {
        public:
            
            ///
            /// @brief          The accept method of the Visitor pattern.
            /// @sa             http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param visitor  The visitor to be accepted.
            ///
            /// This is a non recursive version of accept, which calls
            /// only visit(this) and then returns.
            virtual void accept(dtcc::visitor::Visitor & visitor) = 0;
            
            ///
            /// @brief          The accept method of the Visitor pattern.
            /// @sa             http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param visitor  The visitor to be accepted.
            ///
            /// This is a post recursive version of accept, meaning that
            /// it first calls visit(this) and then accept(visitor) for
            /// all its children nodes.
            virtual void acceptPostRecursive(dtcc::visitor::Visitor & visitor) = 0;
            
            ///
            /// @brief          The accept method of the Visitor pattern.
            /// @sa             http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param visitor  The visitor to be accepted.
            ///
            /// This is a pre recursive version of accept, meaning that
            /// it first calls accept(visitor) for
            /// all its children nodes and only then visit(this).
            virtual void acceptPreRecursive(dtcc::visitor::Visitor & visitor) = 0;
            
            ///
            /// @brief          Calls accept(visitor) on all children nodes.
            /// @param visitor  The visitor to be accepted.
            ///
            virtual void allChildrenAccept(dtcc::visitor::Visitor & visitor) = 0;
            
            ///
            /// @brief          Performes a safe deletion of the given pointer.
            /// @param a        The visitor to be accepted.
            ///
            /// This is a member of node, so that all AST nodes can
            /// access this, as they all inherit from Node.
            template<typename T> void safe_delete(T*& p) {
                delete p;
                p = NULL;
            }
            
            
            virtual ~Node() {};
        };
        
    } // namespace dtcc
} // namespace astnode


// include this at the end, so that first all the nodes are in the pp'ed code
// and only then the visitor, this order should be kept at all time
// to not having to mess around with more forward declarations
// only include if not all nodes are included
#ifndef __DCPU_CC_AST_NODES_ALLNODES_H
#include <visitor/Visitor.h>
#endif

#endif

///
/// @}
///
