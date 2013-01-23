#include "DirectCodeGenVisitor.h"
#include <iostream>
#include <string>
#include <deque>
#include <utility>
#include <algorithm>

#include <errors/derr.defs.h>
#include <errors/InternalCompilerException.h>

#include <types/alltypes.h>
#include <types/IsTypeHelper.h>

#include <visitor/ConstExprEvalVisitor.h>

#include <valuetypes/ValueType.h>
#include <valuetypes/FunctionDesignator.h>
#include <valuetypes/LValue.h>
#include <valuetypes/RValue.h>
#include <valuetypes/CValue.h>
#include <valuetypes/IsValueTypeHelper.h>
#include <valuetypes/PromotionHelper.h>
#include <valuetypes/ConstHelper.h>

#include "ValuePosition.h"

// only include the int tokens
#define YYSTYPE int
#include <parser.hpp>

using namespace dtcc;
using namespace dtcc::codegen;


/* constructor */

DirectCodeGenVisitor::DirectCodeGenVisitor()
{
    this->asm_functions = std::deque<std::stringstream>();
    this->isDebug = true;
}

// TODO this is just while dev, to be removed in final version:
void DirectCodeGenVisitor::printAstName(const char * name)
{
    std::cout << "TODO implement code gen for node '" << name << "'." << std::endl;
}

std::string DirectCodeGenVisitor::getFileAndLineState(astnodes::Node* node)
{
    std::stringstream str;
    str << ".ULINE " << node->line << " \"" << node->file << "\"";
    return str.str();
}


/* register management */

void DirectCodeGenVisitor::initFreeRegisters()
{
    for (ValPosRegister r = REG_A; r <= REG_Z; r++)
    {
        m_registersUsed[r] = false;
    }
    
    m_registersUsed[REG_FRAME_POINTER] = true;
    m_registersUsed[REG_TMP_L] = true;
    m_registersUsed[REG_TMP_R] = true;
}

ValPosRegister DirectCodeGenVisitor::getFreeRegister()
{
    for (ValPosRegister r = REG_A; r <= REG_Z; r++)
    {
        if (!m_registersUsed[r])
        {
            m_registersUsed[r] = true;
            return r;
        }
    }
    
    // register spilling should happen elsewhere
    // TODO implement register spilling
    throw new errors::InternalCompilerException("no free register available");
}

bool DirectCodeGenVisitor::isFreeRegisterAvailable()
{
    for (ValPosRegister r = REG_A; r <= REG_Z; r++)
    {
        if (!m_registersUsed[r])
            return true;
    }
    return false;
}

void DirectCodeGenVisitor::freeTempStack(int pos)
{
    if (m_tempStackObjects.find(pos) != m_tempStackObjects.end())
    {
        int size = m_tempStackObjects[pos];
        for (int i = pos; i < pos+size; i++)
        {
            m_tempStackAlloc[i] = false;
        }
        while (m_tempStackAlloc.size() > 0 && m_tempStackAlloc.back() == false)
        {
            m_tempStackAlloc.pop_back();
        }
    }
}

int DirectCodeGenVisitor::getTempStack(int size)
{
    // find a hole in the bit array of size `size`
    // or append that many bits
    // returns offset from temp stack (not including the local stack offset from FP)
    int pos;
    bool found;
    for (std::vector<bool>::iterator it = m_tempStackAlloc.begin(); it != m_tempStackAlloc.end(); ++it)
    {
        if (!*it)
        {
            // check if the hole is big enough
            std::vector<bool>::iterator it2;
            for (it2 = it+1; it2 != m_tempStackAlloc.end() && it2 - it < size; ++it2)
            {
                if (*it2)
                {
                    // word is allocated
                    break;
                }
            }
            if (it2-it == size)
            {
                // hole found
                for (std::vector<bool>::iterator it3 = it; it3 != it2 ; ++it3)
                {
                    // allocate all words
                    *it3 = true;
                }
                pos = it - m_tempStackAlloc.begin();
                m_tempStackObjects[pos] = size;
                return pos;
            }
            else
                it = it2;
        }
    }
    
    // nothing found, need to allocate more space at the end
    for (int i = 0; i < size; i++)
        m_tempStackAlloc.push_back(true);
    
    // update size
    m_tempStackMax = std::max(m_tempStackMax, m_tempStackAlloc.size());
    
    pos = m_tempStackAlloc.size() - size;
    m_tempStackObjects[pos] = size;
    return pos;
}

// returns either a register (if there are still some available)
// or a [FP-offset] type position (local temp stack)
ValuePosition* DirectCodeGenVisitor::getTempWordPos()
{
    if (isFreeRegisterAvailable())
    {
        ValPosRegister reg = getFreeRegister();
        return ValuePosition::createRegisterPos(reg);
    }
    else
    {
        // get word on temporary stack
        int pos = getTempStack(1);
        return ValuePosition::createFPrelativeWord(-m_currentFunctionTempStackOffset-pos-1);
    }
}

void DirectCodeGenVisitor::maybeFreeTemporary(ValuePosition* vp)
{
    if (vp->usesRegister())
    {
        this->releaseRegister(vp->getRegister());
    }
    else if (vp->isTempStack())
    {
        int pos = - (vp->getOffset() + m_currentFunctionTempStackOffset + 1);
        freeTempStack(pos);
    }
}


void DirectCodeGenVisitor::releaseRegister(ValPosRegister regist)
{
    m_registersUsed[regist] = false;
}




// Generates a random, unique label for use in code.
astnodes::LabelStatement* DirectCodeGenVisitor::getRandomLabel(std::string prefix)
{
    std::string result = "";
    
    while ((result == "") || (this->m_AutomaticLabels.find(result) != this->m_AutomaticLabels.end()))
        result = prefix + "_" + DirectCodeGenVisitor::getRandomString(10);
    
    return new astnodes::LabelStatement(result, new astnodes::EmptyStatement());
}

// Generates a random character.
char DirectCodeGenVisitor::getRandomCharacter()
{
    unsigned char c;
    
    while (!std::isalnum(c = static_cast<unsigned char>(rand() % 256))) ;
    
    return c;
}

// Generates a random string.
std::string DirectCodeGenVisitor::getRandomString(std::string::size_type sz)
{
    std::string s;
    s.reserve(sz);
    std::generate_n(std::back_inserter(s), sz, DirectCodeGenVisitor::getRandomCharacter);
    return s;
}


/******************************/
/* visit functions            */
/******************************/


void DirectCodeGenVisitor::visit(astnodes::Program * program)
{
    // compile everything
    program->allChildrenAccept(*this);
}


