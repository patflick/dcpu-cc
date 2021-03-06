///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       BinaryOperator.h
/// @brief      Declaration of the BinaryOperator AST node.
/// @author     Patrick Flick
///

#include <astnodes/Node.h>

#ifndef __DCPU_CC_AST_NODES_BINARYOPERATOR_H
#define __DCPU_CC_AST_NODES_BINARYOPERATOR_H

// include needed nodes
#include <astnodes/expression/Expression.h>
#include <types/Type.h>


namespace dcpucc
{
    namespace astnodes
    {

        ///
        /// @class      BinaryOperator
        /// @brief      The BinaryOperator AST node.
        ///
        class BinaryOperator : public Expression
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
            Expression * lhsExrp;
            int optoken;
            Expression * rhsExpr;
            
            // filled out by semantic check:
            bool lhsPtr;
            bool rhsPtr;
            unsigned int pointerSize;
            types::Type* commonType;

            
        public:
            ///
            /// @brief      The constructor of the BinaryOperator AST node.
            /// @param lhsExrp TODO: FILLOUT
            /// @param optoken TODO: FILLOUT
            /// @param rhsExpr TODO: FILLOUT

            ///
            BinaryOperator(Expression * lhsExrp, int optoken, Expression * rhsExpr) :
                lhsExrp(lhsExrp), optoken(optoken), rhsExpr(rhsExpr),
                lhsPtr(false), rhsPtr(false), pointerSize(0), commonType(NULL) {}
            
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
            /// @brief      The destructor of the BinaryOperator AST node.
            ///
            virtual ~BinaryOperator();
        };

    } // namespace dcpucc
} // namespace astnode

#endif

///
/// @}
///