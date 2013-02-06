///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       IsTypeHelper.h
/// @brief      Declaration of the IsTypeHelper helper class.
/// @author     Patrick Flick
///

#include "Type.h"

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
            /// @brief          Returns whether the given type is a Type.
            /// @param type     The type to be checked.
            /// @returns        True if the type is Type, false otherwise.
            static bool isType(Type * type);
            
            
            ///
            /// @brief          Returns whether the given type is a ScalarType.
            /// @param type     The type to be checked.
            /// @returns        True if the type is ScalarType, false otherwise.
            static bool isScalarType(Type * type);
            
            
            ///
            /// @brief          Returns whether the given type is a ArithmeticType.
            /// @param type     The type to be checked.
            /// @returns        True if the type is ArithmeticType, false otherwise.
            static bool isArithmeticType(Type * type);
            
            
            ///
            /// @brief          Returns whether the given type is a FloatType.
            /// @param type     The type to be checked.
            /// @returns        True if the type is FloatType, false otherwise.
            static bool isFloatType(Type * type);
            
            
            ///
            /// @brief          Returns whether the given type is a Float.
            /// @param type     The type to be checked.
            /// @returns        True if the type is Float, false otherwise.
            static bool isFloat(Type * type);
            
            
            ///
            /// @brief          Returns whether the given type is a Double.
            /// @param type     The type to be checked.
            /// @returns        True if the type is Double, false otherwise.
            static bool isDouble(Type * type);
            
            
            ///
            /// @brief          Returns whether the given type is a LongDouble.
            /// @param type     The type to be checked.
            /// @returns        True if the type is LongDouble, false otherwise.
            static bool isLongDouble(Type * type);
            
            
            ///
            /// @brief          Returns whether the given type is a IntegralType.
            /// @param type     The type to be checked.
            /// @returns        True if the type is IntegralType, false otherwise.
            static bool isIntegralType(Type * type);
            
            
            ///
            /// @brief          Returns whether the given type is a SignedChar.
            /// @param type     The type to be checked.
            /// @returns        True if the type is SignedChar, false otherwise.
            static bool isSignedChar(Type * type);
            
            
            ///
            /// @brief          Returns whether the given type is a UnsignedChar.
            /// @param type     The type to be checked.
            /// @returns        True if the type is UnsignedChar, false otherwise.
            static bool isUnsignedChar(Type * type);
            
            
            ///
            /// @brief          Returns whether the given type is a SignedShort.
            /// @param type     The type to be checked.
            /// @returns        True if the type is SignedShort, false otherwise.
            static bool isSignedShort(Type * type);
            
            
            ///
            /// @brief          Returns whether the given type is a UnsignedShort.
            /// @param type     The type to be checked.
            /// @returns        True if the type is UnsignedShort, false otherwise.
            static bool isUnsignedShort(Type * type);
            
            
            ///
            /// @brief          Returns whether the given type is a SignedInt.
            /// @param type     The type to be checked.
            /// @returns        True if the type is SignedInt, false otherwise.
            static bool isSignedInt(Type * type);
            
            
            ///
            /// @brief          Returns whether the given type is a UnsignedInt.
            /// @param type     The type to be checked.
            /// @returns        True if the type is UnsignedInt, false otherwise.
            static bool isUnsignedInt(Type * type);
            
            
            ///
            /// @brief          Returns whether the given type is a SignedLong.
            /// @param type     The type to be checked.
            /// @returns        True if the type is SignedLong, false otherwise.
            static bool isSignedLong(Type * type);
            
            
            ///
            /// @brief          Returns whether the given type is a UnsignedLong.
            /// @param type     The type to be checked.
            /// @returns        True if the type is UnsignedLong, false otherwise.
            static bool isUnsignedLong(Type * type);
            
            
            ///
            /// @brief          Returns whether the given type is a EnumType.
            /// @param type     The type to be checked.
            /// @returns        True if the type is EnumType, false otherwise.
            static bool isEnumType(Type * type);
            
            
            ///
            /// @brief          Returns whether the given type is a PointerType.
            /// @param type     The type to be checked.
            /// @returns        True if the type is PointerType, false otherwise.
            static bool isPointerType(Type * type);
            
            
            ///
            /// @brief          Returns whether the given type is a FunctionType.
            /// @param type     The type to be checked.
            /// @returns        True if the type is FunctionType, false otherwise.
            static bool isFunctionType(Type * type);
            
            
            ///
            /// @brief          Returns whether the given type is a AggregateType.
            /// @param type     The type to be checked.
            /// @returns        True if the type is AggregateType, false otherwise.
            static bool isAggregateType(Type * type);
            
            
            ///
            /// @brief          Returns whether the given type is a ArrayType.
            /// @param type     The type to be checked.
            /// @returns        True if the type is ArrayType, false otherwise.
            static bool isArrayType(Type * type);
            
            
            ///
            /// @brief          Returns whether the given type is a StructUnionType.
            /// @param type     The type to be checked.
            /// @returns        True if the type is StructUnionType, false otherwise.
            static bool isStructUnionType(Type * type);
            
            
            ///
            /// @brief          Returns whether the given type is a Void.
            /// @param type     The type to be checked.
            /// @returns        True if the type is Void, false otherwise.
            static bool isVoid(Type * type);
            
            
            ///
            /// @brief          Returns whether the given type is a InvalidType.
            /// @param type     The type to be checked.
            /// @returns        True if the type is InvalidType, false otherwise.
            static bool isInvalidType(Type * type);
            
            
            /* check if it is a valid object type */
            
            ///
            /// @brief          Returns whether the given type is an object type.
            /// @param type     The type to be checked.
            /// @returns        True if the type is an object type, false otherwise.
            static bool isObjectType(Type* type);
            
            
            /* "casting" operations */
            
            ///
            /// @brief          Returns the pointer type if this is a pointer type, and NULL otherwise.
            /// @param type     The type to be cast to pointer and returned.
            /// @returns        The pointer type if this is a pointer type, and NULL otherwise.
            static PointerType* getPointerType(Type* type);
            
            ///
            /// @brief          Returns the array type if this is a array type, and NULL otherwise.
            /// @param type     The type to be cast to arraytype and returned.
            /// @returns        The array type if this is a array type, and NULL otherwise.
            static ArrayType* getArrayType(Type* type);
            
            ///
            /// @brief          Returns the StructUnion type if this is a StructUnion type, and NULL otherwise.
            /// @param type     The type to be cast to StructUnion and returned.
            /// @returns        The StructUnion type if this is a StructUnion type, and NULL otherwise.
            static StructUnionType* getStructUnionType(Type* type);
            
            ///
            /// @brief          Returns the corresponding pointer type if this is an array type, and NULL otherwise.
            /// @param type     The type to be cast to pointer and returned.
            /// @returns        The pointer type if this is an array type, and NULL otherwise.
            static PointerType* pointerFromArrayType(Type* type);
            
            ///
            /// @brief          Returns the function type if this is a function type, and NULL otherwise.
            /// @param type     The type to be cast to function and returned.
            /// @returns        The function type if this is a function type, and NULL otherwise.
            static FunctionType* getFunctionType(Type* type);
            
            ///
            /// @brief          Returns the size of the base type that the pointer points to.
            /// @param type     The type to be cast to pointer and returned.
            /// @returns        The size of the base type, 1 if the base class is incomplete.
            static uint16_t getPointerBaseSize(Type* type);
            
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