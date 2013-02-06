///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       Type.h
/// @brief      Declaration of the Type type class.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_TYPES_TYPE_H
#define __DCPU_CC_TYPES_TYPE_H

#include <string>
#include <stdint.h>


namespace dtcc
{
    namespace types
    {
        
        // forward declare the type visitor
        class TypeVisitor;

        ///
        /// @class      Type
        /// @brief      The Type type class.
        ///
        class Type
        {
            
        public:
            bool isConst;
            bool isVolatile;
            
        public:
            ///
            /// @brief      The constructor of the Type type class.

            ///
            Type() : isConst(false), isVolatile(false) {}
            
            ///
            /// @brief          Returns the size of the type in words.
            /// @return         The size of the type.
            ///
            /// This might return 0 if the type is not yet resolved
            /// (i.e. for structs).
            virtual uint16_t getWordSize() = 0;

            ///
            /// @brief          Returns the size of the type in bytes.
            /// @return         The size of the type.
            ///
            /// This might return 0 if the type is not yet resolved
            /// (i.e. for structs).
            virtual uint16_t getByteSize() = 0;
            
            ///
            /// @brief          Returns whether the type is a complete type.
            /// @return         True, if the type is a complete type, false
            ///                 otherwise
            ///
            virtual bool isComplete() = 0;
            
            
            ///
            /// @brief          The accept method of the visitor pattern.
            /// @param tv       The TypeVisitor to be accepted.
            /// @return         The boolean value returned by tv.accept(this)
            ///
            virtual bool accept(TypeVisitor& tv) = 0;
            
            ///
            /// @brief          Returns a string representation of the type.
            /// @return         A string representation of the type.
            ///
            /// This is used especially for error messages and warnings.
            virtual std::string toString();
            
            ///
            /// @brief          Performes a safe deletion of the given pointer.
            /// @param a        The visitor to be accepted.
            ///
            /// This is a member of node, so that all AST nodes can
            /// access this, as they all inherit from Node.
            template<typename T> void safe_delete(T*& p) {
                delete p;
                p = NULL;
            }
            
            ///
            /// @brief      The destructor of the Type type class.
            ///
            virtual ~Type();
        };

    } // namespace types
} // namespace dtcc


// include type visitor afterwards
#ifndef __DCPU_CC_TYPES_ALLTYPES_H
#include "TypeVisitor.h"
#endif

#endif

///
/// @}
///