void DirectCodeGenVisitor::visit(astnodes::FunctionDefinition * functionDefinition)
{
    std::stringstream asmStr;
    asmStr << getFileAndLineState(functionDefinition);
    
    // Output a safety boundary if the assembler supports
    // it and we want to output in debug mode.
    if (isDebug)
    {
        if (assembler.supportsSafetyBoundary)
            asmStr << ".BOUNDARY" << std::endl;
        else if (assembler.supportsDataInstruction)
            asmStr << "DAT 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0" << std::endl;
    }
    
    // If the assembler supports exporting symbols, automatically
    // export this function.
    // TODO unless specified as static
    if (assembler.supportsLinkedExportDirective)
        asmStr <<  ".EXPORT cfunc_" << functionDefinition->name << std::endl;
    
    // Output the leading information and immediate jump.
    asmStr <<  ":cfunc_" << functionDefinition->name << std::endl;
    asmStr <<  "    SET PC, cfunc_" << functionDefinition->name << "_actual" << std::endl;
    asmStr <<  "    DAT " << functionDefinition->paramSize << std::endl;
    asmStr <<  ":cfunc_" << functionDefinition->name << "_actual" << std::endl;
    
    
    // clear and set temp stack info
    m_currentFunctionTempStackOffset = functionDefinition->stackSize+2;
    m_tempStackAlloc.clear();
    m_tempStackObjects.clear();
    m_tempStackMax = 0;
            
    // clear output:
    asm_current.str(std::string());
    
    // Now compile the block.
    functionDefinition->block->accept(*this);
    
    // Allocate locals and temporaries
    asmStr <<  "    SUB SP, " << functionDefinition->stackSize + m_tempStackMax << std::endl;
    
    asmStr << asm_current.str();
    
    // an end of function label, a return; jumps here after saving the result
    asmStr <<  ":cfunc_" << functionDefinition->name << "_end" << std::endl;
    
    // Free locals and temporaries
    asmStr <<  "    ADD SP, " << functionDefinition->stackSize + m_tempStackMax << std::endl;
    
    // Return from this function.
    asmStr <<  "    SET A, 0xFFFF" << std::endl;
    asmStr <<  "    SET X, " << functionDefinition->paramSize << std::endl;
    asmStr <<  "    SET PC, _stack_callee_return" << std::endl;
    
    // put the generated code in the functions list
    asm_functions.push_back(asmStr.str());
}


void DirectCodeGenVisitor::visit(astnodes::GotoStatement * gotoStatement)
{
    // Add file and line information.
    asm_current << this->getFileAndLineState(gotoStatement);
    // jump to the label:
    asm_current << "    SET PC, " << gotoStatement->lbl->label << std::endl;
}


void DirectCodeGenVisitor::visit(astnodes::ContinueStatement * continueStatement)
{
    // Add file and line information.
    asm_current << this->getFileAndLineState(continueStatement);
    // jump to the label
    asm_current << "    SET PC, " << continueStatement->label->label << std::endl;
}


void DirectCodeGenVisitor::visit(astnodes::BreakStatement * breakStatement)
{
    // Add file and line information.
    asm_current << this->getFileAndLineState(breakStatement);
    // jump to the label
    asm_current << "    SET PC, " << breakStatement->label->label << std::endl;
}


void DirectCodeGenVisitor::visit(astnodes::DefaultStatement * defaultStatement)
{
    // Add file and line information.
    asm_current << this->getFileAndLineState(defaultStatement);
    // jump to the label
    asm_current << ":" << defaultStatement->lbl->label << std::endl;
    
    // compile child statement:
    defaultStatement->allChildrenAccept(*this);
}


void DirectCodeGenVisitor::visit(astnodes::CaseStatement * caseStatement)
{
    // TODO const expression evaluator
    // TODO
    // TODO the expression evaluator (first finish semantic check for expressions)
    printAstName("CaseStatement");
    caseStatement->allChildrenAccept(*this);
}



void DirectCodeGenVisitor::visit(astnodes::Expression * expression)
{
    throw new errors::InternalCompilerException("Expression Node is only abstract and cannot be visited");
}


void DirectCodeGenVisitor::visit(astnodes::Statement * statement)
{
    throw new errors::InternalCompilerException("Statement Node is only abstract and cannot be visited");
}


void DirectCodeGenVisitor::visit(astnodes::ExternalDeclaration * externalDeclaration)
{
    throw new errors::InternalCompilerException("ExternalDeclaration Node is only abstract and cannot be visited");
}


void DirectCodeGenVisitor::visit(astnodes::ReturnStatement * returnStatement)
{
    // Add file and line information.
    asm_current << this->getFileAndLineState(returnStatement);
    
    // first check the expression
    returnStatement->allChildrenAccept(*this);
    // then check if it is compatible with the function return value
    // TODO TODO FIXME
}


void DirectCodeGenVisitor::visit(astnodes::ForStatement * forStatement)
{
    // Add file and line information.
    asm_current << this->getFileAndLineState(forStatement);
    
    // Do the initalization statement.
    forStatement->initExpr->accept(*this);
    
    // Output the start label.
    asm_current << ":" << forStatement->startLbl->label << std::endl;
    
    // translate the check expression
    forStatement->condExpr->accept(*this);
    
    // If A is not true, jump to the end.
    asm_current <<   "   IFE A, 0x0" << std::endl;
    asm_current <<   "       SET PC, " << forStatement->endLbl->label << std::endl;
    
    // Compile the main block.
    forStatement->statement->accept(*this);
    
    // Output the continue label.
    asm_current << ":" << forStatement->continueLbl->label << std::endl;
    
    // Do the loop statement.
    forStatement->loopExpr->accept(*this);
    
    // Jump back up to the start to do the evaluation.
    asm_current <<   "   SET PC, " << forStatement->startLbl->label << std::endl;
    
    // And insert the end label.
    asm_current << ":" << forStatement->endLbl->label << std::endl;
}


void DirectCodeGenVisitor::visit(astnodes::DoWhileStatement * doWhileStatement)
{
    // Add file and line information.
    asm_current << this->getFileAndLineState(doWhileStatement);
    
    // Output the start label.
    asm_current << ":" << doWhileStatement->startLbl->label << std::endl;
    
    // compile the block
    doWhileStatement->statement->accept(*this);
    
    // output continue label
    asm_current << ":" << doWhileStatement->continueLbl->label << std::endl;
    
    // compile the condition 
    doWhileStatement->condExpr->accept(*this);
    
    // while the expression is true, jump to beginning
    asm_current <<   "   IFN A, 0x0" << std::endl;
    asm_current <<   "       SET PC, " << doWhileStatement->startLbl->label << std::endl;
    
    // And insert the end label.
    asm_current << ":" << doWhileStatement->endLbl->label << std::endl;
}


void DirectCodeGenVisitor::visit(astnodes::WhileStatement * whileStatement)
{
    // Add file and line information.
    asm_current << this->getFileAndLineState(whileStatement);
    
    // Output the start label.
    asm_current << ":" << whileStatement->startLbl->label << std::endl;
    
    // compile the condition 
    whileStatement->condExpr->accept(*this);
    
    // if the expression evaluates to false, jump to end
    asm_current <<   "   IFE A, 0x0" << std::endl;
    asm_current <<   "       SET PC, " << whileStatement->endLbl->label << std::endl;
    
    // compile the block
    whileStatement->statement->accept(*this);
    
    // Jump back up to the start to do the evaluation.
    asm_current <<   "   SET PC, " << whileStatement->startLbl->label << std::endl;
    
    // And insert the end label.
    asm_current << ":" << whileStatement->endLbl->label << std::endl;
}


