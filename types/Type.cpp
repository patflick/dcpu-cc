///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       Type.cpp
/// @brief      Definition of the Type type class.
/// @author     Patrick Flick
///

#include "Type.h"

using namespace dcpucc::types;

// returns the word size of this type
std::string Type::toString()
{
    // return the name of the type
    return std::string("Type");
}


// implements the destructor, which deletes all children
Type::~Type()
{

}

///
/// @}
///