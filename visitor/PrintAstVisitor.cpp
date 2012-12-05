#include "PrintAstVisitor.h"
#include <iostream>
#include <string>
using namespace dtcc::visitor;


void PrintAstVisitor::printAstName(const char * name)
{
    std::string str(name);
    for (int i = 4; i < this->identation; i++)
        std::cout << " ";
    if (this->identation > 3)
        std::cout << "|---";
    std::cout << str << std::endl;
}

void PrintAstVisitor::increaseIdentation()
{
    this->identation += 4;
}

void PrintAstVisitor::decreaseIdentation()
{
    this->identation -= 4;
}

void PrintAstVisitor::visit(astnodes::FunctionDefinition * functionDefinition)
{
    printAstName("FunctionDefinition");
    increaseIdentation();
    functionDefinition->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::GotoStatement * gotoStatement)
{
    printAstName("GotoStatement");
    increaseIdentation();
    gotoStatement->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::ContinueStatement * continueStatement)
{
    printAstName("ContinueStatement");
    increaseIdentation();
    continueStatement->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::BreakStatement * breakStatement)
{
    printAstName("BreakStatement");
    increaseIdentation();
    breakStatement->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::Expression * expression)
{
    printAstName("Expression");
    increaseIdentation();
    expression->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::Statement * statement)
{
    printAstName("Statement");
    increaseIdentation();
    statement->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::ExternalDeclaration * externalDeclaration)
{
    printAstName("ExternalDeclaration");
    increaseIdentation();
    externalDeclaration->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::ReturnStatement * returnStatement)
{
    printAstName("ReturnStatement");
    increaseIdentation();
    returnStatement->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::ForStatement * forStatement)
{
    printAstName("ForStatement");
    increaseIdentation();
    forStatement->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::DoWhileStatement * doWhileStatement)
{
    printAstName("DoWhileStatement");
    increaseIdentation();
    doWhileStatement->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::WhileStatement * whileStatement)
{
    printAstName("WhileStatement");
    increaseIdentation();
    whileStatement->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::SwitchStatement * switchStatement)
{
    printAstName("SwitchStatement");
    increaseIdentation();
    switchStatement->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::IfStatement * ifStatement)
{
    printAstName("IfStatement");
    increaseIdentation();
    ifStatement->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::ExpressionStatement * expressionStatement)
{
    printAstName("ExpressionStatement");
    increaseIdentation();
    expressionStatement->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::EmptyStatement * emptyStatement)
{
    printAstName("EmptyStatement");
    increaseIdentation();
    emptyStatement->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::BlockStatement * blockStatement)
{
    printAstName("BlockStatement");
    increaseIdentation();
    blockStatement->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::DefaultStatement * defaultStatement)
{
    printAstName("DefaultStatement");
    increaseIdentation();
    defaultStatement->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::CaseStatement * caseStatement)
{
    printAstName("CaseStatement");
    increaseIdentation();
    caseStatement->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::LabelStatement * labelStatement)
{
    printAstName("LabelStatement");
    increaseIdentation();
    labelStatement->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::Declarator * declarator)
{
    printAstName("Declarator");
    increaseIdentation();
    declarator->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::FunctionDeclarator * functionDeclarator)
{
    printAstName("FunctionDeclarator");
    increaseIdentation();
    functionDeclarator->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::NoIdentifierDeclarator * noIdentifierDeclarator)
{
    printAstName("NoIdentifierDeclarator");
    increaseIdentation();
    noIdentifierDeclarator->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::IdentifierDeclarator * identifierDeclarator)
{
    printAstName("IdentifierDeclarator");
    increaseIdentation();
    identifierDeclarator->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::ArrayDeclarator * arrayDeclarator)
{
    printAstName("ArrayDeclarator");
    increaseIdentation();
    arrayDeclarator->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::TypeName * typeName)
{
    printAstName("TypeName");
    increaseIdentation();
    typeName->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::Declaration * declaration)
{
    printAstName("Declaration");
    increaseIdentation();
    declaration->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::Pointer * pointer)
{
    printAstName("Pointer");
    increaseIdentation();
    pointer->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::TypeQualifier * typeQualifier)
{
    printAstName("TypeQualifier");
    increaseIdentation();
    typeQualifier->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::TypeSpecifier * typeSpecifier)
{
    printAstName("TypeSpecifier");
    increaseIdentation();
    typeSpecifier->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::TypeNameSpecifier * typeNameSpecifier)
{
    printAstName("TypeNameSpecifier");
    increaseIdentation();
    typeNameSpecifier->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::TypeBaseSpecifier * typeBaseSpecifier)
{
    printAstName("TypeBaseSpecifier");
    increaseIdentation();
    typeBaseSpecifier->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::StorageSpecifier * storageSpecifier)
{
    printAstName("StorageSpecifier");
    increaseIdentation();
    storageSpecifier->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::AssignmentOperator * assignmentOperator)
{
    printAstName("AssignmentOperator");
    increaseIdentation();
    assignmentOperator->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::ConditionalOperator * conditionalOperator)
{
    printAstName("ConditionalOperator");
    increaseIdentation();
    conditionalOperator->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::BinaryOperator * binaryOperator)
{
    printAstName("BinaryOperator");
    increaseIdentation();
    binaryOperator->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::ExplicitCastOperator * explicitCastOperator)
{
    printAstName("ExplicitCastOperator");
    increaseIdentation();
    explicitCastOperator->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::SizeOfOperator * sizeOfOperator)
{
    printAstName("SizeOfOperator");
    increaseIdentation();
    sizeOfOperator->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::UnaryOperator * unaryOperator)
{
    printAstName("UnaryOperator");
    increaseIdentation();
    unaryOperator->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::PreIncDec * preIncDec)
{
    printAstName("PreIncDec");
    increaseIdentation();
    preIncDec->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::PostIncDec * postIncDec)
{
    printAstName("PostIncDec");
    increaseIdentation();
    postIncDec->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::MethodCall * methodCall)
{
    printAstName("MethodCall");
    increaseIdentation();
    methodCall->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::ArrayAccessOperator * arrayAccessOperator)
{
    printAstName("ArrayAccessOperator");
    increaseIdentation();
    arrayAccessOperator->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::StringLiteral * stringLiteral)
{
    printAstName("StringLiteral");
    increaseIdentation();
    stringLiteral->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::Constant * constant)
{
    printAstName("Constant");
    increaseIdentation();
    constant->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::Identifier * identifier)
{
    printAstName("Identifier");
    increaseIdentation();
    identifier->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::ChainExpressions * chainExpressions)
{
    printAstName("ChainExpressions");
    increaseIdentation();
    chainExpressions->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::Program * program)
{
    printAstName("Program");
    increaseIdentation();
    program->allChildrenAccept(*this);
    decreaseIdentation();
}

