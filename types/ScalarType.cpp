///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       ScalarType.cpp
/// @brief      Definition of the ScalarType type class.
/// @author     Patrick Flick
///

#include "ScalarType.h"

using namespace dtcc::types;


// returns the word size of this type
std::string ScalarType::toString()
{
    // return the name of the type
    return std::string("ScalarType");
}


// implements the destructor, which deletes all children
ScalarType::~ScalarType()
{

}

///
/// @}
///