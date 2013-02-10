cmake_minimum_required(VERSION 2.8.5)

# Set header .h files
SET (VALUETYPES_HEADER
    valuetypes/LValue.h
    valuetypes/RValue.h
    valuetypes/CValue.h
    valuetypes/ValueType.h
    valuetypes/FunctionDesignator.h
    valuetypes/IsValueTypeHelper.h
    valuetypes/PromotionHelper.h
    valuetypes/ConstHelper.h
PARENT_SCOPE)



# Set source .cpp files
set (VALUETYPES_SOURCE
    valuetypes/LValue.cpp
    valuetypes/IsValueTypeHelper.cpp
    valuetypes/PromotionHelper.cpp
    valuetypes/ConstHelper.cpp
PARENT_SCOPE) 
