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

using namespace dcpucc::types;

// returns the word size of this type
uint16_t %ClassName%::getWordSize()
{
    // return the word size
    // on the DCPU byte size == word size
    // (smallest addressable unit is 16 bit)
    return this->getByteSize();
}

// returns the word size of this type
uint16_t %ClassName%::getByteSize()
{
    // return the word size
    // TODO in case of bigger types, return something else here
    return (uint16_t) 1;
}

// returns the word size of this type
bool %ClassName%::isComplete()
{
    // TODO in case of aggregate types, return the actual state here
    return true;
}

// function for the type visitors
bool %ClassName%::accept(TypeVisitor& tv)
{
    return tv.visit(this);
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