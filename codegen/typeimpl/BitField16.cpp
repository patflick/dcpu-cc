///
/// @addtogroup LibDCPU-CI-Lang-C/CodeGen
/// @{
///

///
/// @file       BitField16.cpp
/// @brief      Definition of the BitField16 class.
/// @author     Patrick Flick
///
/// The type operations for 16 bit ints that do not depend on the sign of the value
/// are implemented here.

/*
 *  IMPORTANT: 32 bit integers are implemented using BIG ENDIAN
 *              -> valpos[0] is the most significant byte
 *              -> valpos[1] is the least significant byte
 */

#include "BitField16.h"
#include <errors/InternalCompilerException.h>
#include <string>
#include <sstream>


#include <deque>

using namespace dcpucc;
using namespace dcpucc::codegen;

BitField16::BitField16(int offset, int bitlen) : offset(offset), bitlen(bitlen)
{
    uint16_t mask = (0xffff >> (16-bitlen)) << offset;
    std::stringstream ss1;
    ss1 << "0x" << std::hex << (uint16_t) mask;
    this->mask_field = ss1.str();
    std::stringstream ss2;
    mask = ~mask;
    ss2 << "0x" << std::hex << (uint16_t) mask;
    this->mask_other = ss2.str();
    std::stringstream ss3;
    ss3 << "0x" << std::hex << (uint16_t) offset;
    this->shift_by = ss3.str();
}


std::deque<std::string> BitField16::printConstant(double value)
{
    throw new errors::InternalCompilerException("cannot print a bitfield as constant");
}

std::deque<std::string> BitField16::printConstant(long value)
{
    throw new errors::InternalCompilerException("cannot print a bitfield as constant");
}

unsigned int BitField16::getWordSize()
{
    return 1;
}

void BitField16::saveToStack(AsmBlock& ass, ValuePosition* vp)
{
    ass << "SET PUSH, " << vp->toAtomicOperand() << std::endl;
    ass << "AND PEEK, " << this->mask_field << std::endl;
    ass << "SHR PEEK, " << this->shift_by << std::endl;
}

void BitField16::loadFromStack(AsmBlock& ass, ValuePosition* vp)
{
    ass << "SHL PEEK, " << this->shift_by << std::endl;
    ass << "AND PEEK, " << this->mask_field << std::endl;
    ass << "AND " << vp->toAtomicOperand() << ", " << this->mask_other << std::endl;
    ass << "BOR " << vp->toAtomicOperand() << ", POP" << std::endl;
}



/* increase/decrease ops */

/// implements increase: B++
void BitField16::inc(AsmBlock& ass, ValuePosition* posB, int by)
{
    saveToStack(ass, posB);
    ass << "ADD PEEK, 0x" << std::hex << (uint16_t) by << std::endl;
    loadFromStack(ass, posB);
}

/// implements decrease: B--
void BitField16::dec(AsmBlock& ass, ValuePosition* posB, int by)
{
    saveToStack(ass, posB);
    ass << "SUB PEEK, 0x" << std::hex << (uint16_t) by << std::endl;
    loadFromStack(ass, posB);
}


/* unary operations */

/// implements arithmetic inverse: B = -B
void BitField16::ainv(AsmBlock& ass, ValuePosition* posB)
{
    throw new errors::InternalCompilerException("operation not valid for bitfield type");
}

/// implements binary inverse (not): B = ~B
void BitField16::binv(AsmBlock& ass, ValuePosition* posB)
{
    throw new errors::InternalCompilerException("operation not valid for bitfield type");
}

/// implements logical inverse (not): C = ~B
/// C is a 16 bit integer
void BitField16::linv(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB)
{
    throw new errors::InternalCompilerException("operation not valid for bitfield type");
}



/* arithmetic binary operations */

/// implements addition: B = B + A
void BitField16::add(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    saveToStack(ass, posB);
    ass << "ADD PEEK, " << posA->toAtomicOperand() << std::endl;
    loadFromStack(ass, posB);
}

/// implements subtraction: B = B - A
void BitField16::sub(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    saveToStack(ass, posB);
    ass << "SUB PEEK, " << posA->toAtomicOperand() << std::endl;
    loadFromStack(ass, posB);
}


