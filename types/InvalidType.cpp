///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       InvalidType.cpp
/// @brief      Definition of the InvalidType type class.
/// @author     Patrick Flick
///

#include "InvalidType.h"

using namespace dtcc::types;

// returns the word size of this type
uint16_t InvalidType::getWordSize()
{
    // return the word size
    return (uint16_t) 0;
}

// returns the word size of this type
bool InvalidType::isComplete()
{
    return false;
}

// returns the word size of this type
std::string InvalidType::toString()
{
    // return the name of the type
    return std::string("InvalidType");
}

///
/// @}
///