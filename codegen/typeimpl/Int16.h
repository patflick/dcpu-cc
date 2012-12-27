///
/// @addtogroup LibDCPU-CI-Lang-C/CodeGen
/// @{
///

///
/// @file       Int16.h
/// @brief      Declaration of the Int16 class.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_CODEGEN_TYPEIMPL_INT16_H
#define __DCPU_CC_CODEGEN_TYPEIMPL_INT16_H

#include "TypeImplementation.h"

namespace dtcc
{
    namespace codegen
    {

        /// @brief      Implements generic 16 bit integer operations.
        ///             This excludes signed operations, those are implemented
        ///             in the classes UnsignedInt16 and SignedInt16
        ///             by extending from this class.
        ///             This class should never be initiated and only
        ///             be used to extend from.
        class Int16 : TypeImplementation
        {
        private:
            
            // private constructor prevents construction of this class.
            Int16() { };
            
        public:
            
            virtual std::deque<std::string> printConstant(double value);
            virtual std::deque<std::string> printConstant(long value);
            
            
            /* arithmetic binary operations */
            
            /// implements addition: B = B + A
            virtual void add(AsmBlock* ass, ValuePosition* posB, ValuePosition* posA);
            
            /// implements subtraction: B = B - A
            virtual void sub(AsmBlock* ass, ValuePosition* posB, ValuePosition* posA);
            
            /// implements multiplication: B = B * A
            virtual void mul(AsmBlock* ass, ValuePosition* posB, ValuePosition* posA) = 0;
            
            /// implements division: B = B / A
            virtual void div(AsmBlock* ass, ValuePosition* posB, ValuePosition* posA) = 0;
            
            /// implements modulo: B = B % A
            virtual void mod(AsmBlock* ass, ValuePosition* posB, ValuePosition* posA) = 0;
            
            
            /* shift ops */
            
            /// implements left shift: B = B << A
            virtual void shl(AsmBlock* ass, ValuePosition* posB, ValuePosition* posA);
            
            /// implements right shift: B = B >> A
            virtual void shr(AsmBlock* ass, ValuePosition* posB, ValuePosition* posA);
            
            
            /* relational ops */
            
            /// implements equality check: C = (B == A)
            virtual void seq(AsmBlock* ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA);
            
            /// implements not equal check: C = (B != A)
            virtual void sne(AsmBlock* ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA);
            
            /// implements less to check: C = (B < A)
            virtual void slt(AsmBlock* ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA) = 0;
            
            /// implements less or equal to check: C = (B <= A)
            virtual void sle(AsmBlock* ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA) = 0;
            
            /// implements greater to check: C = (B > A)
            virtual void sgt(AsmBlock* ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA) = 0;
            
            /// implements greater or equal to check: C = (B >= A)
            virtual void sge(AsmBlock* ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA) = 0;
            
            
            /* binary ops */
            
            /// implements binary and: B = B & A
            virtual void band(AsmBlock* ass, ValuePosition* posB, ValuePosition* posA);
            
            /// implements binary or: B = B | A
            virtual void bor(AsmBlock* ass, ValuePosition* posB, ValuePosition* posA);
            
            /// implements binary xor: B = B ^ A
            virtual void bor(AsmBlock* ass, ValuePosition* posB, ValuePosition* posA);
            
            
            /* logical ops */
            
            /// implements logical and: C = B && A
            virtual void land(AsmBlock* ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA);
            
            /// implements logical or: C = B || A
            virtual void lor(AsmBlock* ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA);
        };


    } // namespace codegen
} // namespace dtcc

#endif
