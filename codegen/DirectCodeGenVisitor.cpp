#include "DirectCodeGenVisitor.h"
#include <iostream>
#include <string>
#include <deque>
#include <utility>
#include <algorithm>

#include <errors/derr.defs.h>
#include <errors/InternalCompilerException.h>

#include <types/alltypes.h>
#include <types/IsTypeHelper.h>

#include <visitor/ConstExprEvalVisitor.h>

#include <valuetypes/ValueType.h>
#include <valuetypes/FunctionDesignator.h>
#include <valuetypes/LValue.h>
#include <valuetypes/RValue.h>
#include <valuetypes/CValue.h>
#include <valuetypes/IsValueTypeHelper.h>
#include <valuetypes/PromotionHelper.h>
#include <valuetypes/ConstHelper.h>

// only include the int tokens
#define YYSTYPE int
#include <parser.hpp>

using namespace dtcc;
using namespace dtcc::visitor;


/* constructor */

DirectCodeGenVisitor::DirectCodeGenVisitor()
{
    this->asm_functions = std::deque<std::stringstream>();
    this->isDebug = true;
}

// TODO this is just while dev, to be removed in final version:
void DirectCodeGenVisitor::printAstName(const char * name)
{
    std::cout << "TODO implement code gen for node '" << name << "'." << std::endl;
}

std::string DirectCodeGenVisitor::getFileAndLineState(astnodes::Node* node)
{
    std::stringstream str;
    str << ".ULINE " << node->line << " \"" << node->file << "\"";
    return str.str();
}


/******************************/
/* visit functions            */
/******************************/


void DirectCodeGenVisitor::visit(astnodes::Program * program)
{
    // compile everything
    program->allChildrenAccept(*this);
}


void DirectCodeGenVisitor::visit(astnodes::FunctionDefinition * functionDefinition)
{
    std::stringstream asmStr;
    asmStr << getFileAndLineState(functionDefinition);
    
    // Output a safety boundary if the assembler supports
    // it and we want to output in debug mode.
    if (isDebug)
    {
        if (assembler.supportsSafetyBoundary)
            asmStr << ".BOUNDARY" << std::endl;
        else if (assembler.supportsDataInstruction)
            asmStr << "DAT 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0" << std::endl;
    }
    
    // If the assembler supports exporting symbols, automatically
    // export this function.
    // TODO unless specified as static
    if (assembler.supportsLinkedExportDirective)
        asmStr <<  ".EXPORT cfunc_" << functionDefinition->name << std::endl;
    
    // Output the leading information and immediate jump.
    asmStr <<  ":cfunc_" << functionDefinition->name << std::endl;
    asmStr <<  "    SET PC, cfunc_" << functionDefinition->name << "_actual" << std::endl;
    asmStr <<  "    DAT " << functionDefinition->paramSize << std::endl;
    asmStr <<  ":cfunc_" << functionDefinition->name << "_actual" << std::endl;
    
    // Allocate locals.
    asmStr <<  "    SUB SP, " << functionDefinition->stackSize << std::endl;
    
    // Now compile the block.
    asm_current = asmStr;
    functionDefinition->block->accept(*this);
    
    // an end of function label, a return; jumps here after saving the result
    asmStr <<  ":cfunc_" << functionDefinition->name << "_end" << std::endl;
    
    // Free locals.
    asmStr <<  "    ADD SP, " << functionDefinition->stackSize << std::endl;
    
    // Return from this function.
    asmStr <<  "    SET A, 0xFFFF" << std::endl;
    asmStr <<  "    SET X, " << functionDefinition->paramSize << std::endl;
    asmStr <<  "    SET PC, _stack_callee_return" << std::endl;
    
    // put the generated code in the functions list
    asm_functions.push_back(asmStr.str());
}


void DirectCodeGenVisitor::visit(astnodes::GotoStatement * gotoStatement)
{
    // Add file and line information.
    asm_current << this->getFileAndLineState(gotoStatement);
    // jump to the label:
    asm_current << "    SET PC, " << gotoStatement->lbl->label << std::endl;
}


void DirectCodeGenVisitor::visit(astnodes::ContinueStatement * continueStatement)
{
    // Add file and line information.
    asm_current << this->getFileAndLineState(continueStatement);
    // jump to the label
    asm_current << "    SET PC, " << continueStatement->label->label << std::endl;
}


void DirectCodeGenVisitor::visit(astnodes::BreakStatement * breakStatement)
{
    // Add file and line information.
    asm_current << this->getFileAndLineState(breakStatement);
    // jump to the label
    asm_current << "    SET PC, " << breakStatement->label->label << std::endl;
}


void DirectCodeGenVisitor::visit(astnodes::DefaultStatement * defaultStatement)
{
    // Add file and line information.
    asm_current << this->getFileAndLineState(defaultStatement);
    // jump to the label
    asm_current << ":" << defaultStatement->lbl->label << std::endl;
    
    // compile child statement:
    defaultStatement->allChildrenAccept(*this);
}


void DirectCodeGenVisitor::visit(astnodes::CaseStatement * caseStatement)
{
    // TODO const expression evaluator
    // TODO
    // TODO the expression evaluator (first finish semantic check for expressions)
    printAstName("CaseStatement");
    caseStatement->allChildrenAccept(*this);
}



void DirectCodeGenVisitor::visit(astnodes::Expression * expression)
{
    throw new errors::InternalCompilerException("Expression Node is only abstract and cannot be visited");
}


void DirectCodeGenVisitor::visit(astnodes::Statement * statement)
{
    throw new errors::InternalCompilerException("Statement Node is only abstract and cannot be visited");
}


