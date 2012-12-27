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
#include <errors/InternalCompilerException.h>

using namespace dtcc::codegen;

bool GetTypeImplVisitor::visit(Type * type)
{
    throw new errors::InternalCompilerException("Invalid type instance encountered: " + type->toString());
}


bool GetTypeImplVisitor::visit(Float * floatType)
{
    return false;
}


bool GetTypeImplVisitor::visit(Double * doubleType)
{
    return false;
}


bool GetTypeImplVisitor::visit(LongDouble * longDouble)
{
    return false;
}


bool GetTypeImplVisitor::visit(SignedChar * signedChar)
{
    return false;
}


bool GetTypeImplVisitor::visit(UnsignedChar * unsignedChar)
{
    return false;
}


bool GetTypeImplVisitor::visit(SignedShort * signedShort)
{
    return false;
}


bool GetTypeImplVisitor::visit(UnsignedShort * unsignedShort)
{
    return false;
}


bool GetTypeImplVisitor::visit(SignedInt * signedInt)
{
    return false;
}


bool GetTypeImplVisitor::visit(UnsignedInt * unsignedInt)
{
    return false;
}


bool GetTypeImplVisitor::visit(SignedLong * signedLong)
{
    return false;
}


bool GetTypeImplVisitor::visit(UnsignedLong * unsignedLong)
{
    return false;
}


bool GetTypeImplVisitor::visit(EnumType * enumType)
{
    return false;
}


bool GetTypeImplVisitor::visit(PointerType * pointerType)
{
    return false;
}


bool GetTypeImplVisitor::visit(FunctionType * functionType)
{
    return false;
}


bool GetTypeImplVisitor::visit(ArrayType * arrayType)
{
    return false;
}


bool GetTypeImplVisitor::visit(StructUnionType * structUnionType)
{
    return false;
}


bool GetTypeImplVisitor::visit(Void * voidType)
{
    return false;
}


bool GetTypeImplVisitor::visit(InvalidType * invalidType)
{
    return false;
}

///
/// @}
///