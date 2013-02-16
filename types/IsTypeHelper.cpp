///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       IsTypeHelper.cpp
/// @brief      Definition of the IsTypeHelper helper class.
/// @author     Patrick Flick
///
    
#include "IsTypeHelper.h"
#include "alltypes.h"
#include "TypeVisitor.h"
#include <errors/InternalCompilerException.h>

using namespace dcpucc;
using namespace dcpucc::types;
    

bool IsTypeHelper::isType(Type * type)
{
    // quite a trivial question, but yea .. xD
    return true;
}


bool IsTypeHelper::isScalarType(Type * type)
{
    if (IsTypeHelper::isArithmeticType(type)
        || IsTypeHelper::isPointerType(type))
    {
        return true;
    }
    else
        return false;
}


bool IsTypeHelper::isArithmeticType(Type * type)
{
    if (IsTypeHelper::isFloatType(type)
        || IsTypeHelper::isIntegralType(type))
    {
        return true;
    }
    else
        return false;
}


bool IsTypeHelper::isFloatType(Type * type)
{
    if (IsTypeHelper::isFloat(type)
        || IsTypeHelper::isDouble(type)
        || IsTypeHelper::isLongDouble(type))
    {
        return true;
    }
    else
        return false;
}


bool IsTypeHelper::isFloat(Type * type)
{
    class : public TypeVisitor
    {
    public:
        virtual bool visit(Float * t)
        {
            return true;
        }
    } tv;
    return type->accept(tv);
}


bool IsTypeHelper::isDouble(Type * type)
{
    class : public TypeVisitor
    {
    public:
        virtual bool visit(Double * t)
        {
            return true;
        }
    } tv;
    return type->accept(tv);
}


bool IsTypeHelper::isLongDouble(Type * type)
{
    class : public TypeVisitor
    {
    public:
        virtual bool visit(LongDouble * t)
        {
            return true;
        }
    } tv;
    return type->accept(tv);
}


bool IsTypeHelper::isIntegralType(Type * type)
{
    if (IsTypeHelper::isSignedChar(type)
        || IsTypeHelper::isUnsignedChar(type)
        || IsTypeHelper::isSignedShort(type)
        || IsTypeHelper::isUnsignedShort(type)
        || IsTypeHelper::isSignedInt(type)
        || IsTypeHelper::isUnsignedInt(type)
        || IsTypeHelper::isSignedLong(type)
        || IsTypeHelper::isUnsignedLong(type)
        || IsTypeHelper::isEnumType(type)
        || IsTypeHelper::isBitField(type))
    {
        return true;
    }
    else
        return false;
}


bool IsTypeHelper::isSignedChar(Type * type)
{
    class : public TypeVisitor
    {
    public:
        virtual bool visit(SignedChar * t)
        {
            return true;
        }
    } tv;
    return type->accept(tv);
}


bool IsTypeHelper::isUnsignedChar(Type * type)
{
    class : public TypeVisitor
    {
    public:
        virtual bool visit(UnsignedChar * t)
        {
            return true;
        }
    } tv;
    return type->accept(tv);
}


bool IsTypeHelper::isSignedShort(Type * type)
{
    class : public TypeVisitor
    {
    public:
        virtual bool visit(SignedShort * t)
        {
            return true;
        }
    } tv;
    return type->accept(tv);
}


bool IsTypeHelper::isUnsignedShort(Type * type)
{
    class : public TypeVisitor
    {
    public:
        virtual bool visit(UnsignedShort * t)
        {
            return true;
        }
    } tv;
    return type->accept(tv);
}


bool IsTypeHelper::isSignedInt(Type * type)
{
    class : public TypeVisitor
    {
    public:
        virtual bool visit(SignedInt * t)
        {
            return true;
        }
    } tv;
    return type->accept(tv);
}


bool IsTypeHelper::isUnsignedInt(Type * type)
{
    class : public TypeVisitor
    {
    public:
        virtual bool visit(UnsignedInt * t)
        {
            return true;
        }
    } tv;
    return type->accept(tv) || isNullPointer(type);
}

bool IsTypeHelper::isNullPointer(Type * type)
{
    class : public TypeVisitor
    {
    public:
        virtual bool visit(NullPointer * t)
        {
            return true;
        }
    } tv;
    return type->accept(tv);
}


