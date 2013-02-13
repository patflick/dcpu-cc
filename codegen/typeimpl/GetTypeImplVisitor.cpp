///
/// @addtogroup LibDCPU-CI-Lang-C/CodeGen
/// @{
///

///
/// @file       GetTypeImplVisitor.cpp
/// @brief      Definition of the GetTypeImplVisitor visitor class.
/// @author     Patrick Flick
///

#include "GetTypeImplVisitor.h"
#include "SignedInt16.h"
#include "UnsignedInt16.h"
#include "BitField16.h"
#include <errors/InternalCompilerException.h>

using namespace dcpucc::codegen;

bool GetTypeImplVisitor::visit(Type * type)
{
    throw new errors::InternalCompilerException("Invalid type instance encountered: " + type->toString());
}

TypeImplementation* GetTypeImplVisitor::getTypeImplementation()
{
    return this->typeImpl;
}


bool GetTypeImplVisitor::visit(Float * floatType)
{
    this->typeImpl = this->sint16;
    return true;
}


bool GetTypeImplVisitor::visit(Double * doubleType)
{
    this->typeImpl = this->sint16;
    return true;
}


bool GetTypeImplVisitor::visit(LongDouble * longDouble)
{
    this->typeImpl = this->sint16;
    return true;
}


bool GetTypeImplVisitor::visit(SignedChar * signedChar)
{
    this->typeImpl = this->sint16;
    return true;
}


bool GetTypeImplVisitor::visit(UnsignedChar * unsignedChar)
{
    this->typeImpl = this->uint16;
    return true;
}


bool GetTypeImplVisitor::visit(SignedShort * signedShort)
{
    this->typeImpl = this->sint16;
    return true;
}


bool GetTypeImplVisitor::visit(UnsignedShort * unsignedShort)
{
    this->typeImpl = this->uint16;
    return true;
}


bool GetTypeImplVisitor::visit(SignedInt * signedInt)
{
    this->typeImpl = this->sint16;
    return true;
}


bool GetTypeImplVisitor::visit(UnsignedInt * unsignedInt)
{
    this->typeImpl = this->uint16;
    return true;
}


bool GetTypeImplVisitor::visit(SignedLong * signedLong)
{
    this->typeImpl = this->sint16;
    return true;
}


bool GetTypeImplVisitor::visit(UnsignedLong * unsignedLong)
{
    this->typeImpl = this->uint16;
    return true;
}


bool GetTypeImplVisitor::visit(EnumType * enumType)
{
    this->typeImpl = this->sint16;
    return true;
}


bool GetTypeImplVisitor::visit(PointerType * pointerType)
{
    this->typeImpl = this->uint16;
    return true;
}

bool GetTypeImplVisitor::visit(BitField * bitfield)
{
    this->typeImpl = new BitField16(bitfield->offset, bitfield->length);
    return true;
}


bool GetTypeImplVisitor::visit(FunctionType * functionType)
{
    throw new errors::InternalCompilerException("Type is not a base type: " + functionType->toString());
}


bool GetTypeImplVisitor::visit(ArrayType * arrayType)
{
    throw new errors::InternalCompilerException("Type is not a base type: " + arrayType->toString());
}


bool GetTypeImplVisitor::visit(StructUnionType * structUnionType)
{
    throw new errors::InternalCompilerException("Type is not a base type: " + structUnionType->toString());
}


bool GetTypeImplVisitor::visit(Void * voidType)
{
    throw new errors::InternalCompilerException("Type is not a base type: " + voidType->toString());
}


bool GetTypeImplVisitor::visit(InvalidType * invalidType)
{
    throw new errors::InternalCompilerException("Type is not a base type: " + invalidType->toString());
}

///
/// @}
///