void DirectCodeGenVisitor::visit(astnodes::ExternalDeclaration * externalDeclaration)
{
    throw new errors::InternalCompilerException("ExternalDeclaration Node is only abstract and cannot be visited");
}


void DirectCodeGenVisitor::visit(astnodes::ReturnStatement * returnStatement)
{
    // Add file and line information.
    asm_current << this->getFileAndLineState(returnStatement);
    
    // first check the expression
    returnStatement->allChildrenAccept(*this);
    // then check if it is compatible with the function return value
    // TODO TODO FIXME
}


void DirectCodeGenVisitor::visit(astnodes::ForStatement * forStatement)
{
    // Add file and line information.
    asm_current << this->getFileAndLineState(forStatement);
    
    // Do the initalization statement.
    forStatement->initExpr->accept(*this);
    
    // Output the start label.
    asm_current << ":" << forStatement->startLbl->label << std::endl;
    
    // translate the check expression
    forStatement->condExpr->accept(*this);
    
    // If A is not true, jump to the end.
    asm_current <<   "   IFE A, 0x0" << std::endl;
    asm_current <<   "       SET PC, " << forStatement->endLbl->label << std::endl;
    
    // Compile the main block.
    forStatement->statement->accept(*this);
    
    // Output the continue label.
    asm_current << ":" << forStatement->continueLbl->label << std::endl;
    
    // Do the loop statement.
    forStatement->loopExpr->accept(*this);
    
    // Jump back up to the start to do the evaluation.
    asm_current <<   "   SET PC, " << forStatement->startLbl->label << std::endl;
    
    // And insert the end label.
    asm_current << ":" << forStatement->endLbl->label << std::endl;
}


void DirectCodeGenVisitor::visit(astnodes::DoWhileStatement * doWhileStatement)
{
    // Add file and line information.
    asm_current << this->getFileAndLineState(doWhileStatement);
    
    // Output the start label.
    asm_current << ":" << doWhileStatement->startLbl->label << std::endl;
    
    // compile the block
    doWhileStatement->statement->accept(*this);
    
    // output continue label
    asm_current << ":" << doWhileStatement->continueLbl->label << std::endl;
    
    // compile the condition 
    doWhileStatement->condExpr->accept(*this);
    
    // while the expression is true, jump to beginning
    asm_current <<   "   IFN A, 0x0" << std::endl;
    asm_current <<   "       SET PC, " << doWhileStatement->startLbl->label << std::endl;
    
    // And insert the end label.
    asm_current << ":" << doWhileStatement->endLbl->label << std::endl;
}


void DirectCodeGenVisitor::visit(astnodes::WhileStatement * whileStatement)
{
    // Add file and line information.
    asm_current << this->getFileAndLineState(whileStatement);
    
    // Output the start label.
    asm_current << ":" << whileStatement->startLbl->label << std::endl;
    
    // compile the condition 
    whileStatement->condExpr->accept(*this);
    
    // if the expression evaluates to false, jump to end
    asm_current <<   "   IFE A, 0x0" << std::endl;
    asm_current <<   "       SET PC, " << whileStatement->endLbl->label << std::endl;
    
    // compile the block
    whileStatement->statement->accept(*this);
    
    // Jump back up to the start to do the evaluation.
    asm_current <<   "   SET PC, " << whileStatement->startLbl->label << std::endl;
    
    // And insert the end label.
    asm_current << ":" << whileStatement->endLbl->label << std::endl;
}


void DirectCodeGenVisitor::visit(astnodes::SwitchStatement * switchStatement)
{
    // Add file and line information.
    asm_current << this->getFileAndLineState(switchStatement);
    
    // TODO TODO TODO
    
    // first evaluate the controlling expression
    switchStatement->expr->accept(*this);
    
    printAstName("SwitchStatement");
}


void DirectCodeGenVisitor::visit(astnodes::IfStatement * ifStatement)
{
    // Add file and line information.
    asm_current << this->getFileAndLineState(ifStatement);
    
    // When an expression is evaluated, the result goes into the A register.
    ifStatement->condExpr->accept(*this);
    
    // check for the result of the conditional expression
    asm_current << "   IFE A, 0x0" << std::endl;
    if (ifStatement->elseStmt != NULL)
        asm_current << "       SET PC, " << ifStatement->elselbl->label << std::endl;
    else
        asm_current << "       SET PC, " << ifStatement->endlbl->label << std::endl;
        
    // compile if block
    ifStatement->ifStmt->accept(*this);
    
    // compile else block
    if (ifStatement->elseStmt != NULL)
    {
        // jump to end 
        asm_current << "    SET PC, " << ifStatement->endlbl->label << std::endl;
        
        // Output the else label.
        asm_current << ":" << ifStatement->elselbl->label << std::endl;
        
        // compile else block
        ifStatement->elseStmt->accept(*this);
    }
    
    // Output the end label.
    asm_current << ":" << ifStatement->endlbl->label << std::endl;
}


void DirectCodeGenVisitor::visit(astnodes::ExpressionStatement * expressionStatement)
{
    // Add file and line information.
    asm_current << this->getFileAndLineState(expressionStatement);
    // just pass through
    expressionStatement->allChildrenAccept(*this);
}


void DirectCodeGenVisitor::visit(astnodes::EmptyStatement * emptyStatement)
{
    // nothing to do here
}


void DirectCodeGenVisitor::visit(astnodes::BlockStatement * blockStatement)
{
    // Add file and line information.
    asm_current << this->getFileAndLineState(blockStatement);
    
    // compile the statements 
    blockStatement->allChildrenAccept(*this);
}


