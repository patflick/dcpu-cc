///
/// @addtogroup LibDCPU-CI-Lang-C/SymbolTable
/// @{
///

///
/// @file       SymbolTableScope.h
/// @brief      Declares the SymbolTableScope class.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_SYMBOLTABLE_SYMBOLTABLESCOPE_H
#define __DCPU_CC_SYMBOLTABLE_SYMBOLTABLESCOPE_H

#include <string>
#include <map>
#include "SymbolTypes.h"
#include "SymbolObject.h"
#include <types/Type.h>


namespace dcpucc
{
    namespace symboltable
    {
        

        class SymbolTableScope
        {
            
        private:
            // symbols = {functions, function declarations, variables}
            std::map<std::string, SymbolObject> m_symbolMap;
            // tags = {struct X, union X, enum X, typedefs}
            std::map<std::string, SymbolObject> m_tagMap;
            uint16_t m_localStackSize;
            uint16_t m_parameterStackSize;
            uint16_t m_globalsSize;
        public:
            SymbolTableScope* prevScope;
            // TODO do i still need this??
            bool doneInsert;
        public:
            SymbolTableScope() :
                    m_symbolMap(std::map<std::string, SymbolObject>()),
                    m_tagMap(std::map<std::string, SymbolObject>()),
                    m_localStackSize(0),
                    m_parameterStackSize(0),
                    m_globalsSize(0),
                    prevScope(NULL),
                    doneInsert(false) {}

            SymbolTableScope(SymbolTableScope* prev) :
                    m_symbolMap(std::map<std::string, SymbolObject>()),
                    m_tagMap(std::map<std::string, SymbolObject>()),
                    m_localStackSize(0),
                    m_parameterStackSize(0),
                    m_globalsSize(0),
                    prevScope(prev),
                    doneInsert(false) {}
            
            friend class SymbolTable;
            
            bool isGlobalScope();
            
            void clearScope();
            
            bool contains(std::string name);
            bool containsRec(std::string name);
            bool containsSymbol(std::string name);
            bool containsSymbolRec(std::string name);
            bool containsTag(std::string name);
            bool containsTagRec(std::string name);
            
            uint16_t getParameterStackSize();
            uint16_t getLocalStackSize();
            uint16_t getGlobalsSize();
            
            // finds any reference
            bool findSymbol(std::string name, SymbolObject& result);
            bool findTag(std::string name, SymbolObject& result);
            
            void insertSymbol(std::string name, DeclType declType, types::Type* type, ObjectPosition pos);
            void insertTag(std::string name, TagType tagType, types::Type* type);
        };

    } // namespace symboltable
} // namespace dcpucc

#endif


///
/// @}
///
