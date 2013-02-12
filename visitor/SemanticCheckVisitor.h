///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Visitor
/// @{
///

///
/// @file       SemanticCheckVisitor.h
/// @brief      Declaration of the Visitor interface
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_VISITOR_SEMANTIC_CHECK_VISITOR_H
#define __DCPU_CC_VISITOR_SEMANTIC_CHECK_VISITOR_H

// include all AST nodes
#include <astnodes/allnodes.h>
#include "Visitor.h"
#include <symboltable/SymbolTable.h>
#include <errors/ErrorList.h>
#include <errors/derr.defs.h>
#include <visitor/GotoResolvalVisitor.h>
#include <deque>
#include <set>
#include <string>

namespace dcpucc
{
    namespace visitor
    {
        
        ///
        /// @class      SemanticCheckVisitor
        /// @brief      Visitor for semantic check and type resolution.
        ///
        class SemanticCheckVisitor : public Visitor
        {
            
            friend class GotoResolvalVisitor;
            
        private:
            /* errors and warnings */
            void addError(astnodes::Node* node, int errid);
            void addError(astnodes::Node* node, int errid, std::string msg);
            void addWarning(astnodes::Node* node, int errid);
            void addWarning(astnodes::Node* node, int errid, std::string msg);
            
            /* the symbol table */
            symboltable::SymbolTable* m_symbolTable;
            
            /* break and continue label management */
            std::deque<std::pair<astnodes::LabelStatement*, astnodes::LabelStatement*> > m_loopStack;
            void initLoopStack();
            void popLoopStack();
            void pushLoopStack(astnodes::LabelStatement* breakLabel, astnodes::LabelStatement* continueLabel);
            astnodes::LabelStatement* getBreakLabel();
            astnodes::LabelStatement* getContinueLabel();
            
            /* automatic/random label management */
            astnodes::LabelStatement* getRandomLabel(std::string prefix);
            
            /* general label management */
            std::map<std::string, astnodes::LabelStatement*> m_funcLabels;
            
            /* stack for switch-statements */
            // this is needed by case and default statements
            std::deque<astnodes::SwitchStatement*> m_switchStack;
            
            
            /* type management */
            valuetypes::ValueType* m_invalidValType;
            valuetypes::ValueType* getInvalidValType();
            
            /* declaration specifiers */
            struct DeclSpecs {
                bool isAdvType;
                types::Type* type;
                bool isVoid;
                bool isChar;
                bool isSigned;
                bool isUnsigned;
                bool isInt;
                bool isLong;
                bool isShort;
                bool isFloat;
                bool isDouble;
            } m_declSpecs;
            void resetDeclSpecs();
            types::Type* typeSpecsToType(dcpucc::astnodes::Node* decl);
            types::Type* declSpecsToType(astnodes::DeclarationSpecifiers* declSpecs);
            
            /* declaration handleing */
            enum DeclarationState_t { DECLSTATE_LOCAL, DECLSTATE_GLOBAL, DECLSTATE_PARAM, DECLSTATE_FUNDEF, DECLSTATE_TYPE_ONLY, DECLSTATE_STRUCT};
            DeclarationState_t m_declState;
            types::Type* m_curDeclType;
            astnodes::StorSpec_t m_curStorSpec;
            astnodes::Expressions* m_declarationInitializer;
            std::string m_functionName;
            std::string m_currentFunctionName;
            types::StructUnionType* m_curStructDecl;
            
            
            /* TODO this needs to be removed once work is done on this */
            void printAstName(const char * name);
            
            
            
        public:
            
