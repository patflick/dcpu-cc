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
    ass << "ADD " << posB->toAtomicOperand() << ", 0x" << std::hex << (0xffff & by) << std::endl;
}

/// implements decrease: B--
void Int32::dec(AsmBlock& ass, ValuePosition* posB, int by)
{
    ass << "SUB " << posB->toAtomicOperand() << ", 0x" << std::hex << (0xffff & by) << std::endl;
}



/* unary operations */

/// implements arithmetic inverse: B = -B
void Int32::ainv(AsmBlock& ass, ValuePosition* posB)
{
    ass << "SET PUSH ," << posB->toAtomicOperand() << std::endl;
    ass << "SET " << posB->toAtomicOperand() << ", 0x0" << std::endl;
    ass << "SUB " << posB->toAtomicOperand() << ", POP" << std::endl;
}

/// implements binary inverse (not): B = ~B
void Int32::binv(AsmBlock& ass, ValuePosition* posB)
{
    ass << "SET PUSH ," << posB->toAtomicOperand() << std::endl;
    ass << "SET " << posB->toAtomicOperand() << ", 0xffff" << std::endl;
    ass << "XOR " << posB->toAtomicOperand() << ", POP" << std::endl;
}

/// implements logical inverse (not): C = ~B
void Int32::linv(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB)
{
    ass << "SET " << posC->toAtomicOperand() << ", 0x0" << std::endl;
    ass << "IFE " << posB->toAtomicOperand() << ", 0x0" << std::endl;
    ass << "    SET " << posC->toAtomicOperand() << ", 0x1" << std::endl;
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
    ass << "SUB " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
}


/* shift ops */

/// implements left shift: B = B << A
void Int32::shl(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    ass << "SHL " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
}


/// implements right shift: B = B >> A
void Int32::shr(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    ass << "SHR " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
}



/* relational ops */

/// implements equality check: C = (B == A)
void Int32::seq(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA)
{
    ass << "SET " << posC->toAtomicOperand() << ", 0x0" << std::endl;
    ass << "IFE " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
    ass << "    SET " << posC->toAtomicOperand() << ", 0x1" << std::endl;
}


/// implements not equal check: C = (B != A)
void Int32::sne(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA)
{
    ass << "SET " << posC->toAtomicOperand() << ", 0x0" << std::endl;
    ass << "IFN " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
    ass << "    SET " << posC->toAtomicOperand() << ", 0x1" << std::endl;
}


/* binary ops */

/// implements binary and: B = B & A
void Int32::band(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    ass << "AND " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
}


/// implements binary or: B = B | A
void Int32::bor(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    ass << "BOR " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
}


/// implements binary xor: B = B ^ A
void Int32::bxor(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    ass << "XOR " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
}



/* logical ops */

/// implements logical and: C = B && A
void Int32::land(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA)
{
    ass << "SET " << posC->toAtomicOperand() << ", 0x0" << std::endl;
    ass << "IFN " << posB->toAtomicOperand() << ", 0x0" << std::endl;
    ass << "    IFN " << posA->toAtomicOperand() << ", 0x0" << std::endl;
    ass << "        SET " << posC->toAtomicOperand() << ", 0x1" << std::endl;
}


/// implements logical or: C = B || A
void Int32::lor(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA)
{
    ass << "SET " << posC->toAtomicOperand() << ", 0x1" << std::endl;
    ass << "IFE " << posB->toAtomicOperand() << ", 0x0" << std::endl;
    ass << "    IFE " << posA->toAtomicOperand() << ", 0x0" << std::endl;
    ass << "        SET " << posC->toAtomicOperand() << ", 0x0" << std::endl;
}

/// implements IF A == 0: JUMP label
void Int32::jmpeqz(AsmBlock& ass, ValuePosition* posA, std::string label)
{
    ass << "IFE " << posA->toAtomicOperand() << ", 0x0" << std::endl;
    ass << "    SET PC, " << label << std::endl;
}

/// implements IF A != 0: JUMP label
void Int32::jmpneqz(AsmBlock& ass, ValuePosition* posA, std::string label)
{
    ass << "IFN " << posA->toAtomicOperand() << ", 0x0" << std::endl;
    ass << "    SET PC, " << label << std::endl;
}

/// implements IF A == constant: JUMP label
void Int32::jmpneq(AsmBlock& ass, ValuePosition* posA, std::string label, long integralConst)
{
    ass << "IFE " << posA->toAtomicOperand() << ", " << printConstant(integralConst).front() << std::endl;
    ass << "    SET PC, " << label << std::endl;
}

/// implements IF A == constant: JUMP label
void Int32::jmpneq(AsmBlock& ass, ValuePosition* posA, std::string label, double floatConst)
{
    jmpneq(ass,  posA, label, (long) floatConst);
}


///
/// @}
///