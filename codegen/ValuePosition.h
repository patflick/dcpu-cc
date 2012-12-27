///
/// @addtogroup LibDCPU-CI-Lang-C/CodeGen
/// @{
///

///
/// @file       ValuePosition.h
/// @brief      Declaration of the ValuePosition class.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_CODEGEN_VALUEPOSITION_H
#define __DCPU_CC_CODEGEN_VALUEPOSITION_H

#include <stdint.h>
#include <string>

#define REG_FRAME_POINTER REG_Y


namespace dtcc
{
    namespace codegen
    {
        // TODO remove this temporary typedef
        typedef std::stringstream AsmBlock;
        // TODO remove this temporary typedef
        typedef uint16_t typesize_t;
        
        enum ValPosType {LABEL, LABEL_REL, FP_REL, REG, REG_REL, STACK, STACK_REL, CONST_LITERAL};
        enum ValPosRegister {REG_A, REG_B, REG_C, REG_I, REG_J, REG_X, REG_Y, REG_Z};
        
        ///
        /// @class      ValuePosition
        /// @brief      The ValuePosition class.
        ///
        class ValuePosition
        {
            
        private:
            ValPosType posType;
            ValPosRegister regist;
            
            typesize_t size;
            bool isDeref;
            bool isAdr;
            bool isTemp;
            int offset;
            uint16_t constValue;
            std::string labelName;
            
            std::string registerToString(ValPosRegister regist);
            
        public:
            
                
        public:
            ///
            /// @brief      The constructor of the ValuePosition class.
            ///
            ValuePosition()  {}
            
            ///
            /// @brief          Returns the size of the value in words.
            /// @return         The size of the value.
            ///
            virtual uint16_t getWordSize();


            bool canAtomicDeref();
            bool canAtomicDerefOffset();
            
            ValuePosition* atomicDeref();
            ValuePosition* atomicDerefOffset(int offset);
            
            ValuePosition* getAtomicDeref(AsmBlock* ass, ValPosRegister regist);
            
            std::string toAtomicOperand();
            
            
            ///
            /// @brief      The destructor of the ValuePosition class.
            ///
            virtual ~ValuePosition();
        };

    } // namespace codegen
} // namespace dtcc

#endif

///
/// @}
///