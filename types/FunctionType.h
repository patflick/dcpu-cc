///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       FunctionType.h
/// @brief      Declaration of the FunctionType type class.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_TYPES_FUNCTIONTYPE_H
#define __DCPU_CC_TYPES_FUNCTIONTYPE_H

#include <string>
#include <stdint.h>

// include needed type classes
#include "Type.h"
#include "ParameterTypeList.h"


namespace dtcc
{
    namespace types
    {

        ///
        /// @class      FunctionType
        /// @brief      The FunctionType type class.
        ///
        class FunctionType : public Type
        {
            
        public:
            Type* returnType;
            ParameterTypeList* paramTypes;

            
        public:
            ///
            /// @brief      The constructor of the FunctionType type class.
            /// @param returnType TODO: FILLOUT
            /// @param paramTypes TODO: FILLOUT

            ///
            FunctionType(Type* returnType, ParameterTypeList* paramTypes) : returnType(returnType), paramTypes(paramTypes) {}
            
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
            /// @brief      The destructor of the FunctionType type class.
            ///
            virtual ~FunctionType();
        };

    } // namespace types
} // namespace dtcc

#endif

///
/// @}
///