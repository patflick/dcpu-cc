///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       EnumType.cpp
/// @brief      Definition of the EnumType type class.
/// @author     Patrick Flick
///

#include "EnumType.h"

using namespace dcpucc::types;

// returns the word size of this type
uint16_t EnumType::getWordSize()
{
    // return the word size
    // on the DCPU byte size == word size
    // (smallest addressable unit is 16 bit)
    return this->getByteSize();
}

// returns the word size of this type
uint16_t EnumType::getByteSize()
{
    // return the word size
    // TODO in case of bigger types, return something else here
    return (uint16_t) 1;
}

// returns the word size of this type
bool EnumType::isComplete()
{
    // TODO in case of aggregate types, return the actual state here
    return true;
}

// function for the type visitors
bool EnumType::accept(TypeVisitor& tv)
{
    return tv.visit(this);
}

// returns the word size of this type
std::string EnumType::toString()
{
    // return the name of the type
    return std::string("EnumType");
}


// implements the destructor, which deletes all children
EnumType::~EnumType()
{

}

///
/// @}
///