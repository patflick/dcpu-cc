///
/// @addtogroup LibDCPU-CI-Lang-C/ValueTypes
/// @{
///

///
/// @file       PromotionHelper.h
/// @brief      Declaration of the PromotionHelper helper class.
/// @author     Patrick Flick
///


#ifndef __DCPU_CC_VALUETYPES_PROMOTIONHELPER_H
#define __DCPU_CC_VALUETYPES_PROMOTIONHELPER_H

#include "ValueType.h"
#include "RValue.h"
#include "LValue.h"
#include "FunctionDesignator.h"

namespace dtcc
{
    namespace valuetypes
    {
        
        ///
        /// @class      PromotionHelper
        /// @brief      The PromotionHelper helper class.
        ///
        class PromotionHelper
        {
            
        private:
            // private constructor, this class is only implementing static methods.
            PromotionHelper() {};
        public:
            

            ///
            /// @brief          Does integer promotion, and returns a CValue or RValue depending on the given type.
            /// @param type     The value type to be converted.
            /// @returns        A RValue or CValue, depending whether type was a RValue or CValue.
            static ValueType* promote(ValueType* type);
            
            ///
            /// @brief          Returns the common type of the both given types.
            /// @param t1       First type.
            /// @param t2       Second type.
            /// @returns        A RValue or CValue with the common type. A
            ///                 CValue in the case that both value types were CValues.
            static ValueType* commonType(ValueType* t1, ValueType* t2);
            
            ///
            /// @brief      The destructor of the PromotionHelper helper class.
            ///
            virtual ~PromotionHelper();
        };
        
    } // namespace types
} // namespace dtcc

#endif

///
/// @}
///