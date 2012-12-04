///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       ArithmeticType.cpp
/// @brief      Definition of the ArithmeticType type class.
/// @author     Patrick Flick
///

#include "ArithmeticType.h"

using namespace dtcc::types;

// returns the word size of this type
uint16_t ArithmeticType::getWordSize()
{
    // return the word size
    // TODO in case of bigger types, return something else here
    return (uint16_t) 1u;
}

// returns the word size of this type
bool ArithmeticType::isComplete()
{
    // TODO in case of aggregate types, return the actual state here
    return true;
}

// returns the word size of this type
std::string ArithmeticType::toString()
{
    // return the name of the type
    return std::string("ArithmeticType");
}


// implements the destructor, which deletes all children
ArithmeticType::~ArithmeticType()
{

}

///
/// @}
///