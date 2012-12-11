///
/// @addtogroup LibDCPU-CI-Lang-C/ValueTypes
/// @{
///

///
/// @file       LValue.cpp
/// @brief      Definition of the LValue class.
/// @author     Patrick Flick
///

#include "LValue.h"
#include <types/IsTypeHelper.h>

using namespace dtcc;
using namespace dtcc::valuetypes;

LValue::LValue(types::Type* type) : ValueType(type, LVALUE)
{
    // TODO check if type is a struct type 
    // and whether this struct type has const members
    if (types::IsTypeHelper::isArrayType(type)
        || ! type->isComplete()
        || type->isConst
    )
    {
        this->m_modifiable = false;
    }
    else
    {
        this->m_modifiable = true;
    }
}


bool LValue::isModifiable()
{
    return this->m_modifiable;
}


///
/// @}
///