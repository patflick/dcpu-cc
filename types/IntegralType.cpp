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

using namespace dcpucc::types;


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