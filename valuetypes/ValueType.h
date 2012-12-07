///
/// @addtogroup LibDCPU-CI-Lang-C/ValueTypes
/// @{
///

///
/// @file       ValueType.h
/// @brief      Declaration of the ValueType class.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_VALUETYPES_VALUETYPE_H
#define __DCPU_CC_VALUETYPES_VALUETYPE_H

#include <string>
#include <stdint.h>

// include needed type classes
#include <types/Type.h>


namespace dtcc
{
    namespace valuetypes
    {
        
        ///
        /// @class      ValueType
        /// @brief      The ValueType class.
        ///
        class ValueType
        {
            
        public:
            /// The base type of this value type.
            types::Type* type;
            
        public:
            ///
            /// @brief      The constructor of the ValueType class.
            ///
            ValueType(types::Type* type) : type(type) {}
            
            ///
            /// @brief          Performes a safe deletion of the given pointer.
            /// @param p        The object to be deleted
            ///
            template<typename T> void safe_delete(T*& p) {
                delete p;
                p = NULL;
            }
            
            ///
            /// @brief      The destructor of the ValueType class.
            ///
            virtual ~ValueType() {}
        };
        
    } // namespace valuetypes
} // namespace dtcc

#endif

///
/// @}
///