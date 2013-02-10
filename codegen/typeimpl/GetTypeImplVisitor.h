


#ifndef __DCPU_CC_CODEGEN_GETIMPL_TYPEVISITOR_H
#define __DCPU_CC_CODEGEN_GETIMPL_TYPEVISITOR_H
#include <stdio.h>
#include <types/alltypes.h>
#include <types/TypeVisitor.h>
#include "TypeImplementation.h"
#include "SignedInt16.h"
#include "UnsignedInt16.h"

namespace dcpucc
{
    namespace codegen
    {
        using namespace types;
        class GetTypeImplVisitor : public dcpucc::types::TypeVisitor
        {
        private:
            /// holds the resolved type implementation after visiting a type
            TypeImplementation* typeImpl;
            // type implementations to be returned:
            SignedInt16* sint16;
            UnsignedInt16* uint16;
            
        public:
            
            /// @brief Constructor for the GetTypeImplVisitor class.
            GetTypeImplVisitor() : typeImpl(NULL), sint16(new SignedInt16()), uint16(new UnsignedInt16()) {}
            
            /// @brief      Returns the resolved type implementation.
            /// @returns    The resolved type implementation as pointer to
            ///             TypeImplementation. Returns NULL if no type
            ///             implementation is available for the given type.
            virtual TypeImplementation* getTypeImplementation();
            
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
    } // namespace codegen
} // namespace dcpucc




#endif