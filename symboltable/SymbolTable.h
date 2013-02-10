///
/// @addtogroup LibDCPU-CI-Lang-C/SymbolTable
/// @{
///

///
/// @file       SymbolTable.h
/// @brief      Declares the SymbolTable class.
/// @author     Patrick Flick
///


#ifndef __DCPU_CC_SYMBOLTABLE_SYMBOLTABLE_H
#define __DCPU_CC_SYMBOLTABLE_SYMBOLTABLE_H

#include <string>
#include "SymbolObject.h"
#include "SymbolTableScope.h"
#include "TypePosition.h"
#include <types/Type.h>
#include <types/FunctionType.h>
#include <types/StructUnionType.h>
#include <types/EnumType.h>

namespace dcpucc
{
    namespace symboltable
    {

        class SymbolTable
        {
        private:
            SymbolTableScope* m_globalScope;
            SymbolTableScope* m_currentScope;
            
        public:
            
            SymbolTable();
            
            SymbolTableScope* beginNewScope();
            void beginScope(SymbolTableScope* newScope);
            void endScope();
            
            bool contains(std::string name);
            bool containsRec(std::string name);
            bool findSymbol(std::string name, SymbolObject& result);
            // void insert(std::string name, IType* type, StackFramePosition stackPosition);
            
            SymbolTableScope& getCurrentScope();
            SymbolTableScope& getGlobalScope();
            bool isGlobalCurScope();
            
            TypePosition getPositionOfVariable(std::string name);
            TypePosition getPositionOfVariable(std::string name, bool previousStackFrame);
            types::Type* getTypeOfVariable(std::string name);
            types::FunctionType* getFunction(std::string name);
            std::vector<std::string> getFunctionDeclarations();
            types::StructUnionType* getStructType(std::string name);
            types::Type* getTagType(std::string name);
            types::EnumType* getEnumType(std::string name);
            
            //uint16_t getSizeOfVariable(std::string name);
        };

    } // namespace symboltable
} // namespace dcpucc


#endif


///
/// @}
///
