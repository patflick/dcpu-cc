///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       alltypes.h
/// @brief      Includes all AST Nodes.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_TYPES_ALLTYPES_H
#define __DCPU_CC_TYPES_ALLTYPES_H

/*
 * Simply includes all types
 * 
 * When adding new types, just bash this: 
 *      $ for i in *.h; do echo "#include \"$i\""; done
 * in the wd 'types/'. Copy&Paste and then remove the alltypes.h and Node.h
 * and include Node.h first.
 * 
 * We don't want to make our lives too complicated ;)
 */

// first include Node.h
#include "Type.h"

// then all other types:
#include "AggregateType.h"
#include "ArithmeticType.h"
#include "ArrayType.h"
#include "Double.h"
#include "EnumType.h"
#include "Float.h"
#include "FloatType.h"
#include "FunctionType.h"
#include "IntegralType.h"
#include "InvalidType.h"
#include "LongDouble.h"
#include "ParameterTypeList.h"
#include "ScalarType.h"
#include "PointerType.h"
#include "SignedChar.h"
#include "SignedInt.h"
#include "SignedLong.h"
#include "SignedShort.h"
#include "StructUnionType.h"
#include "Type.h"
#include "UnsignedChar.h"
#include "UnsignedInt.h"
#include "UnsignedLong.h"
#include "UnsignedShort.h"
#include "Void.h"

// include the TypeVisitor and helper classes last
#include "TypeVisitor.h"
#include "IsTypeHelper.h"
#include "IntegralPromotion.h"
#include "ArithmeticConversion.h"

#endif

///
/// @}
///
