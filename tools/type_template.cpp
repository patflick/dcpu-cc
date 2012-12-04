///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       %ClassName%.cpp
/// @brief      Definition of the %ClassName% type class.
/// @author     Patrick Flick
///

#include "%ClassName%.h"

using namespace dtcc::types;

// returns the word size of this type
uint16_t %ClassName%::getWordSize()
{
    // return the word size
    // TODO in case of bigger types, return something else here
    return (uint16_t) 1u;
}

// returns the word size of this type
bool %ClassName%::isComplete()
{
    // TODO in case of aggregate types, return the actual state here
    return true;
}

// returns the word size of this type
std::string %ClassName%::toString()
{
    // return the name of the type
    return std::string("%ClassName%");
}


// implements the destructor, which deletes all children
%ClassName%::~%ClassName%()
{
%deleteClassMembers%
}

///
/// @}
///