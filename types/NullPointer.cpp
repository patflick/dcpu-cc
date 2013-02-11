///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       NullPointer.cpp
/// @brief      Definition of the NullPointer type class.
/// @author     Patrick Flick
///

#include "NullPointer.h"

using namespace dcpucc::types;

// returns the word size of this type
uint16_t NullPointer::getWordSize()
{
    // return the word size
    // on the DCPU byte size == word size
    // (smallest addressable unit is 16 bit)
    return this->getByteSize();
}

// returns the word size of this type
uint16_t NullPointer::getByteSize()
{
    // return the word size
    return (uint16_t) 1;
}

// returns the word size of this type
bool NullPointer::isComplete()
{
    return true;
}

// function for the type visitors
bool NullPointer::accept(TypeVisitor& tv)
{
    return tv.visit(this);
}

// returns the word size of this type
std::string NullPointer::toString()
{
    // return the name of the type
    return std::string("NullPointer");
}


// implements the destructor, which deletes all children
NullPointer::~NullPointer()
{

}

///
/// @}
///