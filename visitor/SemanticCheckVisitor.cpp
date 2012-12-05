#include "SemanticCheckVisitor.h"
#include <iostream>
#include <string>
#include <deque>
#include <utility>


using namespace dtcc;
using namespace dtcc::visitor;

/* constructor */

SemanticCheckVisitor::SemanticCheckVisitor()
{
    this->m_loopStack = std::deque<std::pair<astnodes::LabelStatement*, astnodes::LabelStatement*> >();
    this->m_symbolTable = new symboltable::SymbolTable();
    this->m_errorList = errors::ErrorList();
}

// TODO this is just while dev, to be removed in final version:
void SemanticCheckVisitor::printAstName(const char * name)
{
    std::cout << "TODO implement semantic check for node '" << name << "'." << std::endl;
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
    // TODO this is a tough one
    functionDefinition->allChildrenAccept(*this);
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
    
}


void SemanticCheckVisitor::visit(astnodes::BreakStatement * breakStatement)
{
    printAstName("BreakStatement");
    breakStatement->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::Expression * expression)
{
    printAstName("Expression");
    expression->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::Statement * statement)
{
    printAstName("Statement");
    statement->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::ExternalDeclaration * externalDeclaration)
{
    printAstName("ExternalDeclaration");
    externalDeclaration->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::ReturnStatement * returnStatement)
{
    printAstName("ReturnStatement");
    returnStatement->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::ForStatement * forStatement)
{
    printAstName("ForStatement");
    forStatement->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::DoWhileStatement * doWhileStatement)
{
    printAstName("DoWhileStatement");
    doWhileStatement->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::WhileStatement * whileStatement)
{
    printAstName("WhileStatement");
    whileStatement->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::SwitchStatement * switchStatement)
{
    printAstName("SwitchStatement");
    switchStatement->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::IfStatement * ifStatement)
{
    printAstName("IfStatement");
    ifStatement->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::ExpressionStatement * expressionStatement)
{
    printAstName("ExpressionStatement");
    expressionStatement->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::EmptyStatement * emptyStatement)
{
    printAstName("EmptyStatement");
    emptyStatement->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::BlockStatement * blockStatement)
{
    printAstName("BlockStatement");
    blockStatement->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::DefaultStatement * defaultStatement)
{
    printAstName("DefaultStatement");
    defaultStatement->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::CaseStatement * caseStatement)
{
    printAstName("CaseStatement");
    caseStatement->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::LabelStatement * labelStatement)
{
    printAstName("LabelStatement");
    labelStatement->allChildrenAccept(*this);
}


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


void SemanticCheckVisitor::visit(astnodes::AssignmentOperator * assignmentOperator)
{
    printAstName("AssignmentOperator");
    assignmentOperator->allChildrenAccept(*this);
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


void SemanticCheckVisitor::visit(astnodes::ArrayAccessOperator * arrayAccessOperator)
{
    printAstName("ArrayAccessOperator");
    arrayAccessOperator->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::StringLiteral * stringLiteral)
{
    printAstName("StringLiteral");
    stringLiteral->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::Constant * constant)
{
    printAstName("Constant");
    constant->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::Identifier * identifier)
{
    printAstName("Identifier");
    identifier->allChildrenAccept(*this);
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


void SemanticCheckVisitor::visit(astnodes::CharacterLiteral * characterLiteral)
{
    printAstName("CharacterLiteral");
    characterLiteral->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::SignedIntLiteral * signedIntLiteral)
{
    printAstName("SignedIntLiteral");
    signedIntLiteral->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::UnsignedIntLiteral * unsignedIntLiteral)
{
    printAstName("UnsignedIntLiteral");
    unsignedIntLiteral->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::SignedLongLiteral * signedLongLiteral)
{
    printAstName("SignedLongLiteral");
    signedLongLiteral->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::UnsignedLongLiteral * unsignedLongLiteral)
{
    printAstName("UnsignedLongLiteral");
    unsignedLongLiteral->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::FloatLiteral * floatLiteral)
{
    printAstName("FloatLiteral");
    floatLiteral->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::DoubleLiteral * doubleLiteral)
{
    printAstName("DoubleLiteral");
    doubleLiteral->allChildrenAccept(*this);
}


void SemanticCheckVisitor::visit(astnodes::LongDoubleLiteral * longDoubleLiteral)
{
    printAstName("LongDoubleLiteral");
    longDoubleLiteral->allChildrenAccept(*this);
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