void DirectCodeGenVisitor::visit(astnodes::LabelStatement * labelStatement)
{    
    // Add file and line information.
    asm_current << this->getFileAndLineState(labelStatement);
    
    // Output the end label.
    asm_current << ":" << labelStatement->label << std::endl;
    
    // compile children statements
    labelStatement->allChildrenAccept(*this);
}






/*######################################*/
/*        3.5 DECLARATIONS              */
/*######################################*/



// TODO TODO FIXME TODO TODO FIXME
// implement declarators ;)
// first now implementing expressions

void DirectCodeGenVisitor::visit(astnodes::Declaration * declaration)
{
    // visit all the declarators
    if (!declaration->isParamDecl)
    {
        for (astnodes::Declarators::iterator i = declaration->declarators->begin(); i != declaration->declarators->end(); ++i)
        {
            // visit all the declarators
            (*i)->accept(*this);
        }
    }
}




/******************************/
/*     3.5.4 Declarators      */
/******************************/

void DirectCodeGenVisitor::visit(astnodes::Declarator * declarator)
{
    throw new errors::InternalCompilerException("Declarator Node is only abstract and cannot be visited");
}

void DirectCodeGenVisitor::visit(astnodes::NoIdentifierDeclarator * noIdentifierDeclarator)
{
    // nothing to do
}

void DirectCodeGenVisitor::visit(astnodes::IdentifierDeclarator * identifierDeclarator)
{
    // TODO compile initializers
}


/* 3.5.4.1 Pointer declarators */

void DirectCodeGenVisitor::visit(astnodes::Pointer * pointer)
{
    // nothing to do
}


/* 3.5.4.2 Array declarators */

void DirectCodeGenVisitor::visit(astnodes::ArrayDeclarator * arrayDeclarator)
{
    // TODO compile the the initializers
    if (arrayDeclarator->initializers != NULL)
        for (astnodes::Expressions::iterator i = arrayDeclarator->initializers->begin(); i != arrayDeclarator->initializers->end(); ++i)
        {
            // evaluate the expression
            (*i)->accept(*this);
            
            // save the result
            // TODO
        }
}


/* 3.5.4.3 Function declarators */

void DirectCodeGenVisitor::visit(astnodes::FunctionDeclarator * functionDeclarator)
{
    // TODO compile the the initializers
}



/**********************************/
/*       3.5.5 Type names         */
/**********************************/

void DirectCodeGenVisitor::visit(astnodes::TypeName * typeName)
{
    // nothing to do here
}











/**********************************/
/* 3.5.1 Storage-class specifiers */
/**********************************/

void DirectCodeGenVisitor::visit(astnodes::StorageSpecifier * storageSpecifier)
{
    throw new errors::InternalCompilerException("a storage specifier should not be visited");
}




/******************************/
/*  3.5.2 Type specifiers     */
/******************************/

void DirectCodeGenVisitor::visit(astnodes::TypeSpecifier * typeSpecifier)
{
    throw new errors::InternalCompilerException("Declarator Node is only abstract and cannot be visited");
}

void DirectCodeGenVisitor::visit(astnodes::TypeBaseSpecifier * typeBaseSpecifier)
{
    // nothing to do here
}



void DirectCodeGenVisitor::visit(astnodes::StructUnionSpecifier * structUnionSpecifier)
{
    // nothing to do here
}


void DirectCodeGenVisitor::visit(astnodes::EnumSpecifier * enumSpecifier)
{
    // nothing to do here
}



void DirectCodeGenVisitor::visit(astnodes::TypeNameSpecifier * typeNameSpecifier)
{
    // nothing to do here
}


/******************************/
/*  3.5.3 Type qualifiers     */
/******************************/

void DirectCodeGenVisitor::visit(astnodes::TypeQualifier * typeQualifier)
{
    throw new errors::InternalCompilerException("a type qualifier should not be visited");
}



/*######################################*/
/*      3.3 Expressions                 */
/*######################################*/


/******************************/
/*  3.3.1 Primary expressions */
/******************************/

/* identifier */

void DirectCodeGenVisitor::visit(astnodes::Identifier * identifier)
{
    if (!this->m_symbolTable->containsRec(identifier->name))
    {
        addError(identifier, ERR_CC_VARIABLE_NOT_IN_SCOPE, identifier->name);
        identifier->valType = getInvalidValType();
        // don't handle anything below
        return;
    }
    
    // TODO enum types are constants!! 
    
    types::Type* varType = this->m_symbolTable->getTypeOfVariable(identifier->name);
    if (varType == NULL)
    {
        // this must be a function then
        types::FunctionType* funcType = this->m_symbolTable->getFunction(identifier->name);
        if (funcType == NULL)
        {
            throw new errors::InternalCompilerException("Neither a variable nor a function was found by the name '" + identifier->name + "'.");
        }
        identifier->valType = new valuetypes::FunctionDesignator(funcType);
    }
    else
    {
        identifier->valType = new valuetypes::LValue(varType);
    }
}


/* constants */

void DirectCodeGenVisitor::visit(astnodes::CharacterLiteral * characterLiteral)
{
    characterLiteral->valType = new valuetypes::CValue(new types::UnsignedChar());
}


void DirectCodeGenVisitor::visit(astnodes::SignedIntLiteral * signedIntLiteral)
{
    signedIntLiteral->valType = new valuetypes::CValue(new types::SignedInt());
}


void DirectCodeGenVisitor::visit(astnodes::UnsignedIntLiteral * unsignedIntLiteral)
{
    unsignedIntLiteral->valType = new valuetypes::CValue(new types::UnsignedInt());
}


