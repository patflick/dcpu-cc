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

#include <valuetypes/ValueType.h>
#include <valuetypes/FunctionDesignator.h>
#include <valuetypes/LValue.h>
#include <valuetypes/RValue.h>
#include <valuetypes/CValue.h>

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
    return this->m_invalidValType;
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
    printAstName("Declarator");
    declarator->allChildrenAccept(*this);
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


void SemanticCheckVisitor::visit(astnodes::TypeSpecifier * typeSpecifier)
{
    printAstName("TypeSpecifier");
    typeSpecifier->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::TypeNameSpecifier * typeNameSpecifier)
{
    printAstName("TypeNameSpecifier");
    typeNameSpecifier->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::TypeBaseSpecifier * typeBaseSpecifier)
{
    printAstName("TypeBaseSpecifier");
    typeBaseSpecifier->allChildrenAccept(*this);
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
        // don't handle anything below
        return;
    }
    
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




void SemanticCheckVisitor::visit(astnodes::AssignmentOperator * assignmentOperator)
{
    // first check lhs and rhs expression
    assignmentOperator->allChildrenAccept(*this);
    
    // TODO check compatible types
}


void SemanticCheckVisitor::visit(astnodes::ConditionalOperator * conditionalOperator)
{
    printAstName("ConditionalOperator");
    conditionalOperator->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::BinaryOperator * binaryOperator)
{
    printAstName("BinaryOperator");
    binaryOperator->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::ExplicitCastOperator * explicitCastOperator)
{
    printAstName("ExplicitCastOperator");
    explicitCastOperator->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::SizeOfOperator * sizeOfOperator)
{
    printAstName("SizeOfOperator");
    sizeOfOperator->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::UnaryOperator * unaryOperator)
{
    printAstName("UnaryOperator");
    unaryOperator->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::PreIncDec * preIncDec)
{
    printAstName("PreIncDec");
    preIncDec->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::PostIncDec * postIncDec)
{
    printAstName("PostIncDec");
    postIncDec->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::MethodCall * methodCall)
{
    printAstName("MethodCall");
    methodCall->allChildrenAccept(*this);
}




void SemanticCheckVisitor::visit(astnodes::Constant * constant)
{
    printAstName("Constant");
    constant->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::ChainExpressions * chainExpressions)
{
    printAstName("ChainExpressions");
    chainExpressions->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::Program * program)
{
    printAstName("Program");
    program->allChildrenAccept(*this);
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


void SemanticCheckVisitor::visit(astnodes::Enumerator * enumerator)
{
    printAstName("Enumerator");
    enumerator->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::StructureResolutionOperator * structureResolutionOperator)
{
    printAstName("StructureResolutionOperator");
    structureResolutionOperator->allChildrenAccept(*this);
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

