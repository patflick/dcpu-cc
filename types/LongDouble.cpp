///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       LongDouble.cpp
/// @brief      Definition of the LongDouble type class.
/// @author     Patrick Flick
///

#include "LongDouble.h"

using namespace dcpucc::types;

// returns the word size of this type
uint16_t LongDouble::getWordSize()
{
    // return the word size
    // on the DCPU byte size == word size
    // (smallest addressable unit is 16 bit)
    return this->getByteSize();
}

// returns the word size of this type
uint16_t LongDouble::getByteSize()
{
    // return the word size
    // TODO in case of bigger types, return something else here
    return (uint16_t) 1;
}

// returns the word size of this type
bool LongDouble::isComplete()
{
    // TODO in case of aggregate types, return the actual state here
    return true;
}

// function for the type visitors
bool LongDouble::accept(TypeVisitor& tv)
{
    return tv.visit(this);
}

// returns the word size of this type
std::string LongDouble::toString()
{
    // return the name of the type
    return std::string("LongDouble");
}


// implements the destructor, which deletes all children
LongDouble::~LongDouble()
{

}

///
/// @}
///