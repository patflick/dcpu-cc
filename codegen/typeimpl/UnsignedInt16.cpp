///
/// @addtogroup LibDCPU-CI-Lang-C/CodeGen
/// @{
///

///
/// @file       UnsignedInt16.cpp
/// @brief      Definition of the UnsignedInt16 class.
/// @author     Patrick Flick
///
/// The type operations for 16 bit ints that depend on the sign of the value
/// are implemented here, for the signed variants of the operations.

#include "UnsignedInt16.h"
#include <errors/InternalCompilerException.h>

#include <deque>

using namespace dtcc::codegen;

/* arithmetic binary operations */

/// implements multiplication: B = B * A
void UnsignedInt16::mul(AsmBlock* ass, ValuePosition* posB, ValuePosition* posA)
{
    ass << "MUL " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
}

/// implements division: B = B / A
void UnsignedInt16::div(AsmBlock* ass, ValuePosition* posB, ValuePosition* posA)
{
    ass << "DIV " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
}

/// implements modulo: B = B % A
void UnsignedInt16::mod(AsmBlock* ass, ValuePosition* posB, ValuePosition* posA)
{
    ass << "MOD " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
}


/* relational ops */

/// implements less to check: C = (B < A)
void UnsignedInt16::slt(AsmBlock* ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA)
{
    ass << "SET " << posC->toAtomicOperand() << ", 0x0" << std::endl;
    ass << "IFL " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
    ass << "    SET " << posC->toAtomicOperand() << ", 0x1" << std::endl;
}

/// implements less or equal to check: C = (B <= A)
void UnsignedInt16::sle(AsmBlock* ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA)
{
    ass << "SET " << posC->toAtomicOperand() << ", 0x1" << std::endl;
    ass << "IFG " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
    ass << "    SET " << posC->toAtomicOperand() << ", 0x0" << std::endl;
}

/// implements greater to check: C = (B > A)
void UnsignedInt16::sgt(AsmBlock* ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA)
{
    ass << "SET " << posC->toAtomicOperand() << ", 0x0" << std::endl;
    ass << "IFG " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
    ass << "    SET " << posC->toAtomicOperand() << ", 0x1" << std::endl;
}


/// implements greater or equal to check: C = (B >= A)
void UnsignedInt16::sge(AsmBlock* ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA)
{
    ass << "SET " << posC->toAtomicOperand() << ", 0x1" << std::endl;
    ass << "IFL " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
    ass << "    SET " << posC->toAtomicOperand() << ", 0x0" << std::endl;
}




///
/// @}
///