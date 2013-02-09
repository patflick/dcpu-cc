///
/// @addtogroup LibDCPU-CI-Lang-C/AST-Nodes
/// @{
///

///
/// @file       Expression.cpp
/// @brief      Definition of the Expression AST node.
/// @author     Patrick Flick
///

#include <astnodes/expression/Expression.h>

using namespace dtcc::astnodes;

// implements the destructor, which deletes all children
Expression::~Expression()
{
    //this->safe_delete(valType);
}

///
/// @}
///