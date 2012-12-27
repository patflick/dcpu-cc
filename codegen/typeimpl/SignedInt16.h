///
/// @addtogroup LibDCPU-CI-Lang-C/CodeGen
/// @{
///

///
/// @file       SignedInt16.h
/// @brief      Declaration of the SignedInt16 class.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_CODEGEN_TYPEIMPL_SIGNEDINT16_H
#define __DCPU_CC_CODEGEN_TYPEIMPL_SIGNEDINT16_H

#include "Int16.h"

namespace dtcc
{
    namespace codegen
    {

        /// @brief      Implements signed 16 bit integer operations.
        ///             This implements the operations on 16 bit integers
        ///             that depend on the sign. This class implements
        ///             signed variants of those operations.
        class SignedInt16 : Int16
        {
        private:
            
            
            
        public:
            
            /// @brief Constructor of the SignedInt16 class.
            SignedInt16() { };
            
            
            /* arithmetic binary operations */
            
            /// implements multiplication: B = B * A
            virtual void mul(AsmBlock* ass, ValuePosition* posB, ValuePosition* posA);
            
            /// implements division: B = B / A
            virtual void div(AsmBlock* ass, ValuePosition* posB, ValuePosition* posA);
            
            /// implements modulo: B = B % A
            virtual void mod(AsmBlock* ass, ValuePosition* posB, ValuePosition* posA);
            
            
            /* relational ops */
            
            /// implements less to check: C = (B < A)
            virtual void slt(AsmBlock* ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA);
            
            /// implements less or equal to check: C = (B <= A)
            virtual void sle(AsmBlock* ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA);
            
            /// implements greater to check: C = (B > A)
            virtual void sgt(AsmBlock* ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA);
            
            /// implements greater or equal to check: C = (B >= A)
            virtual void sge(AsmBlock* ass, ValuePosition* posC, ValuePosition* posB, ValuePosition* posA);
            
        };


    } // namespace codegen
} // namespace dtcc

#endif
