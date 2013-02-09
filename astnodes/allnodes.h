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
 *      $ find . -name \*.h -print | sed -rn "s/\.\/([A-Za-z\/]+)\.(h|cpp)/#include \"\1\.\2\"/p" | sort
 * in the wd 'nodes/'. Copy&Paste and then remove the allnodes.h and Node.h
 * and include Node.h first.
 * 
 * We don't want to make our lives too complicated ;)
 */

// first include Node.h
#include "Node.h"

// then all other nodes:
#include "declaration/ArrayDeclarator.h"
#include "declaration/Declaration.h"
#include "declaration/Declarations.h"
#include "declaration/DeclarationSpecifiers.h"
#include "declaration/Declarator.h"
#include "declaration/Declarators.h"
#include "declaration/Enumerator.h"
#include "declaration/Enumerators.h"
#include "declaration/EnumSpecifier.h"
#include "declaration/ExternalDeclaration.h"
#include "declaration/ExternalDeclarations.h"
#include "declaration/FunctionDeclarator.h"
#include "declaration/IdentifierDeclarator.h"
#include "declaration/NoIdentifierDeclarator.h"
#include "declaration/ParameterDeclarations.h"
#include "declaration/Pointer.h"
#include "declaration/Pointers.h"
#include "declaration/StorageSpecifier.h"
#include "declaration/StructUnionSpecifier.h"
#include "declaration/TypeBaseSpecifier.h"
#include "declaration/TypeName.h"
#include "declaration/TypeNameSpecifier.h"
#include "declaration/TypeQualifier.h"
#include "declaration/TypeQualifiers.h"
#include "declaration/TypeSpecifier.h"
#include "expression/AddressOfOperator.h"
#include "expression/ArrayAccessOperator.h"
#include "expression/AssignmentOperator.h"
#include "expression/BinaryOperator.h"
#include "expression/ChainExpressions.h"
#include "expression/ConditionalOperator.h"
#include "expression/DerefOperator.h"
#include "expression/ExplicitCastOperator.h"
#include "expression/Expression.h"
#include "expression/Expressions.h"
#include "expression/Identifier.h"
#include "expression/literals/CharacterLiteral.h"
#include "expression/literals/DoubleLiteral.h"
#include "expression/literals/FloatLiteral.h"
#include "expression/literals/LongDoubleLiteral.h"
#include "expression/literals/SignedIntLiteral.h"
#include "expression/literals/SignedLongLiteral.h"
#include "expression/literals/StringLiteral.h"
#include "expression/literals/UnsignedIntLiteral.h"
#include "expression/literals/UnsignedLongLiteral.h"
#include "expression/MethodCall.h"
#include "expression/PostIncDec.h"
#include "expression/PreIncDec.h"
#include "expression/SizeOfOperator.h"
#include "expression/StructureResolutionOperator.h"
#include "expression/TypeConversionOperator.h"
#include "expression/UnaryOperator.h"
#include "extensions/AssemblyStatement.h"
#include "extensions/BuiltInVaStart.h"
#include "FunctionDefinition.h"
#include "Program.h"
#include "statement/BlockStatement.h"
#include "statement/BreakStatement.h"
#include "statement/CaseStatement.h"
#include "statement/ContinueStatement.h"
#include "statement/DefaultStatement.h"
#include "statement/DoWhileStatement.h"
#include "statement/EmptyStatement.h"
#include "statement/ExpressionStatement.h"
#include "statement/ForStatement.h"
#include "statement/GotoStatement.h"
#include "statement/IfStatement.h"
#include "statement/LabelStatement.h"
#include "statement/ReturnStatement.h"
#include "statement/Statement.h"
#include "statement/Statements.h"
#include "statement/SwitchStatement.h"
#include "statement/WhileStatement.h"

#include <visitor/Visitor.h>

#endif

///
/// @}
///
