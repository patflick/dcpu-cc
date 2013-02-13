


#ifndef __DCPU_CC_TYPES_TYPEVISITOR_H
#define __DCPU_CC_TYPES_TYPEVISITOR_H
#include <stdio.h>
#include "alltypes.h"

namespace dcpucc
{
    namespace types
    {
        
        class TypeVisitor
        {
        public:
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param type    The node to visit this visitor
            virtual bool visit(Type * type);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param float    The node to visit this visitor
            virtual bool visit(Float * floatType);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param double    The node to visit this visitor
            virtual bool visit(Double * doubleType);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param longDouble    The node to visit this visitor
            virtual bool visit(LongDouble * longDouble);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param signedChar    The node to visit this visitor
            virtual bool visit(SignedChar * signedChar);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param unsignedChar    The node to visit this visitor
            virtual bool visit(UnsignedChar * unsignedChar);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param signedShort    The node to visit this visitor
            virtual bool visit(SignedShort * signedShort);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param unsignedShort    The node to visit this visitor
            virtual bool visit(UnsignedShort * unsignedShort);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param signedInt    The node to visit this visitor
            virtual bool visit(SignedInt * signedInt);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param unsignedInt    The node to visit this visitor
            virtual bool visit(UnsignedInt * unsignedInt);
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param nullPointer    The node to visit this visitor
            virtual bool visit(NullPointer * nullPointer);
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param nullPointer    The node to visit this visitor
            virtual bool visit(BitField * bitField);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param signedLong    The node to visit this visitor
            virtual bool visit(SignedLong * signedLong);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param unsignedLong    The node to visit this visitor
            virtual bool visit(UnsignedLong * unsignedLong);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param enumType    The node to visit this visitor
            virtual bool visit(EnumType * enumType);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param pointerType    The node to visit this visitor
            virtual bool visit(PointerType * pointerType);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param functionType    The node to visit this visitor
            virtual bool visit(FunctionType * functionType);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param arrayType    The node to visit this visitor
            virtual bool visit(ArrayType * arrayType);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param structUnionType    The node to visit this visitor
            virtual bool visit(StructUnionType * structUnionType);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param void    The node to visit this visitor
            virtual bool visit(Void * voidType);
            
            
            ///
            /// @brief      Visit function of the visitor pattern.
            /// @sa         http://en.wikipedia.org/wiki/Visitor_pattern
            /// @param invalidType    The node to visit this visitor
            virtual bool visit(InvalidType * invalidType);
            
        };
    }
}




#endif