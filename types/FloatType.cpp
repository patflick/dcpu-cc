///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       FloatType.cpp
/// @brief      Definition of the FloatType type class.
/// @author     Patrick Flick
///

#include "FloatType.h"

using namespace dtcc::types;

// returns the word size of this type
uint16_t FloatType::getWordSize()
{
    // return the word size
    // TODO in case of bigger types, return something else here
    return (uint16_t) 1u;
}

// returns the word size of this type
bool FloatType::isComplete()
{
    // TODO in case of aggregate types, return the actual state here
    return true;
}

// returns the word size of this type
std::string FloatType::toString()
{
    // return the name of the type
    return std::string("FloatType");
}


// implements the destructor, which deletes all children
FloatType::~FloatType()
{

}

///
/// @}
///