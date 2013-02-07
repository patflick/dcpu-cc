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




void StructUnionType::addMember(std::string name, Type* type)
{
    if (isUnion)
        m_offsets[name] = 0;
    else
        m_offsets[name] = size;
    m_types[name] = type;
    if (isUnion)
    {
        if (size < type->getWordSize())
            size = type->getWordSize();
    }
    else
    {
        size += type->getWordSize();
    }
}

bool StructUnionType::hasMember(std::string name)
{
    if (m_offsets.find(name) == m_offsets.end())
        return false;
    else
        return true;
}


Type* StructUnionType::getMember(std::string name)
{
    return m_types[name];
}

unsigned int StructUnionType::getOffset(std::string name)
{
    return m_offsets[name];
}


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
    if (complete)
        return (uint16_t) size;
    else
        return 0;
}

// returns the word size of this type
bool StructUnionType::isComplete()
{
    return complete;
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