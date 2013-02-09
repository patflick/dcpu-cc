///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Visitor
/// @{
///

///
/// @file       ConstExprEvalVisitor.cpp
/// @brief      Definitions of the ConstExprEvalVisitor class.
/// @author     Patrick Flick
///

// import parser tokens
#define YYSTYPE int
#include <parser.hpp>

#include "ConstExprEvalVisitor.h"

#include <types/IsTypeHelper.h>
#include <valuetypes/ConstHelper.h>
#include <errors/InternalCompilerException.h>

using namespace dtcc;
using namespace dtcc::visitor;


/*######################################*/
/*      3.3 Expressions                 */
/*######################################*/


/******************************/
/*  3.3.1 Primary expressions */
/******************************/

/* identifier */

void ConstExprEvalVisitor::visit(astnodes::Identifier * identifier)
{
    // TODO TODO TODO TODO
    // TODO TODO TODO TODO
    // TODO TODO TODO TODO
    // TODO must be an enum type or a function declarator
    // in case of enum type, there must be the constant value insude the
    // type variable somehow
    // in case of a function declarator it must be an actual function
    // not a function pointer
}


/* constants */

void ConstExprEvalVisitor::visit(astnodes::CharacterLiteral * characterLiteral)
{
    valuetypes::ConstHelper::setIntegralConst(characterLiteral->valType, (int) characterLiteral->str[0]);
}


void ConstExprEvalVisitor::visit(astnodes::SignedIntLiteral * signedIntLiteral)
{
    valuetypes::ConstHelper::setIntegralConst(signedIntLiteral->valType, signedIntLiteral->literalValue);
}


void ConstExprEvalVisitor::visit(astnodes::UnsignedIntLiteral * unsignedIntLiteral)
{
    valuetypes::ConstHelper::setIntegralConst(unsignedIntLiteral->valType, unsignedIntLiteral->literalValue);
}


void ConstExprEvalVisitor::visit(astnodes::SignedLongLiteral * signedLongLiteral)
{
    valuetypes::ConstHelper::setIntegralConst(signedLongLiteral->valType, signedLongLiteral->literalValue);
}


void ConstExprEvalVisitor::visit(astnodes::UnsignedLongLiteral * unsignedLongLiteral)
{
    valuetypes::ConstHelper::setIntegralConst(unsignedLongLiteral->valType, unsignedLongLiteral->literalValue);
}


void ConstExprEvalVisitor::visit(astnodes::FloatLiteral * floatLiteral)
{
    valuetypes::ConstHelper::setFloatConst(floatLiteral->valType, floatLiteral->literalValue);
}


void ConstExprEvalVisitor::visit(astnodes::DoubleLiteral * doubleLiteral)
{
    valuetypes::ConstHelper::setFloatConst(doubleLiteral->valType, doubleLiteral->literalValue);
}


void ConstExprEvalVisitor::visit(astnodes::LongDoubleLiteral * longDoubleLiteral)
{
    valuetypes::ConstHelper::setFloatConst(longDoubleLiteral->valType, longDoubleLiteral->literalValue);
}


/* string literal */

// not a constant


/******************************/
/*  3.3.2 Postfix expressions */
/******************************/

/* 3.3.2.1 array subscripting */

// not a constant


/* 3.3.2.2 Function calls */

// not a constant

/* 3.3.2.3 Structure and union members */

// not a constant


/* 3.3.2.4 Postfix increment and decrement operators */

// not a constant



/******************************/
/*  3.3.3 Unary operators     */
/******************************/

/* 3.3.3.1 Prefix increment and decrement operators */

// not a constant

/* 3.3.3.2 Address and indirection operators */
// TODO add the Address of Operator!


/* 3.3.3.3 Unary arithmetic operators */

void ConstExprEvalVisitor::visit(astnodes::UnaryOperator * unaryOperator)
{
    // analyse inner expression first:
    unaryOperator->allChildrenAccept(*this);
    
    // check whether this is a float operation
    bool floatOp = types::IsTypeHelper::isFloatType(unaryOperator->valType->type);
    bool subExprFloatConst = types::IsTypeHelper::isFloatType(unaryOperator->expr->valType->type);
    double oldFloatConst = valuetypes::ConstHelper::getFloatConst(unaryOperator->expr->valType);
    long oldIntegralConst = valuetypes::ConstHelper::getIntegralConst(unaryOperator->expr->valType);
    double newFloatConst = 0.0;
    long newIntegralConst = 0l;
    
    switch(unaryOperator->optoken)
    {
        case ADD_OP:
            newFloatConst = oldFloatConst;
            newIntegralConst = oldIntegralConst;
            break;
        case SUB_OP:
            newFloatConst = - oldFloatConst;
            newIntegralConst = - oldIntegralConst;
            break;
            
        case BIN_INV_OP:
            if (floatOp)
                throw new errors::InternalCompilerException("invalid unary operator ~ on float type");
            // TODO maybe i need to cut out the higher bits here after the OP
            newIntegralConst = ~ oldIntegralConst;
            break;
            
        case NOT_OP:
            if (subExprFloatConst)
                newIntegralConst = ! oldFloatConst;
            else
                newIntegralConst = ! oldIntegralConst;
            break;
        default:
            throw new errors::InternalCompilerException("Unknown unary operator encountered");
    }
    
    if (floatOp)
        valuetypes::ConstHelper::setFloatConst(unaryOperator->valType, newFloatConst);
    else
        valuetypes::ConstHelper::setIntegralConst(unaryOperator->valType, newIntegralConst);
}


