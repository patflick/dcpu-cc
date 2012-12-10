///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       SignedInt.cpp
/// @brief      Definition of the SignedInt type class.
/// @author     Patrick Flick
///

#include "SignedInt.h"

using namespace dtcc::types;

// returns the word size of this type
uint16_t SignedInt::getWordSize()
{
    // return the word size
    // on the DCPU byte size == word size
    // (smallest addressable unit is 16 bit)
    return this->getByteSize();
}

// returns the word size of this type
uint16_t SignedInt::getByteSize()
{
    // return the word size
    // TODO in case of bigger types, return something else here
    return (uint16_t) 1;
}

// returns the word size of this type
bool SignedInt::isComplete()
{
    // TODO in case of aggregate types, return the actual state here
    return true;
}

// function for the type visitors
bool SignedInt::accept(TypeVisitor& tv)
{
    return tv.visit(this);
}

// returns the word size of this type
std::string SignedInt::toString()
{
    // return the name of the type
    return std::string("SignedInt");
}


// implements the destructor, which deletes all children
SignedInt::~SignedInt()
{

}

///
/// @}
///