///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       Void.cpp
/// @brief      Definition of the Void type class.
/// @author     Patrick Flick
///

#include "Void.h"

using namespace dtcc::types;

// returns the word size of this type
uint16_t Void::getWordSize()
{
    // return the word size
    // on the DCPU byte size == word size
    // (smallest addressable unit is 16 bit)
    return this->getByteSize();
}

// returns the word size of this type
uint16_t Void::getByteSize()
{
    // return the word size
    // TODO in case of bigger types, return something else here
    return (uint16_t) 1;
}

// returns the word size of this type
bool Void::isComplete()
{
    // TODO in case of aggregate types, return the actual state here
    return true;
}

// function for the type visitors
bool Void::accept(TypeVisitor& tv)
{
    return tv.visit(this);
}

// returns the word size of this type
std::string Void::toString()
{
    // return the name of the type
    return std::string("Void");
}


// implements the destructor, which deletes all children
Void::~Void()
{

}

///
/// @}
///