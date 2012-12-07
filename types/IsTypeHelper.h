///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       IsTypeHelper.h
/// @brief      Declaration of the IsTypeHelper helper class.
/// @author     Patrick Flick
///


#ifndef __DCPU_CC_TYPES_ISTYPEHELPER_H
#define __DCPU_CC_TYPES_ISTYPEHELPER_H

// include needed nodes
#include "alltypes.h"

namespace dtcc
{
    namespace types
    {
        
        ///
        /// @class      IsTypeHelper
        /// @brief      The IsTypeHelper helper class.
        ///
        /// This class uses a visitor like pattern, with function overloading
        /// in order to check which class the given class is a type of.
        class IsTypeHelper
        {

        private:
            // private constructor, this class is only implementing static methods.
            IsTypeHelper() {};
        public:
            
            
            ///
            /// @brief          Returns whether the given type is a scalar type.
            /// @param type     The type to be checked.
            /// @returns        True if the type is of type ScalarType, false otherwise.
            static bool isScalarType(ScalarType* type);
            
            ///
            /// @brief          Returns whether the given type is a scalar type.
            /// @param type     The type to be checked.
            /// @returns        True if the type is of type ScalarType, false otherwise.
            static bool isScalarType(Type* type);
            
            ///
            /// @brief          Returns whether the given type is a pointer type.
            /// @param type     The type to be checked.
            /// @returns        True if the type is of type pointer, false otherwise.
            static bool isPointerType(PointerType* type);
            
            ///
            /// @brief          Returns whether the given type is a pointer type.
            /// @param type     The type to be checked.
            /// @returns        True if the type is of type pointer, false otherwise.
            static bool isPointerType(Type* type);
            
            ///
            /// @brief          Returns whether the given type is a scalar type.
            /// @param type     The type to be checked.
            /// @returns        True if the type is of type ScalarType, false otherwise.
            static bool isIntegralType(IntegralType* type);
            
            ///
            /// @brief          Returns whether the given type is a scalar type.
            /// @param type     The type to be checked.
            /// @returns        True if the type is of type ScalarType, false otherwise.
            static bool isIntegralType(Type* type);
            
            ///
            /// @brief          Returns whether the given type is a scalar type.
            /// @param type     The type to be checked.
            /// @returns        True if the type is of type ScalarType, false otherwise.
            static bool isArrayType(ArrayType* type);
            
            ///
            /// @brief          Returns whether the given type is a scalar type.
            /// @param type     The type to be checked.
            /// @returns        True if the type is of type ScalarType, false otherwise.
            static bool isArrayType(Type* type);
            
            ///
            /// @brief          Returns whether the given type is a object type.
            /// @param type     The type to be checked.
            /// @returns        True if the type is of type object, false otherwise.
            static bool isObjectType(FunctionType* type);
            
            ///
            /// @brief          Returns whether the given type is a object type.
            /// @param type     The type to be checked.
            /// @returns        True if the type is of type object, false otherwise.
            static bool isObjectType(Type* type);
            
            
            /* "casting" operations */
            
            ///
            /// @brief          Returns the pointer type if this is a pointer type, and NULL otherwise.
            /// @param type     The type to be cast to pointer and returned.
            /// @returns        The pointer type if this is a pointer type, and NULL otherwise.
            static PointerType* getPointerType(Type* type);
            
            ///
            /// @brief      The destructor of the IsTypeHelper helper class.
            ///
            virtual ~IsTypeHelper();
        };
        
    } // namespace types
} // namespace dtcc

#endif

///
/// @}
///