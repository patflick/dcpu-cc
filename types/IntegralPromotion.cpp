///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       IntegralPromotion.cpp
/// @brief      Definition of the IntegralPromotion helper class.
/// @author     Patrick Flick
///

#include "IntegralPromotion.h"
#include <errors/InternalCompilerException.h>

using namespace dtcc;
using namespace dtcc::types;


IntegralType* IntegralPromotion::promote(Type* type)
{
    throw new errors::InternalCompilerException("Cannot promote the general type " + type->toString());
}

IntegralType* IntegralPromotion::promote(SignedChar* type)
{
    return new SignedInt();
}

IntegralType* IntegralPromotion::promote(UnsignedChar* type)
{
    return new UnsignedInt();
}

IntegralType* IntegralPromotion::promote(SignedShort* type)
{
    return new SignedInt();
}

IntegralType* IntegralPromotion::promote(UnsignedShort* type)
{
    return new UnsignedInt();
}

IntegralType* IntegralPromotion::promote(EnumType* type)
{
    return new UnsignedInt();
}

IntegralType* IntegralPromotion::promote(IntegralType* type)
{
    // all others stay as they are
    return type;
}

///
/// @}
///