///
/// @addtogroup LibDCPU-CI-Lang-C/ValueTypes
/// @{
///

///
/// @file       ConstHelper.h
/// @brief      Declaration of the ConstHelper helper class.
/// @author     Patrick Flick
///


#ifndef __DCPU_CC_VALUETYPES_CONSTHELPER_H
#define __DCPU_CC_VALUETYPES_CONSTHELPER_H

#include "ValueType.h"
#include "RValue.h"
#include "LValue.h"
#include "CValue.h"
#include "FunctionDesignator.h"

namespace dtcc
{
    namespace valuetypes
    {
        
        ///
        /// @class      ConstHelper
        /// @brief      The ConstHelper helper class.
        ///
        class ConstHelper
        {
            
        private:
            // private constructor, this class is only implementing static methods.
            ConstHelper() {};
        public:

            
            ///
            /// @brief          Returns the CValue casted pointer.
            /// @param type     The value type to be casted.
            /// @returns        The CValue casted pointer.
            ///
            /// This throws an exception if type was not a CValue.
            static CValue* getCValue(ValueType* type);
    
            ///
            /// @brief              Sets the floating type constant in the given CValue.
            /// @param type         The CValue to be set.
            /// @param floatConst   The floating constant to be set in the CValue.
            ///
            /// This throws an exception if type was not a CValue.
            static void setFloatConst(ValueType* type, double floatConst);
            
            ///
            /// @brief              Returns the floating type constant in the given CValue.
            /// @param type         The CValue to be read.
            /// @returns            The floating type constant.
            ///
            /// This throws an exception if type was not a CValue.
            static double getFloatConst(ValueType* type);
            
            ///
            /// @brief              Sets the integral type constant in the given CValue.
            /// @param type         The CValue to be set.
            /// @param intConst     The integral constant to be set in the CValue.
            ///
            /// This throws an exception if type was not a CValue.
            static void setIntegralConst(ValueType* type, long intConst);
            
            ///
            /// @brief              Returns the integral type constant in the given CValue.
            /// @param type         The CValue to be read.
            /// @returns            The integral type constant.
            ///
            /// This throws an exception if type was not a CValue.
            static long getIntegralConst(ValueType* type);
            
            ///
            /// @brief      The destructor of the ConstHelper helper class.
            ///
            virtual ~ConstHelper();
        };
        
    } // namespace types
} // namespace dtcc

#endif

///
/// @}
///