bool IsTypeHelper::isBitField(Type * type)
{
    class : public TypeVisitor
    {
    public:
        virtual bool visit(BitField * t)
        {
            return true;
        }
    } tv;
    return type->accept(tv);
}

bool IsTypeHelper::isSignedLong(Type * type)
{
    class : public TypeVisitor
    {
    public:
        virtual bool visit(SignedLong * t)
        {
            return true;
        }
    } tv;
    return type->accept(tv);
}


bool IsTypeHelper::isUnsignedLong(Type * type)
{
    class : public TypeVisitor
    {
    public:
        virtual bool visit(UnsignedLong * t)
        {
            return true;
        }
    } tv;
    return type->accept(tv);
}


bool IsTypeHelper::isEnumType(Type * type)
{
    class : public TypeVisitor
    {
    public:
        virtual bool visit(EnumType * t)
        {
            return true;
        }
    } tv;
    return type->accept(tv);
}


bool IsTypeHelper::isPointerType(Type * type)
{
    class : public TypeVisitor
    {
    public:
        virtual bool visit(PointerType * t)
        {
            return true;
        }
    } tv;
    return type->accept(tv) || isNullPointer(type);
}


bool IsTypeHelper::isFunctionType(Type * type)
{
    class : public TypeVisitor
    {
    public:
        virtual bool visit(FunctionType * t)
        {
            return true;
        }
    } tv;
    return type->accept(tv);
}


bool IsTypeHelper::isAggregateType(Type * type)
{
    if (IsTypeHelper::isArrayType(type)
        || IsTypeHelper::isStructUnionType(type))
    {
        return true;
    }
    else
        return false;
}


bool IsTypeHelper::isArrayType(Type * type)
{
    class : public TypeVisitor
    {
    public:
        virtual bool visit(ArrayType * t)
        {
            return true;
        }
    } tv;
    return type->accept(tv);
}


bool IsTypeHelper::isStructUnionType(Type * type)
{
    class : public TypeVisitor
    {
    public:
        virtual bool visit(StructUnionType * t)
        {
            return true;
        }
    } tv;
    return type->accept(tv);
}


bool IsTypeHelper::isVoid(Type * type)
{
    class : public TypeVisitor
    {
    public:
        virtual bool visit(Void * t)
        {
            return true;
        }
    } tv;
    return type->accept(tv);
}


bool IsTypeHelper::isInvalidType(Type * type)
{
    class : public TypeVisitor
    {
    public:
        virtual bool visit(InvalidType * t)
        {
            return true;
        }
    } tv;
    return type->accept(tv);
}


bool IsTypeHelper::isObjectType(Type* type)
{
    return type->isComplete();
}


/* "casting" ops */

PointerType* IsTypeHelper::getPointerType(Type* type)
{
    if (IsTypeHelper::isPointerType(type))
    {
        if (IsTypeHelper::isNullPointer(type))
        {
            return new PointerType(new Void());
        }
        return (PointerType*) type;
    }
    else
        return NULL;
}

ArrayType* IsTypeHelper::getArrayType(Type* type)
{
    if (IsTypeHelper::isArrayType(type))
        return (ArrayType*) type;
    else
        return NULL;
}

StructUnionType* IsTypeHelper::getStructUnionType(Type* type)
{
    if (IsTypeHelper::isStructUnionType(type))
        return (StructUnionType*) type;
    else
        return NULL;
}

PointerType* IsTypeHelper::pointerFromArrayType(Type* type)
{
    if (IsTypeHelper::isArrayType(type))
    {
        ArrayType* arType = (ArrayType*) type;
        PointerType* ptrType = new PointerType(arType->basetype);
        ptrType->isConst = true;
        return ptrType;
    }
    else
        return NULL;
}

FunctionType* IsTypeHelper::getFunctionType(Type* type)
{
    if (IsTypeHelper::isFunctionType(type))
        return (FunctionType*) type;
    else
        return NULL;
}


uint16_t IsTypeHelper::getPointerBaseSize(Type* type)
{
    PointerType* ptr;
    if (!IsTypeHelper::isPointerType(type))
        throw new errors::InternalCompilerException("Cannot get size of base class of non pointer type");
        
    ptr = IsTypeHelper::getPointerType(type);
    
    uint16_t size = ptr->baseType->getWordSize();
    if (size == 0)
        return 1;
    return size;
}

///
/// @}
///