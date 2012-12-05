///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       UnsignedShort.cpp
/// @brief      Definition of the UnsignedShort type class.
/// @author     Patrick Flick
///

#include "UnsignedShort.h"

using namespace dtcc::types;

// returns the word size of this type
uint16_t UnsignedShort::getWordSize()
{
    // return the word size
    // TODO in case of bigger types, return something else here
    return (uint16_t) 1u;
}

// returns the word size of this type
bool UnsignedShort::isComplete()
{
    // TODO in case of aggregate types, return the actual state here
    return true;
}

// returns the word size of this type
std::string UnsignedShort::toString()
{
    // return the name of the type
    return std::string("UnsignedShort");
}


// implements the destructor, which deletes all children
UnsignedShort::~UnsignedShort()
{

}

///
/// @}
///