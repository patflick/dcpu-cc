///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       ArrayType.cpp
/// @brief      Definition of the ArrayType type class.
/// @author     Patrick Flick
///

#include "ArrayType.h"

using namespace dtcc::types;

// returns the word size of this type
uint16_t ArrayType::getWordSize()
{
    // return the word size
    // TODO in case of bigger types, return something else here
    return (uint16_t) 1u;
}

// returns the word size of this type
bool ArrayType::isComplete()
{
    // TODO in case of aggregate types, return the actual state here
    return true;
}

// returns the word size of this type
std::string ArrayType::toString()
{
    // return the name of the type
    return std::string("ArrayType");
}


// implements the destructor, which deletes all children
ArrayType::~ArrayType()
{

}

///
/// @}
///