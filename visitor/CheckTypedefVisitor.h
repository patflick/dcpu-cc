///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Visitor
/// @{
///

///
/// @file       CheckTypedefVisitor.h
/// @brief      Declaration of the CheckTypedefVisitor class.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_VISITOR_CHECKTYPEDEF_VISITOR_H
#define __DCPU_CC_VISITOR_CHECKTYPEDEF_VISITOR_H

// include all AST nodes
#include <astnodes/allnodes.h>
#include "EmptyVisitor.h"
#include <string>
#include <vector>

namespace dtcc
{
    namespace visitor
    {
        
        ///
        /// @class      CheckTypedefVisitor
        /// @brief      A visitor which is checks for a Typedef in a Declaration. IMPORTANT: call only with acceptPreRecursive(..).
        ///
        /// IMPORTANT: start the visitor routines with
        /// declaration.acceptPreRecursive(...).
        ///
        /// This visitor has to be started via acceptPreRecursive(Declaration).
        /// It then checks if the given declaration is a typedef, and if it
        /// is, it holds the identifiers of the typedef in the typeNameList
        /// public member.
        /// On completion the boolean isTypedef member holds whether the
        /// declaration was a typedef (true=typedef, false= no typedef).
        class CheckTypedefVisitor : public EmptyVisitor
        {   
        public:
            /// This member holds the list of type names if the declaration
            /// was a typedef.
            std::vector<std::string> typeNameList;
            
            /// This bool will be true if the declaration was a typedef.
            /// and false if it was regular non-typedef declaration.
            bool isTypedef;
            
            ///
            /// @brief Constructor for the CheckTypedefVisitor visitor.
            CheckTypedefVisitor() : typeNameList(std::vector<std::string>()), isTypedef(false) {}
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param identifierDeclarator    The node to visit this visitor
            virtual void visit(astnodes::IdentifierDeclarator * identifierDeclarator);
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param identifierDeclarator    The node to visit this visitor
            virtual void visit(astnodes::FunctionDeclarator * functionDeclarator);
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param declaration    The node to visit this visitor
            ///
            /// This is the start point of this visitor.
            /// IMPORTANT: start the visitor routines with
            /// declaration.acceptPreRecursive(...).
            virtual void visit(astnodes::Declaration * declaration);
            
        };
        
    } // namespace dtcc
} // namespace astnode

#endif

///
/// @}
///
