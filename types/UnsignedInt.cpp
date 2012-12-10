///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       UnsignedInt.cpp
/// @brief      Definition of the UnsignedInt type class.
/// @author     Patrick Flick
///

#include "UnsignedInt.h"

using namespace dtcc::types;

// returns the word size of this type
uint16_t UnsignedInt::getWordSize()
{
    // return the word size
    // on the DCPU byte size == word size
    // (smallest addressable unit is 16 bit)
    return this->getByteSize();
}

// returns the word size of this type
uint16_t UnsignedInt::getByteSize()
{
    // return the word size
    // TODO in case of bigger types, return something else here
    return (uint16_t) 1;
}

// returns the word size of this type
bool UnsignedInt::isComplete()
{
    // TODO in case of aggregate types, return the actual state here
    return true;
}

// function for the type visitors
bool UnsignedInt::accept(TypeVisitor& tv)
{
    return tv.visit(this);
}

// returns the word size of this type
std::string UnsignedInt::toString()
{
    // return the name of the type
    return std::string("UnsignedInt");
}


// implements the destructor, which deletes all children
UnsignedInt::~UnsignedInt()
{

}

///
/// @}
///