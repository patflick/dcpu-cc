///
/// @addtogroup LibDCPU-CI-Lang-C/CodeGen
/// @{
///

///
/// @file       SignedInt16.cpp
/// @brief      Definition of the SignedInt16 class.
/// @author     Patrick Flick
///
/// The type operations for 16 bit ints that depend on the sign of the value
/// are implemented here, for the signed variants of the operations.

#include "SignedInt16.h"
#include <errors/InternalCompilerException.h>

#include <deque>

using namespace dtcc::codegen;

/* arithmetic binary operations */

/// implements multiplication: B = B * A
void SignedInt16::mul(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    ass << "MLI " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
}

/// implements division: B = B / A
void SignedInt16::div(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    ass << "DVI " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
}

/// implements modulo: B = B % A
void SignedInt16::mod(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA)
{
    ass << "MDI " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
}


/* relational ops */

/// implements less to check: C = (B < A)
void SignedInt16::slt(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA)
{
    ass << "SET " << posC->toAtomicOperand() << ", 0x0" << std::endl;
    ass << "IFU " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
    ass << "    SET " << posC->toAtomicOperand() << ", 0x1" << std::endl;
}

/// implements less or equal to check: C = (B <= A)
void SignedInt16::sle(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA)
{
    ass << "SET " << posC->toAtomicOperand() << ", 0x1" << std::endl;
    ass << "IFA " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
    ass << "    SET " << posC->toAtomicOperand() << ", 0x0" << std::endl;
}

/// implements greater to check: C = (B > A)
void SignedInt16::sgt(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA)
{
    ass << "SET " << posC->toAtomicOperand() << ", 0x0" << std::endl;
    ass << "IFA " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
    ass << "    SET " << posC->toAtomicOperand() << ", 0x1" << std::endl;
}


/// implements greater or equal to check: C = (B >= A)
void SignedInt16::sge(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA)
{
    ass << "SET " << posC->toAtomicOperand() << ", 0x1" << std::endl;
    ass << "IFU " << posB->toAtomicOperand() << ", " << posA->toAtomicOperand() << std::endl;
    ass << "    SET " << posC->toAtomicOperand() << ", 0x0" << std::endl;
}




///
/// @}
///