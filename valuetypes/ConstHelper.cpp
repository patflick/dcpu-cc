///
/// @addtogroup LibDCPU-CI-Lang-C/ValueTypes
/// @{
///

///
/// @file       ConstHelper.cpp
/// @brief      Definition of the ConstHelper helper class.
/// @author     Patrick Flick
///


#include "ConstHelper.h"
#include "IsValueTypeHelper.h"
#include <errors/InternalCompilerException.h>

using namespace dtcc::valuetypes;

void ConstHelper::setFloatConst(ValueType* type, double floatConst)
{
    CValue* cv = ConstHelper::getCValue(type);
    cv->floatConst = floatConst;
    cv->isDoubleConst = true;
}

double ConstHelper::getFloatConst(ValueType* type)
{
    CValue* cv = ConstHelper::getCValue(type);
    if (cv->isDoubleConst)
        return cv->floatConst;
    else
        return (double) cv->integralConst;
}

void ConstHelper::setIntegralConst(ValueType* type, long intConst)
{
    CValue* cv = ConstHelper::getCValue(type);
    cv->integralConst = intConst;
    cv->isDoubleConst = false;
}

long ConstHelper::getIntegralConst(ValueType* type)
{
    CValue* cv = ConstHelper::getCValue(type);
    if (cv->isDoubleConst)
        return (long) cv->floatConst;
    else
        return cv->integralConst;
}


CValue* ConstHelper::getCValue(ValueType* type)
{
    if (!IsValueTypeHelper::isCValue(type))
    {
        throw new errors::InternalCompilerException("Trying to set constant value in non-constant ValueType");
    }
    return (CValue*) type;
}


///
/// @}
///