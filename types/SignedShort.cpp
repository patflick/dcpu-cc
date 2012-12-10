///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       SignedShort.cpp
/// @brief      Definition of the SignedShort type class.
/// @author     Patrick Flick
///

#include "SignedShort.h"

using namespace dtcc::types;

// returns the word size of this type
uint16_t SignedShort::getWordSize()
{
    // return the word size
    // on the DCPU byte size == word size
    // (smallest addressable unit is 16 bit)
    return this->getByteSize();
}

// returns the word size of this type
uint16_t SignedShort::getByteSize()
{
    // return the word size
    // TODO in case of bigger types, return something else here
    return (uint16_t) 1;
}

// returns the word size of this type
bool SignedShort::isComplete()
{
    // TODO in case of aggregate types, return the actual state here
    return true;
}

// function for the type visitors
bool SignedShort::accept(TypeVisitor& tv)
{
    return tv.visit(this);
}

// returns the word size of this type
std::string SignedShort::toString()
{
    // return the name of the type
    return std::string("SignedShort");
}


// implements the destructor, which deletes all children
SignedShort::~SignedShort()
{

}

///
/// @}
///