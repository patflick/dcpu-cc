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
            static void copyIfDifferent(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA);
            
            
            static bool isSigned(types::Type* type);
            static int typeToNr(types::Type* type);
            
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
            static void convert(types::Type* from, types::Type* to, AsmBlock& ass, ValuePosition* posB, ValuePosition* posA);
            
            /// Returns whether a type conversion has to be executed
            static bool needsConvert(types::Type* from, types::Type* to);
            
            /// implements conversion char -> short
            static void char2short(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA, bool isSigned);
            
            /// implements conversion short -> char
            static void short2char(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA, bool isSigned);
            
            /// implements conversion short -> int
            static void short2int(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA, bool isSigned);
            
            /// implements conversion int -> short
            static void int2short(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA, bool isSigned);
            
            /// implements conversion int -> long
            static void int2long(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA, bool isSigned);
            
            /// implements conversion long -> int
            static void long2int(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA, bool isSigned);

            /// implements conversion int -> float
            static void int2float(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA, bool isSigned);
            
            /// implements conversion float -> int
            static void float2int(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA, bool isSigned);
            
            /// implements conversion long -> double
            static void long2double(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA, bool isSigned);
            
            /// implements conversion double -> long
            static void double2long(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA, bool isSigned);
            
            /// implements conversion float -> double
            static void float2double(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA);
            
            /// implements conversion double -> float
            static void double2float(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA);
            
            /// implements conversion double -> long double
            static void double2longdouble(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA);
            
            /// implements conversion long double -> double
            static void longdouble2double(AsmBlock& ass, ValuePosition* posB, ValuePosition* posA);

        };


    } // namespace codegen
} // namespace dtcc

#endif