void DirectCodeGenVisitor::visit(astnodes::SignedLongLiteral * signedLongLiteral)
{
    signedLongLiteral->valType = new valuetypes::CValue(new types::SignedLong());
}


void DirectCodeGenVisitor::visit(astnodes::UnsignedLongLiteral * unsignedLongLiteral)
{
    unsignedLongLiteral->valType = new valuetypes::CValue(new types::UnsignedLong());
}


void DirectCodeGenVisitor::visit(astnodes::FloatLiteral * floatLiteral)
{
    floatLiteral->valType = new valuetypes::CValue(new types::Float());
}


void DirectCodeGenVisitor::visit(astnodes::DoubleLiteral * doubleLiteral)
{
    doubleLiteral->valType = new valuetypes::CValue(new types::Double());
}


void DirectCodeGenVisitor::visit(astnodes::LongDoubleLiteral * longDoubleLiteral)
{
    longDoubleLiteral->valType = new valuetypes::CValue(new types::LongDouble());
}


/* string literal */

void DirectCodeGenVisitor::visit(astnodes::StringLiteral * stringLiteral)
{
   stringLiteral->valType = new valuetypes::LValue(new types::ArrayType(new types::UnsignedChar(), stringLiteral->str.length(), 1));
}




/******************************/
/*  3.3.2 Postfix expressions */
/******************************/

/* 3.3.2.1 array subscripting */

void DirectCodeGenVisitor::visit(astnodes::ArrayAccessOperator * arrayAccessOperator)
{
    // analyse both sub expressions
    arrayAccessOperator->allChildrenAccept(*this);
    
    // check LHS type
    types::Type* lhsType = arrayAccessOperator->lhsExpr->valType->type;
    
    if(!types::IsTypeHelper::isPointerType(lhsType))
    {
        addError(arrayAccessOperator, ERR_CC_ARRAY_ACCESS_NO_POINTER);
        arrayAccessOperator->valType = getInvalidValType();
        return;
    }
    if (!types::IsTypeHelper::isObjectType(types::IsTypeHelper::getPointerType(lhsType)->baseType))
    {
        addError(arrayAccessOperator, ERR_CC_DEREF_INCOMPLETE_TYPE);
        arrayAccessOperator->valType = getInvalidValType();
        return;
    }
    
    // check RHS type
    types::Type* rhsType = arrayAccessOperator->rhsExpr->valType->type;
    if(!types::IsTypeHelper::isIntegralType(rhsType))
    {
        addError(arrayAccessOperator, ERR_CC_ARRAY_SUB_NOT_INT);
        arrayAccessOperator->valType = getInvalidValType();
        return;
    }
    
    arrayAccessOperator->valType = new valuetypes::LValue(types::IsTypeHelper::getPointerType(lhsType)->baseType);
}


/* 3.3.2.2 Function calls */

void DirectCodeGenVisitor::visit(astnodes::MethodCall * methodCall)
{
    // analyse lhs and all arguments
    methodCall->allChildrenAccept(*this);
    
    // check LHS type
    types::Type* lhsType = methodCall->lhsExpr->valType->type;
    
    types::FunctionType* funType = NULL;
    
    if (! valuetypes::IsValueTypeHelper::isFunctionDesignator(methodCall->lhsExpr->valType))
    {
        if (!types::IsTypeHelper::isFunctionType(lhsType)){
            if(!types::IsTypeHelper::isPointerType(lhsType))
            {
                addError(methodCall, ERR_CC_CALLED_OBJ_NOT_FUNC);
                methodCall->valType = getInvalidValType();
                return;
            }
            if (!types::IsTypeHelper::isFunctionType(types::IsTypeHelper::getPointerType(lhsType)->baseType))
            {
                addError(methodCall, ERR_CC_CALLED_OBJ_NOT_FUNC);
                methodCall->valType = getInvalidValType();
                return;
            }
            funType = types::IsTypeHelper::getFunctionType(types::IsTypeHelper::getPointerType(lhsType)->baseType);
        }
        else
        {
            funType = types::IsTypeHelper::getFunctionType(lhsType);
        }
    }
    else
    {
        funType = types::IsTypeHelper::getFunctionType(methodCall->lhsExpr->valType->type);
    }
    
    // now we are sure it is a pointer to a function, get the functiontype
    methodCall->valType = new valuetypes::RValue(funType->returnType);
    
    // check for same size (or in case of variable arguments (...) for the call having
    // at least as many arguments as there are parameters in the function type.
    if ((funType->isVarArgs && methodCall->rhsExprs->size() < funType->paramTypes->size())
        || (!funType->isVarArgs && methodCall->rhsExprs->size() != funType->paramTypes->size()))
    {
        addError(methodCall, ERR_CC_CALLED_FUNC_NUM_PARAMS);
        return;
    }
    
    for (unsigned int i = 0; i < methodCall->rhsExprs->size(); i++)
    {
        valuetypes::ValueType* from = (*methodCall->rhsExprs)[i]->valType;
        types::Type* to = (*funType->paramTypes)[i];
        // make sure all the parameter types match
        // TODO check that they are assignable (see assignment operator)
        // TODO FIXME TODO FIXME
    }
    
    // TODO what to do if return type is bigger than 1 word??
}


/* 3.3.2.3 Structure and union members */

void DirectCodeGenVisitor::visit(astnodes::StructureResolutionOperator * structureResolutionOperator)
{
    // TODO FIXME TODO FIXME
    // TODO implement structs properly
    printAstName("StructureResolutionOperator");
    structureResolutionOperator->allChildrenAccept(*this);
}


