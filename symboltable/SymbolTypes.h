///
/// @addtogroup LibDCPU-CI-Lang-C/SymbolTable
/// @{
///

///
/// @file       SymbolTypes.h
/// @brief      Declares the Symbol Types for the SymbolTable.
/// @author     Patrick Flick
///


#ifndef __DCPU_CC_SYMBOLTABLE_SYMBOLTYPES_H
#define __DCPU_CC_SYMBOLTABLE_SYMBOLTYPES_H

namespace dtcc
{
    namespace symboltable
    {
        enum DeclType {VARIABLE_DECL, FUNCTION_DECL, FUNCTION_DEF};
        // only relevant to decl types
        enum ObjectPosition {GLOBAL, LOCAL_STACK, PARAMETER_STACK};
        enum TagType {STRUCT_TAG, UNION_TAG, ENUM_TAG, TYPEDEF_TAG};
        
    } // namespace symboltable
} // namespace dtcc

#endif


///
/// @}
///