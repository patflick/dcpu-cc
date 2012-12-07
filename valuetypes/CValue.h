///
/// @addtogroup LibDCPU-CI-Lang-C/ValueTypes
/// @{
///

///
/// @file       CValue.h
/// @brief      Declaration of the CValue class.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_VALUETYPES_CVALUE_H
#define __DCPU_CC_VALUETYPES_CVALUE_H

#include <string>
#include <stdint.h>

// include needed type classes
#include <types/Type.h>
#include "RValue.h"

namespace dtcc
{
    namespace valuetypes
    {
        
        ///
        /// @class      CValue
        /// @brief      The CValue class.
        ///
        class CValue : public RValue
        {
            
        public:
            
        public:
            ///
            /// @brief      The constructor of the CValue class.
            ///
            CValue(types::Type* type) : RValue(type) {}
            
            ///
            /// @brief      The destructor of the CValue class.
            ///
            virtual ~CValue() {}
        };
        
    } // namespace valuetypes
} // namespace dtcc

#endif

///
/// @}
///