/* shift ops */

/// implements left shift: B = B << A
void BitField16::shl(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    saveToStack(ass, posB);
    ass << "SHL PEEK, " << posA->toAtomicOperand() << std::endl;
    loadFromStack(ass, posB);
}


/// implements right shift: B = B >> A
void BitField16::shr(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    saveToStack(ass, posB);
    ass << "SHR PEEK, " << posA->toAtomicOperand() << std::endl;
    loadFromStack(ass, posB);
}



/* relational ops */

/// implements equality check: C = (B == A)
void BitField16::seq(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA)
{
    throw new errors::InternalCompilerException("operation not valid for bitfield type");
}


/// implements not equal check: C = (B != A)
void BitField16::sne(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA)
{
    throw new errors::InternalCompilerException("operation not valid for bitfield type");
}


/* binary ops */

/// implements binary and: B = B & A
void BitField16::band(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    saveToStack(ass, posB);
    ass << "AND PEEK, " << posA->toAtomicOperand() << std::endl;
    loadFromStack(ass, posB);
}


/// implements binary or: B = B | A
void BitField16::bor(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    saveToStack(ass, posB);
    ass << "BOR PEEK, " << posA->toAtomicOperand() << std::endl;
    loadFromStack(ass, posB);
}


/// implements binary xor: B = B ^ A
void BitField16::bxor(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    saveToStack(ass, posB);
    ass << "XOR PEEK, " << posA->toAtomicOperand() << std::endl;
    loadFromStack(ass, posB);
}


/* arithmetic binary operations */

/// implements multiplication: B = B * A
void BitField16::mul(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    saveToStack(ass, posB);
    ass << "MUL PEEK, " << posA->toAtomicOperand() << std::endl;
    loadFromStack(ass, posB);
}

/// implements division: B = B / A
void BitField16::div(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    saveToStack(ass, posB);
    ass << "DIV PEEK, " << posA->toAtomicOperand() << std::endl;
    loadFromStack(ass, posB);
}

/// implements modulo: B = B % A
void BitField16::mod(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    saveToStack(ass, posB);
    ass << "MOD PEEK, " << posA->toAtomicOperand() << std::endl;
    loadFromStack(ass, posB);
}


/* relational ops */

/// implements less to check: C = (B < A)
void BitField16::slt(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA)
{
    throw new errors::InternalCompilerException("operation not valid for bitfield type");
}

/// implements less or equal to check: C = (B <= A)
void BitField16::sle(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA)
{
    throw new errors::InternalCompilerException("operation not valid for bitfield type");
}

/// implements greater to check: C = (B > A)
void BitField16::sgt(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA)
{
    throw new errors::InternalCompilerException("operation not valid for bitfield type");
}


/// implements greater or equal to check: C = (B >= A)
void BitField16::sge(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA)
{
    throw new errors::InternalCompilerException("operation not valid for bitfield type");
}



/* logical ops */

/// implements logical and: C = B && A
void BitField16::land(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA)
{
    throw new errors::InternalCompilerException("operation not valid for bitfield type");
}


/// implements logical or: C = B || A
void BitField16::lor(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA)
{
    throw new errors::InternalCompilerException("operation not valid for bitfield type");
}

/// implements IF A == 0: JUMP label
void BitField16::jmpeqz(AsmBlock& ass, ValuePosition* posA, std::string label)
{
    throw new errors::InternalCompilerException("operation not valid for bitfield type");
}

/// implements IF A != 0: JUMP label
void BitField16::jmpneqz(AsmBlock& ass, ValuePosition* posA, std::string label)
{
    throw new errors::InternalCompilerException("operation not valid for bitfield type");
}

/// implements IF A == constant: JUMP label
void BitField16::jmpneq(AsmBlock& ass, ValuePosition* posA, std::string label, long integralConst)
{
    throw new errors::InternalCompilerException("operation not valid for bitfield type");
}

/// implements IF A == constant: JUMP label
void BitField16::jmpneq(AsmBlock& ass, ValuePosition* posA, std::string label, double floatConst)
{
    throw new errors::InternalCompilerException("operation not valid for bitfield type");
}


///
/// @}
///
