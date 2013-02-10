///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Visitor
/// @{
///

///
/// @file       ConstExprEvalVisitor.h
/// @brief      Declaration of the ConstExprEvalVisitor class.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_VISITOR_CONSTEXPREVAL_VISITOR_H
#define __DCPU_CC_VISITOR_CONSTEXPREVAL_VISITOR_H

// include all AST nodes
#include <astnodes/allnodes.h>
#include "EmptyVisitor.h"
#include <string>
#include <vector>

namespace dcpucc
{
    namespace visitor
    {
        
        ///
        /// @class      ConstExprEvalVisitor
        /// @brief      A AST visitor which evalutes constant expressions.
        ///
        class ConstExprEvalVisitor : public EmptyVisitor
        {   
        public:
            
            ///
            /// @brief Constructor for the ConstExprEvalVisitor visitor.
            ConstExprEvalVisitor()  {}
            
            
            /*######################################*/
            /*      3.3 Expressions                 */
            /*######################################*/
            
            
            /******************************/
            /*  3.3.1 Primary expressions */
            /******************************/
            
            /* identifier */
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param identifier    The node to visit this visitor
            virtual void visit(astnodes::Identifier * identifier);
            
            
            /* constants */
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param characterLiteral    The node to visit this visitor
            virtual void visit(astnodes::CharacterLiteral * characterLiteral);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param signedIntLiteral    The node to visit this visitor
            virtual void visit(astnodes::SignedIntLiteral * signedIntLiteral);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param unsignedIntLiteral    The node to visit this visitor
            virtual void visit(astnodes::UnsignedIntLiteral * unsignedIntLiteral);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param signedLongLiteral    The node to visit this visitor
            virtual void visit(astnodes::SignedLongLiteral * signedLongLiteral);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param unsignedLongLiteral    The node to visit this visitor
            virtual void visit(astnodes::UnsignedLongLiteral * unsignedLongLiteral);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param floatLiteral    The node to visit this visitor
            virtual void visit(astnodes::FloatLiteral * floatLiteral);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param doubleLiteral    The node to visit this visitor
            virtual void visit(astnodes::DoubleLiteral * doubleLiteral);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param longDoubleLiteral    The node to visit this visitor
            virtual void visit(astnodes::LongDoubleLiteral * longDoubleLiteral);
            
            
            /* string literal */
            
            // not constant
            
            
            /******************************/
            /*  3.3.2 Postfix expressions */
            /******************************/
            
            /* 3.3.2.1 array subscripting */
            
            // not constant
            
            
            /* 3.3.2.2 Function calls */
            
            // not constant
            
            
            /* 3.3.2.3 Structure and union members */
            
            // not constant
            
            
            /* 3.3.2.4 Postfix increment and decrement operators */
            
            // not constant
            
            
            /******************************/
            /*  3.3.3 Unary operators     */
            /******************************/
            
            /* 3.3.3.1 Prefix increment and decrement operators */
            
            // not constant
            
            
            /* 3.3.3.2 Address and indirection operators */
            // TODO add the Address of Operator!
            
            
            /* 3.3.3.3 Unary arithmetic operators */
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param unaryOperator    The node to visit this visitor
            virtual void visit(astnodes::UnaryOperator * unaryOperator);
            
            
            /* 3.3.3.4 The sizeof operator */
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param sizeOfOperator    The node to visit this visitor
            virtual void visit(astnodes::SizeOfOperator * sizeOfOperator);
            
            
            /******************************/
            /*  3.3.4 Cast operators      */
            /******************************/
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param explicitCastOperator    The node to visit this visitor
            virtual void visit(astnodes::ExplicitCastOperator * explicitCastOperator);
            
            
            /******************************/
            /*     binary operators       */
            /******************************/
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param binaryOperator    The node to visit this visitor
            virtual void visit(astnodes::BinaryOperator * binaryOperator);
            
            
            /********************************/
            /* 3.3.15 Conditional operator  */
            /********************************/
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param conditionalOperator    The node to visit this visitor
            virtual void visit(astnodes::ConditionalOperator * conditionalOperator);
            
            
            /********************************/
            /* 3.3.16 Assignment operators  */
            /********************************/
            
            // not constant

            
            /********************************/
            /*  3.3.17 Comma operator       */
            /********************************/

            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param chainExpressions    The node to visit this visitor
            virtual void visit(astnodes::ChainExpressions * chainExpressions);
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param typeConv    The node to visit this visitor
            virtual void visit(astnodes::TypeConversionOperator * typeConv);

        };
        
    } // namespace dcpucc
} // namespace astnode

#endif

///
/// @}
///