void PrintAstVisitor::visit(astnodes::StructUnionSpecifier * structUnionSpecifier)
{
    printAstName("StructUnionSpecifier");
    increaseIdentation();
    structUnionSpecifier->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::EnumSpecifier * enumSpecifier)
{
    printAstName("EnumSpecifier");
    increaseIdentation();
    enumSpecifier->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::Enumerator * enumerator)
{
    printAstName("Enumerator");
    increaseIdentation();
    enumerator->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::StructureResolutionOperator * structureResolutionOperator)
{
    printAstName("StructureResolutionOperator");
    increaseIdentation();
    structureResolutionOperator->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::CharacterLiteral * characterLiteral)
{
    printAstName("CharacterLiteral");
    increaseIdentation();
    characterLiteral->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::SignedIntLiteral * signedIntLiteral)
{
    printAstName("SignedIntLiteral");
    increaseIdentation();
    signedIntLiteral->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::UnsignedIntLiteral * unsignedIntLiteral)
{
    printAstName("UnsignedIntLiteral");
    increaseIdentation();
    unsignedIntLiteral->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::SignedLongLiteral * signedLongLiteral)
{
    printAstName("SignedLongLiteral");
    increaseIdentation();
    signedLongLiteral->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::UnsignedLongLiteral * unsignedLongLiteral)
{
    printAstName("UnsignedLongLiteral");
    increaseIdentation();
    unsignedLongLiteral->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::FloatLiteral * floatLiteral)
{
    printAstName("FloatLiteral");
    increaseIdentation();
    floatLiteral->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::DoubleLiteral * doubleLiteral)
{
    printAstName("DoubleLiteral");
    increaseIdentation();
    doubleLiteral->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::LongDoubleLiteral * longDoubleLiteral)
{
    printAstName("LongDoubleLiteral");
    increaseIdentation();
    longDoubleLiteral->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::AssemblyStatement * assemblyStatement)
{
    printAstName("AssemblyStatement");
    increaseIdentation();
    assemblyStatement->allChildrenAccept(*this);
    decreaseIdentation();
}


void PrintAstVisitor::visit(astnodes::BuiltInVaStart * builtInVaStart)
{
    printAstName("BuiltInVaStart");
    increaseIdentation();
    builtInVaStart->allChildrenAccept(*this);
    decreaseIdentation();
}

