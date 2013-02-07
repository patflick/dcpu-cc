///
/// @addtogroup LibDCPU-CI-Lang-C/CodeGen
/// @{
///

///
/// @file       Int16.cpp
/// @brief      Definition of the Int16 class.
/// @author     Patrick Flick
///
/// The type operations for 16 bit ints that do not depend on the sign of the value
/// are implemented here.

#include "Int16.h"
#include <errors/InternalCompilerException.h>

#include <deque>

using namespace dtcc::codegen;


std::deque<std::string> Int16::printConstant(double value)
{
    return printConstant((long) value);
}

std::deque<std::string> Int16::printConstant(long value)
{
    std::deque<std::string> result;
    std::stringstream strstr;
    uint16_t val16 = 0xffff & value;
    strstr << "0x" << std::hex << val16;
    result.push_back(strstr.str());
    return result;
}

unsigned int Int16::getWordSize()
{
    return 1;
}


/* increase/decrease ops */


/// implements increase: B++
void Int16::inc(AsmBlock& ass, ValuePosition* posB, int by)
{
    ass << "ADD " << posB->toAtomicOperand() << ", 0x" << std::hex << (0xffff & by) << std::endl;
}

/// implements decrease: B--
void Int16::dec(AsmBlock& ass, ValuePosition* posB, int by)
{
    ass << "SUB " << posB->toAtomicOperand() << ", 0x" << std::hex << (0xffff & by) << std::endl;
}



/* unary operations */

/// implements arithmetic inverse: B = -B
void Int16::ainv(AsmBlock& ass, ValuePosition* posB)
{
    ass << "SET PUSH ," << posB->toAtomicOperand() << std::endl;
    ass << "SET " << posB->toAtomicOperand() << ", 0x0" << std::endl;
    ass << "SUB " << posB->toAtomicOperand() << ", POP" << std::endl;
}

/// implements binary inverse (not): B = ~B
void Int16::binv(AsmBlock& ass, ValuePosition* posB)
{
    ass << "SET PUSH ," << posB->toAtomicOperand() << std::endl;
    ass << "SET " << posB->toAtomicOperand() << ", 0xffff" << std::endl;
    ass << "XOR " << posB->toAtomicOperand() << ", POP" << std::endl;
}

/// implements logical inverse (not): C = ~B
void Int16::linv(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB)
{
    ass << "SET " << posC->toAtomicOperand() << ", 0x0" << std::endl;
    ass << "IFE " << posB->toAtomicOperand() << ", 0x0" << std::endl;
    ass << "    SET " << posC->toAtomicOperand() << ", 0x1" << std::endl;
}



/* arithmetic binary operations */

/// implements addition: B = B + A
void Int16::add(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    ass << "ADD " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
}

/// implements subtraction: B = B - A
void Int16::sub(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    ass << "SUB " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
}


/* shift ops */

/// implements left shift: B = B << A
void Int16::shl(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    ass << "SHL " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
}


/// implements right shift: B = B >> A
void Int16::shr(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    ass << "SHR " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
}



/* relational ops */

/// implements equality check: C = (B == A)
void Int16::seq(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA)
{
    ass << "SET " << posC->toAtomicOperand() << ", 0x0" << std::endl;
    ass << "IFE " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
    ass << "    SET " << posC->toAtomicOperand() << ", 0x1" << std::endl;
}


/// implements not equal check: C = (B != A)
void Int16::sne(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA)
{
    ass << "SET " << posC->toAtomicOperand() << ", 0x0" << std::endl;
    ass << "IFN " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
    ass << "    SET " << posC->toAtomicOperand() << ", 0x1" << std::endl;
}


/* binary ops */

/// implements binary and: B = B & A
void Int16::band(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    ass << "AND " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
}


/// implements binary or: B = B | A
void Int16::bor(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    ass << "BOR " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
}


/// implements binary xor: B = B ^ A
void Int16::bxor(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    ass << "XOR " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
}



/* logical ops */

/// implements logical and: C = B && A
void Int16::land(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA)
{
    ass << "SET " << posC->toAtomicOperand() << ", 0x0" << std::endl;
    ass << "IFN " << posB->toAtomicOperand() << ", 0x0" << std::endl;
    ass << "    IFN " << posA->toAtomicOperand() << ", 0x0" << std::endl;
    ass << "        SET " << posC->toAtomicOperand() << ", 0x1" << std::endl;
}


/// implements logical or: C = B || A
void Int16::lor(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA)
{
    ass << "SET " << posC->toAtomicOperand() << ", 0x1" << std::endl;
    ass << "IFE " << posB->toAtomicOperand() << ", 0x0" << std::endl;
    ass << "    IFE " << posA->toAtomicOperand() << ", 0x0" << std::endl;
    ass << "        SET " << posC->toAtomicOperand() << ", 0x0" << std::endl;
}

/// implements IF A == 0: JUMP label
void Int16::jmpeqz(AsmBlock& ass, ValuePosition* posA, std::string label)
{
    ass << "IFE " << posA->toAtomicOperand() << ", 0x0" << std::endl;
    ass << "    SET PC, " << label << std::endl;
}

/// implements IF A != 0: JUMP label
void Int16::jmpneqz(AsmBlock& ass, ValuePosition* posA, std::string label)
{
    ass << "IFN " << posA->toAtomicOperand() << ", 0x0" << std::endl;
    ass << "    SET PC, " << label << std::endl;
}

/// implements IF A == constant: JUMP label
void Int16::jmpneq(AsmBlock& ass, ValuePosition* posA, std::string label, long integralConst)
{
    ass << "IFE " << posA->toAtomicOperand() << ", " << printConstant(integralConst).front() << std::endl;
    ass << "    SET PC, " << label << std::endl;
}

/// implements IF A == constant: JUMP label
void Int16::jmpneq(AsmBlock& ass, ValuePosition* posA, std::string label, double floatConst)
{
    jmpneq(ass,  posA, label, (long) floatConst);
}


///
/// @}
///