/* 3.3.2.4 Postfix increment and decrement operators */

void DirectCodeGenVisitor::visit(astnodes::PostIncDec * postIncDec)
{
    // fist analyse the inner expression
    postIncDec->allChildrenAccept(*this);
    
    // check that the expression type is a scalar type
    if(!types::IsTypeHelper::isScalarType(postIncDec->expr->valType->type))
    {
        addError(postIncDec, ERR_CC_EXPECTED_SCALAR_INCDEC);
    }
    
    // check that the expression type is a scalar type
    if(!valuetypes::IsValueTypeHelper::isModifiableLValue(postIncDec->expr->valType))
    {
        addError(postIncDec, ERR_CC_INCDEC_NO_MOD_LVALUE);
    }
    
    // same value type
    postIncDec->valType = postIncDec->expr->valType;
}



/******************************/
/*  3.3.3 Unary operators     */
/******************************/

/* 3.3.3.1 Prefix increment and decrement operators */

void DirectCodeGenVisitor::visit(astnodes::PreIncDec * preIncDec)
{
    // fist analyse the inner expression
    preIncDec->allChildrenAccept(*this);
    
    // check that the expression type is a scalar type
    if(!types::IsTypeHelper::isScalarType(preIncDec->expr->valType->type))
    {
        addError(preIncDec, ERR_CC_EXPECTED_SCALAR_INCDEC);
    }
    
    // check that the expression type is a scalar type
    if(!valuetypes::IsValueTypeHelper::isModifiableLValue(preIncDec->expr->valType))
    {
        addError(preIncDec, ERR_CC_INCDEC_NO_MOD_LVALUE);
    }
    
    // same value type
    preIncDec->valType = preIncDec->expr->valType;
}

/* 3.3.3.2 Address and indirection operators */
// TODO add the Address of Operator!


/* 3.3.3.3 Unary arithmetic operators */

void DirectCodeGenVisitor::visit(astnodes::UnaryOperator * unaryOperator)
{
    // analyse inner expression first:
    unaryOperator->allChildrenAccept(*this);
    
    switch(unaryOperator->optoken)
    {
        case ADD_OP:
        case SUB_OP:
            // check that the expression type is a arithmetic type
            if(!types::IsTypeHelper::isArithmeticType(unaryOperator->expr->valType->type))
            {
                addError(unaryOperator, ERR_CC_UNARY_PLUS_MINUS_ARITH);
                unaryOperator->valType = getInvalidValType();
                return;
            }
            unaryOperator->valType = valuetypes::PromotionHelper::promote(unaryOperator->expr->valType);
            break;
            
        case BIN_INV_OP:
            // check that the expression type is a arithmetic type
            if(!types::IsTypeHelper::isIntegralType(unaryOperator->expr->valType->type))
            {
                addError(unaryOperator, ERR_CC_UNARY_INV_INTEGRAL);
                unaryOperator->valType = getInvalidValType();
                return;
            }
            unaryOperator->valType = valuetypes::PromotionHelper::promote(unaryOperator->expr->valType);
            break;
            
        case NOT_OP:
            // check that the expression type is a arithmetic type
            if(!types::IsTypeHelper::isScalarType(unaryOperator->expr->valType->type))
            {
                addError(unaryOperator, ERR_CC_UNARY_NOT_SCALAR);
                unaryOperator->valType = getInvalidValType();
                return;
            }
            unaryOperator->valType = new valuetypes::RValue(new types::SignedInt());
            break;
        default:
            throw new errors::InternalCompilerException("Unknown unary operator encountered");
    }
}


/* 3.3.3.4 The sizeof operator */

void DirectCodeGenVisitor::visit(astnodes::SizeOfOperator * sizeOfOperator)
{
    // analyse the expression inside the sizeof operator
    sizeOfOperator->allChildrenAccept(*this);
    
    // set return type as a CValue (constant RValue)
    sizeOfOperator->valType = new valuetypes::CValue(new types::UnsignedInt());
    
    // check it is not a function type
    if (valuetypes::IsValueTypeHelper::isFunctionDesignator(sizeOfOperator->valType))
    {
        addError(sizeOfOperator, ERR_CC_SIZEOF_FUNC);
        return;
    }
    
    // return the word size of the expression type
    // TODO special return value for array types??
    sizeOfOperator->constExpr = new astnodes::UnsignedIntLiteral(sizeOfOperator->valType->type->getByteSize());
    sizeOfOperator->constExpr->accept(*this);
}


/******************************/
/*  3.3.4 Cast operators      */
/******************************/

void DirectCodeGenVisitor::visit(astnodes::ExplicitCastOperator * explicitCastOperator)
{
    // TODO TODO TODO TODO
    // TODO TODO TODO TODO
    // TODO TODO TODO TODO
    printAstName("ExplicitCastOperator");
    explicitCastOperator->allChildrenAccept(*this);
}



/******************************/
/*     binary operators       */
/******************************/