/* 3.3.3.4 The sizeof operator */

void ConstExprEvalVisitor::visit(astnodes::SizeOfOperator * sizeOfOperator)
{
    // visit the constant literal of the size of operator
    sizeOfOperator->constExpr->accept(*this);
    
    // get the constant value ...
    long size = valuetypes::ConstHelper::getIntegralConst(sizeOfOperator->constExpr->valType);
    
    // ... and pass it on
    valuetypes::ConstHelper::setIntegralConst(sizeOfOperator->valType, size);
}


/******************************/
/*  3.3.4 Cast operators      */
/******************************/

void ConstExprEvalVisitor::visit(astnodes::ExplicitCastOperator * explicitCastOperator)
{
    // TODO TODO TODO TODO
    // TODO TODO TODO TODO
    // TODO TODO TODO TODO
    explicitCastOperator->allChildrenAccept(*this);
}



/******************************/
/*     binary operators       */
/******************************/

void ConstExprEvalVisitor::visit(astnodes::BinaryOperator * binaryOperator)
{
    // analyse both sub-expressions
    binaryOperator->allChildrenAccept(*this);
    
    valuetypes::ValueType* lhsVtype = binaryOperator->lhsExrp->valType;
    valuetypes::ValueType* rhsVtype = binaryOperator->rhsExpr->valType;
    types::Type* lhsType = lhsVtype->type;
    types::Type* rhsType = rhsVtype->type;
    
    
    bool floatOp = types::IsTypeHelper::isFloatType(binaryOperator->commonType);
    double lhsFloatConst = valuetypes::ConstHelper::getFloatConst(binaryOperator->lhsExrp->valType);
    long lhsIntegralConst = valuetypes::ConstHelper::getIntegralConst(binaryOperator->lhsExrp->valType);
    double rhsFloatConst = valuetypes::ConstHelper::getFloatConst(binaryOperator->rhsExpr->valType);
    long rhsIntegralConst = valuetypes::ConstHelper::getIntegralConst(binaryOperator->rhsExpr->valType);
    double newFloatConst = 0.0;
    long newIntegralConst = 0l;
    
    switch(binaryOperator->optoken)
    {
        
        /* 3.3.5 Multiplicative operators */
        
        case MUL_OP:
            newFloatConst = lhsFloatConst * rhsFloatConst;
            newIntegralConst = lhsIntegralConst * rhsIntegralConst;
            break;
        case DIV_OP:
            newFloatConst = lhsFloatConst / rhsFloatConst;
            newIntegralConst = lhsIntegralConst / rhsIntegralConst;
            break;
        case MOD_OP:
            newIntegralConst = lhsIntegralConst % rhsIntegralConst;
            break;
        
            
        /* 3.3.6 Additive operators */
        
        case ADD_OP:
            if (binaryOperator->lhsPtr)
            {
                newIntegralConst = lhsIntegralConst + binaryOperator->pointerSize * rhsIntegralConst;
            }
            else if (binaryOperator->rhsPtr)
            {
                newIntegralConst = binaryOperator->pointerSize * lhsIntegralConst + rhsIntegralConst;
            }
            else
            {
                newFloatConst = lhsFloatConst + rhsFloatConst;
                newIntegralConst = lhsIntegralConst + rhsIntegralConst;
            }
            break;
            
        case SUB_OP:
            if (binaryOperator->lhsPtr && binaryOperator->rhsPtr)
            {
                newIntegralConst = (lhsIntegralConst + rhsIntegralConst) / binaryOperator->pointerSize;
            }
            else if (binaryOperator->lhsPtr)
            {
                newIntegralConst = lhsIntegralConst - binaryOperator->pointerSize * rhsIntegralConst;
            }
            else
            {
                newFloatConst = lhsFloatConst - rhsFloatConst;
                newIntegralConst = lhsIntegralConst - rhsIntegralConst;
            }
            break;
            
            
        /* 3.3.7 Bitwise shift operators */
            
        case LEFT_OP:
            newIntegralConst = lhsIntegralConst << (int) rhsIntegralConst;
            break;
        case RIGHT_OP:
            newIntegralConst = lhsIntegralConst >> (int) rhsIntegralConst;
            break;
            
        /* 3.3.8 Relational operators */
        case LT_OP:
            if (floatOp)
                newIntegralConst =  (lhsFloatConst < rhsFloatConst);
            else
                newIntegralConst =  (lhsIntegralConst < rhsIntegralConst);
            break;
        case GT_OP:
            if (floatOp)
                newIntegralConst =  (lhsFloatConst > rhsFloatConst);
            else
                newIntegralConst =  (lhsIntegralConst > rhsIntegralConst);
            break;
        case LE_OP:
            if (floatOp)
                newIntegralConst =  (lhsFloatConst <= rhsFloatConst);
            else
                newIntegralConst =  (lhsIntegralConst <= rhsIntegralConst);
            break;
        case GE_OP:
            if (floatOp)
                newIntegralConst =  (lhsFloatConst >= rhsFloatConst);
            else
                newIntegralConst =  (lhsIntegralConst >= rhsIntegralConst);
            break;
            
            
        /* 3.3.9 Equality operators */
            
        case EQ_OP:
            if (floatOp)
                newIntegralConst =  (lhsFloatConst == rhsFloatConst);
            else
                newIntegralConst =  (lhsIntegralConst == rhsIntegralConst);
            break;
        case NE_OP:
            if (floatOp)
                newIntegralConst =  (lhsFloatConst != rhsFloatConst);
            else
                newIntegralConst =  (lhsIntegralConst != rhsIntegralConst);
            break;
            
            
        /* 3.3.10 Bitwise AND operator */
        /* 3.3.11 Bitwise exclusive OR operator */
        /* 3.3.12 Bitwise inclusive OR operator */
        
        case BIN_AND_OP:
            newIntegralConst = lhsIntegralConst & rhsIntegralConst;
            break;
        case BIN_XOR_OP:
            newIntegralConst = lhsIntegralConst ^ rhsIntegralConst;
            break;
        case BIN_OR_OP:
            newIntegralConst = lhsIntegralConst | rhsIntegralConst;
            break;
            
            /* 3.3.13 Logical AND operator */
            /* 3.3.14 Logical OR operator */
            
        case AND_OP:
            newIntegralConst = lhsIntegralConst && rhsIntegralConst;
            break;
        case OR_OP:
            newIntegralConst = lhsIntegralConst || rhsIntegralConst;
            break;
            
        default:
            throw new errors::InternalCompilerException("unknown binary operator encountered");
    }
    
    // set result
    bool resultFloat = types::IsTypeHelper::isFloatType(binaryOperator->valType->type);
    if (resultFloat)
        valuetypes::ConstHelper::setFloatConst(binaryOperator->valType, newFloatConst);
    else
        valuetypes::ConstHelper::setIntegralConst(binaryOperator->valType, newIntegralConst);
}

