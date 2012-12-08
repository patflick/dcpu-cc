///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       IsTypeHelper.cpp
/// @brief      Definition of the IsTypeHelper helper class.
/// @author     Patrick Flick
///
    
#include "IsTypeHelper.h"
using namespace dtcc::types;
    

bool IsTypeHelper::isVoid(Void* type)
{
    return true;
}

bool IsTypeHelper::isVoid(Type* type)
{
    return false;
}

bool IsTypeHelper::isScalarType(ScalarType* type)
{
    return true;
}

bool IsTypeHelper::isScalarType(Type* type)
{
    return false;
}

bool IsTypeHelper::isArithmeticType(ArithmeticType* type)
{
    return true;
}

bool IsTypeHelper::isArithmeticType(Type* type)
{
    return false;
}

bool IsTypeHelper::isPointerType(PointerType* type)
{
    return true;
}

bool IsTypeHelper::isPointerType(Type* type)
{
    return false;
}

bool IsTypeHelper::isIntegralType(IntegralType* type)
{
    return true;
}

bool IsTypeHelper::isIntegralType(Type* type)
{
    return false;
}

bool IsTypeHelper::isArrayType(ArrayType* type)
{
    return true;
}

bool IsTypeHelper::isArrayType(Type* type)
{
    return false;
}


bool IsTypeHelper::isObjectType(FunctionType* type)
{
    return false;
}

bool IsTypeHelper::isObjectType(Type* type)
{
    return type->isComplete();
}

bool IsTypeHelper::isFunctionType(FunctionType* type)
{
    return true;
}

bool IsTypeHelper::isFunctionType(Type* type)
{
    return false;
}

/* base types */

bool IsTypeHelper::isLongDouble(LongDouble* type)
{
    return true;
}

bool IsTypeHelper::isLongDouble(Type* type)
{
    return false;
}

bool IsTypeHelper::isDouble(Double* type)
{
    return true;
}

bool IsTypeHelper::isDouble(Type* type)
{
    return false;
}

bool IsTypeHelper::isFloat(Float* type)
{
    return true;
}

bool IsTypeHelper::isFloat(Type* type)
{
    return false;
}

bool IsTypeHelper::isUnsignedLong(UnsignedLong* type)
{
    return true;
}

bool IsTypeHelper::isUnsignedLong(Type* type)
{
    return false;
}

bool IsTypeHelper::isSignedLong(SignedLong* type)
{
    return true;
}

bool IsTypeHelper::isSignedLong(Type* type)
{
    return false;
}

bool IsTypeHelper::isUnsignedInt(UnsignedInt* type)
{
    return true;
}

bool IsTypeHelper::isUnsignedInt(Type* type)
{
    return false;
}

/* "casting" ops */

PointerType* IsTypeHelper::getPointerType(Type* type)
{
    if (IsTypeHelper::isPointerType(type))
        return (PointerType*) type;
    else
        return NULL;
}

FunctionType* IsTypeHelper::getFunctionType(Type* type)
{
    if (IsTypeHelper::isFunctionType(type))
        return (FunctionType*) type;
    else
        return NULL;
}

///
/// @}
///