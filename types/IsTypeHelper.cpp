///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       IsTypeHelper.h
/// @brief      Definition of the IsTypeHelper helper class.
/// @author     Patrick Flick
///
    
#include "IsTypeHelper.h"
using namespace dtcc::types;
    
bool IsTypeHelper::isScalarType(ScalarType* type)
{
    return true;
}

bool IsTypeHelper::isScalarType(Type* type)
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


///
/// @}
///