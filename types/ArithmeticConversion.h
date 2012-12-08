///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       ArithmeticConversion.h
/// @brief      Declaration of the ArithmeticConversion helper class.
/// @author     Patrick Flick
///


#ifndef __DCPU_CC_TYPES_ARITHMETICCONVERSION_H
#define __DCPU_CC_TYPES_ARITHMETICCONVERSION_H

// include needed nodes
#include "alltypes.h"

namespace dtcc
{
    namespace types
    {
        
        ///
        /// @class      ArithmeticConversion
        /// @brief      The ArithmeticConversion helper class.
        ///
        class ArithmeticConversion
        {
            
        private:
            // private constructor, this class is only implementing static methods.
            ArithmeticConversion() {};
        public:
            
            ///
            /// @brief          Returns the type of the integral that is promoted.
            /// @param type     The type to be promoted.
            /// @returns        The promoted type.
            static ArithmeticType* commonType(ArithmeticType* t1, ArithmeticType* t2);
            
            ///
            /// @brief      The destructor of the ArithmeticConversion helper class.
            ///
            virtual ~ArithmeticConversion();
        };
        
    } // namespace types
} // namespace dtcc

#endif

///
/// @}
///