            SemanticCheckVisitor();
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param functionDefinition    The node to visit this visitor
            virtual void visit(astnodes::FunctionDefinition * functionDefinition);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param gotoStatement    The node to visit this visitor
            virtual void visit(astnodes::GotoStatement * gotoStatement);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param continueStatement    The node to visit this visitor
            virtual void visit(astnodes::ContinueStatement * continueStatement);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param breakStatement    The node to visit this visitor
            virtual void visit(astnodes::BreakStatement * breakStatement);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param expression    The node to visit this visitor
            virtual void visit(astnodes::Expression * expression);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param statement    The node to visit this visitor
            virtual void visit(astnodes::Statement * statement);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param externalDeclaration    The node to visit this visitor
            virtual void visit(astnodes::ExternalDeclaration * externalDeclaration);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param returnStatement    The node to visit this visitor
            virtual void visit(astnodes::ReturnStatement * returnStatement);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param forStatement    The node to visit this visitor
            virtual void visit(astnodes::ForStatement * forStatement);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param doWhileStatement    The node to visit this visitor
            virtual void visit(astnodes::DoWhileStatement * doWhileStatement);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param whileStatement    The node to visit this visitor
            virtual void visit(astnodes::WhileStatement * whileStatement);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param switchStatement    The node to visit this visitor
            virtual void visit(astnodes::SwitchStatement * switchStatement);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param ifStatement    The node to visit this visitor
            virtual void visit(astnodes::IfStatement * ifStatement);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param expressionStatement    The node to visit this visitor
            virtual void visit(astnodes::ExpressionStatement * expressionStatement);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param emptyStatement    The node to visit this visitor
            virtual void visit(astnodes::EmptyStatement * emptyStatement);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param blockStatement    The node to visit this visitor
            virtual void visit(astnodes::BlockStatement * blockStatement);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param defaultStatement    The node to visit this visitor
            virtual void visit(astnodes::DefaultStatement * defaultStatement);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param caseStatement    The node to visit this visitor
            virtual void visit(astnodes::CaseStatement * caseStatement);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param labelStatement    The node to visit this visitor
            virtual void visit(astnodes::LabelStatement * labelStatement);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param declarator    The node to visit this visitor
            virtual void visit(astnodes::Declarator * declarator);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param functionDeclarator    The node to visit this visitor
            virtual void visit(astnodes::FunctionDeclarator * functionDeclarator);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param noIdentifierDeclarator    The node to visit this visitor
            virtual void visit(astnodes::NoIdentifierDeclarator * noIdentifierDeclarator);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param identifierDeclarator    The node to visit this visitor
            virtual void visit(astnodes::IdentifierDeclarator * identifierDeclarator);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param arrayDeclarator    The node to visit this visitor
            virtual void visit(astnodes::ArrayDeclarator * arrayDeclarator);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param typeName    The node to visit this visitor
            virtual void visit(astnodes::TypeName * typeName);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param declaration    The node to visit this visitor
            virtual void visit(astnodes::Declaration * declaration);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param pointer    The node to visit this visitor
            virtual void visit(astnodes::Pointer * pointer);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param typeQualifier    The node to visit this visitor
            virtual void visit(astnodes::TypeQualifier * typeQualifier);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param typeSpecifier    The node to visit this visitor
            virtual void visit(astnodes::TypeSpecifier * typeSpecifier);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param typeNameSpecifier    The node to visit this visitor
            virtual void visit(astnodes::TypeNameSpecifier * typeNameSpecifier);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param typeBaseSpecifier    The node to visit this visitor
            virtual void visit(astnodes::TypeBaseSpecifier * typeBaseSpecifier);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param storageSpecifier    The node to visit this visitor
            virtual void visit(astnodes::StorageSpecifier * storageSpecifier);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param assignmentOperator    The node to visit this visitor
            virtual void visit(astnodes::AssignmentOperator * assignmentOperator);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param conditionalOperator    The node to visit this visitor
            virtual void visit(astnodes::ConditionalOperator * conditionalOperator);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param binaryOperator    The node to visit this visitor
            virtual void visit(astnodes::BinaryOperator * binaryOperator);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param explicitCastOperator    The node to visit this visitor
            virtual void visit(astnodes::ExplicitCastOperator * explicitCastOperator);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param sizeOfOperator    The node to visit this visitor
            virtual void visit(astnodes::SizeOfOperator * sizeOfOperator);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param unaryOperator    The node to visit this visitor
            virtual void visit(astnodes::UnaryOperator * unaryOperator);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param preIncDec    The node to visit this visitor
            virtual void visit(astnodes::PreIncDec * preIncDec);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param postIncDec    The node to visit this visitor
            virtual void visit(astnodes::PostIncDec * postIncDec);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param methodCall    The node to visit this visitor
            virtual void visit(astnodes::MethodCall * methodCall);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param arrayAccessOperator    The node to visit this visitor
            virtual void visit(astnodes::ArrayAccessOperator * arrayAccessOperator);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param stringLiteral    The node to visit this visitor
            virtual void visit(astnodes::StringLiteral * stringLiteral);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param identifier    The node to visit this visitor
            virtual void visit(astnodes::Identifier * identifier);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param chainExpressions    The node to visit this visitor
            virtual void visit(astnodes::ChainExpressions * chainExpressions);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param program    The node to visit this visitor
            virtual void visit(astnodes::Program * program);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param structUnionSpecifier    The node to visit this visitor
            virtual void visit(astnodes::StructUnionSpecifier * structUnionSpecifier);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param enumSpecifier    The node to visit this visitor
            virtual void visit(astnodes::EnumSpecifier * enumSpecifier);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param enumerator    The node to visit this visitor
            virtual void visit(astnodes::Enumerator * enumerator);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param structureResolutionOperator    The node to visit this visitor
            virtual void visit(astnodes::StructureResolutionOperator * structureResolutionOperator);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param characterLiteral    The node to visit this visitor
            virtual void visit(astnodes::CharacterLiteral * characterLiteral);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param signedIntLiteral    The node to visit this visitor
            virtual void visit(astnodes::SignedIntLiteral * signedIntLiteral);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param unsignedIntLiteral    The node to visit this visitor
            virtual void visit(astnodes::UnsignedIntLiteral * unsignedIntLiteral);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param signedLongLiteral    The node to visit this visitor
            virtual void visit(astnodes::SignedLongLiteral * signedLongLiteral);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param unsignedLongLiteral    The node to visit this visitor
            virtual void visit(astnodes::UnsignedLongLiteral * unsignedLongLiteral);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param floatLiteral    The node to visit this visitor
            virtual void visit(astnodes::FloatLiteral * floatLiteral);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param doubleLiteral    The node to visit this visitor
            virtual void visit(astnodes::DoubleLiteral * doubleLiteral);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param longDoubleLiteral    The node to visit this visitor
            virtual void visit(astnodes::LongDoubleLiteral * longDoubleLiteral);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param assemblyStatement    The node to visit this visitor
            virtual void visit(astnodes::AssemblyStatement * assemblyStatement);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param builtInVaStart    The node to visit this visitor
            virtual void visit(astnodes::BuiltInVaStart * builtInVaStart);
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param addressOfOperator    The node to visit this visitor
            virtual void visit(astnodes::AddressOfOperator * addressOfOperator);
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param derefOperator    The node to visit this visitor
            virtual void visit(astnodes::DerefOperator * derefOperator);
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param typeConversionOperator    The node to visit this visitor
            virtual void visit(astnodes::TypeConversionOperator * typeConversionOperator);
        };
        
    } // namespace dcpucc
} // namespace astnode

#endif

///
/// @}
///
