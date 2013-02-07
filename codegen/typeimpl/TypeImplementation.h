///
/// @addtogroup LibDCPU-CI-Lang-C/CodeGen
/// @{
///

///
/// @file       TypeImplementation.h
/// @brief      Declaration of the TypeImplementation class.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_CODEGEN_TYPEIMPL_TYPEIMPLEMENTATION_H
#define __DCPU_CC_CODEGEN_TYPEIMPL_TYPEIMPLEMENTATION_H

#include "../ValuePosition.h"
#include <deque>

namespace dtcc
{
    namespace codegen
    {

        /// @brief      Defines the interface for base type implementations.
        class TypeImplementation
        {
            
        public:
            virtual std::deque<std::string> printConstant(double value) = 0;
            virtual std::deque<std::string> printConstant(long value) = 0;
            
            /// returns the size of the type
            virtual unsigned int getWordSize() = 0;
            
            
            /* increase/decrease ops */
            
            /// implements increase: B++
            virtual void inc(AsmBlock& ass, ValuePosition* posB, int by) = 0;
            
            /// implements decrease: B--
            virtual void dec(AsmBlock& ass, ValuePosition* posB, int by) = 0;
            
            
            /* unary operations */
            
            /// implements arithmetic inverse: B = -B
            virtual void ainv(AsmBlock& ass, ValuePosition* posB) = 0;
            
            /// implements binary inverse (not): B = ~B
            virtual void binv(AsmBlock& ass, ValuePosition* posB) = 0;
            
            /// implements logical inverse (not): C = ~B
            virtual void linv(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB) = 0;
            
            
            
            /* arithmetic binary operations */
            
            /// implements addition: B = B + A
            virtual void add(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA) = 0;
            
            /// implements subtraction: B = B - A
            virtual void sub(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA) = 0;
            
            /// implements multiplication: B = B * A
            virtual void mul(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA) = 0;
            
            /// implements division: B = B / A
            virtual void div(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA) = 0;
            
            /// implements modulo: B = B % A
            virtual void mod(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA) = 0;
            
            
            /* shift ops */
            
            /// implements left shift: B = B << A
            virtual void shl(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA) = 0;
            
            /// implements right shift: B = B >> A
            virtual void shr(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA) = 0;
            
            
            /* relational ops */
            
            /// implements equality check: C = (B == A)
            virtual void seq(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA) = 0;
            
            /// implements not equal check: C = (B != A)
            virtual void sne(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA) = 0;
            
            /// implements less to check: C = (B < A)
            virtual void slt(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA) = 0;
            
            /// implements less or equal to check: C = (B <= A)
            virtual void sle(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA) = 0;
            
            /// implements greater to check: C = (B > A)
            virtual void sgt(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA) = 0;
            
            /// implements greater or equal to check: C = (B >= A)
            virtual void sge(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA) = 0;
            
            
            /* binary ops */
            
            /// implements binary and: B = B & A
            virtual void band(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA) = 0;
            
            /// implements binary or: B = B | A
            virtual void bor(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA) = 0;
            
            /// implements binary xor: B = B ^ A
            virtual void bxor(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA) = 0;
            
            
            /* logical ops */
            
            /// implements logical and: C = B && A
            virtual void land(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA) = 0;
            
            /// implements logical or: C = B || A
            virtual void lor(AsmBlock& ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA) = 0;
            
            
            /* conditional jump instructions */
            
            /// implements IF A == 0: JUMP label
            virtual void jmpeqz(AsmBlock& ass, ValuePosition* posA, std::string label) = 0;
            
            /// implements IF A != 0: JUMP label
            virtual void jmpneqz(AsmBlock& ass, ValuePosition* posA, std::string label) = 0;
            
            /// implements IF A == constant: JUMP label
            virtual void jmpneq(AsmBlock& ass, ValuePosition* posA, std::string label, long integralConst) = 0;
            
            /// implements IF A == constant: JUMP label
            virtual void jmpneq(AsmBlock& ass, ValuePosition* posA, std::string label, double floatConst) = 0;
        };


    } // namespace codegen
} // namespace dtcc

#endif
