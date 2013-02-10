///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       ArithmeticType.h
/// @brief      Declaration of the ArithmeticType type class.
/// @author     Patrick Flick
///

#include "Type.h"

#ifndef __DCPU_CC_TYPES_ARITHMETICTYPE_H
#define __DCPU_CC_TYPES_ARITHMETICTYPE_H

#include <string>
#include <stdint.h>

// include needed type classes
#include "ScalarType.h"


namespace dcpucc
{
    namespace types
    {

        ///
        /// @class      ArithmeticType
        /// @brief      The ArithmeticType type class.
        ///
        class ArithmeticType : public ScalarType
        {
            
        public:

            
        public:
            ///
            /// @brief      The constructor of the ArithmeticType type class.

            ///
            ArithmeticType()  {}
            
            ///
            /// @brief          Returns the size of the type in words.
            /// @return         The size of the type.
            ///
            /// This might return 0 if the type is not yet resolved
            /// (i.e. for structs).
            virtual uint16_t getWordSize() = 0;

            ///
            /// @brief          Returns whether the type is a complete type.
            /// @return         True, if the type is a complete type, false
            ///                 otherwise
            ///
            virtual bool isComplete() = 0;
            
            
            ///
            /// @brief          The accept method of the visitor pattern.
            /// @param tv       The TypeVisitor to be accepted.
            /// @return         The boolean value returned by tv.accept(this)
            ///
            virtual bool accept(TypeVisitor& tv) = 0;
            
            ///
            /// @brief          Returns a string representation of the type.
            /// @return         A string representation of the type.
            ///
            /// This is used especially for error messages and warnings.
            virtual std::string toString();
            
            ///
            /// @brief      The destructor of the ArithmeticType type class.
            ///
            virtual ~ArithmeticType();
        };

    } // namespace types
} // namespace dcpucc

#endif

///
/// @}
///