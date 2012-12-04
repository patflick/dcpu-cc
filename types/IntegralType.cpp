///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       IntegralType.cpp
/// @brief      Definition of the IntegralType type class.
/// @author     Patrick Flick
///

#include "IntegralType.h"

using namespace dtcc::types;

// returns the word size of this type
uint16_t IntegralType::getWordSize()
{
    // return the word size
    // TODO in case of bigger types, return something else here
    return (uint16_t) 1u;
}

// returns the word size of this type
bool IntegralType::isComplete()
{
    // TODO in case of aggregate types, return the actual state here
    return true;
}

// returns the word size of this type
std::string IntegralType::toString()
{
    // return the name of the type
    return std::string("IntegralType");
}


// implements the destructor, which deletes all children
IntegralType::~IntegralType()
{

}

///
/// @}
///