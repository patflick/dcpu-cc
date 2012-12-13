#include "SemanticCheckVisitor.h"
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

SemanticCheckVisitor::SemanticCheckVisitor()
{
    this->m_loopStack = std::deque<std::pair<astnodes::LabelStatement*, astnodes::LabelStatement*> >();
    this->m_symbolTable = new symboltable::SymbolTable();
    this->m_errorList = errors::ErrorList();
    this->m_AutomaticLabels = std::set<std::string>();
    this->m_switchStack = std::deque<astnodes::SwitchStatement*>();
    this->m_funcLabels = std::map<std::string, astnodes::LabelStatement*>();
    this->m_invalidValType = new valuetypes::RValue(new types::InvalidType());
}

// TODO this is just while dev, to be removed in final version:
void SemanticCheckVisitor::printAstName(const char * name)
{
    std::cout << "TODO implement semantic check for node '" << name << "'." << std::endl;
}

valuetypes::ValueType* SemanticCheckVisitor::getInvalidValType()
{
    return new valuetypes::RValue(new types::InvalidType());
}


/******************************/
/* break and continue         */
/* label management           */
/******************************/

void SemanticCheckVisitor::initLoopStack()
{
    this->m_loopStack.clear();
}
void SemanticCheckVisitor::popLoopStack()
{
    this->m_loopStack.pop_back();
}

void SemanticCheckVisitor::pushLoopStack(astnodes::LabelStatement* breakLabel, astnodes::LabelStatement* continueLabel)
{
    this->m_loopStack.push_back(std::pair<astnodes::LabelStatement*, astnodes::LabelStatement*>(breakLabel, continueLabel));
}

astnodes::LabelStatement* SemanticCheckVisitor::getBreakLabel()
{
    if (this->m_loopStack.size() > 0)
    {
        return this->m_loopStack.back().first;
    }
    else
    {
        return NULL;
    }
}

astnodes::LabelStatement* SemanticCheckVisitor::getContinueLabel()
{
    // this can be inside a switch (which just uses break)
    // so search in the list for the next non NULL continue label
    for (std::deque<std::pair<astnodes::LabelStatement*, astnodes::LabelStatement*> >::reverse_iterator it = this->m_loopStack.rbegin(); it != this->m_loopStack.rend(); it++)
        if (it->second != NULL)
            return it->second;
    return NULL;
}

// Generates a random, unique label for use in code.
astnodes::LabelStatement* SemanticCheckVisitor::getRandomLabel(std::string prefix)
{
    std::string result = "";
    
    while ((result == "") || (this->m_AutomaticLabels.find(result) != this->m_AutomaticLabels.end()))
        result = "__" + prefix + "_" + SemanticCheckVisitor::getRandomString(10);
    
    return new astnodes::LabelStatement(result, new astnodes::EmptyStatement());
}

// Generates a random character.
char SemanticCheckVisitor::getRandomCharacter()
{
    unsigned char c;
    
    while (!std::isalnum(c = static_cast<unsigned char>(std::rand() % 256))) ;
    
    return c;
}

// Generates a random string.
std::string SemanticCheckVisitor::getRandomString(std::string::size_type sz)
{
    std::string s;
    s.reserve(sz);
    std::generate_n(std::back_inserter(s), sz, SemanticCheckVisitor::getRandomCharacter);
    return s;
}



/******************************/
/* error & warning management */
/******************************/

void SemanticCheckVisitor::addError(astnodes::Node* node, int errid)
{
    this->m_errorList.addError(node->line, node->file, errid);
}

void SemanticCheckVisitor::addError(astnodes::Node* node, int errid, std::string msg)
{
    this->m_errorList.addError(node->line, node->file, errid, msg);
}

void SemanticCheckVisitor::addWarning(astnodes::Node* node, int errid)
{
    this->m_errorList.addWarning(node->line, node->file, errid);
}

void SemanticCheckVisitor::addWarning(astnodes::Node* node, int errid, std::string msg)
{
    this->m_errorList.addWarning(node->line, node->file, errid, msg);
}




/******************************/
/* visit functions            */
/******************************/


void SemanticCheckVisitor::visit(astnodes::Program * program)
{
    // analyse everything
    program->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::FunctionDefinition * functionDefinition)
{
    // clear labels
    m_funcLabels.clear();
    
    // TODO this is a tough one
    functionDefinition->allChildrenAccept(*this);
    
    // TODO call goto label resolval visitor here:
    
    // clear labels
    m_funcLabels.clear();
}


