///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       FunctionType.cpp
/// @brief      Definition of the FunctionType type class.
/// @author     Patrick Flick
///

#include "FunctionType.h"

using namespace dtcc::types;

// returns the word size of this type
uint16_t FunctionType::getWordSize()
{
    // return the word size
    // TODO in case of bigger types, return something else here
    return (uint16_t) 1u;
}

// returns the word size of this type
bool FunctionType::isComplete()
{
    // TODO in case of aggregate types, return the actual state here
    return true;
}

// returns the word size of this type
std::string FunctionType::toString()
{
    // return the name of the type
    return std::string("FunctionType");
}


// implements the destructor, which deletes all children
FunctionType::~FunctionType()
{
    this->safe_delete(this->returnType);
    this->safe_delete(this->paramTypes);
}

///
/// @}
///