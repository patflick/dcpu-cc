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
#include "typeimpl/TypeConversions.h"

// only include the int tokens
#define YYSTYPE int
#include <parser.hpp>

using namespace dtcc;
using namespace dtcc::codegen;


/* constructor */
// TODO make the assembler a constructor parameter
DirectCodeGenVisitor::DirectCodeGenVisitor() : assembler(*Assembler::getAssembler("toolchain"))
{
    this->asm_functions = std::deque<std::string>();
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
    // TODO implement this correctly
    //str << ".ULINE " << node->line << " \"" << node->file << "\"" << std::endl;
    return str.str();
}

std::string DirectCodeGenVisitor::getAssembly()
{
    std::stringstream ss;
    ss << "; ================================================" << std::endl;
    ss << ";  dtcc2 - an ANSI C (C89) compiler for the DCPU"   << std::endl;
    ss << "; ================================================" << std::endl;
    ss << ";  Repository: https://github.com/r4d2/dtcc2" << std::endl;
    ss << ";  Bug reports and fixes to: https://github.com/r4d2/dtcc2/issues" << std::endl;
    ss << std::endl;
    ss << std::endl;
    ss << "; ------------------" << std::endl;
    ss << ";  Import Bootstrap" << std::endl;
    ss << "; ------------------" << std::endl;
    ss << ".IMPORT _stack_caller_init" << std::endl;
    ss << ".IMPORT _stack_caller_init_overlap" << std::endl;
    ss << ".IMPORT _stack_callee_return" << std::endl;
    ss << ".IMPORT cfunc__stdlib_enter" << std::endl;
    ss << std::endl;
    ss << std::endl;
    ss << "; ---------------------" << std::endl;
    ss << ";  Extern Declarations" << std::endl;
    ss << "; ---------------------" << std::endl;
    ss << asm_globalImport.str();
    ss << std::endl;
    ss << std::endl;
    ss << "; ------------------" << std::endl;
    ss << ";  Global Variables" << std::endl;
    ss << "; ------------------" << std::endl;
    ss << asm_globalSpace.str();
    ss << std::endl;
    ss << std::endl;
    ss << "; ------------------" << std::endl;
    ss << ";  Global Constants" << std::endl;
    ss << "; ------------------" << std::endl;
    ss << asm_Constants.str();
    ss << std::endl;
    ss << std::endl;
    ss << "; ------------------" << std::endl;
    ss << ";  String Constants" << std::endl;
    ss << "; ------------------" << std::endl;
    ss << asm_stringConstants.str();
    ss << std::endl;
    ss << std::endl;
    ss << "; ------------------------" << std::endl;
    ss << ";  Globals Initialization" << std::endl;
    ss << "; ------------------------" << std::endl;
    ss << ".SECTION INIT" << std::endl;
    ss << asm_globalInit.str();
    ss << std::endl;
    ss << std::endl;
    ss << "; --------------------------" << std::endl;
    ss << ";  Code (call stdlib_enter)" << std::endl;
    ss << "; --------------------------" << std::endl;
    ss << ".SECTION CODE" << std::endl;
    ss << "    SET X, 0" << std::endl;
    ss << "    SET Z, 0" << std::endl;
    ss << "    JSR _stack_caller_init" << std::endl;
    ss << "    SET PC, cfunc__stdlib_enter" << std::endl;
    ss << std::endl;
    ss << std::endl;
    ss << "; ------------------" << std::endl;
    ss << ";  Code (functions)" << std::endl;
    ss << "; ------------------" << std::endl;
    for (std::deque<std::string>::iterator i = asm_functions.begin(); i != asm_functions.end(); ++i)
    {
        ss << *i;
    }
    ss << std::endl;
    ss << std::endl;
    
    return ss.str();
}


/* register management */

void DirectCodeGenVisitor::initFreeRegisters()
{
    for (int r = REG_A; r <= REG_Z; r++)
    {
        m_registersUsed[r] = false;
    }

    m_registersUsed[REG_FRAME_POINTER] = true;
    m_registersUsed[REG_TMP_L] = true;
    m_registersUsed[REG_TMP_R] = true;
}

ValPosRegister DirectCodeGenVisitor::getFreeRegister()
{
    for (int r = REG_A; r <= REG_Z; r++)
    {
        if (!m_registersUsed[r])
        {
            m_registersUsed[r] = true;
            return (ValPosRegister)r;
        }
    }
    
    // register spilling should happen elsewhere
    // TODO implement register spilling
    throw new errors::InternalCompilerException("no free register available");
}

