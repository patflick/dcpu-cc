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
#include "IsTypeHelper.h"
#include <errors/InternalCompilerException.h>

using namespace dtcc;
using namespace dtcc::types;


IntegralType* IntegralPromotion::promote(Type* type)
{
    if (!IsTypeHelper::isIntegralType(type))
    {
        throw new errors::InternalCompilerException("Cannot promote the non integral type " + type->toString());
    }
    else if (IsTypeHelper::isSignedChar(type)
        || IsTypeHelper::isSignedShort(type)
        || IsTypeHelper::isEnumType(type))
    {
        return new SignedInt();
    } else if (IsTypeHelper::isUnsignedChar(type)
        || IsTypeHelper::isUnsignedShort(type))
    {
        return new UnsignedInt();
    }
    else
        // type stays the same
        // we can safely cast, because we know it is an integral type
        return (IntegralType*) type;
    
}

///
/// @}
///