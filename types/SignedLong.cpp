///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       SignedLong.cpp
/// @brief      Definition of the SignedLong type class.
/// @author     Patrick Flick
///

#include "SignedLong.h"

using namespace dcpucc::types;

// returns the word size of this type
uint16_t SignedLong::getWordSize()
{
    // return the word size
    // on the DCPU byte size == word size
    // (smallest addressable unit is 16 bit)
    return this->getByteSize();
}

// returns the word size of this type
uint16_t SignedLong::getByteSize()
{
    // return the word size
    // TODO in case of bigger types, return something else here
    return (uint16_t) 1;
}

// returns the word size of this type
bool SignedLong::isComplete()
{
    // TODO in case of aggregate types, return the actual state here
    return true;
}

// function for the type visitors
bool SignedLong::accept(TypeVisitor& tv)
{
    return tv.visit(this);
}

// returns the word size of this type
std::string SignedLong::toString()
{
    // return the name of the type
    return std::string("SignedLong");
}


// implements the destructor, which deletes all children
SignedLong::~SignedLong()
{

}

///
/// @}
///