void DirectCodeGenVisitor::visit(astnodes::SwitchStatement * switchStatement)
{
    // Add file and line information.
    asm_current << this->getFileAndLineState(switchStatement);
    
    // TODO TODO TODO
    
    // first evaluate the controlling expression
    switchStatement->expr->accept(*this);
    
    printAstName("SwitchStatement");
}


void DirectCodeGenVisitor::visit(astnodes::IfStatement * ifStatement)
{
    // Add file and line information.
    asm_current << this->getFileAndLineState(ifStatement);
    
    // When an expression is evaluated, the result goes into the A register.
    ifStatement->condExpr->accept(*this);
    
    // check for the result of the conditional expression
    asm_current << "   IFE A, 0x0" << std::endl;
    if (ifStatement->elseStmt != NULL)
        asm_current << "       SET PC, " << ifStatement->elselbl->label << std::endl;
    else
        asm_current << "       SET PC, " << ifStatement->endlbl->label << std::endl;
        
    // compile if block
    ifStatement->ifStmt->accept(*this);
    
    // compile else block
    if (ifStatement->elseStmt != NULL)
    {
        // jump to end 
        asm_current << "    SET PC, " << ifStatement->endlbl->label << std::endl;
        
        // Output the else label.
        asm_current << ":" << ifStatement->elselbl->label << std::endl;
        
        // compile else block
        ifStatement->elseStmt->accept(*this);
    }
    
    // Output the end label.
    asm_current << ":" << ifStatement->endlbl->label << std::endl;
}


void DirectCodeGenVisitor::visit(astnodes::ExpressionStatement * expressionStatement)
{
    // Add file and line information.
    asm_current << this->getFileAndLineState(expressionStatement);
    // just pass through
    expressionStatement->allChildrenAccept(*this);
}


void DirectCodeGenVisitor::visit(astnodes::EmptyStatement * emptyStatement)
{
    // nothing to do here
}


void DirectCodeGenVisitor::visit(astnodes::BlockStatement * blockStatement)
{
    // Add file and line information.
    asm_current << this->getFileAndLineState(blockStatement);
    
    // compile the statements 
    blockStatement->allChildrenAccept(*this);
}


void DirectCodeGenVisitor::visit(astnodes::LabelStatement * labelStatement)
{    
    // Add file and line information.
    asm_current << this->getFileAndLineState(labelStatement);
    
    // Output the end label.
    asm_current << ":" << labelStatement->label << std::endl;
    
    // compile children statements
    labelStatement->allChildrenAccept(*this);
}






/*######################################*/
/*        3.5 DECLARATIONS              */
/*######################################*/



// TODO TODO FIXME TODO TODO FIXME
// implement declarators ;)
// first now implementing expressions

void DirectCodeGenVisitor::visit(astnodes::Declaration * declaration)
{
    // visit all the declarators
    if (!declaration->isParamDecl)
    {
        for (astnodes::Declarators::iterator i = declaration->declarators->begin(); i != declaration->declarators->end(); ++i)
        {
            // visit all the declarators
            (*i)->accept(*this);
        }
    }
}




/******************************/
/*     3.5.4 Declarators      */
/******************************/

void DirectCodeGenVisitor::visit(astnodes::Declarator * declarator)
{
    throw new errors::InternalCompilerException("Declarator Node is only abstract and cannot be visited");
}

void DirectCodeGenVisitor::visit(astnodes::NoIdentifierDeclarator * noIdentifierDeclarator)
{
    // nothing to do
}

void DirectCodeGenVisitor::visit(astnodes::IdentifierDeclarator * identifierDeclarator)
{
    // TODO compile initializers
}


/* 3.5.4.1 Pointer declarators */

void DirectCodeGenVisitor::visit(astnodes::Pointer * pointer)
{
    // nothing to do
}


/* 3.5.4.2 Array declarators */

void DirectCodeGenVisitor::visit(astnodes::ArrayDeclarator * arrayDeclarator)
{
    // TODO compile the the initializers
    if (arrayDeclarator->initializers != NULL)
        for (astnodes::Expressions::iterator i = arrayDeclarator->initializers->begin(); i != arrayDeclarator->initializers->end(); ++i)
        {
            // evaluate the expression
            (*i)->accept(*this);
            
            // save the result
            // TODO
        }
}


/* 3.5.4.3 Function declarators */

void DirectCodeGenVisitor::visit(astnodes::FunctionDeclarator * functionDeclarator)
{
    // TODO compile the the initializers
}



/**********************************/
/*       3.5.5 Type names         */
/**********************************/

void DirectCodeGenVisitor::visit(astnodes::TypeName * typeName)
{
    // nothing to do here
}











/**********************************/
/* 3.5.1 Storage-class specifiers */
/**********************************/

void DirectCodeGenVisitor::visit(astnodes::StorageSpecifier * storageSpecifier)
{
    throw new errors::InternalCompilerException("a storage specifier should not be visited");
}




/******************************/
/*  3.5.2 Type specifiers     */
/******************************/

void DirectCodeGenVisitor::visit(astnodes::TypeSpecifier * typeSpecifier)
{
    throw new errors::InternalCompilerException("Declarator Node is only abstract and cannot be visited");
}

void DirectCodeGenVisitor::visit(astnodes::TypeBaseSpecifier * typeBaseSpecifier)
{
    // nothing to do here
}



void DirectCodeGenVisitor::visit(astnodes::StructUnionSpecifier * structUnionSpecifier)
{
    // nothing to do here
}


void DirectCodeGenVisitor::visit(astnodes::EnumSpecifier * enumSpecifier)
{
    // nothing to do here
}



void DirectCodeGenVisitor::visit(astnodes::TypeNameSpecifier * typeNameSpecifier)
{
    // nothing to do here
}


/******************************/
/*  3.5.3 Type qualifiers     */
/******************************/

void DirectCodeGenVisitor::visit(astnodes::TypeQualifier * typeQualifier)
{
    throw new errors::InternalCompilerException("a type qualifier should not be visited");
}



/*######################################*/
/*      3.3 Expressions                 */
/*######################################*/


/******************************/
/*  3.3.1 Primary expressions */
/******************************/

/* identifier */

