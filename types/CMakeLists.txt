cmake_minimum_required(VERSION 2.8.5)
project(libdcpu-cc)


# Set header .h files
SET (TYPES_HEADER
    types/AggregateType.h
    types/alltypes.h
    types/ArithmeticConversion.h
    types/ArithmeticType.h
    types/ArrayType.h
    types/Double.h
    types/EnumType.h
    types/Float.h
    types/FloatType.h
    types/FunctionType.h
    types/IntegralPromotion.h
    types/IntegralType.h
    types/InvalidType.h
    types/IsTypeHelper.h
    types/LongDouble.h
    types/ParameterTypeList.h
    types/PointerType.h
    types/ScalarType.h
    types/SignedChar.h
    types/SignedInt.h
    types/SignedLong.h
    types/SignedShort.h
    types/StructUnionType.h
    types/Type.h
    types/TypeVisitor.h
    types/UnsignedChar.h
    types/UnsignedInt.h
    types/UnsignedLong.h
    types/UnsignedShort.h
    types/Void.h
PARENT_SCOPE)

# Set source .cpp files
set (TYPES_SOURCE
    types/AggregateType.cpp
    types/ArithmeticConversion.cpp
    types/ArithmeticType.cpp
    types/ArrayType.cpp
    types/Double.cpp
    types/EnumType.cpp
    types/Float.cpp
    types/FloatType.cpp
    types/FunctionType.cpp
    types/IntegralPromotion.cpp
    types/IntegralType.cpp
    types/InvalidType.cpp
    types/IsTypeHelper.cpp
    types/LongDouble.cpp
    types/PointerType.cpp
    types/ScalarType.cpp
    types/SignedChar.cpp
    types/SignedInt.cpp
    types/SignedLong.cpp
    types/SignedShort.cpp
    types/StructUnionType.cpp
    types/Type.cpp
    types/TypeVisitor.cpp
    types/UnsignedChar.cpp
    types/UnsignedInt.cpp
    types/UnsignedLong.cpp
    types/UnsignedShort.cpp
    types/Void.cpp
PARENT_SCOPE) 