///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       TypeVisitor.cpp
/// @brief      Definition of the TypeVisitor visitor class.
/// @author     Patrick Flick
///

#include "TypeVisitor.h"
#include <errors/InternalCompilerException.h>

using namespace dcpucc::types;

bool TypeVisitor::visit(Type * type)
{
    throw new errors::InternalCompilerException("Invalid type instance encountered: " + type->toString());
}


bool TypeVisitor::visit(Float * floatType)
{
    return false;
}


bool TypeVisitor::visit(Double * doubleType)
{
    return false;
}


bool TypeVisitor::visit(LongDouble * longDouble)
{
    return false;
}


bool TypeVisitor::visit(SignedChar * signedChar)
{
    return false;
}


bool TypeVisitor::visit(UnsignedChar * unsignedChar)
{
    return false;
}


bool TypeVisitor::visit(SignedShort * signedShort)
{
    return false;
}


bool TypeVisitor::visit(UnsignedShort * unsignedShort)
{
    return false;
}


bool TypeVisitor::visit(SignedInt * signedInt)
{
    return false;
}


bool TypeVisitor::visit(UnsignedInt * unsignedInt)
{
    return false;
}

bool TypeVisitor::visit(NullPointer * nullPointer)
{
    return false;
}

bool TypeVisitor::visit(BitField * bitField)
{
    return false;
}

bool TypeVisitor::visit(SignedLong * signedLong)
{
    return false;
}


bool TypeVisitor::visit(UnsignedLong * unsignedLong)
{
    return false;
}


bool TypeVisitor::visit(EnumType * enumType)
{
    return false;
}


bool TypeVisitor::visit(PointerType * pointerType)
{
    return false;
}


bool TypeVisitor::visit(FunctionType * functionType)
{
    return false;
}


bool TypeVisitor::visit(ArrayType * arrayType)
{
    return false;
}


bool TypeVisitor::visit(StructUnionType * structUnionType)
{
    return false;
}


bool TypeVisitor::visit(Void * voidType)
{
    return false;
}


bool TypeVisitor::visit(InvalidType * invalidType)
{
    return false;
}

///
/// @}
///