void DirectCodeGenVisitor::visit(astnodes::Identifier * identifier)
{
    // huge TODO
    // get typeposition (which should be added by the semantic check visitor)
    // and add that as expression result
    
    // this will be depending on type either:
    // => Labels:
    // -  cfunc_somefunc :  global label as adress to function
    // -  cglob_somename :  some global variable
    // -  cstat_somename : some static variable saved at global scope
    // => Stack relative addresses:
    // -  FP+offset for parameters
    // -  FP-offset for locals
    
    // if we consider structs we can also have:
    // Label+offset as value position (this will not fit in an atomic instruction
    // unless the linker supports expressions)
    
    // so we have two cases (so far?!?):
    // 1. Labels:
    //    ValuePosition is atomic addressable and atomic deref
    // 2. Stack relative addresses
    //    ValuePosition is not atomic addressable, but atomic deref
    // 3. Labels + offset
    //    ValuePosition is not atomic addressable, and only atomic deref
    //                  if linker supports expressions (not yet the case)
    
    
    // in the first case it can addressed without any registers used
    // deref can always happen without register use
    // getting the address only works with an additional register
    // thus the ValuePosition needs to be able to request a free register
    
    // 
    
    
    // this is a terminal expression
    // how will i make this work exactly??
    
    // Ideas:
    //  - terminal 
}


/* constants */

ValuePosition* DirectCodeGenVisitor::handleLiteral(std::deque<std::string> vals)
{
    if (vals.size() > 1)
    {
        std::string label = getRandomLabel("constant_");
        asm_Constants << label << ":" << std::endl;
        asm_Constants << "    DAT ";
        for (std::deque<std::string>::iterator it = vals.begin(); it != vals.end(); ++it)
        {
            if (it != vals.begin())
            {
                asm_Constants << ", ";
            }
            asm_Constants << *it;
        }
        asm_Constants << std::endl;
        
        // return a label valuepos
        return ValuePosition::createLabelPos(label);
    }
    else if (vals.size() == 1)
    {
        // return an atomic constant literal valuepos
        return ValuePosition::createAtomicConstPos(vals.front());
    }
    else
    {
        throw new errors::InternalCompilerException("literal value list of length 0 encountered");
    }
}



void DirectCodeGenVisitor::visit(astnodes::CharacterLiteral * characterLiteral)
{
    characterLiteral->valType->type->accept(getTypeImpl);
    std::deque<std::string> ch;
    ch.push_back(characterLiteral->str[0]);
    characterLiteral->valPos = handleLiteral(ch);
}


void DirectCodeGenVisitor::visit(astnodes::SignedIntLiteral * signedIntLiteral)
{
    signedIntLiteral->valType->type->accept(getTypeImpl);
    signedIntLiteral->valPos = handleLiteral(getTypeImpl.getTypeImplementation()->printConstant(signedIntLiteral->literalValue));
}


void DirectCodeGenVisitor::visit(astnodes::UnsignedIntLiteral * unsignedIntLiteral)
{
    unsignedIntLiteral->valType->type->accept(getTypeImpl);
    unsignedIntLiteral->valPos = handleLiteral(getTypeImpl.getTypeImplementation()->printConstant(unsignedIntLiteral->literalValue));
}


void DirectCodeGenVisitor::visit(astnodes::SignedLongLiteral * signedLongLiteral)
{
    signedLongLiteral->valType->type->accept(getTypeImpl);
    signedLongLiteral->valPos = handleLiteral(getTypeImpl.getTypeImplementation()->printConstant(signedLongLiteral->literalValue));
}


void DirectCodeGenVisitor::visit(astnodes::UnsignedLongLiteral * unsignedLongLiteral)
{
    unsignedLongLiteral->valType->type->accept(getTypeImpl);
    unsignedLongLiteral->valPos = handleLiteral(getTypeImpl.getTypeImplementation()->printConstant(unsignedLongLiteral->literalValue));
}


void DirectCodeGenVisitor::visit(astnodes::FloatLiteral * floatLiteral)
{
    floatLiteral->valType->type->accept(getTypeImpl);
    floatLiteral->valPos = handleLiteral(getTypeImpl.getTypeImplementation()->printConstant(floatLiteral->literalValue));
}


void DirectCodeGenVisitor::visit(astnodes::DoubleLiteral * doubleLiteral)
{
    doubleLiteral->valType->type->accept(getTypeImpl);
    doubleLiteral->valPos = handleLiteral(getTypeImpl.getTypeImplementation()->printConstant(doubleLiteral->literalValue));
}


void DirectCodeGenVisitor::visit(astnodes::LongDoubleLiteral * longDoubleLiteral)
{
    longDoubleLiteral->valType->type->accept(getTypeImpl);
    longDoubleLiteral->valPos = handleLiteral(getTypeImpl.getTypeImplementation()->printConstant(longDoubleLiteral->literalValue));
}


/* string literal */

void DirectCodeGenVisitor::visit(astnodes::StringLiteral * stringLiteral)
{
    // get string
    std::string s = stringLiteral->str;
    std::stringstream outputstr;
    outputstr << "\"";
    // replace escape characters
    for (std::string::const_iterator i = s.begin(), end = s.end(); i != end; ++i)
    {
        unsigned char c = *i;
        switch (c)
        {
            case '"':
                outputstr << "\\\"";
                break;
            case '\'':
                outputstr << "\\\'";
                break;
            case '\\':
                outputstr << "\\\\";
                break;
            case '\t':
                outputstr << "\\t";
                break;
            case '\r':
                outputstr << "\\r";
                break;
            case '\n':
                outputstr << "\\n";
                break;
            case '\v':
                outputstr << "\\v";
                break;
            case '\f':
                outputstr << "\\f";
                break;
            case '\b':
                outputstr << "\\b";
                break;
            case '\a':
                outputstr << "\\a";
                break;
            case '\0':
                outputstr << "\\0";
                break;
            case '\?':
                outputstr << "\\\?";
                break;
            default :
                outputstr << c;
        }
    }
    outputstr << "\"";
    
    // add string constant to global string constants
    std::string label = getRandomLabel("string_const_");
    asm_stringConstants << label << ":" << std::endl;
    asm_stringConstants << "    DAT " << outputstr.str() << ", 0x0" << std::endl;
    
    // set a label ValuePosition
    stringLiteral->valPos = ValuePosition::createLabelPos(label);
}



ValuePosition* DirectCodeGenVisitor::atomizeOperand(ValuePosition* operandVP)
{
    ValuePosition* newVP = operandVP;
    if (operandVP->getWordSize() == 1)
    {
        if (!operandVP->isAtomicOperand())
        {
            ValPosRegister newReg = this->getFreeRegister();
            newVP = operandVP->valToRegister(asm_current, newReg);
            maybeReleaseRegister(operandVP);
        }
    }
    else if (operandVP->getWordSize() > 1)
    {
        if (!operandVP->canAtomicDerefOffset())
        {
            ValPosRegister newReg = this->getFreeRegister();
            newVP = operandVP->valToRegister(asm_current, newReg);
            maybeReleaseRegister(operandVP);
        }
    }
    return newVP;
}


ValuePosition* DirectCodeGenVisitor::derefOperand(ValuePosition* operandVP)
{
    if (operandVP->getWordSize() == 1)
    {
        if (operandVP->canAtomicDeref())
            operandVP = operandVP->atomicDeref();
        else
        {
            ValPosRegister newReg = this->getFreeRegister();
            ValuePosition* newVP = operandVP->valToRegister(asm_current, newReg);
            newVP = newVP->atomicDeref();
            maybeReleaseRegister(operandVP);
            operandVP = newVP;
        }
    }
    return operandVP;
}