void SemanticCheckVisitor::visit(astnodes::GotoStatement * gotoStatement)
{
    // goto statements are resolved in an extra pass
}


void SemanticCheckVisitor::visit(astnodes::ContinueStatement * continueStatement)
{
    astnodes::LabelStatement* label = getContinueLabel();
    if (label == NULL)
    {
        addError(continueStatement, ERR_CC_CONTINUE_OUTSIDE_OF_LOOP);
        return;
    }
    continueStatement->label = label;
}


void SemanticCheckVisitor::visit(astnodes::BreakStatement * breakStatement)
{
    astnodes::LabelStatement* label = getBreakLabel();
    if (label == NULL)
    {
        addError(breakStatement, ERR_CC_BREAK_OUTSIDE_OF_LOOP);
        return;
    }
    breakStatement->label = label;
}


void SemanticCheckVisitor::visit(astnodes::Expression * expression)
{
    throw new errors::InternalCompilerException("Expression Node is only abstract and cannot be visited");
}


void SemanticCheckVisitor::visit(astnodes::Statement * statement)
{
    throw new errors::InternalCompilerException("Statement Node is only abstract and cannot be visited");
}


void SemanticCheckVisitor::visit(astnodes::ExternalDeclaration * externalDeclaration)
{
    throw new errors::InternalCompilerException("ExternalDeclaration Node is only abstract and cannot be visited");
}


void SemanticCheckVisitor::visit(astnodes::ReturnStatement * returnStatement)
{
    // first check the expression
    returnStatement->allChildrenAccept(*this);
    // then check if it is compatible with the function return value
    // TODO TODO FIXME
}


void SemanticCheckVisitor::visit(astnodes::ForStatement * forStatement)
{
    // Create labels for the for statement:
    forStatement->startLbl = getRandomLabel("for_start");
    forStatement->endLbl = getRandomLabel("for_end");
    forStatement->continueLbl = getRandomLabel("for_continue");
    // put the labels on the loop stack
    pushLoopStack(forStatement->endLbl, forStatement->continueLbl);
    // evaluate all children
    forStatement->allChildrenAccept(*this);
    
    // check that the expression type is a scalar type
    if(!types::IsTypeHelper::isScalarType(forStatement->condExpr->expr->valType->type))
    {
        addError(forStatement, ERR_CC_EXPECTED_SCALAR_FOR);
    }
    
    // pop loop stack
    popLoopStack();
}


void SemanticCheckVisitor::visit(astnodes::DoWhileStatement * doWhileStatement)
{
    // Create labels for the for statement:
    doWhileStatement->startLbl = getRandomLabel("dowhile_start");
    doWhileStatement->endLbl = getRandomLabel("dowhile_end");
    doWhileStatement->continueLbl = getRandomLabel("dowhile_continue");
    
    // put the labels on the loop stack
    pushLoopStack(doWhileStatement->endLbl, doWhileStatement->continueLbl);
    // evaluate all children
    doWhileStatement->allChildrenAccept(*this);
    
    // check that the expression type is a scalar type
    if(!types::IsTypeHelper::isScalarType(doWhileStatement->condExpr->valType->type))
    {
        addError(doWhileStatement, ERR_CC_EXPECTED_SCALAR_DOWHILE);
    }
    
    // pop loop stack
    popLoopStack();
}


void SemanticCheckVisitor::visit(astnodes::WhileStatement * whileStatement)
{
    // Create labels for the for statement:
    whileStatement->startLbl = getRandomLabel("while_start");
    whileStatement->endLbl = getRandomLabel("while_end");
    
    // put the labels on the loop stack
    pushLoopStack(whileStatement->endLbl, whileStatement->startLbl);
    // evaluate all children
    whileStatement->allChildrenAccept(*this);
    
    // check that the expression type is a scalar type
    if(!types::IsTypeHelper::isScalarType(whileStatement->condExpr->valType->type))
    {
        addError(whileStatement, ERR_CC_EXPECTED_SCALAR_WHILE);
    }
    
    // pop loop stack
    popLoopStack();
}


