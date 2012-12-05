///
/// @addtogroup LibDCPU-CI-Lang-C/SymbolTable
/// @{
///

///
/// @file       SymbolObject.h
/// @brief      Declares the SymbolObject class.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_SYMBOLTABLE_SYMBOLOBJECT_H
#define __DCPU_CC_SYMBOLTABLE_SYMBOLOBJECT_H

#include <string>

#include <types/Type.h>
#include "SymbolTypes.h"

namespace dtcc
{
    namespace symboltable
    {

        class SymbolObject
        {
        public:

        public:
            std::string name;
            types::Type* type;
            DeclType declType;
            TagType tagType;
            ObjectPosition objectPos;
            uint16_t positionOffset;

        public:
            SymbolObject() : name(""), type(NULL),
                objectPos(LOCAL_STACK), positionOffset(0) {}
            SymbolObject(std::string name, DeclType declType, types::Type* type, ObjectPosition pos, uint16_t posOffset) :
                name(name), type(type), declType(declType), objectPos(pos), positionOffset(posOffset) {}
            SymbolObject(std::string name, TagType tagType, types::Type* type) :
                name(name), type(type), tagType(tagType) {}
        };

    } // namespace symboltable
} // namespace dtcc

#endif

///
/// @}
///