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


std::string registerToString(ValPosRegister regist)
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

bool ValuePosition::canAtomicDeref()
{
    // TODO make this depend on the assembler and linker used
    if (this->isDeref || this->posType == LABEL_REL)
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

ValuePosition* ValuePosition::getAtomicDeref(AsmBlock* ass, ValPosRegister regist)
{
    ass << "SET " << this->registerToString(regist) << ", " << this->toString() << std::endl;
    
    ValuePosition* newVP = new ValuePosition(*this);
    newVP->posType = REG;
    newVP->regist = regist;
    newVP->isDeref = false;
    return newVP;
}

std::string ValuePosition::toAtomicOperand()
{
    std::stringstream base;
    switch (this->posType)
    {
        case LABEL:
            base << this->labelName;
            break;
        case LABEL_REL:
            base << this->labelName << " + " << this->offset;
            break;
        case FP_REL:
            base << this->registerToString(REG_FRAME_POINTER) << " + " << this->offset;
            break;
        case REG:
            base << this->registerToString(this->regist);
            break;
        case REG_REL:
            base << this->registerToString(this->regist) << " + " << this->offset;
            break;
        case STACK:
            base << "SP";
            break;
        case STACK_REL:
            base << "SP + " << this->offset;
            break;
        case CONST_LITERAL:
            base << std::hex << this->constValue;
    }
    
    if (this->isDeref)
        return std::string("[") + base.str() + std::string("]");
    else
        return base.str();
}



// implements the destructor
ValuePosition::~ValuePosition()
{

}

///
/// @}
///