void SemanticCheckVisitor::visit(astnodes::SwitchStatement * switchStatement)
{
    // first evaluate the controlling expression
    switchStatement->expr->accept(*this);
    
    // check for integral type
    if(!types::IsTypeHelper::isIntegralType(switchStatement->expr->valType->type))
    {
        addError(switchStatement, ERR_CC_EXPECTED_INTEGRAL_SWITCH);
        // don't handle anything inside the switch statement
        return;
    }
    
    // set promoted type
    switchStatement->promotedType = switchStatement->expr->valType->type;
    
    // push switch statement on switch-statement stack
    this->m_switchStack.push_back(switchStatement);
    
    // now check the block statement
    switchStatement->statement->accept(*this);
    
    // pop switch statement stack
    this->m_switchStack.pop_back();
    
    // check if this is still an integral type
    if(!types::IsTypeHelper::isIntegralType(switchStatement->promotedType))
    {
        addError(switchStatement, ERR_CC_EXPECTED_INTEGRAL_SWITCH);
    }
}


void SemanticCheckVisitor::visit(astnodes::IfStatement * ifStatement)
{
    // first evaluate the controlling expression
    ifStatement->condExpr->accept(*this);
    
    // check for integral type
    if(!types::IsTypeHelper::isScalarType(ifStatement->condExpr->valType->type))
    {
        addError(ifStatement, ERR_CC_EXPECTED_SCALAR_IF);
        // don't handle anything inside the if statement
        return;
    }
    
    // Create labels for the if statement:
    ifStatement->endlbl = getRandomLabel("if_end");
    if (ifStatement->elseStmt != NULL)
        ifStatement->elselbl = getRandomLabel("if_else");
    
    // recurse into the statements
    ifStatement->ifStmt->accept(*this);
    if (ifStatement->elseStmt != NULL)
        ifStatement->elseStmt->accept(*this);
}


void SemanticCheckVisitor::visit(astnodes::ExpressionStatement * expressionStatement)
{
    // just path through
    expressionStatement->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::EmptyStatement * emptyStatement)
{
    // nothing to do here
}


void SemanticCheckVisitor::visit(astnodes::BlockStatement * blockStatement)
{
    // create new scope, or if this is the main block of a function
    // then use the scope already filled with the function parameters
    if (blockStatement->scope == NULL)
        blockStatement->scope = m_symbolTable->beginNewScope();
    else
        m_symbolTable->beginScope(blockStatement->scope);
    
    // analyse the statements 
    blockStatement->allChildrenAccept(*this);
    
    // end the scope
    m_symbolTable->endScope();
}


void SemanticCheckVisitor::visit(astnodes::DefaultStatement * defaultStatement)
{
    if (m_switchStack.empty())
    {
        addError(defaultStatement, ERR_CC_DEFAULT_OUTSIDE_OF_SWITCH);
        // don't handle anything inside the default statement
        return;
    }
    
    if (m_switchStack.back()->defaultLbl != NULL)
    {
        addError(defaultStatement, ERR_CC_MULTIPLE_DEFAULT);
        // don't handle anything inside the default statement
        return;
    }
    
    defaultStatement->lbl = getRandomLabel("default");
    
    m_switchStack.back()->defaultLbl = defaultStatement->lbl;
    
    // analyse child statement:
    defaultStatement->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::CaseStatement * caseStatement)
{
    // TODO const expression evaluator
    // TODO
    // TODO the expression evaluator (first finish semantic check for expressions)
    printAstName("CaseStatement");
    caseStatement->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::LabelStatement * labelStatement)
{
    // look if a label with the same name already exists
    std::map<std::string, astnodes::LabelStatement*>::iterator it;
    if ((it = this->m_funcLabels.find(labelStatement->label)) != this->m_funcLabels.end())
    {
        addError(labelStatement, ERR_CC_DUPLICATE_LABEL, labelStatement->label);
        addError(it->second, ERR_CC_NOTE_DUPLICATE_LABEL, labelStatement->label);
        // don't handle anything inside the default statement
        return;
    }
    
    // insert label into the map
    this->m_funcLabels[labelStatement->label] = labelStatement;
    
    // go on analysing the statement after the label:
    labelStatement->allChildrenAccept(*this);
}





/******************************/
/*   Declarators !!           */
/******************************/



// TODO TODO FIXME TODO TODO FIXME
// implement declarators ;)
// first now implementing expressions

