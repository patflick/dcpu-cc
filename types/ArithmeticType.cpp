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

using namespace dcpucc::types;


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