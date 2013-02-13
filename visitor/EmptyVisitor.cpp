///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Visitor
/// @{
///

///
/// @file       EmptyVisitor.cpp
/// @brief      Definitions of the EmptyVisitor class.
/// @author     Patrick Flick
///

#include "EmptyVisitor.h"
#include <iostream>
#include <string>

using namespace dcpucc;
using namespace dcpucc::visitor;

void EmptyVisitor::visit(astnodes::FunctionDefinition * functionDefinition)
{
}


void EmptyVisitor::visit(astnodes::GotoStatement * gotoStatement)
{
}


void EmptyVisitor::visit(astnodes::ContinueStatement * continueStatement)
{
}


void EmptyVisitor::visit(astnodes::BreakStatement * breakStatement)
{
}


void EmptyVisitor::visit(astnodes::Expression * expression)
{
}


void EmptyVisitor::visit(astnodes::Statement * statement)
{
}


void EmptyVisitor::visit(astnodes::ExternalDeclaration * externalDeclaration)
{
}


void EmptyVisitor::visit(astnodes::ReturnStatement * returnStatement)
{
}


void EmptyVisitor::visit(astnodes::ForStatement * forStatement)
{
}


void EmptyVisitor::visit(astnodes::DoWhileStatement * doWhileStatement)
{
}


void EmptyVisitor::visit(astnodes::WhileStatement * whileStatement)
{
}


void EmptyVisitor::visit(astnodes::SwitchStatement * switchStatement)
{
}


void EmptyVisitor::visit(astnodes::IfStatement * ifStatement)
{
}


void EmptyVisitor::visit(astnodes::ExpressionStatement * expressionStatement)
{
}


void EmptyVisitor::visit(astnodes::EmptyStatement * emptyStatement)
{
}


void EmptyVisitor::visit(astnodes::BlockStatement * blockStatement)
{
}


void EmptyVisitor::visit(astnodes::DefaultStatement * defaultStatement)
{
}


void EmptyVisitor::visit(astnodes::CaseStatement * caseStatement)
{
}


void EmptyVisitor::visit(astnodes::LabelStatement * labelStatement)
{
}


void EmptyVisitor::visit(astnodes::Declarator * declarator)
{
}


void EmptyVisitor::visit(astnodes::FunctionDeclarator * functionDeclarator)
{
}


void EmptyVisitor::visit(astnodes::NoIdentifierDeclarator * noIdentifierDeclarator)
{
}


void EmptyVisitor::visit(astnodes::IdentifierDeclarator * identifierDeclarator)
{
}


void EmptyVisitor::visit(astnodes::ArrayDeclarator * arrayDeclarator)
{
}


void EmptyVisitor::visit(astnodes::TypeName * typeName)
{
}


void EmptyVisitor::visit(astnodes::Declaration * declaration)
{
}


void EmptyVisitor::visit(astnodes::Pointer * pointer)
{
}


void EmptyVisitor::visit(astnodes::TypeQualifier * typeQualifier)
{
}


void EmptyVisitor::visit(astnodes::TypeSpecifier * typeSpecifier)
{
}


void EmptyVisitor::visit(astnodes::TypeNameSpecifier * typeNameSpecifier)
{
}


void EmptyVisitor::visit(astnodes::TypeBaseSpecifier * typeBaseSpecifier)
{
}


void EmptyVisitor::visit(astnodes::StorageSpecifier * storageSpecifier)
{
}


void EmptyVisitor::visit(astnodes::AssignmentOperator * assignmentOperator)
{
}


void EmptyVisitor::visit(astnodes::ConditionalOperator * conditionalOperator)
{
}


void EmptyVisitor::visit(astnodes::BinaryOperator * binaryOperator)
{
}


void EmptyVisitor::visit(astnodes::ExplicitCastOperator * explicitCastOperator)
{
}


void EmptyVisitor::visit(astnodes::SizeOfOperator * sizeOfOperator)
{
}


void EmptyVisitor::visit(astnodes::UnaryOperator * unaryOperator)
{
}


void EmptyVisitor::visit(astnodes::PreIncDec * preIncDec)
{
}


void EmptyVisitor::visit(astnodes::PostIncDec * postIncDec)
{
}


void EmptyVisitor::visit(astnodes::MethodCall * methodCall)
{
}


void EmptyVisitor::visit(astnodes::ArrayAccessOperator * arrayAccessOperator)
{
}


void EmptyVisitor::visit(astnodes::StringLiteral * stringLiteral)
{
}


void EmptyVisitor::visit(astnodes::Identifier * identifier)
{
}


void EmptyVisitor::visit(astnodes::ChainExpressions * chainExpressions)
{
}


void EmptyVisitor::visit(astnodes::Program * program)
{
}


void EmptyVisitor::visit(astnodes::StructUnionSpecifier * structUnionSpecifier)
{
}


void EmptyVisitor::visit(astnodes::EnumSpecifier * enumSpecifier)
{
}


void EmptyVisitor::visit(astnodes::Enumerator * enumerator)
{
}


void EmptyVisitor::visit(astnodes::StructureResolutionOperator * structureResolutionOperator)
{
}


void EmptyVisitor::visit(astnodes::CharacterLiteral * characterLiteral)
{
}


void EmptyVisitor::visit(astnodes::SignedIntLiteral * signedIntLiteral)
{
}


void EmptyVisitor::visit(astnodes::UnsignedIntLiteral * unsignedIntLiteral)
{
}


void EmptyVisitor::visit(astnodes::SignedLongLiteral * signedLongLiteral)
{
}


void EmptyVisitor::visit(astnodes::UnsignedLongLiteral * unsignedLongLiteral)
{
}


void EmptyVisitor::visit(astnodes::FloatLiteral * floatLiteral)
{
}


void EmptyVisitor::visit(astnodes::DoubleLiteral * doubleLiteral)
{
}


void EmptyVisitor::visit(astnodes::LongDoubleLiteral * longDoubleLiteral)
{
}


void EmptyVisitor::visit(astnodes::AssemblyStatement * assemblyStatement)
{
}


void EmptyVisitor::visit(astnodes::BuiltInVaStart * builtInVaStart)
{
}

void EmptyVisitor::visit(astnodes::AddressOfOperator * addressOfOperator)
{
}

void EmptyVisitor::visit(astnodes::DerefOperator * derefOperator)
{
}

void EmptyVisitor::visit(astnodes::TypeConversionOperator * typeConversionOperator)
{
}

void EmptyVisitor::visit(astnodes::StructMemberDeclarator * structMem)
{
}

///
/// @}
///
