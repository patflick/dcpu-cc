///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       ParameterTypeList.h
/// @brief      Declaration of the ParameterTypeList.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_AST_TYPES_TYPELIST_H
#define __DCPU_CC_AST_TYPES_TYPELIST_H

#include "Type.h"
#include <vector>

namespace dtcc
{
    namespace types
    {
        ///
        /// @brief      The ParameterTypeList AST node.
        ///
        /// This is a std::vector of Declaration.
        typedef std::vector<Type*> ParameterTypeList;
    } // namespace types
} // namespace dtcc

#endif

///
/// @}
///