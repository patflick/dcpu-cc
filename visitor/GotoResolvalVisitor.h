///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Visitor
/// @{
///

///
/// @file       GotoResolvalVisitor.h
/// @brief      Declaration of the GotoResolvalVisitor class.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_VISITOR_GOTORESOLVAL_VISITOR_H
#define __DCPU_CC_VISITOR_GOTORESOLVAL_VISITOR_H

// include all AST nodes
#include <astnodes/allnodes.h>
#include "EmptyVisitor.h"
#include <string>
#include <vector>
#include <visitor/SemanticCheckVisitor.h>

namespace dcpucc
{
    namespace visitor
    {
        // forward declaration
        class SemanticCheckVisitor;
        
        ///
        /// @class      GotoResolvalVisitor
        /// @brief      A visitor which resolves goto labels. IMPORTANT: call only with acceptPreRecursive(..).
        ///
        /// IMPORTANT: start the visitor routines with
        /// declaration.acceptPreRecursive(...).
        class GotoResolvalVisitor : public EmptyVisitor
        {   
        private:
            /// The SemanticCheckVisitor that is calling this visitor to resolve
            /// goto statements after all labels have been visited
            SemanticCheckVisitor* semCheck;
            
        public:
            
            
            ///
            /// @brief Constructor for the GotoResolvalVisitor visitor.
            /// @param semCheck The SemanticCheckVisitor that is calling this GotoResolvalVisitor.
            GotoResolvalVisitor(SemanticCheckVisitor* semCheck) :semCheck(semCheck) {}
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param gotoStatement    The node to visit this visitor
            virtual void visit(astnodes::GotoStatement * gotoStatement);
            
        };
        
    } // namespace dcpucc
} // namespace astnode

#endif

///
/// @}
///
