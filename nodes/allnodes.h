///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       allnodes.h
/// @brief      Includes all AST Nodes.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_AST_NODES_ALLNODES_H
#define __DCPU_CC_AST_NODES_ALLNODES_H

/*
 * Simply includes all nodes
 * 
 * When adding new nodes, just bash this: 
 *      $ for i in *.h; do echo "#include \"$i\""; done
 * in the wd 'nodes/'. Copy&Paste and then remove the allnodes.h and Node.h
 * and include Node.h first.
 * 
 * We don't want to make our lives too complicated ;)
 */

// first include Node.h
#include "Node.h"

// then all other nodes:
#include "ArrayAccessOperator.h"
#include "ArrayDeclarator.h"
#include "AssignmentOperator.h"
#include "BinaryOperator.h"
#include "BlockStatement.h"
#include "BreakStatement.h"
#include "CaseStatement.h"
#include "ChainExpressions.h"
#include "ConditionalOperator.h"
#include "Constant.h"
#include "ContinueStatement.h"
#include "Declaration.h"
#include "Declarations.h"
#include "DeclarationSpecifiers.h"
#include "Declarator.h"
#include "Declarators.h"
#include "DefaultStatement.h"
#include "DoWhileStatement.h"
#include "EmptyStatement.h"
#include "ExplicitCastOperator.h"
#include "Expression.h"
#include "Expressions.h"
#include "ExpressionStatement.h"
#include "ExternalDeclaration.h"
#include "ExternalDeclarations.h"
#include "ForStatement.h"
#include "FunctionDeclarator.h"
#include "FunctionDefinition.h"
#include "GotoStatement.h"
#include "IdentifierDeclarator.h"
#include "Identifier.h"
#include "IfStatement.h"
#include "LabelStatement.h"
#include "MethodCall.h"
#include "NoIdentifierDeclarator.h"
#include "ParameterDeclarations.h"
#include "Pointer.h"
#include "Pointers.h"
#include "PostIncDec.h"
#include "PreIncDec.h"
#include "Program.h"
#include "ReturnStatement.h"
#include "SizeOfOperator.h"
#include "Statement.h"
#include "Statements.h"
#include "StorageSpecifier.h"
#include "StringLiteral.h"
#include "SwitchStatement.h"
#include "TypeBaseSpecifier.h"
#include "TypeName.h"
#include "TypeNameSpecifier.h"
#include "TypeQualifier.h"
#include "TypeQualifiers.h"
#include "TypeSpecifier.h"
#include "UnaryOperator.h"
#include "WhileStatement.h"

#include <visitor/Visitor.h>

#endif

///
/// @}
///