void SemanticCheckVisitor::visit(astnodes::Declarator * declarator)
{
    throw new errors::InternalCompilerException("Declarator Node is only abstract and cannot be visited");
}


void SemanticCheckVisitor::visit(astnodes::FunctionDeclarator * functionDeclarator)
{
    printAstName("FunctionDeclarator");
    functionDeclarator->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::NoIdentifierDeclarator * noIdentifierDeclarator)
{
    printAstName("NoIdentifierDeclarator");
    noIdentifierDeclarator->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::IdentifierDeclarator * identifierDeclarator)
{
    printAstName("IdentifierDeclarator");
    identifierDeclarator->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::ArrayDeclarator * arrayDeclarator)
{
    printAstName("ArrayDeclarator");
    arrayDeclarator->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::TypeName * typeName)
{
    printAstName("TypeName");
    typeName->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::Declaration * declaration)
{
    printAstName("Declaration");
    declaration->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::Pointer * pointer)
{
    printAstName("Pointer");
    pointer->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::TypeQualifier * typeQualifier)
{
    printAstName("TypeQualifier");
    typeQualifier->allChildrenAccept(*this);
}





void SemanticCheckVisitor::resetDeclSpecs()
{
    declSpecs.isAdvType = false;
    declSpecs.type = NULL;
    declSpecs.isVoid = false;
    declSpecs.isChar = false;
    declSpecs.isSigned = false;
    declSpecs.isUnsigned = false;
    declSpecs.isInt = false;
    declSpecs.isLong = false;
    declSpecs.isShort = false;
    declSpecs.isFloat = false;
    declSpecs.isDouble = false;
}

types::Type* SemanticCheckVisitor::declSpecsToType(astnodes::Declaration* decl)
{
    types::Type* result = NULL;
    
    // check for non-basic types
    if (declSpecs.isAdvType && declSpecs.type != NULL)
    {
        result = declSpecs.type;
    }
    // now check for all the basic types
    else if (declSpecs.isVoid)
    {
        result = new types::Void();
        declSpecs.isVoid = false;
    }
    else if (declSpecs.isFloat)
    {
        result = new types::Float();
        declSpecs.isFloat = false;
    }
    else if (declSpecs.isDouble && declSpecs.isLong)
    {
        result = new types::LongDouble();
        declSpecs.isDouble = false;
        declSpecs.isLong = false;
    }
    else if (declSpecs.isDouble)
    {
        result = new types::Double();
        declSpecs.isDouble = false;
    }
    else if (declSpecs.isChar && declSpecs.isSigned)
    {
        result = new types::SignedChar();
        declSpecs.isSigned = false;
        declSpecs.isChar = false;
    }
    else if (declSpecs.isChar)
    {
        result = new types::UnsignedChar();
        declSpecs.isUnsigned = false;
        declSpecs.isChar = false;
    }
    else if (declSpecs.isShort && declSpecs.isUnsigned)
    {
        result = new types::UnsignedShort();
        declSpecs.isUnsigned = false;
        declSpecs.isShort = false;
        declSpecs.isInt = false;
    }
    else if (declSpecs.isShort)
    {
        result = new types::SignedShort();
        declSpecs.isSigned = false;
        declSpecs.isShort = false;
        declSpecs.isInt = false;
    }

    else if (declSpecs.isLong && declSpecs.isUnsigned)
    {
        result = new types::UnsignedLong();
        declSpecs.isUnsigned = false;
        declSpecs.isLong = false;
        declSpecs.isInt = false;
    }
    else if (declSpecs.isLong)
    {
        result = new types::SignedLong();
        declSpecs.isSigned = false;
        declSpecs.isLong = false;
        declSpecs.isInt = false;
    }
    else if (declSpecs.isUnsigned)
    {
        result = new types::UnsignedInt();
        declSpecs.isUnsigned = false;
        declSpecs.isInt = false;
    }
    else
    {
        result = new types::SignedInt();
        declSpecs.isSigned = false;
        declSpecs.isInt = false;
    }
    
    // if any of the bools are still set, we've got a conflict
    if (   declSpecs.isVoid
        || declSpecs.isChar
        || declSpecs.isSigned
        || declSpecs.isUnsigned
        || declSpecs.isInt
        || declSpecs.isLong
        || declSpecs.isShort
        || declSpecs.isFloat
        || declSpecs.isDouble)
    {
        addError(decl, ERR_CC_DECLSPEC_CONFL);
        return new types::InvalidType();
    }
    
    if (result == NULL)
        throw new errors::InternalCompilerException("something weird has happend during resolution of type specifiers");
    
    return result;
}