ValuePosition* DirectCodeGenVisitor::pushToStack(ValuePosition* valPos)
{
    if (valPos->getWordSize() == 1)
    {
        asm_current << "SET PUSH, " << valPos->toAtomicOperand() << std::endl;
    } else if (valPos < MIN_SIZE_LOOP_COPY)
    {
        for (int i = valPos->getWordSize() - 1; i >= 0; i--)
        {
            if (i > 0)
                asm_current << "SET PUSH, " << valPos->atomicDerefOffset(i)->toAtomicOperand() << std::endl;
            else
                asm_current << "SET PUSH, " << valPos->atomicDeref()->toAtomicOperand() << std::endl;
        }
    }
    else if (valPos->getWordSize() >= MIN_SIZE_LOOP_COPY)
    {
        asm_current << "SUB SP, " << valPos->getWordSize() << std::endl;
        
        int stackoffset = 0;
        // save I and J
        if (m_registersUsed[REG_I])
        {
            asm_current << "SET PUSH, I" << std::endl;
            stackoffset++;
        }
        if (m_registersUsed[REG_J])
        {
            asm_current << "SET PUSH, J" << std::endl;
            stackoffset++;
        }
        
        std::string loopLabel = getRandomLabel("copy_loop_");
        std::string loopEndLabel = getRandomLabel("copy_loop_");
        
        // set up registers and stack pointer 
        // TODO i have the feeling this could be done more efficient :(
        asm_current << "SET I, " << valPos->toAtomicOperand() << std::endl;
        asm_current << "ADD I, " << valPos->getWordSize()-1 << std::endl;
        asm_current << "SET J, SP" << std::endl;
        asm_current << "ADD J, " << valPos->getWordSize() + stackoffset - 1 << std::endl;
        asm_current << "ADD SP, " << stackoffset << std::endl;
        
        // compile the copy loop
        asm_current << loopLabel << ":" << std::endl;
        asm_current << "    STD [I], [J]" << std::endl;
        asm_current << "    IFL J, SP" << std::endl;
        asm_current << "        SET PC, " << loopEndLabel << std::endl;
        asm_current << "    SET PC, " << loopLabel << std::endl;
        asm_current << loopEndLabel << ":" << std::endl;
        
        // restore SP
        asm_current << "SUB SP, " << stackoffset << std::endl;
        
        
        // restore I and J
        if (m_registersUsed[REG_I])
            asm_current << "SET I, POP" << std::endl;
        if (m_registersUsed[REG_J])
            asm_current << "SET J, POP" << std::endl;
    }
    
    return ValuePosition::createStackPos(valPos->getWordSize());
}

ValuePosition* DirectCodeGenVisitor::getTmpCopy(ValuePosition* from)
{
    if (from->getWordSize() == 1)
    {
        // try to get a register copy
        if (from->isAtomicOperand())
        {
            ValPosRegister newReg = this->getFreeRegister();
            ValuePosition* newVP = from->valToRegister(asm_current, newReg);
            maybeReleaseRegister(from);
            return newVP;
        }
        else
        {
            // atomize will return a new register
            return atomizeOperand(from);
        }
    }
    else if (from->getWordSize() > 1)
    {
        // if this is already on the stack, it is a temporary
        // and does not need replacement
        if (!from->isStackPos())
        {
            return this->pushToStack(from);
        }
    }
}

ValuePosition* DirectCodeGenVisitor::getTmp(int size)
{
    
}


TypeImplementation* DirectCodeGenVisitor::getTypeImplementation(types::Type* type)
{
    type->accept(getTypeImpl);
    return getTypeImpl.getTypeImplementation();
}


/******************************/
/*  3.3.2 Postfix expressions */
/******************************/

/* 3.3.2.1 array subscripting */

void DirectCodeGenVisitor::visit(astnodes::ArrayAccessOperator * arrayAccessOperator)
{
    // first compile lhs expression (i.e. the array)
    arrayAccessOperator->lhsExpr->accept(*this);
    
    ValuePosition* lhsVP = arrayAccessOperator->lhsExpr->valPos;
    
    // get new register for lhs adress to be modified
    ValPosRegister newReg = this->getFreeRegister();
    ValuePosition* newLhsVP = NULL;
    
    // deref lhs if necessary
    if (arrayAccessOperator->lhsLtoR)
        lhsVP = derefOperand(lhsVP);
    else
    {
        newLhsVP = lhsVP->valToRegister(asm_current, newReg);
        maybeReleaseRegister(lhsVP);
        lhsVP = newLhsVP;
    }
    
    
    // compile offset
    arrayAccessOperator->rhsExpr->accept(*this);
    
    ValuePosition* rhsVP = arrayAccessOperator->rhsExpr->valPos;
    
    if (arrayAccessOperator->rhsLtoR)
    {
        rhsVP = derefOperand(rhsVP);
    }
    
    rhsVP = atomizeOperand(rhsVP);

    TypeImplementation* typeImpl = this->getTypeImplementation(new types::UnsignedInt());
    
    // multiply by pointer size
    typeImpl->mul(asm_current, rhsVP, ValuePosition::createAtomicConstPos(arrayAccessOperator->pointerSize));
    // add to address
    typeImpl->add(asm_current, lhsVP, rhsVP);
    
    // return this value (which is a LValue)
    arrayAccessOperator->valPos = lhsVP;
}


/* 3.3.2.2 Function calls */

void DirectCodeGenVisitor::visit(astnodes::MethodCall * methodCall)
{
    // TODO TODO
    printAstName("MethodCall");
}


/* 3.3.2.3 Structure and union members */

void DirectCodeGenVisitor::visit(astnodes::StructureResolutionOperator * structureResolutionOperator)
{
    // TODO FIXME TODO FIXME
    // TODO implement structs properly
    printAstName("StructureResolutionOperator");
    structureResolutionOperator->allChildrenAccept(*this);
}


/* 3.3.2.4 Postfix increment and decrement operators */

void DirectCodeGenVisitor::visit(astnodes::PostIncDec * postIncDec)
{
    // first analyse the inner expression
    postIncDec->expr->accept(*this);
    
    ValuePosition* valPos = postIncDec->expr->valPos;
    
    valPos = atomizeOperand(valPos);
    ValuePosition* derefValPos = derefOperand(valPos);
    
    ValuePosition* derefCpy = getTmpCopy(derefValPos);
    
    TypeImplementation* typeImpl = this->getTypeImplementation(postIncDec->valType->type);
    
    switch (postIncDec->optoken)
    {
        case INC_OP:
            typeImpl->inc(asm_current, derefValPos, postIncDec->pointerSize);
            break;
        case DEC_OP:
            typeImpl->dec(asm_current, derefValPos, postIncDec->pointerSize);
            break;
        default:
            throw new errors::InternalCompilerException("invalid inc/dec operator encountered");
    }
    
    // TODO delete derefValPos
    
    postIncDec->valPos = derefCpy;
}



