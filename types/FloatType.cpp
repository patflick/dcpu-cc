///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       FloatType.cpp
/// @brief      Definition of the FloatType type class.
/// @author     Patrick Flick
///

#include "FloatType.h"

using namespace dtcc::types;


// returns the word size of this type
std::string FloatType::toString()
{
    // return the name of the type
    return std::string("FloatType");
}


// implements the destructor, which deletes all children
FloatType::~FloatType()
{

}

///
/// @}
///