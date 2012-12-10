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