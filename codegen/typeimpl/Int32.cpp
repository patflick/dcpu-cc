///
/// @addtogroup LibDCPU-CI-Lang-C/CodeGen
/// @{
///

///
/// @file       Int32.cpp
/// @brief      Definition of the Int32 class.
/// @author     Patrick Flick
///
/// The type operations for 16 bit ints that do not depend on the sign of the value
/// are implemented here.

/*
 *  IMPORTANT: 32 bit integers are implemented using BIG ENDIAN
 *              -> valpos[0] is the most significant byte
 *              -> valpos[1] is the least significant byte
 */

#include "Int32.h"
#include <errors/InternalCompilerException.h>

// defines a helpful macro to get the msb and lsb bytse from the valuepostion
// into a string to be used during assembly generation
#define GET_BYTES(valpos, msb, lsb) \
    std::string msb = valpos->atomicDeref()->toAtomicOperand();\
    std::string lsb = valpos->atomicDerefOffset(1)->toAtomicOperand();

#include <deque>

using namespace dtcc::codegen;


std::deque<std::string> Int32::printConstant(double value)
{
    return printConstant((long) value);
}

std::deque<std::string> Int32::printConstant(long value)
{
    std::deque<std::string> result;
    std::stringstream strstr;
    
    // big word goes first (big endian)
    uint16_t val16 = (0xffff0000 & value) >> 16;
    strstr << "0x" << std::hex << val16;
    result.push_back(strstr.str());
    
    uint16_t val16 = 0xffff & value;
    strstr << "0x" << std::hex << val16;
    result.push_back(strstr.str());
    return result;
}

unsigned int Int32::getWordSize()
{
    return 2;
}


/* increase/decrease ops */


/// implements increase: B++
void Int32::inc(AsmBlock& ass, ValuePosition* posB, int by)
{
    GET_BYTES(posB, msb_B, lsb_B);

    ass << "ADD " << lsb_B << ", 0x" << std::hex << (0xffff & by) << std::endl;
    ass << "ADX " << msb_B << ", 0x" << std::hex << ((0xffff0000 & by) >> 16) <<< std::endl;
}

/// implements decrease: B--
void Int32::dec(AsmBlock& ass, ValuePosition* posB, int by)
{
    GET_BYTES(posB, msb_B, lsb_B);

    ass << "SUB " << lsb_B << ", 0x" << std::hex << (0xffff & by) << std::endl;
    ass << "SBX " << msb_B << ", 0x" << std::hex << ((0xffff0000 & by) >> 16) <<< std::endl;
}



/* unary operations */

/// implements arithmetic inverse: B = -B
void Int32::ainv(AsmBlock& ass, ValuePosition* posB)
{
    GET_BYTES(posB, msb_B, lsb_B);
    GET_BYTES(posA, msb_A, lsb_A);

    ass << "SET PUSH ," << msb_B << std::endl;
    ass << "SET PUSH ," << lsb_B << std::endl;
    
    ass << "SET " << msb_B << ", 0x0" << std::endl;
    ass << "SET " << lsb_B << ", 0x0" << std::endl;
    
    ass << "SUB " << lsb_B << ", POP" << std::endl;
    ass << "SBX " << msb_B << ", POP" << std::endl;
}

/// implements binary inverse (not): B = ~B
void Int32::binv(AsmBlock& ass, ValuePosition* posB)
{
    GET_BYTES(posB, msb_B, lsb_B);

    ass << "XOR " << msb_B << ", 0xffff" << std::endl;
    ass << "XOR " << lsb_B << ", 0xffff" << std::endl;
}

/// implements logical inverse (not): C = ~B
/// C is a 16 bit integer
void Int32::linv(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB)
{
    GET_BYTES(posB, msb_B, lsb_B)

    ass << "SET " << posC->toAtomicOperand() << ", 0x0" << std::endl;
    ass << "IFE " << lsb_B << ", 0x0" << std::endl;
    ass << "    IFE " << msb_B << ", 0x0" << std::endl;
    ass << "        SET " << posC->toAtomicOperand() << ", 0x1" << std::endl;
}



/* arithmetic binary operations */

/// implements addition: B = B + A
void Int32::add(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    GET_BYTES(posB, msb_B, lsb_B);
    GET_BYTES(posA, msb_A, lsb_A);
    
    ass << "ADD " << lsb_B << ", " << lsb_A << std::endl;
    ass << "ADX " << msb_B << ", " << msb_A << std::endl;
}

/// implements subtraction: B = B - A
void Int32::sub(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    GET_BYTES(posB, msb_B, lsb_B);
    GET_BYTES(posA, msb_A, lsb_A);

    ass << "SUB " << lsb_B << ", " << lsb_A << std::endl;
    ass << "SBX " << msb_B << ", " << msb_A << std::endl;
}


/* shift ops */

/// implements left shift: B = B << A
void Int32::shl(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    GET_BYTES(posB, msb_B, lsb_B);
    GET_BYTES(posA, msb_A, lsb_A);

    ass << "SHL " << msb_B << ", " << posA->toAtomicOperand() << std::endl;
    ass << "SHL " << lsb_B << ", " << posA->toAtomicOperand() << std::endl;
    ass << "BOR " << msb_B << ", EX" << std::endl;
}


/// implements right shift: B = B >> A
void Int32::shr(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    GET_BYTES(posB, msb_B, lsb_B);
    GET_BYTES(posA, msb_A, lsb_A);

    ass << "SHR " << lsb_B << ", " << posA->toAtomicOperand() << std::endl;
    ass << "SHL " << msb_B << ", " << posA->toAtomicOperand() << std::endl;
    ass << "BOR " << lsb_B << ", EX" << std::endl;
}



