///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       Float.cpp
/// @brief      Definition of the Float type class.
/// @author     Patrick Flick
///

#include "Float.h"

using namespace dtcc::types;

// returns the word size of this type
uint16_t Float::getWordSize()
{
    // return the word size
    // on the DCPU byte size == word size
    // (smallest addressable unit is 16 bit)
    return this->getByteSize();
}

// returns the word size of this type
uint16_t Float::getByteSize()
{
    // return the word size
    // TODO in case of bigger types, return something else here
    return (uint16_t) 1;
}

// returns the word size of this type
bool Float::isComplete()
{
    // TODO in case of aggregate types, return the actual state here
    return true;
}

// function for the type visitors
bool Float::accept(TypeVisitor& tv)
{
    return tv.visit(this);
}

// returns the word size of this type
std::string Float::toString()
{
    // return the name of the type
    return std::string("Float");
}


// implements the destructor, which deletes all children
Float::~Float()
{

}

///
/// @}
///