bool DirectCodeGenVisitor::isFreeRegisterAvailable()
{
    for (int r = REG_A; r <= REG_Z; r++)
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
    m_tempStackMax = std::max(m_tempStackMax, (int)m_tempStackAlloc.size());
    
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
        return ValuePosition::createTmpRegisterPos(reg);
    }
    else
    {
        // get word on temporary stack
        int pos = getTempStack(1);
        return ValuePosition::createTempStackWord(-m_currentFunctionTempStackOffset-pos-1);
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


std::string DirectCodeGenVisitor::getRandomLabelName(std::string prefix)
{
    std::string result = "";
    
    while ((result == "") || (this->m_AutomaticLabels.find(result) != this->m_AutomaticLabels.end()))
        result = prefix + "_" + DirectCodeGenVisitor::getRandomString(10);
    
    return result;
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


TypeImplementation* DirectCodeGenVisitor::getTypeImplementation(types::Type* type)
{
    type->accept(getTypeImpl);
    return getTypeImpl.getTypeImplementation();
}



/******************************/
/* visit functions            */
/******************************/


void DirectCodeGenVisitor::visit(astnodes::Program * program)
{
    // output .IMPORT for all functions that were only declared and not defined
    for (std::vector<std::string>::iterator it = program->functionDecls.begin(); it != program->functionDecls.end(); ++it)
    {
        asm_globalImport << "    .IMPORT cfunc_" << *it << std::endl;
    }
    
    // compile everything
    program->allChildrenAccept(*this);
    
    // put all current asm into global init
    asm_globalInit << asm_current.str();
}


void DirectCodeGenVisitor::visit(astnodes::FunctionDefinition * functionDefinition)
{
    std::stringstream asmStr;
    asmStr << std::endl;
    
    // put all current asm into global init
    asm_globalInit << asm_current.str();
    // clear output:
    asm_current.str(std::string());
    
    // print function header
    asmStr << "; === BEGIN  function: " << functionDefinition->name << "  BEGIN ==="<< std::endl;
    
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
    if (functionDefinition->exportFunction && assembler.supportsLinkedExportDirective)
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
    
    // init temporary registers
    initFreeRegisters();
    
    // Now compile the block.
    functionDefinition->block->accept(*this);
    
    // Allocate locals and temporaries
    unsigned int stacksize = functionDefinition->stackSize + m_tempStackMax;
    if (stacksize > 0)
        asmStr <<  "    SUB SP, " << stacksize << std::endl;
    
    asmStr << asm_current.str();
    
    // an end of function label, a return; jumps here after saving the result
    asmStr <<  ":cfunc_" << functionDefinition->name << "_end" << std::endl;
    
    // Free locals and temporaries
    if (stacksize > 0)
        asmStr <<  "    ADD SP, " << stacksize << std::endl;
    
    // Return from this function.
    asmStr <<  "    SET A, 0xFFFF" << std::endl;
    asmStr <<  "    SET X, " << functionDefinition->paramSize << std::endl;
    asmStr <<  "    SET PC, _stack_callee_return" << std::endl;
    
    // print function footer
    asmStr << std::endl;
    asmStr << "; === END  function: " << functionDefinition->name << "  END ==="<< std::endl;
    asmStr << std::endl;
    asmStr << std::endl;
    
    // put the generated code in the functions list
    asm_functions.push_back(asmStr.str());
    
    // clear output:
    asm_current.str(std::string());
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
    
    ValuePosition* valPos = forStatement->condExpr->expr->valPos;
    TypeImplementation* typeImpl = getTypeImplementation(forStatement->condExpr->expr->valType->type);
    valPos = makeAtomicReadable(valPos);
    
    // If A is not true, jump to the end.
    typeImpl->jmpeqz(asm_current, valPos, forStatement->endLbl->label);
    
    maybeFreeTemporary(valPos);
    
    // Compile the main block.
    forStatement->statement->accept(*this);
    
    // Output the continue label.
    asm_current << ":" << forStatement->continueLbl->label << std::endl;
    
    // Do the loop statement.
    forStatement->loopExpr->accept(*this);
    
    maybeFreeTemporary(forStatement->loopExpr->valPos);
    
    // Jump back up to the start to do the evaluation.
    asm_current << "    SET PC, " << forStatement->startLbl->label << std::endl;
    
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
    
    ValuePosition* valPos = doWhileStatement->condExpr->valPos;
    TypeImplementation* typeImpl = getTypeImplementation(doWhileStatement->condExpr->valType->type);
    valPos = makeAtomicReadable(valPos);
    
    // while the expression is true, jump to beginning
    typeImpl->jmpneqz(asm_current, valPos, doWhileStatement->startLbl->label);
    
    // free now unused temporaries
    maybeFreeTemporary(valPos);
    
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
    
    // get ValuePosition of the conditional expression
    ValuePosition* valPos = whileStatement->condExpr->valPos;
    TypeImplementation* typeImpl = getTypeImplementation(whileStatement->condExpr->valType->type);
    valPos = makeAtomicReadable(valPos);
    
    // if the expression evaluates to false, jump to end
    typeImpl->jmpeqz(asm_current, valPos, whileStatement->endLbl->label);
    
    // free now unused temporaries
    maybeFreeTemporary(valPos);
    
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
    
    // get ValuePosition of the conditional expression
    ValuePosition* valPos = ifStatement->condExpr->valPos;
    TypeImplementation* typeImpl = getTypeImplementation(ifStatement->condExpr->valType->type);
    valPos = makeAtomicReadable(valPos);
    
    // check for the result of the conditional expression
    if (ifStatement->elseStmt != NULL)
        typeImpl->jmpeqz(asm_current, valPos, ifStatement->elselbl->label);
    else
        typeImpl->jmpeqz(asm_current, valPos, ifStatement->endlbl->label);
    
    // free now unused temporaries
    maybeFreeTemporary(valPos);
    
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
    
    // free now unused temporaries
    maybeFreeTemporary(expressionStatement->expr->valPos);
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


std::string DirectCodeGenVisitor::getDats(unsigned int num)
{
    std::stringstream ss;
    unsigned int i;
    while (num > 0)
    {
        ss << "    DAT 0x0";
        for (i = 1; i < 10 && i < num; i++)
        {
            ss << ", 0x0";
        }
        ss << std::endl;
        num -= i;
    }
    return ss.str();
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
    if (!identifierDeclarator->isVariableDeclaration)
        return;
    
    // get value position from identifier
    types::Type* type = identifierDeclarator->variableType;
    unsigned int rawsize = type->getWordSize();
    
    // output globals
    switch (identifierDeclarator->varoutput)
    {
        case astnodes::VAROUT_EXTERN:
            asm_globalImport << ".IMPORT cglob_" << identifierDeclarator->name << std::endl;
            return;
            break;
        // TODO handle local statics separately (otherwise there will be naming conflicts)
        case astnodes::VAROUT_STATIC:
            asm_globalSpace << "cglob_" << identifierDeclarator->name << ":" << std::endl;
            asm_globalSpace << getDats(rawsize);
            break;
        case astnodes::VAROUT_GLOBAL:
            asm_globalSpace << ".EXPORT cglob_" << identifierDeclarator->name << std::endl;
            asm_globalSpace << "cglob_" << identifierDeclarator->name << ":" << std::endl;
            asm_globalSpace << getDats(rawsize);
            break;
        default:
            // no output
            break;
    }
    
    if (types::IsTypeHelper::isArrayType(type))
    {
        types::ArrayType* arrtype = types::IsTypeHelper::getArrayType(type);
        type = arrtype->basetype;
    }
    unsigned int size = type->getWordSize();
    ValuePosition* valPos = typePositionToValuePosition(identifierDeclarator->typePos, size);
    
    if (identifierDeclarator->initializers != NULL)
    {
        for (astnodes::Expressions::iterator i = identifierDeclarator->initializers->begin(); i != identifierDeclarator->initializers->end(); ++i)
        {
            // compile the expression
            (*i)->accept(*this);
            
            // save the result
            ValuePosition* resultVP = (*i)->valPos;
            resultVP = makeAtomicReadable(resultVP, REG_TMP_R);
            ValuePosition* derefValPos = makeAtomicDerefable(valPos, REG_TMP_L);
            
            if (size == 1)
            {
                derefValPos = valPos->atomicDeref();
            }
            
            copyValue(resultVP, derefValPos);
            
            valPos = valPos->addOffset(size);
            
            maybeFreeTemporary(resultVP);
            maybeFreeTemporary(derefValPos);
        }
    }
}


/* 3.5.4.1 Pointer declarators */

void DirectCodeGenVisitor::visit(astnodes::Pointer * pointer)
{
    // nothing to do
}


/* 3.5.4.2 Array declarators */

void DirectCodeGenVisitor::visit(astnodes::ArrayDeclarator * arrayDeclarator)
{
    // nothing to do
    arrayDeclarator->baseDeclarator->accept(*this);
}


/* 3.5.4.3 Function declarators */

void DirectCodeGenVisitor::visit(astnodes::FunctionDeclarator * functionDeclarator)
{
    // nothing to do
    functionDeclarator->baseDeclarator->accept(*this);
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

ValuePosition* DirectCodeGenVisitor::typePositionToValuePosition(symboltable::TypePosition typePos, unsigned int size)
{
    if (typePos.isFPrel())
    {
        return ValuePosition::createFPrel(typePos.getFPoffset(), size);
    }
    else if (typePos.isFunction())
    {
        return ValuePosition::createLabelPos(std::string("cfunc_") + typePos.getFunctionName());
    }
    if (typePos.isGlobal())
    {
        return ValuePosition::createLabelPos(std::string("cglob_") + typePos.getGlobalVariableName());
    }
    else
    {
        throw new errors::InternalCompilerException("unknown typeposition");
    }
}


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
    
    // get value position from identifier
    types::Type* type = identifier->valType->type;
    if (types::IsTypeHelper::isArrayType(type))
    {
        type = types::IsTypeHelper::pointerFromArrayType(type);
    }
    unsigned int size = type->getWordSize();
    identifier->valPos = typePositionToValuePosition(identifier->typePos, size);
}


/* constants */

ValuePosition* DirectCodeGenVisitor::handleLiteral(std::deque<std::string> vals)
{
    if (vals.size() > 1)
    {
        std::string label = getRandomLabelName("constant_");
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
    std::stringstream ss;
    ss << "'" << escapeChar(characterLiteral->str[0]) << "'";
    std::deque<std::string> ch;
    ch.push_back(ss.str());
    characterLiteral->valPos = handleLiteral(ch);
}


void DirectCodeGenVisitor::visit(astnodes::SignedIntLiteral * signedIntLiteral)
{
    TypeImplementation* typeImpl = getTypeImplementation(signedIntLiteral->valType->type);
    signedIntLiteral->valPos = handleLiteral(typeImpl->printConstant(signedIntLiteral->literalValue));
}


void DirectCodeGenVisitor::visit(astnodes::UnsignedIntLiteral * unsignedIntLiteral)
{
    TypeImplementation* typeImpl = getTypeImplementation(unsignedIntLiteral->valType->type);
    unsignedIntLiteral->valPos = handleLiteral(typeImpl->printConstant(unsignedIntLiteral->literalValue));
}


void DirectCodeGenVisitor::visit(astnodes::SignedLongLiteral * signedLongLiteral)
{
    TypeImplementation* typeImpl = getTypeImplementation(signedLongLiteral->valType->type);
    signedLongLiteral->valPos = handleLiteral(typeImpl->printConstant(signedLongLiteral->literalValue));
}


void DirectCodeGenVisitor::visit(astnodes::UnsignedLongLiteral * unsignedLongLiteral)
{
    TypeImplementation* typeImpl = getTypeImplementation(unsignedLongLiteral->valType->type);
    unsignedLongLiteral->valPos = handleLiteral(typeImpl->printConstant(unsignedLongLiteral->literalValue));
}


void DirectCodeGenVisitor::visit(astnodes::FloatLiteral * floatLiteral)
{
    TypeImplementation* typeImpl = getTypeImplementation(floatLiteral->valType->type);
    floatLiteral->valPos = handleLiteral(typeImpl->printConstant(floatLiteral->literalValue));
}


void DirectCodeGenVisitor::visit(astnodes::DoubleLiteral * doubleLiteral)
{
    TypeImplementation* typeImpl = getTypeImplementation(doubleLiteral->valType->type);
    doubleLiteral->valPos = handleLiteral(typeImpl->printConstant(doubleLiteral->literalValue));
}


void DirectCodeGenVisitor::visit(astnodes::LongDoubleLiteral * longDoubleLiteral)
{
    TypeImplementation* typeImpl = getTypeImplementation(longDoubleLiteral->valType->type);
    longDoubleLiteral->valPos = handleLiteral(typeImpl->printConstant(longDoubleLiteral->literalValue));
}

std::string DirectCodeGenVisitor::escapeChar(char c)
{
    std::stringstream outputstr;
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
    return outputstr.str();
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
        outputstr << escapeChar(c);
    }
    outputstr << "\"";
    
    // add string constant to global string constants
    std::string label = getRandomLabelName(std::string("string_const_"));
    asm_stringConstants << label << ":" << std::endl;
    asm_stringConstants << "    DAT " << outputstr.str() << ", 0x0" << std::endl;
    
    // set a label ValuePosition
    stringLiteral->valPos = ValuePosition::createLabelPos(label);
}


/*
 * TODO
 * everything that references a LValue (i.e. assignment, inc/dec) needs:
 * - in case of size == 1:
 *  ->  needs to be atomically dereffable (if it isn't use temp register), then get value (the LValue)
 *      for the assignment of the new value
 *  -> and then return a temp copy (in most cases) or the derefed valuepos
 * 
 * - in case of size > 1:
 *   -> needs atomically offset dereffable (if it isn't, use temp register) in order
 *      to assign or inc/dec.
 *   -> needs to create temp copy for returning of value (in case of post inc/dec before doing the inc/dec).
 * 
 * 
 * LValue -> RValue deref:
 *  - in case of size == 1:
 *      -> if atomically deref:
 *              => do atomically deref
 *      -> else
 *              if valpos is not atomicOperand or valpos is not modifyable
 *                  valpos = get temp copy (which is always an atomic operand)

 *              (use temporary register)
 *              valToRegister(TMP_X, valpos)
 *              SET valpos, [TMP_X]
 * - in case of size > 1:
 *      => do nothing!
 * 
 * RValue modifications:
 *  1) LHS is not modifyable:
 *      get temp copy(of size `size`)
 *  2) RHS or LHS not atomic
 *      case of size == 1:
 *          not atomic:
 *              LHS => get temp copy
 *              RHS => use TMP_L with valToRegister
 *          return LHS valpos, either old or new temp
 *      case of size > 1:
 *          not atomically deref offset:
 *              get value into temp register (which is the address).
 *              this is always atomically deref offset (i.e. [TMP+offset]
 *              but return old LHS/RHS valpos (not the one that uses the temporary register)
 * 
 */


ValuePosition* DirectCodeGenVisitor::makeAtomicModifyable(ValuePosition* operandVP)
{
    return makeAtomicModifyable(operandVP, REG_TMP_L);
}

ValuePosition* DirectCodeGenVisitor::makeAtomicModifyable(ValuePosition* operandVP, ValPosRegister tmpReg)
{
    // for the lhs of operations (i.e. the one that is written)
    ValuePosition* newVP = operandVP;
    if (operandVP->getWordSize() == 1)
    {
        if (!operandVP->isAtomicOperand() || !operandVP->isModifyableTemp())
        {
            newVP = getTmpCopy(operandVP);
        }
    }
    else
    {
        if (!operandVP->canAtomicDerefOffset() || !operandVP->isModifyableTemp())
        {
            if (!operandVP->canAtomicDerefOffset())
            {
                // get the address into the LHS temporary register
                operandVP = operandVP->valToRegister(asm_current, tmpReg);
            }
            newVP = getTmpCopy(operandVP);
        }
    }
    return newVP;
}


ValuePosition* DirectCodeGenVisitor::makeAtomicReadable(ValuePosition* operandVP)
{
    return makeAtomicReadable(operandVP, REG_TMP_R);
}

ValuePosition* DirectCodeGenVisitor::makeAtomicReadable(ValuePosition* operandVP, ValPosRegister tmpReg)
{
    // for operands that only need reading (and can thus use temp registers)
    ValuePosition* newVP = operandVP;
    if (operandVP->getWordSize() == 1)
    {
        if (!operandVP->isAtomicOperand())
        {
            newVP = operandVP->valToRegister(asm_current, tmpReg);
        }
    }
    else
    {
        if (!operandVP->canAtomicDerefOffset())
        {
            // get the address into the LHS temporary register
            newVP = operandVP->valToRegister(asm_current, tmpReg);
        }
    }
    return newVP;
}

ValuePosition* DirectCodeGenVisitor::makeAtomicDerefable(ValuePosition* operandVP, ValPosRegister regist)
{
    ValuePosition* newVP = operandVP;
    if (operandVP->getWordSize() == 1)
    {
        if (!operandVP->canAtomicDeref())
        {
            newVP = operandVP->valToRegister(asm_current, regist);
        }
    }
    else
    {
        if (!operandVP->canAtomicDerefOffset())
        {
            newVP = operandVP->valToRegister(asm_current, regist);
        }
    }
    return newVP;
}


ValuePosition* DirectCodeGenVisitor::derefOperand(ValuePosition* operandVP, ValPosRegister tmpRegist)
{
    /*
     * LValue -> RValue deref:
     *  - in case of size == 1:
     *      -> if atomically deref:
     *              => do atomically deref
     *      -> else
     *              if valpos is not atomicOperand or valpos is not modifyable
     *                  valpos = get temp copy (which is always an atomic operand)
     * 
     *              (use temporary register)
     *              valToRegister(TMP_X, valpos)
     *              SET valpos, [TMP_X]
     * - in case of size > 1:
     *      => do nothing!
     */
    ValuePosition* newVP = operandVP;
    if (operandVP->getWordSize() == 1)
    {
        if (operandVP->canAtomicDeref())
            newVP = operandVP->atomicDeref();
        else
        {
            ValuePosition* tmpRegVP = newVP->valToRegister(asm_current, tmpRegist);
            tmpRegVP = tmpRegVP->atomicDeref();
            if ((!operandVP->isAtomicOperand()) || (!operandVP->isModifyableTemp()))
                newVP = getTmp(1);
            copyValue(tmpRegVP, newVP);
        }
    }
    return newVP;
}

ValuePosition* DirectCodeGenVisitor::pushToStack(ValuePosition* valPos)
{
    if (valPos->getWordSize() == 1)
    {
        asm_current << "SET PUSH, " << valPos->toAtomicOperand() << std::endl;
    } else if (valPos->getWordSize() < MIN_SIZE_LOOP_COPY)
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
        
        std::string loopLabel = getRandomLabelName("copy_loop_");
        std::string loopEndLabel = getRandomLabelName("copy_loop_");
        
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
}

ValuePosition* DirectCodeGenVisitor::getTmpCopy(ValuePosition* from)
{
    ValuePosition* tmp = getTmp(from->getWordSize());
    copyValue(from, tmp);
    return tmp;
}

void DirectCodeGenVisitor::copyValue(ValuePosition* from, ValuePosition* to)
{
    if (from->getWordSize() != to->getWordSize())
    {
        throw new errors::InternalCompilerException("trying to copy values of different size");
    }
    
    int size = from->getWordSize();
    if (size == 1)
    {
        asm_current << "SET " << to->toAtomicOperand() << ", " << from->toAtomicOperand() << std::endl;
    }
    //else if (size < MIN_SIZE_LOOP_COPY)
    else
    {
        for (int i = size - 1; i >= 0; i--)
        {
            if (i > 0)
                asm_current << "SET " << to->atomicDerefOffset(i)->toAtomicOperand() << ", " << from->atomicDerefOffset(i)->toAtomicOperand() << std::endl;
            else
                asm_current << "SET " << to->atomicDeref()->toAtomicOperand() << ", " << from->atomicDeref()->toAtomicOperand() << std::endl;
        }
    }
    /*
    else
    {
        // big copy, use a loop in asm to save code length
        // TODO
        // FIXME
    }
    */
}

ValuePosition* DirectCodeGenVisitor::getTmp(int size)
{
    if (size == 1)
    {
        return getTempWordPos();
    }
    else if (size > 1)
    {
        // get temp on temporary stack
        int pos = getTempStack(size);
        return ValuePosition::createTempStack(-m_currentFunctionTempStackOffset-pos-1, size);
    }
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
    
    // compile offset
    arrayAccessOperator->rhsExpr->accept(*this);
    
    ValuePosition* rhsVP = arrayAccessOperator->rhsExpr->valPos;
    
    // get type implementation
    TypeImplementation* typeImpl = this->getTypeImplementation(new types::UnsignedInt());
    
    // deref lhs if necessary
    if (arrayAccessOperator->lhsLtoR)
        lhsVP = derefOperand(lhsVP, REG_TMP_L);
    else
    {
        // in this case, the value position is the array address.
        ValuePosition* tmpReg = lhsVP->valToRegister(asm_current, REG_TMP_L);
        ValuePosition* newLhsVP = getTmpCopy(tmpReg);
        maybeFreeTemporary(lhsVP);
        lhsVP = newLhsVP;
    }
    
    /* deref RHS if necessary */
    if (arrayAccessOperator->rhsLtoR)
    {
        rhsVP = derefOperand(rhsVP, REG_TMP_R);
    }
    
    if (arrayAccessOperator->pointerSize > 1)
    {
        rhsVP = makeAtomicModifyable(rhsVP, REG_TMP_R);
        // multiply by pointer size
        typeImpl->mul(asm_current, rhsVP, ValuePosition::createAtomicConstPos(arrayAccessOperator->pointerSize));
        // add to address
        typeImpl->add(asm_current, lhsVP, rhsVP);
    }
    else
    {
        // in this case no multiplication is necessary
        rhsVP = makeAtomicReadable(rhsVP);
        // add to address
        typeImpl->add(asm_current, lhsVP, rhsVP);
    }
    
    // return this value (which is a LValue)
    arrayAccessOperator->valPos = lhsVP;
}


/* 3.3.2.2 Function calls */

void DirectCodeGenVisitor::visit(astnodes::MethodCall * methodCall)
{
    // compile the lhs
    methodCall->lhsExpr->accept(*this);
    
    ValuePosition* lhsValPos = methodCall->lhsExpr->valPos;
    
    // reserve some space for the return value
    ValuePosition* returnValPos =  getTmp(methodCall->returnType->getWordSize());
    
    // compile and push on stack in reverse order
    unsigned int parametersize = 0;
    std::string jmpback = getRandomLabelName("_function_call_return_");
    for (int i = methodCall->rhsExprs->size() - 1; i >= 0 ; i--)
    {
        astnodes::Expression* expr = (*methodCall->rhsExprs)[i];
        expr->accept(*this);
        
        ValuePosition* paramValPos = expr->valPos;
        
        // TODO do this part in the semantic analysis visitor
        if (valuetypes::IsValueTypeHelper::isLValue(expr->valType))
        {
            if (!types::IsTypeHelper::isArrayType(expr->valType->type))
                paramValPos = derefOperand(paramValPos, REG_TMP_R);
        }
        
        paramValPos = makeAtomicReadable(paramValPos);
        
        // push to stack (in reverse order)
        pushToStack(paramValPos);
        
        // free any used temporaries
        maybeFreeTemporary(paramValPos);
        
        // add to stack size
        parametersize += paramValPos->getWordSize();
    }
    
    // get atomically readable variable
    lhsValPos = makeAtomicReadable(lhsValPos, REG_TMP_L);
    
    asm_current <<  "    SET Z, " << jmpback << std::endl;
    asm_current <<  "    JSR _stack_caller_init_overlap" << std::endl;
    asm_current <<  "    SET PC, " << lhsValPos->toAtomicOperand() << std::endl;
    asm_current <<  ":" << jmpback << std::endl;
    
    if (methodCall->varArgsSize > 0)
    {
        asm_current << "    ADD SP, " << methodCall->varArgsSize << std::endl;
    }
    
    methodCall->valPos = returnValPos;
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
    /*
    * everything that references a LValue (i.e. assignment, inc/dec) needs:
    * - in case of size == 1:
    *  ->  needs to be atomically dereffable (if it isn't use temp register), then get value (the LValue)
    *      for the assignment of the new value
    *  -> and then return a temp copy (in most cases) or the derefed valuepos
    * 
    * - in case of size > 1:
    *   -> needs atomically offset dereffable (if it isn't, use temp register) in order
    *      to assign or inc/dec.
    *   -> needs to create temp copy for returning of value (in case of post inc/dec before doing the inc/dec).
    */
    
    
    // first analyse the inner expression
    postIncDec->expr->accept(*this);
    
    ValuePosition* valPos = postIncDec->expr->valPos;
    
    valPos = makeAtomicDerefable(valPos, REG_TMP_L);
    
    if (valPos->getWordSize() == 1)
    {
        valPos = valPos->atomicDeref();
    }
    
    ValuePosition* derefCpy = getTmpCopy(valPos);
    
    TypeImplementation* typeImpl = this->getTypeImplementation(postIncDec->valType->type);
    
    switch (postIncDec->optoken)
    {
        case INC_OP:
            typeImpl->inc(asm_current, valPos, postIncDec->pointerSize);
            break;
        case DEC_OP:
            typeImpl->dec(asm_current, valPos, postIncDec->pointerSize);
            break;
        default:
            throw new errors::InternalCompilerException("invalid inc/dec operator encountered");
    }
    
    maybeFreeTemporary(valPos);
    
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
    
    ValuePosition* atomicValPos = makeAtomicDerefable(valPos, REG_TMP_L);
    
    if (atomicValPos->getWordSize() == 1)
    {
        atomicValPos = atomicValPos->atomicDeref();
    }
    
    TypeImplementation* typeImpl = this->getTypeImplementation(preIncDec->valType->type);
    
    switch (preIncDec->optoken)
    {
        case INC_OP:
            typeImpl->inc(asm_current, valPos, preIncDec->pointerSize);
            break;
        case DEC_OP:
            typeImpl->dec(asm_current, valPos, preIncDec->pointerSize);
            break;
        default:
            throw new errors::InternalCompilerException("invalid inc/dec operator encountered");
    }
    
    
    if (atomicValPos == valPos)
        preIncDec->valPos = atomicValPos;
    else
    {
        preIncDec->valPos = getTmpCopy(atomicValPos);
        maybeFreeTemporary(atomicValPos);
    }
}

/* 3.3.3.2 Address and indirection operators */
void DirectCodeGenVisitor::visit(astnodes::AddressOfOperator * addressOfOperator)
{
    // analyse inner expression first:
    addressOfOperator->expr->accept(*this);
    
    // same valpos as inner expression (which was an LValue and is now handled
    // as an RValue)
    addressOfOperator->valPos = addressOfOperator->expr->valPos;
}

void DirectCodeGenVisitor::visit(astnodes::DerefOperator * derefOperator)
{
    // analyse inner expression first:
    derefOperator->expr->accept(*this);
    
    ValuePosition* valPos = derefOperator->expr->valPos;
    
    if (derefOperator->LtoR)
    {
        valPos = derefOperand(valPos, REG_TMP_L);
    }
    
    derefOperator->valPos = valPos;
}

/* 3.3.3.3 Unary arithmetic operators */

void DirectCodeGenVisitor::visit(astnodes::UnaryOperator * unaryOperator)
{
    // analyse inner expression first:
    unaryOperator->expr->accept(*this);
    
    ValuePosition* valPos = unaryOperator->expr->valPos;
    
    TypeImplementation* typeImpl = this->getTypeImplementation(unaryOperator->expr->valType->type);
    
    if (unaryOperator->LtoR)
    {
        valPos = derefOperand(valPos, REG_TMP_L);
    }
    ValuePosition* newTmp = NULL;
    
    switch(unaryOperator->optoken)
    {
        case ADD_OP:
            unaryOperator->valPos = valPos;
            break;
        case SUB_OP:
            // get arithmetic inverse of type
            valPos = makeAtomicModifyable(valPos);
            typeImpl->ainv(asm_current, valPos);
            break;
            
        case BIN_INV_OP:
            valPos = makeAtomicModifyable(valPos);
            typeImpl->binv(asm_current, valPos);
            break;
            
        case NOT_OP:
            // get new register, delete old
            newTmp = getTmp(1);
            valPos = makeAtomicReadable(valPos);
            typeImpl->linv(asm_current, newTmp, valPos);
            maybeFreeTemporary(valPos);
            valPos = newTmp;
            break;
        default:
            throw new errors::InternalCompilerException("Unknown unary operator encountered");
    }
    
    // return value:
    unaryOperator->valPos = valPos;
}


/* 3.3.3.4 The sizeof operator */

void DirectCodeGenVisitor::visit(astnodes::SizeOfOperator * sizeOfOperator)
{
    // just return the constant valpos of the constant expression
    sizeOfOperator->constExpr->accept(*this);
    sizeOfOperator->valPos = sizeOfOperator->constExpr->valPos;
}


/******************************/
/*  3.3.4 Cast operators      */
/******************************/

void DirectCodeGenVisitor::visit(astnodes::ExplicitCastOperator * explicitCastOperator)
{
    // compile sub expression
    explicitCastOperator->allChildrenAccept(*this);
    
    ValuePosition* valPos = explicitCastOperator->expr->valPos;
    
    /* LValue to RValue deref */
    if (explicitCastOperator->LtoR)
    {
        valPos = derefOperand(valPos, REG_TMP_R);
    }
    
    explicitCastOperator->valPos = valPos;
}



/******************************/
/*     binary operators       */
/******************************/

void DirectCodeGenVisitor::visit(astnodes::BinaryOperator * binaryOperator)
{
    // compile both sub-expressions
    binaryOperator->allChildrenAccept(*this);
    
    ValuePosition* lhsValpos = binaryOperator->lhsExrp->valPos;
    ValuePosition* rhsValpos = binaryOperator->rhsExpr->valPos;
    ValuePosition* resultValPos = NULL;
    
    TypeImplementation* typeImpl = this->getTypeImplementation(binaryOperator->commonType);
    
    /* LValue to RValue derefs*/
    if (binaryOperator->lhsLtoR)
    {
        lhsValpos = derefOperand(lhsValpos, REG_TMP_L);
    }
    if (binaryOperator->rhsLtoR)
    {
        rhsValpos = derefOperand(rhsValpos, REG_TMP_R);
    }
    
    /* atomizise and make modifyable */
    switch(binaryOperator->optoken)
    {
        /* 3.3.5 Multiplicative operators */
        case MUL_OP:
        case DIV_OP:
        case MOD_OP:
        /* 3.3.7 Bitwise shift operators */
        case LEFT_OP:
        case RIGHT_OP:
        /* 3.3.10 Bitwise AND operator */
        case BIN_AND_OP:
        /* 3.3.11 Bitwise exclusive OR operator */
        case BIN_XOR_OP:
        /* 3.3.12 Bitwise inclusive OR operator */
        case BIN_OR_OP:
            lhsValpos = makeAtomicModifyable(lhsValpos);
            rhsValpos = makeAtomicReadable(rhsValpos);
            resultValPos = lhsValpos;
            break;
            
        /* 3.3.6 Additive operators */
        case ADD_OP:
        case SUB_OP:
            // add and sub do the makeAtomic themselves depending on
            // whether it is a pointer operation or not
            break;

        /* 3.3.8 Relational operators */
        case LT_OP:
        case GT_OP:
        case LE_OP:
        case GE_OP:
        /* 3.3.9 Equality operators */
        case EQ_OP:
        case NE_OP:
        /* 3.3.13 Logical AND operator */
        case AND_OP:
        /* 3.3.14 Logical OR operator */
        case OR_OP:
            lhsValpos = makeAtomicReadable(lhsValpos, REG_TMP_L);
            rhsValpos = makeAtomicReadable(rhsValpos);
            resultValPos = getTmp(lhsValpos->getWordSize());
            break;

        default:
            throw new errors::InternalCompilerException("unknown binary operator encountered");
    }
    
    /* compile operation */
    
    switch(binaryOperator->optoken)
    {
        
        /* 3.3.5 Multiplicative operators */
        
        case MUL_OP:
            typeImpl->mul(asm_current, lhsValpos, rhsValpos);
            break;
            
        case DIV_OP:
            typeImpl->div(asm_current, lhsValpos, rhsValpos);
            break;
            
        case MOD_OP:
            typeImpl->mod(asm_current, lhsValpos, rhsValpos);
            break;
        
        /* 3.3.6 Additive operators */
        
        case ADD_OP:
            if (binaryOperator->lhsPtr || binaryOperator->rhsPtr)
            {
                // assert type size == 1
                if (typeImpl->getWordSize() != 1)
                    throw new errors::InternalCompilerException("type implementation for pointer operation has size != 1");
                
                // this is a pointer operation
                if (binaryOperator->lhsPtr)
                {
                    lhsValpos = makeAtomicModifyable(lhsValpos);
                    rhsValpos = makeAtomicReadable(rhsValpos);
                    if (binaryOperator->pointerSize > 1)
                    {
                        typeImpl->mul(asm_current, lhsValpos, ValuePosition::createAtomicConstPos(binaryOperator->pointerSize));
                    }
                    typeImpl->add(asm_current, lhsValpos, rhsValpos);
                    resultValPos = lhsValpos;
                }
                else
                {
                    lhsValpos = makeAtomicReadable(lhsValpos);
                    rhsValpos = makeAtomicModifyable(rhsValpos);
                    if (binaryOperator->pointerSize > 1)
                    {
                        typeImpl->mul(asm_current, rhsValpos, ValuePosition::createAtomicConstPos(binaryOperator->pointerSize));
                    }
                    typeImpl->add(asm_current, rhsValpos, lhsValpos);
                    resultValPos = rhsValpos;
                }
            }
            else
            {
                // this is just a simple arithmetic add
                lhsValpos = makeAtomicModifyable(lhsValpos);
                rhsValpos = makeAtomicReadable(rhsValpos);
                typeImpl->add(asm_current, lhsValpos, rhsValpos);
                resultValPos = lhsValpos;
            }
            break;
            
        case SUB_OP:
            if (binaryOperator->lhsPtr && binaryOperator->rhsPtr)
            {
                // assert type size == 1
                if (typeImpl->getWordSize() != 1)
                    throw new errors::InternalCompilerException("type implementation for pointer operation has size != 1");
                
                // pointer subtraction
                lhsValpos = makeAtomicModifyable(lhsValpos);
                rhsValpos = makeAtomicReadable(rhsValpos);
                typeImpl->sub(asm_current, lhsValpos, rhsValpos);
                if (binaryOperator->pointerSize > 1)
                    typeImpl->div(asm_current, lhsValpos, ValuePosition::createAtomicConstPos(binaryOperator->pointerSize));
                resultValPos = lhsValpos;
            }
            else if (binaryOperator->lhsPtr)
            {
                // assert type size == 1
                if (typeImpl->getWordSize() != 1)
                    throw new errors::InternalCompilerException("type implementation for pointer operation has size != 1");
                
                // pointer - integer
                if (binaryOperator->pointerSize > 1)
                {
                    // TODO this is less than optimal:
                    lhsValpos = makeAtomicModifyable(lhsValpos);
                    rhsValpos = makeAtomicModifyable(rhsValpos, REG_TMP_R);
                    typeImpl->mul(asm_current, rhsValpos, ValuePosition::createAtomicConstPos(binaryOperator->pointerSize));
                    typeImpl->sub(asm_current, lhsValpos, rhsValpos);
                    resultValPos = lhsValpos;
                }
                else
                {
                    lhsValpos = makeAtomicModifyable(lhsValpos);
                    rhsValpos = makeAtomicReadable(rhsValpos);
                    typeImpl->sub(asm_current, lhsValpos, rhsValpos);
                    resultValPos = lhsValpos;
                }
            }
            else
            {
                // arithmetic subtraction
                lhsValpos = makeAtomicModifyable(lhsValpos);
                rhsValpos = makeAtomicReadable(rhsValpos);
                typeImpl->sub(asm_current, lhsValpos, rhsValpos);
                resultValPos = lhsValpos;
            }
            break;
            
            
        /* 3.3.7 Bitwise shift operators */
            
        case LEFT_OP:
            typeImpl->shl(asm_current, lhsValpos, rhsValpos);
            break;
        case RIGHT_OP:
            typeImpl->shr(asm_current, lhsValpos, rhsValpos);
            break;
            
        /* 3.3.8 Relational operators */
        case LT_OP:
            typeImpl->slt(asm_current, resultValPos, lhsValpos, rhsValpos);
            break;
        case GT_OP:
            typeImpl->sgt(asm_current, resultValPos, lhsValpos, rhsValpos);
            break;
        case LE_OP:
            typeImpl->sle(asm_current, resultValPos, lhsValpos, rhsValpos);
            break;
        case GE_OP:
            typeImpl->sge(asm_current, resultValPos, lhsValpos, rhsValpos);
            break;

        /* 3.3.9 Equality operators */
        
        case EQ_OP:
            typeImpl->seq(asm_current, resultValPos, lhsValpos, rhsValpos);
            break;
        case NE_OP:
            typeImpl->sne(asm_current, resultValPos, lhsValpos, rhsValpos);
            break;
        
            
        /* 3.3.10 Bitwise AND operator */
        /* 3.3.11 Bitwise exclusive OR operator */
        /* 3.3.12 Bitwise inclusive OR operator */
        
        case BIN_AND_OP:
            typeImpl->band(asm_current, lhsValpos, rhsValpos);
            break;
        case BIN_XOR_OP:
            typeImpl->bxor(asm_current, lhsValpos, rhsValpos);
            break;
        case BIN_OR_OP:
            typeImpl->bor(asm_current, lhsValpos, rhsValpos);
            break;
            
        /* 3.3.13 Logical AND operator */
        /* 3.3.14 Logical OR operator */
            
        case AND_OP:
            typeImpl->land(asm_current, resultValPos, lhsValpos, rhsValpos);
            break;
        case OR_OP:
            typeImpl->lor(asm_current, resultValPos, lhsValpos, rhsValpos);
            break;
            
        default:
            throw new errors::InternalCompilerException("unknown binary operator encountered");
    }
    
    if (lhsValpos != resultValPos)
    {
        maybeFreeTemporary(lhsValpos);
    }
    if (rhsValpos != resultValPos)
    {
        maybeFreeTemporary(rhsValpos);
    }
    
    binaryOperator->valPos = resultValPos;
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
    // compile both sub-expressions
    assignmentOperator->allChildrenAccept(*this);
    
    ValuePosition* lhsValpos = assignmentOperator->lhsExrp->valPos;
    ValuePosition* rhsValpos = assignmentOperator->rhsExpr->valPos;
    
    TypeImplementation* typeImpl = this->getTypeImplementation(assignmentOperator->commonType);
    
    /* LValue to RValue deref */
    if (assignmentOperator->rhsLtoR)
    {
        rhsValpos = derefOperand(rhsValpos, REG_TMP_R);
    }
    
    
    ValuePosition* lhsOperandVP = makeAtomicDerefable(lhsValpos, REG_TMP_L);
    bool createCopy = false;
    if (lhsOperandVP != lhsValpos)
        createCopy = true;
    
    if (lhsOperandVP->getWordSize() == 1)
    {
        lhsOperandVP = lhsOperandVP->atomicDeref();
    }
    
    
    switch (assignmentOperator->optoken)
    {
        
        /* 3.3.16.1 Simple assignment */
        
        case ASSIGN_EQUAL:
            if(!rhsValpos->isAtomicOperand())
            {
                rhsValpos = rhsValpos->valToRegister(asm_current, REG_TMP_R);
            }
            copyValue(rhsValpos, lhsOperandVP);
            break;
            
            
        /* 3.3.16.2 Compound assignment */
            
        case ADD_ASSIGN:
        case SUB_ASSIGN:
            if (assignmentOperator->ptrop && assignmentOperator->pointerSize > 1)
            {
                rhsValpos = makeAtomicModifyable(rhsValpos, REG_TMP_R);
                typeImpl->mul(asm_current, rhsValpos, ValuePosition::createAtomicConstPos(assignmentOperator->pointerSize));
                if (assignmentOperator->optoken == ADD_ASSIGN)
                    typeImpl->add(asm_current, lhsOperandVP,rhsValpos);
                else
                    typeImpl->sub(asm_current, lhsOperandVP,rhsValpos);
            }
            else
            {
                rhsValpos = makeAtomicReadable(rhsValpos);
                if (assignmentOperator->optoken == ADD_ASSIGN)
                    typeImpl->add(asm_current, lhsOperandVP,rhsValpos);
                else
                    typeImpl->sub(asm_current, lhsOperandVP,rhsValpos);
            }
            break;
            
        case MUL_ASSIGN:
            rhsValpos = makeAtomicReadable(rhsValpos);
            typeImpl->mul(asm_current, lhsOperandVP, rhsValpos);
            break;
        case DIV_ASSIGN:
            rhsValpos = makeAtomicReadable(rhsValpos);
            typeImpl->div(asm_current, lhsOperandVP, rhsValpos);
            break;
            
        case MOD_ASSIGN:
            rhsValpos = makeAtomicReadable(rhsValpos);
            typeImpl->mod(asm_current, lhsOperandVP, rhsValpos);
            break;
        case LEFT_ASSIGN:
            rhsValpos = makeAtomicReadable(rhsValpos);
            typeImpl->shl(asm_current, lhsOperandVP, rhsValpos);
            break;
        case RIGHT_ASSIGN:
            rhsValpos = makeAtomicReadable(rhsValpos);
            typeImpl->shr(asm_current, lhsOperandVP, rhsValpos);
            break;
        case AND_ASSIGN:
            rhsValpos = makeAtomicReadable(rhsValpos);
            typeImpl->band(asm_current, lhsOperandVP, rhsValpos);
            break;
        case XOR_ASSIGN:
            rhsValpos = makeAtomicReadable(rhsValpos);
            typeImpl->bxor(asm_current, lhsOperandVP, rhsValpos);
            break;
        case OR_ASSIGN:
            rhsValpos = makeAtomicReadable(rhsValpos);
            typeImpl->bor(asm_current, lhsOperandVP, rhsValpos);
            break;
        default:
            throw new errors::InternalCompilerException("unknown assignment operator encountered");
    }
    
    ValuePosition* resultValPos = lhsOperandVP;
    if (createCopy)
    {
        resultValPos = getTmpCopy(lhsOperandVP);
        maybeFreeTemporary(lhsOperandVP);
    }
    
    maybeFreeTemporary(rhsValpos);
    
    assignmentOperator->valPos = resultValPos;
}



/********************************/
/*  3.3.17 Comma operator       */
/********************************/

void DirectCodeGenVisitor::visit(astnodes::ChainExpressions * chainExpressions)
{
    for (astnodes::Expressions::iterator it = chainExpressions->exprs->begin(); it != chainExpressions->exprs->end(); ++it)
    {
        (*it)->accept(*this);
        if (*it != chainExpressions->exprs->back())
            maybeFreeTemporary((*it)->valPos);
    }
    
    // return the result from the last expression
    chainExpressions->valPos = chainExpressions->exprs->back()->valPos;
}

/* type conversion */

void DirectCodeGenVisitor::visit(astnodes::TypeConversionOperator* typeConversionOperator)
{
    // compile sub expression
    typeConversionOperator->allChildrenAccept(*this);
    
    types::Type* from = typeConversionOperator->fromType;
    types::Type* to = typeConversionOperator->toType;
    
    ValuePosition* fromValPos = typeConversionOperator->expr->valPos;
    // default to in-place conversion
    ValuePosition* toValPos = fromValPos;
    bool delTemp = false;
    
    /* LValue to RValue deref */
    if (typeConversionOperator->LtoR)
    {
        fromValPos = derefOperand(fromValPos, REG_TMP_R);
    }
    
    
    if (to->getWordSize() != from->getWordSize())
    {
        fromValPos = makeAtomicReadable(fromValPos);
        delTemp = true;
        toValPos = getTmp(to->getWordSize());
    }
    else
    {
        fromValPos = makeAtomicModifyable(fromValPos);
        toValPos = fromValPos;
    }
    
    TypeConversions::convert(from, to, asm_current, toValPos, fromValPos);
    
    if (delTemp)
        maybeFreeTemporary(fromValPos);
    
    typeConversionOperator->valPos = toValPos;
}


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

