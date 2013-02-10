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
using namespace dcpucc::valuetypes;


bool IsValueTypeHelper::isFunctionDesignator(ValueType* type)
{
    return type->valType == FUNC_DESIGN;
}

bool IsValueTypeHelper::isRValue(ValueType* type)
{
    return type->valType == RVALUE;
}

bool IsValueTypeHelper::isCValue(ValueType* type)
{
    return type->valType == CVALUE;
}

bool IsValueTypeHelper::isLValue(ValueType* type)
{
    if (type->valType == LVALUE)
        return true;
    else
        return false;
}

bool IsValueTypeHelper::isModifiableLValue(ValueType* type)
{
    if (!type->valType == LVALUE)
        return false;
    else
    {
        LValue* lval = (LValue*) type;
        return lval->isModifiable();
    }
}


RValue* IsValueTypeHelper::toRValue(ValueType* type)
{
    // TODO remove type qualifiers??
    return new RValue(type->type);
}

RValue* IsValueTypeHelper::toCorRValue(types::Type* newType, ValueType* vt)
{
    if (IsValueTypeHelper::isCValue(vt))
    {
        return new CValue(newType);
    }
    else
    {
        return new RValue(newType);
    }
}

RValue* IsValueTypeHelper::toCorRValue(types::Type* newType, ValueType* vt1, ValueType* vt2)
{
    if (IsValueTypeHelper::isCValue(vt1)
        && IsValueTypeHelper::isCValue(vt2))
    {
        return new CValue(newType);
    }
    else
    {
        return new RValue(newType);
    }
}

///
/// @}
///