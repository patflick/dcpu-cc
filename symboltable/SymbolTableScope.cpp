///
/// @addtogroup LibDCPU-CI-Lang-C/SymbolTable
/// @{
///

///
/// @file       SymbolTableScope.cpp
/// @brief      Defines the SymbolTableScope class.
/// @author     Patrick Flick
///

#include "SymbolTableScope.h"
#include <map>
#include <utility>
#include <iostream>

using namespace dtcc::symboltable;

bool SymbolTableScope::isGlobalScope()
{
    return this->prevScope == NULL;
}


bool SymbolTableScope::containsSymbol(std::string name)
{
    if (m_symbolMap.find(name) == m_symbolMap.end())
        return false;
    else
        return true;
}


bool SymbolTableScope::containsSymbolRec(std::string name)
{
    if (!containsSymbol(name))
    {
        if (prevScope == NULL)
            return false;
        else
            return prevScope->containsSymbolRec(name);
    }

    return true;
}

bool SymbolTableScope::containsTag(std::string name)
{
    if (m_tagMap.find(name) == m_tagMap.end())
        return false;
    else
        return true;
}


bool SymbolTableScope::containsTagRec(std::string name)
{
    if (!containsTag(name))
    {
        if (prevScope == NULL)
            return false;
        else
            return prevScope->containsTagRec(name);
    }
    
    return true;
}


bool SymbolTableScope::contains(std::string name)
{
    return (containsSymbol(name) || containsTag(name));
}

bool SymbolTableScope::containsRec(std::string name)
{
    if (!contains(name))
    {
        if (prevScope == NULL)
            return false;
        else
            return prevScope->containsRec(name);
    }
    return true;
}


uint16_t SymbolTableScope::getParameterStackSize()
{
    return this->m_parameterStackSize;
}

uint16_t SymbolTableScope::getLocalStackSize()
{
    return this->m_localStackSize;
}

uint16_t SymbolTableScope::getGlobalsSize()
{
    return this->m_globalsSize;
}


bool SymbolTableScope::findSymbol(std::string name, SymbolObject& result)
{
    std::map<std::string, SymbolObject>::iterator it = this->m_symbolMap.find(name);
    if (it == this->m_symbolMap.end())
    {
        if (prevScope == NULL)
            return false;
        else
            return prevScope->findSymbol(name, result);
    }
    else
    {
        result = it->second;
        return true;
    }
}

bool SymbolTableScope::findTag(std::string name, SymbolObject& result)
{
    std::map<std::string, SymbolObject>::iterator it = this->m_tagMap.find(name);
    if (it == this->m_tagMap.end())
    {
        if (prevScope == NULL)
            return false;
        else
            return prevScope->findTag(name, result);
    }
    else
    {
        result = it->second;
        return true;
    }
}

void SymbolTableScope::insertSymbol(std::string name, DeclType declType, types::Type* type, ObjectPosition pos)
{
    uint16_t offset = 0;
    // only variables need space (i.e. an offset)
    if (declType == VARIABLE_DECL)
    {
        if (pos == LOCAL_STACK)
        {
            // here we have to first add the word size because the
            // local stack is from bottom up, but the adress should point
            // to the first word of the type
            this->m_localStackSize += type->getWordSize();
            offset = this->m_localStackSize;
        }
        else if (pos == PARAMETER_STACK)
        {
            offset = this->m_parameterStackSize;
            this->m_parameterStackSize += type->getWordSize();
        }
        else if (pos == GLOBAL)
        {
            offset = this->m_globalsSize;
            this->m_globalsSize += type->getWordSize();
        }
        this->m_symbolMap.insert(std::pair<std::string, SymbolObject>(name, SymbolObject(name, declType, type, pos, offset)));
    }
    else if (declType == FUNCTION_DECL)
    {
        SymbolObject symb;
        if(!containsSymbol(name))
        {
            this->m_symbolMap.insert(std::pair<std::string, SymbolObject>(name, SymbolObject(name, declType, type, pos, 0)));
            return;
        }
        //. so it already contains a function, well don't do anything then
    }
    else if (declType == FUNCTION_DEF)
    {
        SymbolObject symb;
        if(!containsSymbol(name))
        {
            this->m_symbolMap.insert(std::pair<std::string, SymbolObject>(name, SymbolObject(name, declType, type, pos, 0)));
            return;
        }
        // so if it already contains a function decl, overwrite it
        if(!findSymbol(name, symb))
        {
            // TODO throw some compiler exception
        }
        else
        {
            if (symb.declType != FUNCTION_DECL)
            {
                // TODO throw some compiler exception
            }
            else
            {
                // remove Func decl
                std::map<std::string, SymbolObject>::iterator it = this->m_symbolMap.find(name);
                this->m_symbolMap.erase (it); 
                // insert new func def
                this->m_symbolMap.insert(std::pair<std::string, SymbolObject>(name, SymbolObject(name, declType, type, pos, 0)));
            }
        }
    }
}


void SymbolTableScope::insertTag(std::string name, TagType tagType, types::Type* type)
{
    this->m_tagMap.insert(std::pair<std::string, SymbolObject>(name, SymbolObject(name, tagType, type)));
}


///
/// @}
///