void SemanticCheckVisitor::visit(astnodes::TypeSpecifier * typeSpecifier)
{
    throw new errors::InternalCompilerException("Declarator Node is only abstract and cannot be visited");
}

void SemanticCheckVisitor::visit(astnodes::TypeBaseSpecifier * typeBaseSpecifier)
{
    switch(typeBaseSpecifier->token)
    {
        case VOID:
            if (declSpecs.isVoid)
                addError(typeBaseSpecifier, ERR_CC_DECLSPEC_VOID_DUPL);
            else
                declSpecs.isVoid = true;
            break;
        case CHAR:
            if (declSpecs.isChar)
                addError(typeBaseSpecifier, ERR_CC_DECLSPEC_CHAR_DUPL);
            else
                declSpecs.isChar = true;
            break;
        case SHORT:
            if (declSpecs.isShort)
                addError(typeBaseSpecifier, ERR_CC_DECLSPEC_SHORT_DUPL);
            else
                declSpecs.isShort = true;
            break;
        case INT:
            if (declSpecs.isInt)
                addError(typeBaseSpecifier, ERR_CC_DECLSPEC_INT_DUPL);
            else
                declSpecs.isInt = true;
            break;
        case LONG:
            if (declSpecs.isLong)
                addError(typeBaseSpecifier, ERR_CC_DECLSPEC_LONG_DUPL);
            else
                declSpecs.isLong = true;
            break;
        case FLOAT:
            if (declSpecs.isFloat)
                addError(typeBaseSpecifier, ERR_CC_DECLSPEC_FLOAT_DUPL);
            else
                declSpecs.isFloat = true;
            break;
        case DOUBLE:
            if (declSpecs.isDouble)
                addError(typeBaseSpecifier, ERR_CC_DECLSPEC_DOUBLE_DUPL);
            else
                declSpecs.isDouble = true;
            break;
        case SIGNED:
            if (declSpecs.isSigned)
                addError(typeBaseSpecifier, ERR_CC_DECLSPEC_SIGNED_DUPL);
            else if (declSpecs.isUnsigned)
                addError(typeBaseSpecifier, ERR_CC_DECLSPEC_CONFL_SIGNED);
            else
                declSpecs.isSigned = true;
            break;
        case UNSIGNED:
            if (declSpecs.isUnsigned)
                addError(typeBaseSpecifier, ERR_CC_DECLSPEC_UNSIGNED_DUPL);
            else if (declSpecs.isSigned)
                addError(typeBaseSpecifier, ERR_CC_DECLSPEC_CONFL_SIGNED);
            else
                declSpecs.isUnsigned = true;
            break;
        default:
            throw new errors::InternalCompilerException("unkown type specifier encountered");
    }
}



void SemanticCheckVisitor::visit(astnodes::StructUnionSpecifier * structUnionSpecifier)
{
    printAstName("StructUnionSpecifier");
    structUnionSpecifier->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::EnumSpecifier * enumSpecifier)
{
    printAstName("EnumSpecifier");
    enumSpecifier->allChildrenAccept(*this);
}



void SemanticCheckVisitor::visit(astnodes::TypeNameSpecifier * typeNameSpecifier)
{
    printAstName("TypeNameSpecifier");
    typeNameSpecifier->allChildrenAccept(*this);
}



void SemanticCheckVisitor::visit(astnodes::StorageSpecifier * storageSpecifier)
{
    printAstName("StorageSpecifier");
    storageSpecifier->allChildrenAccept(*this);
}




/*######################################*/
/*      3.3 Expressions                 */
/*######################################*/


/******************************/
/*  3.3.1 Primary expressions */
/******************************/

/* identifier */

void SemanticCheckVisitor::visit(astnodes::Identifier * identifier)
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

void SemanticCheckVisitor::visit(astnodes::CharacterLiteral * characterLiteral)
{
    characterLiteral->valType = new valuetypes::CValue(new types::UnsignedChar());
}


