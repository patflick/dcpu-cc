///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       StructUnionType.cpp
/// @brief      Definition of the StructUnionType type class.
/// @author     Patrick Flick
///

#include "StructUnionType.h"

using namespace dtcc::types;

// returns the word size of this type
uint16_t StructUnionType::getWordSize()
{
    // return the word size
    // on the DCPU byte size == word size
    // (smallest addressable unit is 16 bit)
    return this->getByteSize();
}

// returns the word size of this type
uint16_t StructUnionType::getByteSize()
{
    // return the word size
    // TODO in case of bigger types, return something else here
    return (uint16_t) 1;
}

// returns the word size of this type
bool StructUnionType::isComplete()
{
    // TODO in case of aggregate types, return the actual state here
    return true;
}

// function for the type visitors
bool StructUnionType::accept(TypeVisitor& tv)
{
    return tv.visit(this);
}

// returns the word size of this type
std::string StructUnionType::toString()
{
    // return the name of the type
    return std::string("StructUnionType");
}


// implements the destructor, which deletes all children
StructUnionType::~StructUnionType()
{

}

///
/// @}
///