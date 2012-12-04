///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       ArrayType.h
/// @brief      Declaration of the ArrayType type class.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_TYPES_ARRAYTYPE_H
#define __DCPU_CC_TYPES_ARRAYTYPE_H

#include <string>
#include <stdint.h>

// include needed type classes
#include "AggregateType.h"


namespace dtcc
{
    namespace types
    {

        ///
        /// @class      ArrayType
        /// @brief      The ArrayType type class.
        ///
        class ArrayType : public AggregateType
        {
            
        public:

            
        public:
            ///
            /// @brief      The constructor of the ArrayType type class.

            ///
            ArrayType()  {}
            
            ///
            /// @brief          Returns the size of the type in words.
            /// @return         The size of the type.
            ///
            /// This might return 0 if the type is not yet resolved
            /// (i.e. for structs).
            virtual uint16_t getWordSize();

            ///
            /// @brief          Returns whether the type is a complete type.
            /// @return         True, if the type is a complete type, false
            ///                 otherwise
            ///
            virtual bool isComplete();
            
            ///
            /// @brief          Returns a string representation of the type.
            /// @return         A string representation of the type.
            ///
            /// This is used especially for error messages and warnings.
            virtual std::string toString();
            
            ///
            /// @brief      The destructor of the ArrayType type class.
            ///
            virtual ~ArrayType();
        };

    } // namespace types
} // namespace dtcc

#endif

///
/// @}
///