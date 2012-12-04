///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       UnsignedChar.cpp
/// @brief      Definition of the UnsignedChar type class.
/// @author     Patrick Flick
///

#include "UnsignedChar.h"

using namespace dtcc::types;

// returns the word size of this type
uint16_t UnsignedChar::getWordSize()
{
    // return the word size
    // TODO in case of bigger types, return something else here
    return (uint16_t) 1u;
}

// returns the word size of this type
bool UnsignedChar::isComplete()
{
    // TODO in case of aggregate types, return the actual state here
    return true;
}

// returns the word size of this type
std::string UnsignedChar::toString()
{
    // return the name of the type
    return std::string("UnsignedChar");
}


// implements the destructor, which deletes all children
UnsignedChar::~UnsignedChar()
{

}

///
/// @}
///