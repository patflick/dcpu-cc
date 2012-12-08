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
            /// @brief          Returns whether the given type is a void type.
            /// @param type     The type to be checked.
            /// @returns        True if the type is of type void, false otherwise.
            static bool isVoid(Void* type);
            
            ///
            /// @brief          Returns whether the given type is a void type.
            /// @param type     The type to be checked.
            /// @returns        True if the type is of type void, false otherwise.
            static bool isVoid(Type* type);
            
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
            /// @brief          Returns whether the given type is a arithmetic type.
            /// @param type     The type to be checked.
            /// @returns        True if the type is of type ScalarType, false otherwise.
            static bool isArithmeticType(ArithmeticType* type);
            
            ///
            /// @brief          Returns whether the given type is a arithmetic type.
            /// @param type     The type to be checked.
            /// @returns        True if the type is of type ScalarType, false otherwise.
            static bool isArithmeticType(Type* type);
            
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
            
            ///
            /// @brief          Returns whether the given type is a function type.
            /// @param type     The type to be checked.
            /// @returns        True if the type is of type function, false otherwise.
            static bool isFunctionType(FunctionType* type);
            
            ///
            /// @brief          Returns whether the given type is a function type.
            /// @param type     The type to be checked.
            /// @returns        True if the type is of type function, false otherwise.
            static bool isFunctionType(Type* type);
            
            
            /* base types */
            ///
            /// @brief          Returns whether the given type is a long double.
            /// @param type     The type to be checked.
            /// @returns        True if the type is long double, false otherwise.
            static bool isLongDouble(LongDouble* type);
            
            ///
            /// @brief          Returns whether the given type is a long double.
            /// @param type     The type to be checked.
            /// @returns        True if the type is long double, false otherwise.
            static bool isLongDouble(Type* type);
            
            ///
            /// @brief          Returns whether the given type is a double.
            /// @param type     The type to be checked.
            /// @returns        True if the type is double, false otherwise.
            static bool isDouble(Double* type);
            
            ///
            /// @brief          Returns whether the given type is a double.
            /// @param type     The type to be checked.
            /// @returns        True if the type is double, false otherwise.
            static bool isDouble(Type* type);
            
            ///
            /// @brief          Returns whether the given type is a float.
            /// @param type     The type to be checked.
            /// @returns        True if the type is float, false otherwise.
            static bool isFloat(Float* type);
            
            ///
            /// @brief          Returns whether the given type is a float.
            /// @param type     The type to be checked.
            /// @returns        True if the type is float, false otherwise.
            static bool isFloat(Type* type);
            
            ///
            /// @brief          Returns whether the given type is a UnsignedLong.
            /// @param type     The type to be checked.
            /// @returns        True if the type is UnsignedLong, false otherwise.
            static bool isUnsignedLong(UnsignedLong* type);
            
            ///
            /// @brief          Returns whether the given type is a UnsignedLong.
            /// @param type     The type to be checked.
            /// @returns        True if the type is UnsignedLong, false otherwise.
            static bool isUnsignedLong(Type* type);
            
            ///
            /// @brief          Returns whether the given type is a SignedLong.
            /// @param type     The type to be checked.
            /// @returns        True if the type is SignedLong, false otherwise.
            static bool isSignedLong(SignedLong* type);
            
            ///
            /// @brief          Returns whether the given type is a SignedLong.
            /// @param type     The type to be checked.
            /// @returns        True if the type is SignedLong, false otherwise.
            static bool isSignedLong(Type* type);
            
            ///
            /// @brief          Returns whether the given type is a UnsignedInt.
            /// @param type     The type to be checked.
            /// @returns        True if the type is UnsignedInt, false otherwise.
            static bool isUnsignedInt(UnsignedInt* type);
            
            ///
            /// @brief          Returns whether the given type is a UnsignedInt.
            /// @param type     The type to be checked.
            /// @returns        True if the type is UnsignedInt, false otherwise.
            static bool isUnsignedInt(Type* type);
            
            /* "casting" operations */
            
            ///
            /// @brief          Returns the pointer type if this is a pointer type, and NULL otherwise.
            /// @param type     The type to be cast to pointer and returned.
            /// @returns        The pointer type if this is a pointer type, and NULL otherwise.
            static PointerType* getPointerType(Type* type);
            
            ///
            /// @brief          Returns the function type if this is a function type, and NULL otherwise.
            /// @param type     The type to be cast to function and returned.
            /// @returns        The function type if this is a function type, and NULL otherwise.
            static FunctionType* getFunctionType(Type* type);
            
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