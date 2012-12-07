///
/// @addtogroup LibDCPU-CI-Lang-C/ValueTypes
/// @{
///

///
/// @file       LValue.h
/// @brief      Declaration of the LValue class.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_VALUETYPES_LVALUE_H
#define __DCPU_CC_VALUETYPES_LVALUE_H

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
        /// @class      LValue
        /// @brief      The LValue class.
        ///
        class LValue : public ValueType
        {
            
        private:
            bool m_modifiable;
            
        public:
            ///
            /// @brief      The constructor of the LValue class.
            ///
            LValue(types::Type* type);
            
            ///
            /// @brief      Returns wheather this LValue is modifiable or not.
            /// @returns    True if this is modifiable, false otherwise.
            ///
            bool isModifiable();
            

            ///
            /// @brief      The destructor of the LValue class.
            ///
            virtual ~LValue() {}
        };
        
    } // namespace valuetypes
} // namespace dtcc

#endif

///
/// @}
///