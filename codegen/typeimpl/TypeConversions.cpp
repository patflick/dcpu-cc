///
/// @addtogroup LibDCPU-CI-Lang-C/CodeGen
/// @{
///

///
/// @file       TypeConversions.cpp
/// @brief      Definition of the TypeConversions class.
/// @author     Patrick Flick
///
/// 

#include "TypeConversions.h"
#include <errors/InternalCompilerException.h>
#include <types/alltypes.h>

using namespace dtcc;
using namespace dtcc::codegen;

void TypeConversions::copyIfDifferent(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    if (posB != posA)
    {
        ass << "    SET " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
    }
}

int TypeConversions::typeToNr(types::Type* type)
{
    if (types::IsTypeHelper::isSignedChar(type) || types::IsTypeHelper::isUnsignedChar(type))
    {
        return 1;
    }
    if (types::IsTypeHelper::isSignedShort(type) || types::IsTypeHelper::isUnsignedShort(type))
    {
        return 2;
    }
    if (types::IsTypeHelper::isSignedInt(type) || types::IsTypeHelper::isUnsignedInt(type))
    {
        return 3;
    }
    if (types::IsTypeHelper::isSignedLong(type) || types::IsTypeHelper::isUnsignedLong(type))
    {
        return 4;
    }
    if (types::IsTypeHelper::isFloat(type))
    {
        return 5;
    }
    if (types::IsTypeHelper::isDouble(type))
    {
        return 6;
    }
    if (types::IsTypeHelper::isLongDouble(type))
    {
        return 7;
    }
}

bool TypeConversions::isSigned(types::Type* type)
{
    if (types::IsTypeHelper::isUnsignedChar(type)
        || types::IsTypeHelper::isUnsignedShort(type)
        || types::IsTypeHelper::isUnsignedInt(type)
        || types::IsTypeHelper::isUnsignedLong(type))
    {
        return false;
    }
    else
        return true;
}


/// Returns whether a type conversion has to be executed
bool TypeConversions::needsConvert(types::Type* from, types::Type* to)
{
    int toNr = typeToNr(to);
    int fromNr = typeToNr(from);
    bool sign = isSigned(to);
    
    if (toNr < 4 && fromNr < 4)
        return false;
    else if (toNr == fromNr)
        return false;
    else if (toNr >= 5 && fromNr >= 5)
        return false;
    else
        return true;
}

void TypeConversions::convert(types::Type* from, types::Type* to, AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    /* 
     *  The type conversions are implemented according to this scheme:
     * 
     *   char <-> short <->  int  <-> long
     *                       ^         ^
     *                       |         |
     *                       v         v
     *                     float <-> double <-> long double
     * 
     * i.e. if a float is converted to char it takes the route:
     *       float2int, int2short, short2char
     */
    
    // first assign numbers to each type, so we know whether we need to up or downcast
    
    int toNr = typeToNr(to);
    int fromNr = typeToNr(from);
    bool sign = isSigned(to);
    
    unsigned int toSize = to->getWordSize();
    unsigned int fromSize = from->getWordSize();
    
    
    if (toNr > fromNr)
    {
        ValuePosition* oneWordFrom = posA;
        ValuePosition* oneWordTo = posB;
        ValuePosition* bigFrom = posA;
        ValuePosition* bigTo = posB;
        if (fromSize > toSize && fromSize == 1)
        {
            oneWordTo = posA;
            bigFrom = posB;
        }
        
        // up casting!
        while (toNr != fromNr)
        {
            switch(fromNr)
            {
                case 1:
                    char2short(ass, oneWordTo, oneWordFrom, sign);
                    fromNr = 2;
                    break;
                case 2:
                    short2int(ass, oneWordTo, oneWordFrom, sign);
                    fromNr = 3;
                    break;
                case 3:
                    if (toNr == 4)
                    {
                        int2long(ass, bigTo, oneWordFrom, sign);
                        fromNr = 4;
                    }
                    else
                    {
                        int2float(ass, oneWordTo, oneWordFrom, sign);
                        fromNr = 5;
                    }
                    break;
                case 4:
                    if (toNr == 5)
                    {
                        long2int(ass, oneWordTo, bigFrom, sign);
                        fromNr = 3;
                    }
                    else
                    {
                        long2double(ass, bigTo, bigFrom, sign);
                        fromNr = 6;
                    }
                    break;
                case 5:
                    float2double(ass, bigTo, bigFrom);
                    fromNr = 6;
                    break;
                case 6:
                    double2longdouble(ass, bigTo, bigFrom);
                    fromNr = 7;
                    break;
            }
        }
    }
    else
    {
        ValuePosition* oneWordFrom = posA;
        ValuePosition* oneWordTo = posB;
        ValuePosition* bigFrom = posA;
        ValuePosition* bigTo = posB;
        if (toSize > fromSize && toSize == 1)
        {
            oneWordFrom = posB;
            bigTo = posA;
        }
        
        // down casting!
        while (toNr != fromNr)
        {
            switch(fromNr)
            {
                case 2:
                    short2char(ass, oneWordTo, oneWordFrom, sign);
                    fromNr = 1;
                    break;
                case 3:
                    int2short(ass, oneWordTo, oneWordFrom, sign);
                    fromNr = 2;
                    break;
                case 4:
                    long2int(ass, oneWordTo, bigFrom, sign);
                    fromNr = 3;
                    break;
                case 5:
                    float2int(ass, oneWordTo, oneWordFrom, sign);
                    fromNr = 3;
                    break;
                case 6:
                    if (toNr == 5)
                    {
                        double2float(ass, oneWordTo, bigFrom);
                        fromNr = 5;
                    }
                    else
                    {
                        double2long(ass, bigTo, bigFrom, sign);
                        fromNr = 4;
                    }
                    break;
                    
                case 7:
                    longdouble2double(ass, bigTo, bigFrom);
                    fromNr = 6;
                    break;
            }
        }
    }
}