/********************************/
/* 3.3.15 Conditional operator  */
/********************************/
 
void ConstExprEvalVisitor::visit(astnodes::ConditionalOperator * conditionalOperator)
{
    // TODO TODO TODO TODO
    // TODO TODO TODO TODO
    // TODO TODO TODO TODO
    conditionalOperator->allChildrenAccept(*this);
}



/********************************/
/*  3.3.17 Comma operator       */
/********************************/

void ConstExprEvalVisitor::visit(astnodes::ChainExpressions * chainExpressions)
{
    // analyse only last child
    chainExpressions->exprs->back()->accept(*this);
    
    bool floatOp = types::IsTypeHelper::isFloatType(chainExpressions->exprs->back()->valType->type);
    
    if (floatOp)
        valuetypes::ConstHelper::setFloatConst(chainExpressions->valType, valuetypes::ConstHelper::getFloatConst(chainExpressions->exprs->back()->valType));
    else
        valuetypes::ConstHelper::setIntegralConst(chainExpressions->valType, valuetypes::ConstHelper::getIntegralConst(chainExpressions->exprs->back()->valType));
}


void ConstExprEvalVisitor::visit(astnodes::TypeConversionOperator * typeConv)
{
    
    // analyse children
    typeConv->expr->accept(*this);
    
    bool floatOp = types::IsTypeHelper::isFloatType(typeConv->toType);
    
    if (floatOp)
        valuetypes::ConstHelper::setFloatConst(typeConv->valType, valuetypes::ConstHelper::getFloatConst(typeConv->expr->valType));
    else
        valuetypes::ConstHelper::setIntegralConst(typeConv->valType, valuetypes::ConstHelper::getIntegralConst(typeConv->expr->valType));
}




///
/// @}
///
