///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       StructureResolutionOperator.h
/// @brief      Declaration of the StructureResolutionOperator AST node.
/// @author     Patrick Flick
///

#include <astnodes/Node.h>

#ifndef __DCPU_CC_AST_NODES_STRUCTURERESOLUTIONOPERATOR_H
#define __DCPU_CC_AST_NODES_STRUCTURERESOLUTIONOPERATOR_H

// include needed nodes
#include <astnodes/expression/Expression.h>


namespace dcpucc
{
    namespace astnodes
    {

        ///
        /// @class      StructureResolutionOperator
        /// @brief      The StructureResolutionOperator AST node.
        ///
        class StructureResolutionOperator : public Expression
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
            Expression * lhsExpr;
            std::string fieldName;
            bool isPointered;
            
            unsigned int offset;
            unsigned int fieldSize;

            
        public:
            ///
            /// @brief      The constructor of the StructureResolutionOperator AST node.
            /// @param lhsExpr TODO: FILLOUT
            /// @param fieldName TODO: FILLOUT
            /// @param isPointered TODO: FILLOUT

            ///
            StructureResolutionOperator(Expression * lhsExpr, std::string fieldName, bool isPointered) : lhsExpr(lhsExpr), fieldName(fieldName), isPointered(isPointered), offset(0) {}
            
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
            /// @brief      The destructor of the StructureResolutionOperator AST node.
            ///
            virtual ~StructureResolutionOperator();
        };

    } // namespace dcpucc
} // namespace astnode

#endif

///
/// @}
///