/******************************/
/*  3.3.3 Unary operators     */
/******************************/

/* 3.3.3.1 Prefix increment and decrement operators */

void DirectCodeGenVisitor::visit(astnodes::PreIncDec * preIncDec)
{
    // first analyse the inner expression
    preIncDec->expr->accept(*this);
    
    ValuePosition* valPos = preIncDec->expr->valPos;
    
    valPos = atomizeOperand(valPos);
    ValuePosition* derefValPos = derefOperand(valPos);
    
    TypeImplementation* typeImpl = this->getTypeImplementation(preIncDec->valType->type);
    
    switch (preIncDec->optoken)
    {
        case INC_OP:
            typeImpl->inc(asm_current, derefValPos, preIncDec->pointerSize);
            break;
        case DEC_OP:
            typeImpl->dec(asm_current, derefValPos, preIncDec->pointerSize);
            break;
        default:
            throw new errors::InternalCompilerException("invalid inc/dec operator encountered");
    }
    
    preIncDec->valPos = derefValPos;
}

/* 3.3.3.2 Address and indirection operators */
// TODO add the Address of Operator!


/* 3.3.3.3 Unary arithmetic operators */

void DirectCodeGenVisitor::visit(astnodes::UnaryOperator * unaryOperator)
{
    // analyse inner expression first:
    unaryOperator->expr->accept(*this);
    
    ValuePosition* valPos = unaryOperator->expr->valPos;
    
    TypeImplementation* typeImpl = this->getTypeImplementation(unaryOperator->expr->valType->type);
    
    if (unaryOperator->LtoR)
    {
        valPos = derefOperand(valPos);
    }
    
    valPos = atomizeOperand(valPos);
    
    switch(unaryOperator->optoken)
    {
        case ADD_OP:
            unaryOperator->valPos = valPos;
            break;
        case SUB_OP:
            // get arithmetic inverse of type
            typeImpl->ainv(asm_current, valPos);
            break;
            
        case BIN_INV_OP:
            typeImpl->binv(asm_current, valPos);
            break;
            
        case NOT_OP:
            // get new register, delete old
            ValPosRegister regist = getFreeRegister();
            //ValuePosition* valPos = 
            break;
        default:
            throw new errors::InternalCompilerException("Unknown unary operator encountered");
    }
}


/* 3.3.3.4 The sizeof operator */

void DirectCodeGenVisitor::visit(astnodes::SizeOfOperator * sizeOfOperator)
{
    // analyse the expression inside the sizeof operator
    sizeOfOperator->allChildrenAccept(*this);
    
    // set return type as a CValue (constant RValue)
    sizeOfOperator->valType = new valuetypes::CValue(new types::UnsignedInt());
    
    // check it is not a function type
    if (valuetypes::IsValueTypeHelper::isFunctionDesignator(sizeOfOperator->valType))
    {
        addError(sizeOfOperator, ERR_CC_SIZEOF_FUNC);
        return;
    }
    
    // return the word size of the expression type
    // TODO special return value for array types??
    sizeOfOperator->constExpr = new astnodes::UnsignedIntLiteral(sizeOfOperator->valType->type->getByteSize());
    sizeOfOperator->constExpr->accept(*this);
}


/******************************/
/*  3.3.4 Cast operators      */
/******************************/

void DirectCodeGenVisitor::visit(astnodes::ExplicitCastOperator * explicitCastOperator)
{
    // TODO TODO TODO TODO
    // TODO TODO TODO TODO
    // TODO TODO TODO TODO
    printAstName("ExplicitCastOperator");
    explicitCastOperator->allChildrenAccept(*this);
}



/******************************/
/*     binary operators       */
/******************************/

