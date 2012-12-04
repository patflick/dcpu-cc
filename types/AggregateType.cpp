///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       AggregateType.cpp
/// @brief      Definition of the AggregateType type class.
/// @author     Patrick Flick
///

#include "AggregateType.h"

using namespace dtcc::types;

// returns the word size of this type
uint16_t AggregateType::getWordSize()
{
    // return the word size
    // TODO in case of bigger types, return something else here
    return (uint16_t) 1u;
}

// returns the word size of this type
bool AggregateType::isComplete()
{
    // TODO in case of aggregate types, return the actual state here
    return true;
}

// returns the word size of this type
std::string AggregateType::toString()
{
    // return the name of the type
    return std::string("AggregateType");
}


// implements the destructor, which deletes all children
AggregateType::~AggregateType()
{

}

///
/// @}
///