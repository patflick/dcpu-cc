///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       LongDouble.cpp
/// @brief      Definition of the LongDouble type class.
/// @author     Patrick Flick
///

#include "LongDouble.h"

using namespace dtcc::types;

// returns the word size of this type
uint16_t LongDouble::getWordSize()
{
    // return the word size
    // TODO in case of bigger types, return something else here
    return (uint16_t) 1u;
}

// returns the word size of this type
bool LongDouble::isComplete()
{
    // TODO in case of aggregate types, return the actual state here
    return true;
}

// returns the word size of this type
std::string LongDouble::toString()
{
    // return the name of the type
    return std::string("LongDouble");
}


// implements the destructor, which deletes all children
LongDouble::~LongDouble()
{

}

///
/// @}
///