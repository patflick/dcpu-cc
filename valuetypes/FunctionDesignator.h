///
/// @addtogroup LibDCPU-CI-Lang-C/ValueTypes
/// @{
///

///
/// @file       FunctionDesignator.h
/// @brief      Declaration of the FunctionDesignator class.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_VALUETYPES_FUNCTIONDESIGNATOR_H
#define __DCPU_CC_VALUETYPES_FUNCTIONDESIGNATOR_H

#include <string>
#include <stdint.h>

// include needed type classes
#include <types/Type.h>
#include "ValueType.h"
#include <types/FunctionType.h>

namespace dcpucc
{
    namespace valuetypes
    {
        
        ///
        /// @class      FunctionDesignator
        /// @brief      The FunctionDesignator class.
        ///
        class FunctionDesignator : public ValueType
        {
            
        public:
            /// a function type member, prevents additional casting
            types::FunctionType* funType;
            
        public:
            ///
            /// @brief      The constructor of the FunctionDesignator class.
            ///
            FunctionDesignator(types::FunctionType* type) : ValueType(type, FUNC_DESIGN), funType(type) {}
            
            
            ///
            /// @brief      The destructor of the FunctionDesignator class.
            ///
            virtual ~FunctionDesignator() {}
        };
        
    } // namespace valuetypes
} // namespace dcpucc

#endif

///
/// @}
///