/* relational ops */

/// implements equality check: C = (B == A)
void Int32::seq(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA)
{
    GET_BYTES(posB, msb_B, lsb_B);
    GET_BYTES(posA, msb_A, lsb_A);

    ass << "SET " << posC->toAtomicOperand() << ", 0x0" << std::endl;
    ass << "IFE " << lsb_B << ", " << lsb_A << std::endl;
    ass << "    IFE " << msb_B << ", " << msb_A << std::endl;
    ass << "        SET " << posC->toAtomicOperand() << ", 0x1" << std::endl;
}


/// implements not equal check: C = (B != A)
void Int32::sne(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA)
{
    GET_BYTES(posB, msb_B, lsb_B);
    GET_BYTES(posA, msb_A, lsb_A);

    ass << "SET " << posC->toAtomicOperand() << ", 0x0" << std::endl;
    ass << "IFN " << lsb_B << ", " << lsb_A << std::endl;
    ass << "    IFN " << msb_B << ", " << msb_A << std::endl;
    ass << "        SET " << posC->toAtomicOperand() << ", 0x1" << std::endl;
}


/* binary ops */

/// implements binary and: B = B & A
void Int32::band(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    GET_BYTES(posB, msb_B, lsb_B);
    GET_BYTES(posA, msb_A, lsb_A);

    ass << "AND " << lsb_B << ", " << lsb_A << std::endl;
    ass << "AND " << msb_B << ", " << msb_A << std::endl;
}


/// implements binary or: B = B | A
void Int32::bor(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    GET_BYTES(posB, msb_B, lsb_B);
    GET_BYTES(posA, msb_A, lsb_A);

    ass << "BOR " << lsb_B << ", " << lsb_A << std::endl;
    ass << "BOR " << msb_B << ", " << msb_A << std::endl;
}


/// implements binary xor: B = B ^ A
void Int32::bxor(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    GET_BYTES(posB, msb_B, lsb_B);
    GET_BYTES(posA, msb_A, lsb_A);

    ass << "XOR " << lsb_B << ", " << lsb_A << std::endl;
    ass << "XOR " << msb_B << ", " << msb_A << std::endl;
}



/* logical ops */

/// implements logical and: C = B && A
void Int32::land(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA)
{
    GET_BYTES(posB, msb_B, lsb_B);
    GET_BYTES(posA, msb_A, lsb_A);

    ass << "SET " << posC->toAtomicOperand() << ", 0x1" << std::endl;
    ass << "IFE " << msb_B << ", 0x0" << std::endl;
    ass << "    IFE " << lsb_B << ", 0x0" << std::endl;
    ass << "        SET " << posC->toAtomicOperand() << ", 0x0" << std::endl;

    ass << "IFE " << msb_A << ", 0x0" << std::endl;
    ass << "    IFE " << lsb_A << ", 0x0" << std::endl;
    ass << "        SET " << posC->toAtomicOperand() << ", 0x0" << std::endl;
}


/// implements logical or: C = B || A
void Int32::lor(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA)
{
    GET_BYTES(posB, msb_B, lsb_B);
    GET_BYTES(posA, msb_A, lsb_A);

    ass << "SET " << posC->toAtomicOperand() << ", 0x0" << std::endl;

    ass << "IFN " << lsb_B << ", 0x0" << std::endl;
    ass << "    SET " << posC->toAtomicOperand() << ", 0x1" << std::endl;

    ass << "IFN " << msb_B << ", 0x0" << std::endl;
    ass << "    SET " << posC->toAtomicOperand() << ", 0x1" << std::endl;

    ass << "IFN " << lsb_A << ", 0x0" << std::endl;
    ass << "    SET " << posC->toAtomicOperand() << ", 0x1" << std::endl;

    ass << "IFN " << msb_A << ", 0x0" << std::endl;
    ass << "    SET " << posC->toAtomicOperand() << ", 0x1" << std::endl;
}

/// implements IF A == 0: JUMP label
void Int32::jmpeqz(AsmBlock& ass, ValuePosition* posA, std::string label)
{
    GET_BYTES(posB, msb_B, lsb_B);

    ass << "IFE " << msb_B << ", 0x0" << std::endl;
    ass << "    IFE " << lsb_B << ", 0x0" << std::endl;
    ass << "        SET PC, " << label << std::endl;

}

/// implements IF A != 0: JUMP label
void Int32::jmpneqz(AsmBlock& ass, ValuePosition* posA, std::string label)
{
    GET_BYTES(posB, msb_B, lsb_B);

    ass << "IFN " << lsb_B << ", 0x0" << std::endl;
    ass << "    SET PC, " << label << std::endl;

    ass << "IFN " << msb_B << ", 0x0" << std::endl;
    ass << "    SET PC, " << label << std::endl;
}

/// implements IF A == constant: JUMP label
void Int32::jmpneq(AsmBlock& ass, ValuePosition* posA, std::string label, long integralConst)
{
    GET_BYTES(posB, msb_B, lsb_B);

    ass << "IFE " << msb_B << printConstant(integralConst).front() << std::endl;
    ass << "    IFE " << lsb_B << printConstant(integralConst).back() << std::endl;
    ass << "        SET PC, " << label << std::endl;
}

/// implements IF A == constant: JUMP label
void Int32::jmpneq(AsmBlock& ass, ValuePosition* posA, std::string label, double floatConst)
{
    jmpneq(ass,  posA, label, (long) floatConst);
}


///
/// @}
///