void DirectCodeGenVisitor::visit(astnodes::BinaryOperator * binaryOperator)
{
    // analyse both sub-expressions
    binaryOperator->allChildrenAccept(*this);
    
    // TODO both operand have to be converted from R to L value
    //.TODO when they are converted, array type gets converted to pointer type
    // TODO otherwise all those checks below won't work properly :(
    
    valuetypes::ValueType* lhsVtype = binaryOperator->lhsExrp->valType;
    valuetypes::ValueType* rhsVtype = binaryOperator->rhsExpr->valType;
    types::Type* lhsType = lhsVtype->type;
    types::Type* rhsType = rhsVtype->type;
    
    
    switch(binaryOperator->optoken)
    {
        
        /* 3.3.5 Multiplicative operators */
        
        case MUL_OP:
        case DIV_OP:
            // check that the expression type is a arithmetic type
            if((!types::IsTypeHelper::isArithmeticType(lhsType))
                || !types::IsTypeHelper::isArithmeticType(rhsType))
            {
                addError(binaryOperator, ERR_CC_BIN_EXPECTED_ARITH);
                binaryOperator->valType = getInvalidValType();
                return;
            }
            binaryOperator->valType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype);
            binaryOperator->commonType = binaryOperator->valType->type;
            break;
        case MOD_OP:
            // check that the expression type is a integral type
            if((!types::IsTypeHelper::isIntegralType(lhsType))
                || !types::IsTypeHelper::isIntegralType(rhsType))
            {
                addError(binaryOperator, ERR_CC_BIN_EXPECTED_INTEGRAL);
                binaryOperator->valType = getInvalidValType();
                return;
            }
            binaryOperator->valType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype);
            binaryOperator->commonType = binaryOperator->valType->type;
            break;
        
            
        /* 3.3.6 Additive operators */
        
        case ADD_OP:
            if((types::IsTypeHelper::isArithmeticType(lhsType))
                && types::IsTypeHelper::isArithmeticType(rhsType))
            {
                // both are arithmetic types
                // promote:
                binaryOperator->valType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype);
                binaryOperator->commonType = binaryOperator->valType->type;
            }
            else if(((types::IsTypeHelper::isPointerType(lhsType))
                && types::IsTypeHelper::isIntegralType(rhsType)))

            {
                // pointer op
                binaryOperator->rhsPtr = true;
                binaryOperator->pointerSize = types::IsTypeHelper::getPointerBaseSize(lhsType);
                binaryOperator->commonType = types::IntegralPromotion::promote(rhsType);
                binaryOperator->valType = valuetypes::IsValueTypeHelper::toCorRValue(lhsType, lhsVtype, rhsVtype);
            }
            else if ((types::IsTypeHelper::isIntegralType(lhsType))
                && types::IsTypeHelper::isPointerType(rhsType))
            {
                // pointer op
                binaryOperator->rhsPtr = true;
                binaryOperator->pointerSize = types::IsTypeHelper::getPointerBaseSize(rhsType);
                binaryOperator->commonType = types::IntegralPromotion::promote(lhsType);
                binaryOperator->valType = valuetypes::IsValueTypeHelper::toCorRValue(rhsType, lhsVtype, rhsVtype);
            }
            else
            {
                addError(binaryOperator, ERR_CC_BIN_ADD_INVALID_TYPES);
                binaryOperator->valType = getInvalidValType();
                return;
            }
            break;
        case SUB_OP:
            if((types::IsTypeHelper::isArithmeticType(lhsType))
                && types::IsTypeHelper::isArithmeticType(rhsType))
            {
                // both are arithmetic types
                // promote:
                binaryOperator->valType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype);
                binaryOperator->commonType = binaryOperator->valType->type;
            } else if((binaryOperator->optoken == SUB_OP)
                && (types::IsTypeHelper::isPointerType(lhsType))
                && types::IsTypeHelper::isPointerType(rhsType))
            {
                // TODO add ptrdiff_t to stddef.h
                binaryOperator->lhsPtr = true;
                binaryOperator->rhsPtr = true;
                binaryOperator->pointerSize = types::IsTypeHelper::getPointerBaseSize(lhsType);
                // TODO properly check for compatible types pointed to
                if (binaryOperator->pointerSize != types::IsTypeHelper::getPointerBaseSize(rhsType))
                {
                    addError(binaryOperator, ERR_CC_PTR_NOT_COMPAT);
                    binaryOperator->valType = getInvalidValType();
                    return;
                }
                binaryOperator->valType = valuetypes::IsValueTypeHelper::toCorRValue(new types::SignedInt(), lhsVtype, rhsVtype);
            } else if((types::IsTypeHelper::isPointerType(lhsType))
                && types::IsTypeHelper::isIntegralType(rhsType))
            {
                binaryOperator->lhsPtr = true;
                binaryOperator->pointerSize = types::IsTypeHelper::getPointerBaseSize(lhsType);
                binaryOperator->commonType = types::IntegralPromotion::promote(rhsType);
                binaryOperator->valType = valuetypes::IsValueTypeHelper::toCorRValue(lhsType, lhsVtype, rhsVtype);
            }
            else
            {
                addError(binaryOperator, ERR_CC_BIN_SUB_INVALID_TYPES);
                binaryOperator->valType = getInvalidValType();
                return;
            }
            break;
            
            
        /* 3.3.7 Bitwise shift operators */
            
        case LEFT_OP:
        case RIGHT_OP:
            // check that the expression type is a integral type
            if((!types::IsTypeHelper::isIntegralType(lhsType))
                || !types::IsTypeHelper::isIntegralType(rhsType))
            {
                addError(binaryOperator, ERR_CC_BIN_EXPECTED_INTEGRAL);
                binaryOperator->valType = getInvalidValType();
                return;
            }
            
            binaryOperator->commonType = valuetypes::PromotionHelper::promote(lhsVtype)->type;
            binaryOperator->valType = valuetypes::IsValueTypeHelper::toCorRValue(binaryOperator->commonType, lhsVtype, rhsVtype);
            break;
            
        /* 3.3.8 Relational operators */
        case LT_OP:
        case GT_OP:
        case LE_OP:
        case GE_OP:
            if((types::IsTypeHelper::isArithmeticType(lhsType))
                && types::IsTypeHelper::isArithmeticType(rhsType))
            {
                // both are arithmetic types
                // promote:
                binaryOperator->commonType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype)->type;
                binaryOperator->valType = valuetypes::IsValueTypeHelper::toCorRValue(new types::SignedInt(), lhsVtype, rhsVtype);
            } else if((types::IsTypeHelper::isPointerType(lhsType))
                && types::IsTypeHelper::isPointerType(rhsType))
            {
                binaryOperator->lhsPtr = true;
                binaryOperator->rhsPtr = true;
                binaryOperator->pointerSize = types::IsTypeHelper::getPointerBaseSize(lhsType);
                
                // TODO properly check for compatible types pointed to
                if (binaryOperator->pointerSize != types::IsTypeHelper::getPointerBaseSize(rhsType))
                {
                    addError(binaryOperator, ERR_CC_PTR_NOT_COMPAT);
                    binaryOperator->valType = getInvalidValType();
                    return;
                }
                
                binaryOperator->valType = valuetypes::IsValueTypeHelper::toCorRValue(new types::SignedInt(), lhsVtype, rhsVtype);
            }
            else
            {
                addError(binaryOperator, ERR_CC_COMP_INVALID_TYPES);
                binaryOperator->valType = getInvalidValType();
                return;
            }
            break;
            
        
        /* 3.3.9 Equality operators */
        
        case EQ_OP:
        case NE_OP:
            if((types::IsTypeHelper::isArithmeticType(lhsType))
                && types::IsTypeHelper::isArithmeticType(rhsType))
            {
                // both are arithmetic types
                // promote:
                binaryOperator->commonType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype)->type;
                binaryOperator->valType = valuetypes::IsValueTypeHelper::toCorRValue(new types::SignedInt(), lhsVtype, rhsVtype);
            } else if((types::IsTypeHelper::isPointerType(lhsType))
                && types::IsTypeHelper::isPointerType(rhsType))
            {
                binaryOperator->lhsPtr = true;
                binaryOperator->rhsPtr = true;
                binaryOperator->pointerSize = types::IsTypeHelper::getPointerBaseSize(lhsType);
                
                // TODO properly check for compatible types pointed to
                if (binaryOperator->pointerSize != types::IsTypeHelper::getPointerBaseSize(rhsType))
                {
                    addError(binaryOperator, ERR_CC_PTR_NOT_COMPAT);
                    binaryOperator->valType = getInvalidValType();
                    return;
                }
                
                binaryOperator->valType = valuetypes::IsValueTypeHelper::toCorRValue(new types::SignedInt(), lhsVtype, rhsVtype);
            }
            // TODO case for Null pointer constant
            else
            {
                addError(binaryOperator, ERR_CC_COMP_INVALID_TYPES);
                binaryOperator->valType = getInvalidValType();
                return;
            }
            break;
        
            
        /* 3.3.10 Bitwise AND operator */
        /* 3.3.11 Bitwise exclusive OR operator */
        /* 3.3.12 Bitwise inclusive OR operator */
        
        case BIN_AND_OP:
        case BIN_XOR_OP:
        case BIN_OR_OP:
            // check that the expression type is a integral type
            if((!types::IsTypeHelper::isIntegralType(lhsType))
                || !types::IsTypeHelper::isIntegralType(rhsType))
            {
                addError(binaryOperator, ERR_CC_BIN_EXPECTED_INTEGRAL);
                binaryOperator->valType = getInvalidValType();
                return;
            }
            
            binaryOperator->valType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype);
            binaryOperator->commonType = binaryOperator->valType->type;
            break;
            
            
            /* 3.3.13 Logical AND operator */
            /* 3.3.14 Logical OR operator */
            
        case AND_OP:
        case OR_OP:
            
            // check that the expression type is a integral type
            if((!types::IsTypeHelper::isIntegralType(lhsType))
                || !types::IsTypeHelper::isIntegralType(rhsType))
            {
                addError(binaryOperator, ERR_CC_BIN_EXPECTED_INTEGRAL);
                binaryOperator->valType = getInvalidValType();
                return;
            }

            binaryOperator->commonType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype)->type;
            binaryOperator->valType = valuetypes::IsValueTypeHelper::toCorRValue(new types::SignedInt(), lhsVtype, rhsVtype);
            break;
            
        default:
            throw new errors::InternalCompilerException("unknown binary operator encountered");
    }
}