void DirectCodeGenVisitor::visit(astnodes::BinaryOperator * binaryOperator)
{
    // analyse both sub-expressions
    binaryOperator->allChildrenAccept(*this);
    
    // TODO both operand have to be converted from R to L value
    //.TODO when they are converted, array type gets converted to pointer type
    // TODO otherwise all those checks below won't work properly :(
    
    valuetypes::ValueType* lhsVtype = binaryOperator->lhsExrp->valType;
    valuetypes::ValueType* rhsVtype = binaryOperator->rhsExpr->valType;
    types::Type* lhsType = lhsVtype->type;
    types::Type* rhsType = rhsVtype->type;
    
    
    switch(binaryOperator->optoken)
    {
        
        /* 3.3.5 Multiplicative operators */
        
        case MUL_OP:
        case DIV_OP:
            // check that the expression type is a arithmetic type
            if((!types::IsTypeHelper::isArithmeticType(lhsType))
                || !types::IsTypeHelper::isArithmeticType(rhsType))
            {
                addError(binaryOperator, ERR_CC_BIN_EXPECTED_ARITH);
                binaryOperator->valType = getInvalidValType();
                return;
            }
            binaryOperator->valType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype);
            binaryOperator->commonType = binaryOperator->valType->type;
            break;
        case MOD_OP:
            // check that the expression type is a integral type
            if((!types::IsTypeHelper::isIntegralType(lhsType))
                || !types::IsTypeHelper::isIntegralType(rhsType))
            {
                addError(binaryOperator, ERR_CC_BIN_EXPECTED_INTEGRAL);
                binaryOperator->valType = getInvalidValType();
                return;
            }
            binaryOperator->valType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype);
            binaryOperator->commonType = binaryOperator->valType->type;
            break;
        
            
        /* 3.3.6 Additive operators */
        
        case ADD_OP:
            if((types::IsTypeHelper::isArithmeticType(lhsType))
                && types::IsTypeHelper::isArithmeticType(rhsType))
            {
                // both are arithmetic types
                // promote:
                binaryOperator->valType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype);
                binaryOperator->commonType = binaryOperator->valType->type;
            }
            else if(((types::IsTypeHelper::isPointerType(lhsType))
                && types::IsTypeHelper::isIntegralType(rhsType)))

            {
                // pointer op
                binaryOperator->rhsPtr = true;
                binaryOperator->pointerSize = types::IsTypeHelper::getPointerBaseSize(lhsType);
                binaryOperator->commonType = types::IntegralPromotion::promote(rhsType);
                binaryOperator->valType = valuetypes::IsValueTypeHelper::toCorRValue(lhsType, lhsVtype, rhsVtype);
            }
            else if ((types::IsTypeHelper::isIntegralType(lhsType))
                && types::IsTypeHelper::isPointerType(rhsType))
            {
                // pointer op
                binaryOperator->rhsPtr = true;
                binaryOperator->pointerSize = types::IsTypeHelper::getPointerBaseSize(rhsType);
                binaryOperator->commonType = types::IntegralPromotion::promote(lhsType);
                binaryOperator->valType = valuetypes::IsValueTypeHelper::toCorRValue(rhsType, lhsVtype, rhsVtype);
            }
            else
            {
                addError(binaryOperator, ERR_CC_BIN_ADD_INVALID_TYPES);
                binaryOperator->valType = getInvalidValType();
                return;
            }
            break;
        case SUB_OP:
            if((types::IsTypeHelper::isArithmeticType(lhsType))
                && types::IsTypeHelper::isArithmeticType(rhsType))
            {
                // both are arithmetic types
                // promote:
                binaryOperator->valType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype);
                binaryOperator->commonType = binaryOperator->valType->type;
            } else if((binaryOperator->optoken == SUB_OP)
                && (types::IsTypeHelper::isPointerType(lhsType))
                && types::IsTypeHelper::isPointerType(rhsType))
            {
                // TODO add ptrdiff_t to stddef.h
                binaryOperator->lhsPtr = true;
                binaryOperator->rhsPtr = true;
                binaryOperator->pointerSize = types::IsTypeHelper::getPointerBaseSize(lhsType);
                // TODO properly check for compatible types pointed to
                if (binaryOperator->pointerSize != types::IsTypeHelper::getPointerBaseSize(rhsType))
                {
                    addError(binaryOperator, ERR_CC_PTR_NOT_COMPAT);
                    binaryOperator->valType = getInvalidValType();
                    return;
                }
                binaryOperator->valType = valuetypes::IsValueTypeHelper::toCorRValue(new types::SignedInt(), lhsVtype, rhsVtype);
            } else if((types::IsTypeHelper::isPointerType(lhsType))
                && types::IsTypeHelper::isIntegralType(rhsType))
            {
                binaryOperator->lhsPtr = true;
                binaryOperator->pointerSize = types::IsTypeHelper::getPointerBaseSize(lhsType);
                binaryOperator->commonType = types::IntegralPromotion::promote(rhsType);
                binaryOperator->valType = valuetypes::IsValueTypeHelper::toCorRValue(lhsType, lhsVtype, rhsVtype);
            }
            else
            {
                addError(binaryOperator, ERR_CC_BIN_SUB_INVALID_TYPES);
                binaryOperator->valType = getInvalidValType();
                return;
            }
            break;
            
            
        /* 3.3.7 Bitwise shift operators */
            
        case LEFT_OP:
        case RIGHT_OP:
            // check that the expression type is a integral type
            if((!types::IsTypeHelper::isIntegralType(lhsType))
                || !types::IsTypeHelper::isIntegralType(rhsType))
            {
                addError(binaryOperator, ERR_CC_BIN_EXPECTED_INTEGRAL);
                binaryOperator->valType = getInvalidValType();
                return;
            }
            
            binaryOperator->commonType = valuetypes::PromotionHelper::promote(lhsVtype)->type;
            binaryOperator->valType = valuetypes::IsValueTypeHelper::toCorRValue(binaryOperator->commonType, lhsVtype, rhsVtype);
            break;
            
        /* 3.3.8 Relational operators */
        case LT_OP:
        case GT_OP:
        case LE_OP:
        case GE_OP:
            if((types::IsTypeHelper::isArithmeticType(lhsType))
                && types::IsTypeHelper::isArithmeticType(rhsType))
            {
                // both are arithmetic types
                // promote:
                binaryOperator->commonType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype)->type;
                binaryOperator->valType = valuetypes::IsValueTypeHelper::toCorRValue(new types::SignedInt(), lhsVtype, rhsVtype);
            } else if((types::IsTypeHelper::isPointerType(lhsType))
                && types::IsTypeHelper::isPointerType(rhsType))
            {
                binaryOperator->lhsPtr = true;
                binaryOperator->rhsPtr = true;
                binaryOperator->pointerSize = types::IsTypeHelper::getPointerBaseSize(lhsType);
                
                // TODO properly check for compatible types pointed to
                if (binaryOperator->pointerSize != types::IsTypeHelper::getPointerBaseSize(rhsType))
                {
                    addError(binaryOperator, ERR_CC_PTR_NOT_COMPAT);
                    binaryOperator->valType = getInvalidValType();
                    return;
                }
                
                binaryOperator->valType = valuetypes::IsValueTypeHelper::toCorRValue(new types::SignedInt(), lhsVtype, rhsVtype);
            }
            else
            {
                addError(binaryOperator, ERR_CC_COMP_INVALID_TYPES);
                binaryOperator->valType = getInvalidValType();
                return;
            }
            break;
            
        
        /* 3.3.9 Equality operators */
        
        case EQ_OP:
        case NE_OP:
            if((types::IsTypeHelper::isArithmeticType(lhsType))
                && types::IsTypeHelper::isArithmeticType(rhsType))
            {
                // both are arithmetic types
                // promote:
                binaryOperator->commonType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype)->type;
                binaryOperator->valType = valuetypes::IsValueTypeHelper::toCorRValue(new types::SignedInt(), lhsVtype, rhsVtype);
            } else if((types::IsTypeHelper::isPointerType(lhsType))
                && types::IsTypeHelper::isPointerType(rhsType))
            {
                binaryOperator->lhsPtr = true;
                binaryOperator->rhsPtr = true;
                binaryOperator->pointerSize = types::IsTypeHelper::getPointerBaseSize(lhsType);
                
                // TODO properly check for compatible types pointed to
                if (binaryOperator->pointerSize != types::IsTypeHelper::getPointerBaseSize(rhsType))
                {
                    addError(binaryOperator, ERR_CC_PTR_NOT_COMPAT);
                    binaryOperator->valType = getInvalidValType();
                    return;
                }
                
                binaryOperator->valType = valuetypes::IsValueTypeHelper::toCorRValue(new types::SignedInt(), lhsVtype, rhsVtype);
            }
            // TODO case for Null pointer constant
            else
            {
                addError(binaryOperator, ERR_CC_COMP_INVALID_TYPES);
                binaryOperator->valType = getInvalidValType();
                return;
            }
            break;
        
            
        /* 3.3.10 Bitwise AND operator */
        /* 3.3.11 Bitwise exclusive OR operator */
        /* 3.3.12 Bitwise inclusive OR operator */
        
        case BIN_AND_OP:
        case BIN_XOR_OP:
        case BIN_OR_OP:
            // check that the expression type is a integral type
            if((!types::IsTypeHelper::isIntegralType(lhsType))
                || !types::IsTypeHelper::isIntegralType(rhsType))
            {
                addError(binaryOperator, ERR_CC_BIN_EXPECTED_INTEGRAL);
                binaryOperator->valType = getInvalidValType();
                return;
            }
            
            binaryOperator->valType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype);
            binaryOperator->commonType = binaryOperator->valType->type;
            break;
            
            
            /* 3.3.13 Logical AND operator */
            /* 3.3.14 Logical OR operator */
            
        case AND_OP:
        case OR_OP:
            
            // check that the expression type is a integral type
            if((!types::IsTypeHelper::isIntegralType(lhsType))
                || !types::IsTypeHelper::isIntegralType(rhsType))
            {
                addError(binaryOperator, ERR_CC_BIN_EXPECTED_INTEGRAL);
                binaryOperator->valType = getInvalidValType();
                return;
            }

            binaryOperator->commonType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype)->type;
            binaryOperator->valType = valuetypes::IsValueTypeHelper::toCorRValue(new types::SignedInt(), lhsVtype, rhsVtype);
            break;
            
        default:
            throw new errors::InternalCompilerException("unknown binary operator encountered");
    }
}

