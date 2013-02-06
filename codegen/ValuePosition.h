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
            ///
            /// @brief      The constructor of the ValuePosition class.
            ///
            ValuePosition(); //: posType(REG), size(0), isDeref(false), isAdr(false), isTemp(false), offset(0) {}
            
            ValuePosition(ValuePosition& vp);// : posType(vp.posType), regist(vp.regist) {}
            
            ///
            /// @brief          Returns the size of the value in words.
            /// @return         The size of the value.
            ///
            uint16_t getWordSize();


            bool canAtomicDeref();
            bool canAtomicDerefOffset();
            
            bool isAtomicOperand();
            
            ValuePosition* atomicDeref();
            ValuePosition* atomicDerefOffset(int offset);
            
            void adrToAtomicOperand(AsmBlock& ass, ValuePosition* atomicOperand);
            ValuePosition* adrToRegister(AsmBlock& ass, ValPosRegister regist);
            ValuePosition* valToRegister(AsmBlock& ass, ValPosRegister regist);
            
            std::string toAtomicOperand();
            std::string baseToString();
            
            static ValuePosition* createLabelPos(std::string label, typesize_t size);
            static ValuePosition* createRegisterPos(ValPosRegister regist);
            static ValuePosition* createTmpRegisterPos(ValPosRegister regist);
            static ValuePosition* createTempStackWord(int offset);
            static ValuePosition* createStackPos(int size);
            static ValuePosition* createAtomicConstPos(std::string val);
            static ValuePosition* createAtomicConstPos(uint16_t val);
            static ValuePosition* createTempStack(int offset, typesize_t size);
            static ValuePosition* createFPrel(int offset, typesize_t size);
            
            bool usesRegister();
            bool isStackPos();
            bool isModifyableTemp();
            bool isTempStack();
            int getOffset();
            
            ValuePosition* newSize(typesize_t size);
            ValuePosition* newSizeOffset(typesize_t size, int offset);
            ValuePosition* addOffset(int offset);
            
            ValPosRegister getRegister();
            
            
            ///
            /// @brief      The destructor of the ValuePosition class.
            ///
            ~ValuePosition();
        };

    } // namespace codegen
} // namespace dtcc

#endif

///
/// @}
///