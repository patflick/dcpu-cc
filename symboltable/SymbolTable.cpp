///
/// @addtogroup LibDCPU-CI-Lang-C/SymbolTable
/// @{
///

///
/// @file       SymbolTable.cpp
/// @brief      Defines the SymbolTable class.
/// @author     Patrick Flick
///

#include "SymbolTypes.h"
#include "SymbolTableScope.h"
#include "SymbolTable.h"

using namespace dcpucc;
using namespace dcpucc::symboltable;

SymbolTable::SymbolTable()
{
    this->m_globalScope = new SymbolTableScope();
    this->m_currentScope = this->m_globalScope;
}

SymbolTableScope& SymbolTable::getCurrentScope()
{
    return *(this->m_currentScope);
}

SymbolTableScope& SymbolTable::getGlobalScope()
{
    return *(this->m_globalScope);
}

bool SymbolTable::isGlobalCurScope()
{
    return (this->m_globalScope == this->m_currentScope);
}

SymbolTableScope* SymbolTable::beginNewScope()
{
    SymbolTableScope* tmpScope = this->m_currentScope;
    this->m_currentScope = new SymbolTableScope(tmpScope);
    return this->m_currentScope;
}

void SymbolTable::beginScope(SymbolTableScope* newScope)
{
    SymbolTableScope* tmpScope = this->m_currentScope;
    this->m_currentScope = newScope;
    newScope->prevScope = tmpScope;
}

void SymbolTable::endScope()
{
    if (this->m_currentScope->prevScope != NULL)
    {
        SymbolTableScope* tmpScope = this->m_currentScope->prevScope;
        //delete this->m_currentScope;
        this->m_currentScope = tmpScope;
    }
}

bool SymbolTable::contains(std::string name)
{
    return this->m_currentScope->contains(name);
}

bool SymbolTable::containsRec(std::string name)
{
    return this->m_currentScope->containsRec(name);
}

bool SymbolTable::findSymbol(std::string name, SymbolObject& result)
{
    return this->m_currentScope->findSymbol(name, result);
}
/*
void SymbolTable::insert(std::string name, IType* type, StackFramePosition stackPosition)
{
    this->currentScope->insert(name, type, stackPosition);
}
* */

TypePosition SymbolTable::getPositionOfVariable(std::string name, bool previousStackFrame)
{
    SymbolObject obj;
    if(this->m_currentScope->findSymbol(name, obj))
    {
        // FIXME:
        //    use stack-frames up instead of 'previousStackFrame', this way variables mutliple stack frames up can still be found
        // TODO:
        //    implement GLOBAL symbols aswell, to be used in global stack frame
        //    implement recursive and non-recursive versions of 'contains' and 'find'
        //    replace StackMap, StackFrame and all the calls to it in the compiler
        if (obj.objectPos == LOCAL_STACK)
            return TypePosition(true, false, false, previousStackFrame, obj.positionOffset);
        else if (obj.objectPos == PARAMETER_STACK)
            return TypePosition(true, false, true, previousStackFrame, obj.positionOffset);
        else if (obj.objectPos == GLOBAL)
        {
            if (obj.declType == FUNCTION_DECL || obj.declType == FUNCTION_DEF)
                return TypePosition(true, name);
            else
                return TypePosition::createGlobalPosition(name);
        }
    }
    return TypePosition(false, false, false, false, 0);
}

TypePosition SymbolTable::getPositionOfVariable(std::string name)
{
    return this->getPositionOfVariable(name, false);
}

types::Type* SymbolTable::getTypeOfVariable(std::string name)
{
    SymbolObject obj;
    if(this->m_currentScope->findSymbol(name, obj))
    {
        if (obj.declType == VARIABLE_DECL)
            return obj.type;
        else
            return NULL;
    }
    else
    {
        return NULL;
    }
}

std::vector<std::string> SymbolTable::getFunctionDeclarations()
{
    std::map<std::string, SymbolObject>::iterator it;
    SymbolObject obj;
    std::vector<std::string> result;
    for (it = this->m_globalScope->m_symbolMap.begin(); it != this->m_globalScope->m_symbolMap.end(); ++it)
    {
        obj = it->second;
        if (obj.declType == FUNCTION_DECL)
        {
            result.push_back(it->first);
        }
    }
    return result;
}

types::FunctionType* SymbolTable::getFunction(std::string name)
{
    SymbolObject obj;
    // search for functions only at global scope:
    if(this->m_globalScope->findSymbol(name, obj))
    {
        if (obj.declType == FUNCTION_DECL || obj.declType == FUNCTION_DEF)
            return (types::FunctionType*) obj.type;
        else
            return NULL;
    }
    else
    {
        return NULL;
    }
}

types::StructUnionType* SymbolTable::getStructType(std::string name)
{
    SymbolObject obj;
    // search for functions only at global scope:
    if(this->m_currentScope->findTag(name, obj))
        if (obj.tagType == STRUCT_TAG || obj.tagType == UNION_TAG)
            return (types::StructUnionType*) obj.type;
            
    return NULL;
}

types::Type* SymbolTable::getTagType(std::string name)
{
    SymbolObject obj;
    // search for functions only at global scope:
    if(this->m_currentScope->findTag(name, obj))
        return (types::StructUnionType*) obj.type;
        
    return NULL;
}

types::EnumType* SymbolTable::getEnumType(std::string name)
{
    SymbolObject obj;
    // search for functions only at global scope:
    if(this->m_currentScope->findTag(name, obj))
        if (obj.tagType == ENUM_TAG)
            return (types::EnumType*) obj.type;
        
    return NULL;
}


///
/// @}
///
