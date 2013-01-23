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
// two (left and right) temporary registers that
// are never allocated for intermediary results
#define REG_TMP_L REG_I
#define REG_TMP_R REG_J


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
            std::string constValue;
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
            
            ValuePosition* isAtomicOperand();
            
            ValuePosition* atomicDeref();
            ValuePosition* atomicDerefOffset(int offset);
            
            ValuePosition* adrToRegister(AsmBlock& ass, ValPosRegister regist);
            
            ValuePosition* valToRegister(AsmBlock& ass, ValPosRegister regist);
            
            std::string toAtomicOperand();
            std::string baseToString();
            
            static ValuePosition* createLabelPos(std::string label);
            static ValuePosition* createRegisterPos(ValPosRegister regist);
            static ValuePosition* createFPrelativeWord(int offset);
            static ValuePosition* createStackPos(int size);
            static ValuePosition* createAtomicConstPos(std::string val);
            static ValuePosition* createAtomicConstPos(uint16_t val);
            
            bool usesRegister();
            bool isStackPos();
            bool isTempStack();
            int getOffset();
            
            ValPosRegister getRegister();
            
            
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