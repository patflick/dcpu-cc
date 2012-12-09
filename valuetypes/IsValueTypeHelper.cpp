///
/// @addtogroup LibDCPU-CI-Lang-C/ValueTypes
/// @{
///

///
/// @file       IsValueTypeHelper.cpp
/// @brief      Definition of the IsValueTypeHelper helper class.
/// @author     Patrick Flick
///


#include "IsValueTypeHelper.h"
using namespace dtcc::valuetypes;

bool IsValueTypeHelper::isFunctionDesignator(FunctionDesignator* type)
{
    return true;
}

bool IsValueTypeHelper::isFunctionDesignator(ValueType* type)
{
    return false;
}

bool IsValueTypeHelper::isRValue(RValue* type)
{
    return true;
}

bool IsValueTypeHelper::isRValue(ValueType* type)
{
    return false;
}

bool IsValueTypeHelper::isCValue(CValue* type)
{
    return true;
}

bool IsValueTypeHelper::isCValue(ValueType* type)
{
    return false;
}

bool IsValueTypeHelper::isLValue(LValue* type)
{
    return true;
}

bool IsValueTypeHelper::isLValue(ValueType* type)
{
    return false;
}

bool IsValueTypeHelper::isModifiableLValue(LValue* type)
{
    return type->isModifiable();
}

bool IsValueTypeHelper::isModifiableLValue(ValueType* type)
{
    return false;
}


RValue* IsValueTypeHelper::toRValue(ValueType* type)
{
    // TODO remove type qualifiers??
    return new RValue(type->type);
}

///
/// @}
///