/********************************/
/* 3.3.15 Conditional operator  */
/********************************/
 
void DirectCodeGenVisitor::visit(astnodes::ConditionalOperator * conditionalOperator)
{
    // TODO TODO TODO TODO
    // TODO TODO TODO TODO
    // TODO TODO TODO TODO
    printAstName("ConditionalOperator");
    conditionalOperator->allChildrenAccept(*this);
}



/********************************/
/* 3.3.16 Assignment operators  */
/********************************/

void DirectCodeGenVisitor::visit(astnodes::AssignmentOperator * assignmentOperator)
{
    // first check lhs and rhs expression
    assignmentOperator->allChildrenAccept(*this);
    
    valuetypes::ValueType* lhsVtype = assignmentOperator->lhsExrp->valType;
    valuetypes::ValueType* rhsVtype = assignmentOperator->rhsExpr->valType;
    types::Type* lhsType = lhsVtype->type;
    types::Type* rhsType = rhsVtype->type;
   
    
    // check that the lhs is a modifiable LValue
    if(!valuetypes::IsValueTypeHelper::isModifiableLValue(assignmentOperator->lhsExrp->valType))
    {
        addError(assignmentOperator, ERR_CC_ASSIGN_NO_MOD_LVALUE);
    }
    
    switch (assignmentOperator->optoken)
    {
        
        /* 3.3.16.1 Simple assignment */
        
        case ASSIGN_EQUAL:
            if((types::IsTypeHelper::isArithmeticType(lhsType))
                && types::IsTypeHelper::isArithmeticType(rhsType))
            {
                // both are arithmetic types
                // promote:
                assignmentOperator->valType = new valuetypes::RValue(lhsType);
                assignmentOperator->commonType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype)->type;
            }
            else if((types::IsTypeHelper::isPointerType(lhsType))
                && types::IsTypeHelper::isPointerType(rhsType))
            {
                // TODO properly check for compatible types pointed to
                assignmentOperator->ptrop = true;
                assignmentOperator->valType = new valuetypes::RValue(lhsType);
            }
            else if((types::IsTypeHelper::isStructUnionType(lhsType))
                && types::IsTypeHelper::isStructUnionType(rhsType))
            {
                // TODO properly check for compatible structs/unions
                assignmentOperator->valType = new valuetypes::RValue(lhsType);
            }
            else
            {
                addError(assignmentOperator, ERR_CC_ASSIGN_INVALID_TYPES);
                assignmentOperator->valType = getInvalidValType();
                return;
            }
            break;
            
            
        /* 3.3.16.2 Compound assignment */
            
        case ADD_ASSIGN:
        case SUB_ASSIGN:
            if((types::IsTypeHelper::isArithmeticType(lhsType))
                && types::IsTypeHelper::isArithmeticType(rhsType))
            {
                // both are arithmetic types
                // promote:
                assignmentOperator->valType = new valuetypes::RValue(lhsType);
                assignmentOperator->commonType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype)->type;
            }
            else if(((types::IsTypeHelper::isPointerType(lhsType))
                && types::IsTypeHelper::isIntegralType(rhsType)))
                
            {
                // pointer op
                assignmentOperator->ptrop = true;
                assignmentOperator->pointerSize = types::IsTypeHelper::getPointerBaseSize(lhsType);
                assignmentOperator->valType = new valuetypes::RValue(lhsType);
            }
            else
            {
                addError(assignmentOperator, ERR_CC_ASSIGN_INVALID_TYPES);
                assignmentOperator->valType = getInvalidValType();
                return;
            }
            break;
            
        case MUL_ASSIGN:
        case DIV_ASSIGN:
            if((types::IsTypeHelper::isArithmeticType(lhsType))
                && types::IsTypeHelper::isArithmeticType(rhsType))
            {
                // both are arithmetic types
                // promote:
                assignmentOperator->valType = new valuetypes::RValue(lhsType);
                assignmentOperator->commonType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype)->type;
            }
            else
            {
                addError(assignmentOperator, ERR_CC_ASSIGN_INVALID_TYPES);
                assignmentOperator->valType = getInvalidValType();
                return;
            }
            break;
            
        case MOD_ASSIGN:
        case LEFT_ASSIGN:
        case RIGHT_ASSIGN:
        case AND_ASSIGN:
        case XOR_ASSIGN:
        case OR_ASSIGN:
            if((types::IsTypeHelper::isIntegralType(lhsType))
                && types::IsTypeHelper::isIntegralType(rhsType))
            {
                // both are arithmetic types
                // promote:
                assignmentOperator->valType = new valuetypes::RValue(lhsType);
                assignmentOperator->commonType = valuetypes::PromotionHelper::commonType(lhsVtype, rhsVtype)->type;
            }
            else
            {
                addError(assignmentOperator, ERR_CC_ASSIGN_INVALID_TYPES);
                assignmentOperator->valType = getInvalidValType();
                return;
            }
            break;
        default:
            throw new errors::InternalCompilerException("unknown assignment operator encountered");
    }
}



/********************************/
/*  3.3.17 Comma operator       */
/********************************/

void DirectCodeGenVisitor::visit(astnodes::ChainExpressions * chainExpressions)
{
    // analyse all children
    chainExpressions->allChildrenAccept(*this);
    
    // check if all values types are constant
    bool isCValue = true;
    if (chainExpressions->exprs != NULL && chainExpressions->exprs->size() > 0)
    {
        for (astnodes::Expressions::iterator i = chainExpressions->exprs->begin(); i != chainExpressions->exprs->end(); ++i)
        {
            if (!valuetypes::IsValueTypeHelper::isCValue((*i)->valType))
                isCValue = false;
        }
        
        if (isCValue)
            chainExpressions->valType = new valuetypes::CValue(chainExpressions->exprs->back()->valType->type);
        else
            chainExpressions->valType = new valuetypes::RValue(chainExpressions->exprs->back()->valType->type);
    }
    else
    {
        throw new errors::InternalCompilerException("chain expressions without any expressions");
    }
}






// TODO implement those below
// TODO implement deref und address of operators!!





void DirectCodeGenVisitor::visit(astnodes::Enumerator * enumerator)
{
    printAstName("Enumerator");
    enumerator->allChildrenAccept(*this);
}


void DirectCodeGenVisitor::visit(astnodes::AssemblyStatement * assemblyStatement)
{
    printAstName("AssemblyStatement");
    assemblyStatement->allChildrenAccept(*this);
}


void DirectCodeGenVisitor::visit(astnodes::BuiltInVaStart * builtInVaStart)
{
    printAstName("BuiltInVaStart");
    builtInVaStart->allChildrenAccept(*this);
}

