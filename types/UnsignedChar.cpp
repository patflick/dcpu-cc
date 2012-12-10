///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       UnsignedChar.cpp
/// @brief      Definition of the UnsignedChar type class.
/// @author     Patrick Flick
///

#include "UnsignedChar.h"

using namespace dtcc::types;

// returns the word size of this type
uint16_t UnsignedChar::getWordSize()
{
    // return the word size
    // on the DCPU byte size == word size
    // (smallest addressable unit is 16 bit)
    return this->getByteSize();
}

// returns the word size of this type
uint16_t UnsignedChar::getByteSize()
{
    // return the word size
    // TODO in case of bigger types, return something else here
    return (uint16_t) 1;
}

// returns the word size of this type
bool UnsignedChar::isComplete()
{
    // TODO in case of aggregate types, return the actual state here
    return true;
}

// function for the type visitors
bool UnsignedChar::accept(TypeVisitor& tv)
{
    return tv.visit(this);
}

// returns the word size of this type
std::string UnsignedChar::toString()
{
    // return the name of the type
    return std::string("UnsignedChar");
}


// implements the destructor, which deletes all children
UnsignedChar::~UnsignedChar()
{

}

///
/// @}
///