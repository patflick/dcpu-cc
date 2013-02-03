///
/// @addtogroup LibDCPU-CI-Lang-C/CodeGen
/// @{
///

///
/// @file       TypeConversions.h
/// @brief      Declaration of the TypeConversions class.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_CODEGEN_TYPEIMPL_TYPECONVERSIONS_H
#define __DCPU_CC_CODEGEN_TYPEIMPL_TYPECONVERSIONS_H

#include <types/alltypes.h>
#include "../ValuePosition.h"

namespace dtcc
{
    namespace codegen
    {;
        

        /// @brief      Implements type conversions for basic types.
        class TypeConversions
        {
        private:
            /// Copy A to B (i.e. B = A) if posA and posB are different.
            /// This only works for 1 word sizes
            void copyIfDifferent(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA);
            
            
            bool isSigned(types::Type* type);
            int typeToNr(types::Type* type);
            
        public:
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
            /// @brief Converts a value from one type to another.
            /// @param from The origin type for the casting.
            /// @param to   The target type for the casting.
            /// @param ass  The output string stream for generated DASM
            /// @param posB The target value position.
            /// @param posA The source value position.
            ///
            /// Returns the conversion function for casting from `from` to `to`.
            void convert(types::Type* from, types::Type* to, AsmBlock& ass, ValuePosition* posB, ValuePosition* posA);
            
            /// implements conversion char -> short
            void char2short(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA, bool isSigned);
            
            /// implements conversion short -> char
            void short2char(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA, bool isSigned);
            
            /// implements conversion short -> int
            void short2int(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA, bool isSigned);
            
            /// implements conversion int -> short
            void int2short(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA, bool isSigned);
            
            /// implements conversion int -> long
            void int2long(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA, bool isSigned);
            
            /// implements conversion long -> int
            void long2int(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA, bool isSigned);

            /// implements conversion int -> float
            void int2float(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA, bool isSigned);
            
            /// implements conversion float -> int
            void float2int(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA, bool isSigned);
            
            /// implements conversion long -> double
            void long2double(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA, bool isSigned);
            
            /// implements conversion double -> long
            void double2long(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA, bool isSigned);
            
            /// implements conversion float -> double
            void float2double(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA);
            
            /// implements conversion double -> float
            void double2float(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA);
            
            /// implements conversion double -> long double
            void double2longdouble(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA);
            
            /// implements conversion long double -> double
            void longdouble2double(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA);

        };


    } // namespace codegen
} // namespace dtcc

#endif
