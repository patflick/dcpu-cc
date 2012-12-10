///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       SignedLong.h
/// @brief      Declaration of the SignedLong type class.
/// @author     Patrick Flick
///

#include "Type.h"

#ifndef __DCPU_CC_TYPES_SIGNEDLONG_H
#define __DCPU_CC_TYPES_SIGNEDLONG_H

#include <string>
#include <stdint.h>

// include needed type classes
#include "IntegralType.h"


namespace dtcc
{
    namespace types
    {

        ///
        /// @class      SignedLong
        /// @brief      The SignedLong type class.
        ///
        class SignedLong : public IntegralType
        {
            
        public:

            
        public:
            ///
            /// @brief      The constructor of the SignedLong type class.

            ///
            SignedLong()  {}
            
            ///
            /// @brief          Returns the size of the type in words.
            /// @return         The size of the type.
            ///
            /// This might return 0 if the type is not yet resolved
            /// (i.e. for structs).
            virtual uint16_t getWordSize();

            ///
            /// @brief          Returns the size of the type in bytes.
            /// @return         The size of the type.
            ///
            /// This might return 0 if the type is not yet resolved
            /// (i.e. for structs).
            virtual uint16_t getByteSize();
            
            ///
            /// @brief          Returns whether the type is a complete type.
            /// @return         True, if the type is a complete type, false
            ///                 otherwise
            ///
            virtual bool isComplete();
            
            
            ///
            /// @brief          The accept method of the visitor pattern.
            /// @param tv       The TypeVisitor to be accepted.
            /// @return         The boolean value returned by tv.accept(this)
            ///
            virtual bool accept(TypeVisitor& tv);
            
            ///
            /// @brief          Returns a string representation of the type.
            /// @return         A string representation of the type.
            ///
            /// This is used especially for error messages and warnings.
            virtual std::string toString();
            
            ///
            /// @brief      The destructor of the SignedLong type class.
            ///
            virtual ~SignedLong();
        };

    } // namespace types
} // namespace dtcc

#endif

///
/// @}
///