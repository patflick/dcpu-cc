///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       InvalidType.cpp
/// @brief      Definition of the InvalidType type class.
/// @author     Patrick Flick
///

#include "InvalidType.h"

using namespace dcpucc::types;

// returns the word size of this type
uint16_t InvalidType::getWordSize()
{
    // return the word size
    // on the DCPU byte size == word size
    // (smallest addressable unit is 16 bit)
    return this->getByteSize();
}

// returns the word size of this type
uint16_t InvalidType::getByteSize()
{
    // return the word size
    // TODO in case of bigger types, return something else here
    return (uint16_t) 1;
}

// returns the word size of this type
bool InvalidType::isComplete()
{
    // TODO in case of aggregate types, return the actual state here
    return true;
}

// function for the type visitors
bool InvalidType::accept(TypeVisitor& tv)
{
    return tv.visit(this);
}

// returns the word size of this type
std::string InvalidType::toString()
{
    // return the name of the type
    return std::string("InvalidType");
}


// implements the destructor, which deletes all children
InvalidType::~InvalidType()
{

}

///
/// @}
///