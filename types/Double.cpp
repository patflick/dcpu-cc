///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       Double.cpp
/// @brief      Definition of the Double type class.
/// @author     Patrick Flick
///

#include "Double.h"

using namespace dtcc::types;

// returns the word size of this type
uint16_t Double::getWordSize()
{
    // return the word size
    // TODO in case of bigger types, return something else here
    return (uint16_t) 1u;
}

// returns the word size of this type
bool Double::isComplete()
{
    // TODO in case of aggregate types, return the actual state here
    return true;
}

// returns the word size of this type
std::string Double::toString()
{
    // return the name of the type
    return std::string("Double");
}


// implements the destructor, which deletes all children
Double::~Double()
{

}

///
/// @}
///