///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       PointerType.h
/// @brief      Declaration of the PointerType type class.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_TYPES_POINTERTYPE_H
#define __DCPU_CC_TYPES_POINTERTYPE_H

#include <string>
#include <stdint.h>

// include needed type classes
#include "ScalarType.h"
#include "Type.h"


namespace dtcc
{
    namespace types
    {

        ///
        /// @class      PointerType
        /// @brief      The PointerType type class.
        ///
        class PointerType : public ScalarType
        {
            
        public:
            Type* baseType;

            
        public:
            ///
            /// @brief      The constructor of the PointerType type class.
            /// @param baseType TODO: FILLOUT

            ///
            PointerType(Type* baseType) : baseType(baseType) {}
            
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
            /// @brief      The destructor of the PointerType type class.
            ///
            virtual ~PointerType();
        };

    } // namespace types
} // namespace dtcc

#endif

///
/// @}
///