void SemanticCheckVisitor::visit(astnodes::SignedIntLiteral * signedIntLiteral)
{
    signedIntLiteral->valType = new valuetypes::CValue(new types::SignedInt());
}


void SemanticCheckVisitor::visit(astnodes::UnsignedIntLiteral * unsignedIntLiteral)
{
    unsignedIntLiteral->valType = new valuetypes::CValue(new types::UnsignedInt());
}


void SemanticCheckVisitor::visit(astnodes::SignedLongLiteral * signedLongLiteral)
{
    signedLongLiteral->valType = new valuetypes::CValue(new types::SignedLong());
}


void SemanticCheckVisitor::visit(astnodes::UnsignedLongLiteral * unsignedLongLiteral)
{
    unsignedLongLiteral->valType = new valuetypes::CValue(new types::UnsignedLong());
}


void SemanticCheckVisitor::visit(astnodes::FloatLiteral * floatLiteral)
{
    floatLiteral->valType = new valuetypes::CValue(new types::Float());
}


void SemanticCheckVisitor::visit(astnodes::DoubleLiteral * doubleLiteral)
{
    doubleLiteral->valType = new valuetypes::CValue(new types::Double());
}


void SemanticCheckVisitor::visit(astnodes::LongDoubleLiteral * longDoubleLiteral)
{
    longDoubleLiteral->valType = new valuetypes::CValue(new types::LongDouble());
}


/* string literal */

void SemanticCheckVisitor::visit(astnodes::StringLiteral * stringLiteral)
{
   stringLiteral->valType = new valuetypes::LValue(new types::ArrayType(new types::UnsignedChar(), stringLiteral->str.length()));
}




/******************************/
/*  3.3.2 Postfix expressions */
/******************************/

/* 3.3.2.1 array subscripting */

void SemanticCheckVisitor::visit(astnodes::ArrayAccessOperator * arrayAccessOperator)
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

void SemanticCheckVisitor::visit(astnodes::MethodCall * methodCall)
{
    // analyse lhs and all arguments
    methodCall->allChildrenAccept(*this);
    
    // check LHS type
    types::Type* lhsType = methodCall->lhsExpr->valType->type;
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
    
    // now we are sure it is a pointer to a function, get the functiontype
    types::FunctionType* funType = types::IsTypeHelper::getFunctionType(types::IsTypeHelper::getPointerType(lhsType)->baseType);
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

void SemanticCheckVisitor::visit(astnodes::StructureResolutionOperator * structureResolutionOperator)
{
    // TODO FIXME TODO FIXME
    // TODO implement structs properly
    printAstName("StructureResolutionOperator");
    structureResolutionOperator->allChildrenAccept(*this);
}


/* 3.3.2.4 Postfix increment and decrement operators */

void SemanticCheckVisitor::visit(astnodes::PostIncDec * postIncDec)
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

void SemanticCheckVisitor::visit(astnodes::PreIncDec * preIncDec)
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

void SemanticCheckVisitor::visit(astnodes::UnaryOperator * unaryOperator)
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

void SemanticCheckVisitor::visit(astnodes::SizeOfOperator * sizeOfOperator)
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

void SemanticCheckVisitor::visit(astnodes::ExplicitCastOperator * explicitCastOperator)
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

void SemanticCheckVisitor::visit(astnodes::BinaryOperator * binaryOperator)
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
            std::cout << "bin add with types " << lhsType->toString() << ", " << rhsType->toString() << std::endl;
            std::cout << "are arithmetic? " << types::IsTypeHelper::isArithmeticType(lhsType) << ", " << types::IsTypeHelper::isArithmeticType(rhsType) << std::endl;
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
 
void SemanticCheckVisitor::visit(astnodes::ConditionalOperator * conditionalOperator)
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

void SemanticCheckVisitor::visit(astnodes::AssignmentOperator * assignmentOperator)
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

void SemanticCheckVisitor::visit(astnodes::ChainExpressions * chainExpressions)
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





void SemanticCheckVisitor::visit(astnodes::Enumerator * enumerator)
{
    printAstName("Enumerator");
    enumerator->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::AssemblyStatement * assemblyStatement)
{
    printAstName("AssemblyStatement");
    assemblyStatement->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::BuiltInVaStart * builtInVaStart)
{
    printAstName("BuiltInVaStart");
    builtInVaStart->allChildrenAccept(*this);
}

