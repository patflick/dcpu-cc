///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       Void.cpp
/// @brief      Definition of the Void type class.
/// @author     Patrick Flick
///

#include "Void.h"

using namespace dtcc::types;

// returns the word size of this type
uint16_t Void::getWordSize()
{
    // return the word size
    return (uint16_t) 0;
}

// returns the word size of this type
bool Void::isComplete()
{
    return false;
}

// returns the word size of this type
std::string Void::toString()
{
    // return the name of the type
    return std::string("void");
}

///
/// @}
///