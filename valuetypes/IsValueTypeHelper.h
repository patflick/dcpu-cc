///
/// @addtogroup LibDCPU-CI-Lang-C/ValueTypes
/// @{
///

///
/// @file       IsValueTypeHelper.h
/// @brief      Declaration of the IsValueTypeHelper helper class.
/// @author     Patrick Flick
///


#ifndef __DCPU_CC_VALUETYPES_ISVALUETYPEHELPER_H
#define __DCPU_CC_VALUETYPES_ISVALUETYPEHELPER_H

#include "ValueType.h"
#include "RValue.h"
#include "LValue.h"
#include "FunctionDesignator.h"

namespace dtcc
{
    namespace valuetypes
    {
        
        ///
        /// @class      IsValueTypeHelper
        /// @brief      The IsValueTypeHelper helper class.
        ///
        class IsValueTypeHelper
        {
            
        private:
            // private constructor, this class is only implementing static methods.
            IsValueTypeHelper() {};
        public:
            
            ///
            /// @brief          Returns whether the given value type is a RValue.
            /// @param type     The value type to be checked.
            /// @returns        True if the value type is a RValue, false otherwise.
            static bool isFunctionDesignator(FunctionDesignator* type);
            
            ///
            /// @brief          Returns whether the given value type is a RValue.
            /// @param type     The value type to be checked.
            /// @returns        True if the value type is a RValue, false otherwise.
            static bool isFunctionDesignator(ValueType* type);
            
            ///
            /// @brief          Returns whether the given value type is a RValue.
            /// @param type     The value type to be checked.
            /// @returns        True if the value type is a RValue, false otherwise.
            static bool isRValue(RValue* type);
            
            ///
            /// @brief          Returns whether the given value type is a RValue.
            /// @param type     The value type to be checked.
            /// @returns        True if the value type is a RValue, false otherwise.
            static bool isRValue(ValueType* type);
            
            ///
            /// @brief          Returns whether the given value type is a LValue.
            /// @param type     The value type to be checked.
            /// @returns        True if the value type is a LValue, false otherwise.
            static bool isLValue(LValue* type);
            
            ///
            /// @brief          Returns whether the given value type is a LValue.
            /// @param type     The value type to be checked.
            /// @returns        True if the value type is a LValue, false otherwise.
            static bool isLValue(ValueType* type);

            ///
            /// @brief          Returns whether the given value type is a modifiable LValue.
            /// @param type     The value type to be checked.
            /// @returns        True if the value type is a modifiable LValue, false otherwise.
            static bool isModifiableLValue(LValue* type);
            
            ///
            /// @brief          Returns whether the given value type is a modifiable LValue.
            /// @param type     The value type to be checked.
            /// @returns        True if the value type is a modifiable LValue, false otherwise.
            static bool isModifiableLValue(ValueType* type);
            
            ///
            /// @brief          Converts the given L value into a R value.
            /// @param type     The value type to be converted.
            /// @returns        The converted LValue as RValue.
            static RValue* toRValue(ValueType* type);
            
            ///
            /// @brief      The destructor of the IsValueTypeHelper helper class.
            ///
            virtual ~IsValueTypeHelper();
        };
        
    } // namespace types
} // namespace dtcc

#endif

///
/// @}
///