///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       BitField.cpp
/// @brief      Definition of the BitField type class.
/// @author     Patrick Flick
///

#include "BitField.h"

using namespace dcpucc::types;

// returns the word size of this type
uint16_t BitField::getWordSize()
{
    // return the word size
    // on the DCPU byte size == word size
    // (smallest addressable unit is 16 bit)
    return this->getByteSize();
}

// returns the word size of this type
uint16_t BitField::getByteSize()
{
    // return the word size
    return (uint16_t) 1;
}

// returns the word size of this type
bool BitField::isComplete()
{
    return true;
}

// function for the type visitors
bool BitField::accept(TypeVisitor& tv)
{
    return tv.visit(this);
}

// returns the word size of this type
std::string BitField::toString()
{
    // return the name of the type
    return std::string("BitField");
}


// implements the destructor, which deletes all children
BitField::~BitField()
{

}

///
/// @}
///