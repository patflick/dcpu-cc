///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       Expressions.h
/// @brief      Declaration of the Expressions AST node.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_AST_NODES_EXPRESSIONS_H
#define __DCPU_CC_AST_NODES_EXPRESSIONS_H

#include <astnodes/Node.h>
#include <astnodes/expression/Expression.h>
#include <vector>

namespace dtcc
{
    namespace astnodes
    {
        ///
        /// @brief      The Expressions AST node.
        ///
        /// This is a std::vector of Expression.
        typedef std::vector<Expression*> Expressions;
    } // namespace dtcc
} // namespace astnode

#endif

///
/// @}
///
