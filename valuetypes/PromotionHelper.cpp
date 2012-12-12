///
/// @addtogroup LibDCPU-CI-Lang-C/ValueTypes
/// @{
///

///
/// @file       PromotionHelper.cpp
/// @brief      Definition of the PromotionHelper helper class.
/// @author     Patrick Flick
///


#include "PromotionHelper.h"
#include "IsValueTypeHelper.h"
#include "RValue.h"
#include "CValue.h"
#include <types/Type.h>
#include <types/ArithmeticType.h>
#include <types/IntegralPromotion.h>
#include <types/ArithmeticConversion.h>

#include <errors/InternalCompilerException.h>

#include <iostream>


using namespace dtcc::types;
using namespace dtcc::valuetypes;

ValueType* PromotionHelper::promote(ValueType* type)
{
    Type* promotedType = IntegralPromotion::promote(type->type);
    if (IsValueTypeHelper::isCValue(type))
    {
        return new CValue(promotedType);
    }
    else
        return new RValue(promotedType);
}

ValueType* PromotionHelper::commonType(ValueType* t1, ValueType* t2)
{
    ArithmeticType * at1, * at2;
    if (!IsTypeHelper::isArithmeticType(t1->type) || ! IsTypeHelper::isArithmeticType(t2->type))
    {
        throw new errors::InternalCompilerException("Cannot get common type from non arithmetic types");
    }
    at1 = (ArithmeticType*) t1->type;
    at2 = (ArithmeticType*) t2->type;
        
    
    Type* commonType = ArithmeticConversion::commonType(at1, at2);
    if (IsValueTypeHelper::isCValue(t1) && IsValueTypeHelper::isCValue(t2))
        return new CValue(commonType);
    else
        return new RValue(commonType);
}

///
/// @}
///