/// implements conversion char -> short
void TypeConversions::char2short(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA, bool isSigned)
{
    copyIfDifferent(ass, posB, posA);
    if (isSigned)
    {
        ass << "    IFG " << posB->toAtomicOperand() << ", 0x007f" << std::endl;
        ass << "        BOR " << posB->toAtomicOperand() << ", 0xff00" << std::endl;
    }
}

/// implements conversion short -> char
void TypeConversions::short2char(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA, bool isSigned)
{
    copyIfDifferent(ass, posB, posA);
    ass << "    AND " << posB->toAtomicOperand() << ", 0x00ff" << std::endl;
}

/// implements conversion short -> int
void TypeConversions::short2int(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA, bool isSigned)
{
    copyIfDifferent(ass, posB, posA);
}

/// implements conversion int -> short
void TypeConversions::int2short(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA, bool isSigned)
{
    copyIfDifferent(ass, posB, posA);
}

/// implements conversion int -> long
void TypeConversions::int2long(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA, bool isSigned)
{
    // TODO once longs are implemented
    copyIfDifferent(ass, posB, posA);
}

/// implements conversion long -> int
void TypeConversions::long2int(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA, bool isSigned)
{
    // TODO once longs are implemented
    copyIfDifferent(ass, posB, posA);
}

/// implements conversion int -> float
void TypeConversions::int2float(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA, bool isSigned)
{
    // TODO once floats are implemented
    copyIfDifferent(ass, posB, posA);
}

/// implements conversion float -> int
void TypeConversions::float2int(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA, bool isSigned)
{
    // TODO once floats are implemented
    copyIfDifferent(ass, posB, posA);
}

/// implements conversion long -> double
void TypeConversions::long2double(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA, bool isSigned)
{
    // TODO
    copyIfDifferent(ass, posB, posA);
}

/// implements conversion double -> long
void TypeConversions::double2long(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA, bool isSigned)
{
    // TODO
    copyIfDifferent(ass, posB, posA);
}

/// implements conversion float -> double
void TypeConversions::float2double(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    // TODO
    copyIfDifferent(ass, posB, posA);
}

/// implements conversion double -> float
void TypeConversions::double2float(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    // TODO
    copyIfDifferent(ass, posB, posA);
}

/// implements conversion double -> long double
void TypeConversions::double2longdouble(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    // TODO
    copyIfDifferent(ass, posB, posA);
}

/// implements conversion long double -> double
void TypeConversions::longdouble2double(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    // TODO
    copyIfDifferent(ass, posB, posA);
}

///
/// @}
///