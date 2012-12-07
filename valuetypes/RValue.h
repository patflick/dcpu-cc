///
/// @addtogroup LibDCPU-CI-Lang-C/ValueTypes
/// @{
///

///
/// @file       RValue.h
/// @brief      Declaration of the RValue class.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_VALUETYPES_RVALUE_H
#define __DCPU_CC_VALUETYPES_RVALUE_H

#include <string>
#include <stdint.h>

// include needed type classes
#include <types/Type.h>
#include "ValueType.h"

namespace dtcc
{
    namespace valuetypes
    {
        
        ///
        /// @class      RValue
        /// @brief      The RValue class.
        ///
        class RValue : public ValueType
        {
            
        public:
            
        public:
            ///
            /// @brief      The constructor of the RValue class.
            ///
            RValue(types::Type* type) : ValueType(type) {}
            
            ///
            /// @brief      The destructor of the RValue class.
            ///
            virtual ~RValue() {}
        };
        
    } // namespace valuetypes
} // namespace dtcc

#endif

///
/// @}
///