///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       ArrayType.cpp
/// @brief      Definition of the ArrayType type class.
/// @author     Patrick Flick
///

#include "ArrayType.h"

using namespace dtcc::types;

// returns the word size of this type
uint16_t ArrayType::getWordSize()
{
    // return the word size
    // on the DCPU byte size == word size
    // (smallest addressable unit is 16 bit)
    return this->getByteSize();
}

// returns the word size of this type
uint16_t ArrayType::getByteSize()
{
    // return the word size
    // TODO in case of bigger types, return something else here
    return (uint16_t) size * baseTypeSize;
}

// returns the word size of this type
bool ArrayType::isComplete()
{
    return size > 0;
}

// function for the type visitors
bool ArrayType::accept(TypeVisitor& tv)
{
    return tv.visit(this);
}

// returns the word size of this type
std::string ArrayType::toString()
{
    // return the name of the type
    return std::string("ArrayType");
}


// implements the destructor, which deletes all children
ArrayType::~ArrayType()
{
    this->safe_delete(this->basetype);

}

///
/// @}
///