/********************************/
/* 3.3.15 Conditional operator  */
/********************************/
 
void DirectCodeGenVisitor::visit(astnodes::ConditionalOperator * conditionalOperator)
{
    // TODO TODO TODO TODO
    // TODO TODO TODO TODO
    // TODO TODO TODO TODO
    printAstName("ConditionalOperator");
    conditionalOperator->allChildrenAccept(*this);
}



/********************************/
/* 3.3.16 Assignment operators  */
/********************************/

void DirectCodeGenVisitor::visit(astnodes::AssignmentOperator * assignmentOperator)
{
    // first check lhs and rhs expression
    assignmentOperator->allChildrenAccept(*this);
    
    valuetypes::ValueType* lhsVtype = assignmentOperator->lhsExrp->valType;
    valuetypes::ValueType* rhsVtype = assignmentOperator->rhsExpr->valType;
    types::Type* lhsType = lhsVtype->type;
    types::Type* rhsType = rhsVtype->type;
   
    
    // check that the lhs is a modifiable LValue
    if(!valuetypes::IsValueTypeHelper::isModifiableLValue(assignmentOperator->lhsExrp->valType))
    {
        addError(assignmentOperator, ERR_CC_ASSIGN_NO_MOD_LVALUE);
    }
    
    switch (assignmentOperator->optoken)
    {
        
        /* 3.3.16.1 Simple assignment */
        
        case ASSIGN_EQUAL:
            if((types::IsTypeHelper::isArithmeticType(lhsType))
                && types::IsTypeHelper::isArithmeticType(rhsType))
            {
                // both are arithmetic types
                // promote:
                assignmentOperator->valType = new valuetypes::RValue(lhsType);
                assignmentOperator->commonType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype)->type;
            }
            else if((types::IsTypeHelper::isPointerType(lhsType))
                && types::IsTypeHelper::isPointerType(rhsType))
            {
                // TODO properly check for compatible types pointed to
                assignmentOperator->ptrop = true;
                assignmentOperator->valType = new valuetypes::RValue(lhsType);
            }
            else if((types::IsTypeHelper::isStructUnionType(lhsType))
                && types::IsTypeHelper::isStructUnionType(rhsType))
            {
                // TODO properly check for compatible structs/unions
                assignmentOperator->valType = new valuetypes::RValue(lhsType);
            }
            else
            {
                addError(assignmentOperator, ERR_CC_ASSIGN_INVALID_TYPES);
                assignmentOperator->valType = getInvalidValType();
                return;
            }
            break;
            
            
        /* 3.3.16.2 Compound assignment */
            
        case ADD_ASSIGN:
        case SUB_ASSIGN:
            if((types::IsTypeHelper::isArithmeticType(lhsType))
                && types::IsTypeHelper::isArithmeticType(rhsType))
            {
                // both are arithmetic types
                // promote:
                assignmentOperator->valType = new valuetypes::RValue(lhsType);
                assignmentOperator->commonType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype)->type;
            }
            else if(((types::IsTypeHelper::isPointerType(lhsType))
                && types::IsTypeHelper::isIntegralType(rhsType)))
                
            {
                // pointer op
                assignmentOperator->ptrop = true;
                assignmentOperator->pointerSize = types::IsTypeHelper::getPointerBaseSize(lhsType);
                assignmentOperator->valType = new valuetypes::RValue(lhsType);
            }
            else
            {
                addError(assignmentOperator, ERR_CC_ASSIGN_INVALID_TYPES);
                assignmentOperator->valType = getInvalidValType();
                return;
            }
            break;
            
        case MUL_ASSIGN:
        case DIV_ASSIGN:
            if((types::IsTypeHelper::isArithmeticType(lhsType))
                && types::IsTypeHelper::isArithmeticType(rhsType))
            {
                // both are arithmetic types
                // promote:
                assignmentOperator->valType = new valuetypes::RValue(lhsType);
                assignmentOperator->commonType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype)->type;
            }
            else
            {
                addError(assignmentOperator, ERR_CC_ASSIGN_INVALID_TYPES);
                assignmentOperator->valType = getInvalidValType();
                return;
            }
            break;
            
        case MOD_ASSIGN:
        case LEFT_ASSIGN:
        case RIGHT_ASSIGN:
        case AND_ASSIGN:
        case XOR_ASSIGN:
        case OR_ASSIGN:
            if((types::IsTypeHelper::isIntegralType(lhsType))
                && types::IsTypeHelper::isIntegralType(rhsType))
            {
                // both are arithmetic types
                // promote:
                assignmentOperator->valType = new valuetypes::RValue(lhsType);
                assignmentOperator->commonType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype)->type;
            }
            else
            {
                addError(assignmentOperator, ERR_CC_ASSIGN_INVALID_TYPES);
                assignmentOperator->valType = getInvalidValType();
                return;
            }
            break;
        default:
            throw new errors::InternalCompilerException("unknown assignment operator encountered");
    }
}



