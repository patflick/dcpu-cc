///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       SignedLong.cpp
/// @brief      Definition of the SignedLong type class.
/// @author     Patrick Flick
///

#include "SignedLong.h"

using namespace dtcc::types;

// returns the word size of this type
uint16_t SignedLong::getWordSize()
{
    // return the word size
    // TODO in case of bigger types, return something else here
    return (uint16_t) 1u;
}

// returns the word size of this type
bool SignedLong::isComplete()
{
    // TODO in case of aggregate types, return the actual state here
    return true;
}

// returns the word size of this type
std::string SignedLong::toString()
{
    // return the name of the type
    return std::string("SignedLong");
}


// implements the destructor, which deletes all children
SignedLong::~SignedLong()
{

}

///
/// @}
///