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
#include "CValue.h"
#include "FunctionDesignator.h"

namespace dcpucc
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
            static bool isFunctionDesignator(ValueType* type);
            
            
            ///
            /// @brief          Returns whether the given value type is a RValue.
            /// @param type     The value type to be checked.
            /// @returns        True if the value type is a RValue, false otherwise.
            static bool isRValue(ValueType* type);
            
            
            ///
            /// @brief          Returns whether the given value type is a RValue.
            /// @param type     The value type to be checked.
            /// @returns        True if the value type is a RValue, false otherwise.
            static bool isCValue(ValueType* type);
            
            
            ///
            /// @brief          Returns whether the given value type is a LValue.
            /// @param type     The value type to be checked.
            /// @returns        True if the value type is a LValue, false otherwise.
            static bool isLValue(ValueType* type);
            
            
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
            /// @brief          Creates a new R or C value with the given type.
            /// @param type     The new type of the value type.
            /// @param vt       The previous ValueType
            /// @returns        The converted a RValue or CValue with the type newType.
            ///                 It will be a CValue if vt was a CValue,
            ///                 and an RValue otherwise.
            static RValue* toCorRValue(types::Type* newType, ValueType* vt);
            
            ///
            /// @brief          Creates a new R or C value with the given type.
            /// @param type     The new type of the value type.
            /// @param vt1      The lhs RValue.
            /// @param vt2      The rhs RValue.
            /// @returns        The converted a RValue or CValue with the type newType.
            ///                 It will be a CValue if both vt1 and vt2 were CValues,
            ///                 and an RValue otherwise.
            static RValue* toCorRValue(types::Type* newType, ValueType* vt1, ValueType* vt2);
            
            
            ///
            /// @brief      The destructor of the IsValueTypeHelper helper class.
            ///
            virtual ~IsValueTypeHelper();
        };
        
    } // namespace types
} // namespace dcpucc

#endif

///
/// @}
///