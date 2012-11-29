///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       Declaration.h
/// @brief      Declaration of the Declaration AST node.
/// @author     Patrick Flick
///

#include "Node.h"

#ifndef __DCPU_CC_AST_NODES_DECLARATION_H
#define __DCPU_CC_AST_NODES_DECLARATION_H

// include needed nodes
#include "ExternalDeclaration.h"
#include "DeclarationSpecifiers.h"
#include "Declarators.h"
#include <cstdlib>

namespace dtcc
{
    namespace astnodes
    {

        ///
        /// @class      Declaration
        /// @brief      The Declaration AST node.
        ///
        class Declaration : public ExternalDeclaration
        {
        private:
            ///
            /// @brief          Calls acceptPreRecursive(visitor) on all children nodes.
            /// @param visitor  The visitor to be accepted.
            ///
            void allChildrenAcceptPreRecursive(dtcc::visitor::Visitor & visitor);
            
            ///
            /// @brief          Calls acceptPostRecursive(visitor) on all children nodes.
            /// @param visitor  The visitor to be accepted.
            ///
            void allChildrenAcceptPostRecursive(dtcc::visitor::Visitor & visitor);
            
        public:
            DeclarationSpecifiers * declSpecifiers;
            Declarators * declarators;
            Declarator * singleDeclarator;

            
        public:
            ///
            /// @brief      The constructor of the Declaration AST node.
            /// @param declSpecifiers TODO: FILLOUT
            /// @param declarators TODO: FILLOUT
            Declaration(DeclarationSpecifiers * declSpecifiers, Declarators * declarators) :
                declSpecifiers(declSpecifiers), declarators(declarators), singleDeclarator(NULL) {}
            
            ///
            /// @brief      The constructor of the Declaration AST node.
            /// @param declSpecifiers TODO: FILLOUT
            /// @param declarator TODO: FILLOUT
            Declaration(DeclarationSpecifiers * declSpecifiers, Declarator * declarator) :
            declSpecifiers(declSpecifiers), declarators(NULL), singleDeclarator(declarator) {}
            
            
            ///
            /// @brief          The accept method of the Visitor pattern.
            /// @sa             http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param visitor  The visitor to be accepted.
            ///
            /// This is a non recursive version of accept, which calls
            /// only visit(this) and then returns.
            void accept(dtcc::visitor::Visitor & visitor);
            
            ///
            /// @brief          The accept method of the Visitor pattern.
            /// @sa             http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param visitor  The visitor to be accepted.
            ///
            /// This is a post recursive version of accept, meaning that
            /// it first calls visit(this) and then accept(visitor) for
            /// all its children nodes.
            void acceptPostRecursive(dtcc::visitor::Visitor & visitor);
            
            ///
            /// @brief          The accept method of the Visitor pattern.
            /// @sa             http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param visitor  The visitor to be accepted.
            ///
            /// This is a pre recursive version of accept, meaning that
            /// it first calls accept(visitor) for
            /// all its children nodes and only then visit(this).
            void acceptPreRecursive(dtcc::visitor::Visitor & visitor);
            
            ///
            /// @brief          Calls accept(visitor) on all children nodes.
            /// @param visitor  The visitor to be accepted.
            ///
            void allChildrenAccept(dtcc::visitor::Visitor & visitor);
            
            ///
            /// @brief      The destructor of the Declaration AST node.
            ///
            virtual ~Declaration();
        };

    } // namespace dtcc
} // namespace astnode

#endif

///
/// @}
///