/********************************/
/*  3.3.17 Comma operator       */
/********************************/

void DirectCodeGenVisitor::visit(astnodes::ChainExpressions * chainExpressions)
{
    // analyse all children
    chainExpressions->allChildrenAccept(*this);
    
    // check if all values types are constant
    bool isCValue = true;
    if (chainExpressions->exprs != NULL && chainExpressions->exprs->size() > 0)
    {
        for (astnodes::Expressions::iterator i = chainExpressions->exprs->begin(); i != chainExpressions->exprs->end(); ++i)
        {
            if (!valuetypes::IsValueTypeHelper::isCValue((*i)->valType))
                isCValue = false;
        }
        
        if (isCValue)
            chainExpressions->valType = new valuetypes::CValue(chainExpressions->exprs->back()->valType->type);
        else
            chainExpressions->valType = new valuetypes::RValue(chainExpressions->exprs->back()->valType->type);
    }
    else
    {
        throw new errors::InternalCompilerException("chain expressions without any expressions");
    }
}






// TODO implement those below
// TODO implement deref und address of operators!!





void DirectCodeGenVisitor::visit(astnodes::Enumerator * enumerator)
{
    printAstName("Enumerator");
    enumerator->allChildrenAccept(*this);
}


void DirectCodeGenVisitor::visit(astnodes::AssemblyStatement * assemblyStatement)
{
    printAstName("AssemblyStatement");
    assemblyStatement->allChildrenAccept(*this);
}


void DirectCodeGenVisitor::visit(astnodes::BuiltInVaStart * builtInVaStart)
{
    printAstName("BuiltInVaStart");
    builtInVaStart->allChildrenAccept(*this);
}

