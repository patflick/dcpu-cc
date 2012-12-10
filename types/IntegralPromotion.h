///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       IntegralPromotion.h
/// @brief      Declaration of the IntegralPromotion helper class.
/// @author     Patrick Flick
///

#include "Type.h"

#ifndef __DCPU_CC_TYPES_INTEGRALPROMOTION_H
#define __DCPU_CC_TYPES_INTEGRALPROMOTION_H

// include needed nodes
#include "alltypes.h"

namespace dtcc
{
    namespace types
    {
        
        ///
        /// @class      IntegralPromotion
        /// @brief      The IntegralPromotion helper class.
        ///
        /// This class uses a visitor like pattern, with function overloading
        /// in order to check which class the given class is a type of.
        class IntegralPromotion
        {
            
        private:
            // private constructor, this class is only implementing static methods.
            IntegralPromotion() {};
        public:
            
            ///
            /// @brief          Returns the type of the integral that is promoted.
            /// @param type     The type to be promoted.
            /// @returns        The promoted type.
            static IntegralType* promote(Type* type);
            
            ///
            /// @brief      The destructor of the IntegralPromotion helper class.
            ///
            virtual ~IntegralPromotion();
        };
        
    } // namespace types
} // namespace dtcc

#endif

///
/// @}
///