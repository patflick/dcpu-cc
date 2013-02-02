///
/// @addtogroup LibDCPU-CI-Lang-C/CodeGen
/// @{
///

///
/// @file       ValuePosition.cpp
/// @brief      Definition of the ValuePosition class.
/// @author     Patrick Flick
///

#include "ValuePosition.h"
#include <errors/InternalCompilerException.h>

using namespace dtcc;
using namespace dtcc::codegen;



ValuePosition::ValuePosition() : 
posType(REG), size(0), isDeref(false), isAdr(false),
isTemp(false), offset(0), constValue(std::string("")), labelName(std::string(""))
{

}

ValuePosition::ValuePosition(ValuePosition& vp) : 
posType(vp.posType), size(vp.size), isDeref(vp.isDeref), isAdr(vp.isAdr),
isTemp(vp.isTemp), offset(vp.offset), constValue(vp.constValue), labelName(vp.labelName)
{
    
}

ValuePosition::~ValuePosition()
{

}

uint16_t ValuePosition::getWordSize()
{
    return this->size;
}



ValuePosition* ValuePosition::createLabelPos(std::string label)
{
    ValuePosition* pos = new ValuePosition();
    pos->posType = LABEL;
    pos->labelName = label;
    pos->size = 1;
    return pos;
}

ValuePosition* ValuePosition::createAtomicConstPos(std::string val)
{
    ValuePosition* pos = new ValuePosition();
    pos->posType = CONST_LITERAL;
    pos->constValue = val;
    pos->size = 1;
    return pos;
}

ValuePosition* ValuePosition::createRegisterPos(ValPosRegister regist)
{
    ValuePosition* pos = new ValuePosition();
    pos->posType = REG;
    pos->regist = regist;
    pos->size = 1;
    return pos;
}

ValuePosition* ValuePosition::createTempStackWord(int offset)
{
    ValuePosition* pos = new ValuePosition();
    pos->posType = FP_REL;
    pos->offset = offset;
    pos->isDeref = true;
    pos->isTemp = true;
    pos->size = 1;
    return pos;
}

ValuePosition* ValuePosition::createTempStack(int offset, int size)
{
    ValuePosition* pos = new ValuePosition();
    pos->posType = FP_REL;
    pos->offset = offset;
    pos->isDeref = false;
    pos->isTemp = true;
    pos->size = size;
    return pos;
}

ValuePosition* ValuePosition::createAtomicConstPos(uint16_t val)
{
    std::stringstream strstr;
    strstr << "0x" << std::hex << val;
    return createAtomicConstPos(strstr.str());
}

ValuePosition* ValuePosition::createStackPos(int size)
{
    ValuePosition* pos = new ValuePosition();
    pos->posType = STACK;
    pos->size = size;
    return pos;
}

bool ValuePosition::isStackPos()
{
    if (this->posType == STACK || this->posType == STACK_REL)
        return true;
    else
        return false;
}

std::string ValuePosition::registerToString(ValPosRegister regist)
{
    switch (regist)
    {
        case REG_A:
            return std::string("A");
        case REG_B:
            return std::string("B");
        case REG_C:
            return std::string("C");
        case REG_I:
            return std::string("I");
        case REG_J:
            return std::string("J");
        case REG_X:
            return std::string("X");
        case REG_Y:
            return std::string("Y");
        case REG_Z:
            return std::string("Z");
    }
}


bool ValuePosition::isTempStack()
{
    if (this->posType == FP_REL && this->isTemp)
        return true;
    else
        return false;
}

bool ValuePosition::isModifyableTemp()
{
    return this->isTemp;
}

int ValuePosition::getOffset()
{
    return this->offset;
}

bool ValuePosition::usesRegister()
{
    if (this->posType == REG || this->posType == REG_REL)
        return true;
    else
        return false;
}

ValPosRegister ValuePosition::getRegister()
{
    if (this->usesRegister())
        return this->regist;
    else
        throw new errors::InternalCompilerException("trying to get register of non-register ValuePosition");
}


bool ValuePosition::canAtomicDeref()
{
    // TODO make this depend on the assembler and linker used
    if (this->isDeref || this->posType == LABEL_REL)
        return false;
    else
        return true;
}

bool ValuePosition::isAtomicOperand()
{
    if (!this->isDeref && (this->posType == LABEL_REL || this->posType == REG_REL || this->posType == STACK_REL))
        return false;
    else if (this->isDeref && this->posType == LABEL_REL)
        return false;
    else
        return true;
}


bool ValuePosition::canAtomicDerefOffset()
{
    // TODO make this depend on the assembler and linker used
    if (this->isDeref || this->posType == LABEL_REL || this->posType == LABEL)
        return false;
    else
        return true;
}

ValuePosition* ValuePosition::atomicDeref()
{
    if (! this->canAtomicDeref())
    {
        throw new errors::InternalCompilerException("trying to atomically deref something that cannot");
    }
    ValuePosition* newVP = new ValuePosition(*this);
    newVP->isDeref = true;
}

ValuePosition* ValuePosition::atomicDerefOffset(int offset)
{
    if (! this->canAtomicDerefOffset())
    {
        throw new errors::InternalCompilerException("trying to atomically deref something that cannot");
    }
    ValuePosition* newVP = new ValuePosition(*this);
    newVP->isDeref = true;
    newVP->offset += offset;
    if (newVP->posType == LABEL)
        newVP->posType = LABEL_REL;
    else if (newVP->posType == REG)
        newVP->posType = REG_REL;
    else if (newVP->posType == STACK)
        newVP->posType = STACK_REL;
    return newVP;
}

ValuePosition* ValuePosition::adrToRegister(AsmBlock& ass, ValPosRegister regist)
{
    ass << "SET " << this->registerToString(regist) << ", " << this->baseToString() << std::endl;
    
    // add offset if needed
    switch (this->posType)
    {
        case LABEL_REL:
        case FP_REL:
        case STACK_REL:
            ass << "ADD " << this->registerToString(regist) << ", 0x" << std::hex << this->offset << std::endl;
            break;
        default:
            break;
    }
    
    ValuePosition* newVP = new ValuePosition(*this);
    newVP->posType = REG;
    newVP->regist = regist;
    newVP->isDeref = false;
    return newVP;
}

ValuePosition* ValuePosition::valToRegister(AsmBlock& ass, ValPosRegister regist)
{
    ValuePosition* newVP = this->adrToRegister(ass, regist);
    if (this->isDeref)
    {
        ass << "SET " << this->registerToString(regist) << ", [" << this->registerToString(regist) << "]" << std::endl;
    }
    return newVP;
}

std::string ValuePosition::baseToString()
{
    std::stringstream base;
    switch (this->posType)
    {
        case LABEL:
        case LABEL_REL:
            base << this->labelName;
            break;
        case FP_REL:
            base << this->registerToString(REG_FRAME_POINTER);
            break;
        case REG:
            base << this->registerToString(this->regist);
            base << this->registerToString(this->regist);
            break;
        case STACK:
        case STACK_REL:
            base << "SP";
            break;
        case CONST_LITERAL:
            base << "0x" << std::hex << this->constValue;
            break;
    }
    return base.str();
}

std::string ValuePosition::toAtomicOperand()
{
    std::stringstream base;
    base << this->baseToString();
    switch (this->posType)
    {
        case LABEL_REL:
        case FP_REL:
        case STACK_REL:
            base << " + " << this->offset;
            break;
        default:
            break;
    }
    
    if (this->isDeref)
        return std::string("[") + base.str() + std::string("]");
    else
        return base.str();
}




///
/// @}
///