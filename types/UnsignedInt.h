///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       UnsignedInt.h
/// @brief      Declaration of the UnsignedInt type class.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_TYPES_UNSIGNEDINT_H
#define __DCPU_CC_TYPES_UNSIGNEDINT_H

#include <string>
#include <stdint.h>

// include needed type classes
#include "IntegralType.h"


namespace dtcc
{
    namespace types
    {

        ///
        /// @class      UnsignedInt
        /// @brief      The UnsignedInt type class.
        ///
        class UnsignedInt : public IntegralType
        {
            
        public:

            
        public:
            ///
            /// @brief      The constructor of the UnsignedInt type class.

            ///
            UnsignedInt()  {}
            
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
            /// @brief      The destructor of the UnsignedInt type class.
            ///
            virtual ~UnsignedInt();
        };

    } // namespace types
} // namespace dtcc

#endif

///
/// @}
///