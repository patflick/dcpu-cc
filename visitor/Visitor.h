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

#include<nodes/Node.h>

namespace dtcc
{
    namespace visitor
    {
        
        ///
        /// @class      Node
        /// @brief      The Node AST node.
        ///
        class Visitor
        {
        public:
            
            virtual void visit(dtcc::astnodes::Node * node);
            
        };
        
    } // namespace dtcc
} // namespace astnode

#endif

///
/// @}
///
