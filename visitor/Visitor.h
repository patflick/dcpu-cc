///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Visitor
/// @{
///

///
/// @file       Visitor.h
/// @brief      Declaration of the Visitor interface
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_VISITOR_VISITOR_H
#define __DCPU_CC_VISITOR_VISITOR_H

// include all AST nodes
#include <astnodes/allnodes.h>

namespace dtcc
{
    namespace visitor
    {
        
        ///
        /// @class      Visitor
        /// @brief      The AST Visitor interface.
        ///
        class Visitor
        {
        public:
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param functionDefinition    The node to visit this visitor
            virtual void visit(astnodes::FunctionDefinition * functionDefinition) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param gotoStatement    The node to visit this visitor
            virtual void visit(astnodes::GotoStatement * gotoStatement) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param continueStatement    The node to visit this visitor
            virtual void visit(astnodes::ContinueStatement * continueStatement) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param breakStatement    The node to visit this visitor
            virtual void visit(astnodes::BreakStatement * breakStatement) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param expression    The node to visit this visitor
            virtual void visit(astnodes::Expression * expression) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param statement    The node to visit this visitor
            virtual void visit(astnodes::Statement * statement) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param externalDeclaration    The node to visit this visitor
            virtual void visit(astnodes::ExternalDeclaration * externalDeclaration) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param returnStatement    The node to visit this visitor
            virtual void visit(astnodes::ReturnStatement * returnStatement) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param forStatement    The node to visit this visitor
            virtual void visit(astnodes::ForStatement * forStatement) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param doWhileStatement    The node to visit this visitor
            virtual void visit(astnodes::DoWhileStatement * doWhileStatement) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param whileStatement    The node to visit this visitor
            virtual void visit(astnodes::WhileStatement * whileStatement) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param switchStatement    The node to visit this visitor
            virtual void visit(astnodes::SwitchStatement * switchStatement) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param ifStatement    The node to visit this visitor
            virtual void visit(astnodes::IfStatement * ifStatement) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param expressionStatement    The node to visit this visitor
            virtual void visit(astnodes::ExpressionStatement * expressionStatement) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param emptyStatement    The node to visit this visitor
            virtual void visit(astnodes::EmptyStatement * emptyStatement) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param blockStatement    The node to visit this visitor
            virtual void visit(astnodes::BlockStatement * blockStatement) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param defaultStatement    The node to visit this visitor
            virtual void visit(astnodes::DefaultStatement * defaultStatement) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param caseStatement    The node to visit this visitor
            virtual void visit(astnodes::CaseStatement * caseStatement) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param labelStatement    The node to visit this visitor
            virtual void visit(astnodes::LabelStatement * labelStatement) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param declarator    The node to visit this visitor
            virtual void visit(astnodes::Declarator * declarator) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param functionDeclarator    The node to visit this visitor
            virtual void visit(astnodes::FunctionDeclarator * functionDeclarator) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param noIdentifierDeclarator    The node to visit this visitor
            virtual void visit(astnodes::NoIdentifierDeclarator * noIdentifierDeclarator) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param identifierDeclarator    The node to visit this visitor
            virtual void visit(astnodes::IdentifierDeclarator * identifierDeclarator) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param arrayDeclarator    The node to visit this visitor
            virtual void visit(astnodes::ArrayDeclarator * arrayDeclarator) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param typeName    The node to visit this visitor
            virtual void visit(astnodes::TypeName * typeName) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param declaration    The node to visit this visitor
            virtual void visit(astnodes::Declaration * declaration) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param pointer    The node to visit this visitor
            virtual void visit(astnodes::Pointer * pointer) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param typeQualifier    The node to visit this visitor
            virtual void visit(astnodes::TypeQualifier * typeQualifier) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param typeSpecifier    The node to visit this visitor
            virtual void visit(astnodes::TypeSpecifier * typeSpecifier) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param typeNameSpecifier    The node to visit this visitor
            virtual void visit(astnodes::TypeNameSpecifier * typeNameSpecifier) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param typeBaseSpecifier    The node to visit this visitor
            virtual void visit(astnodes::TypeBaseSpecifier * typeBaseSpecifier) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param storageSpecifier    The node to visit this visitor
            virtual void visit(astnodes::StorageSpecifier * storageSpecifier) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param assignmentOperator    The node to visit this visitor
            virtual void visit(astnodes::AssignmentOperator * assignmentOperator) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param conditionalOperator    The node to visit this visitor
            virtual void visit(astnodes::ConditionalOperator * conditionalOperator) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param binaryOperator    The node to visit this visitor
            virtual void visit(astnodes::BinaryOperator * binaryOperator) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param explicitCastOperator    The node to visit this visitor
            virtual void visit(astnodes::ExplicitCastOperator * explicitCastOperator) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param sizeOfOperator    The node to visit this visitor
            virtual void visit(astnodes::SizeOfOperator * sizeOfOperator) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param unaryOperator    The node to visit this visitor
            virtual void visit(astnodes::UnaryOperator * unaryOperator) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param preIncDec    The node to visit this visitor
            virtual void visit(astnodes::PreIncDec * preIncDec) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param postIncDec    The node to visit this visitor
            virtual void visit(astnodes::PostIncDec * postIncDec) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param methodCall    The node to visit this visitor
            virtual void visit(astnodes::MethodCall * methodCall) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param arrayAccessOperator    The node to visit this visitor
            virtual void visit(astnodes::ArrayAccessOperator * arrayAccessOperator) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param stringLiteral    The node to visit this visitor
            virtual void visit(astnodes::StringLiteral * stringLiteral) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param identifier    The node to visit this visitor
            virtual void visit(astnodes::Identifier * identifier) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param chainExpressions    The node to visit this visitor
            virtual void visit(astnodes::ChainExpressions * chainExpressions) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param program    The node to visit this visitor
            virtual void visit(astnodes::Program * program) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param structUnionSpecifier    The node to visit this visitor
            virtual void visit(astnodes::StructUnionSpecifier * structUnionSpecifier) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param enumSpecifier    The node to visit this visitor
            virtual void visit(astnodes::EnumSpecifier * enumSpecifier) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param enumerator    The node to visit this visitor
            virtual void visit(astnodes::Enumerator * enumerator) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param structureResolutionOperator    The node to visit this visitor
            virtual void visit(astnodes::StructureResolutionOperator * structureResolutionOperator) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param characterLiteral    The node to visit this visitor
            virtual void visit(astnodes::CharacterLiteral * characterLiteral) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param signedIntLiteral    The node to visit this visitor
            virtual void visit(astnodes::SignedIntLiteral * signedIntLiteral) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param unsignedIntLiteral    The node to visit this visitor
            virtual void visit(astnodes::UnsignedIntLiteral * unsignedIntLiteral) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param signedLongLiteral    The node to visit this visitor
            virtual void visit(astnodes::SignedLongLiteral * signedLongLiteral) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param unsignedLongLiteral    The node to visit this visitor
            virtual void visit(astnodes::UnsignedLongLiteral * unsignedLongLiteral) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param floatLiteral    The node to visit this visitor
            virtual void visit(astnodes::FloatLiteral * floatLiteral) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param doubleLiteral    The node to visit this visitor
            virtual void visit(astnodes::DoubleLiteral * doubleLiteral) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param longDoubleLiteral    The node to visit this visitor
            virtual void visit(astnodes::LongDoubleLiteral * longDoubleLiteral) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param assemblyStatement    The node to visit this visitor
            virtual void visit(astnodes::AssemblyStatement * assemblyStatement) = 0;
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param builtInVaStart    The node to visit this visitor
            virtual void visit(astnodes::BuiltInVaStart * builtInVaStart) = 0;
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param addressOfOperator    The node to visit this visitor
            virtual void visit(astnodes::AddressOfOperator * addressOfOperator) = 0;
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param derefOperator    The node to visit this visitor
            virtual void visit(astnodes::DerefOperator * derefOperator) = 0;
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param typeConversionOperator    The node to visit this visitor
            virtual void visit(astnodes::TypeConversionOperator * typeConversionOperator) = 0;
        };
        
    } // namespace dtcc
} // namespace astnode

#endif

///
/// @}
///
