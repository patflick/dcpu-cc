///
/// @addtogroup LibDCPU-CI-Lang-C/Types
/// @{
///

///
/// @file       StructUnionType.h
/// @brief      Declaration of the StructUnionType type class.
/// @author     Patrick Flick
///

#include "Type.h"

#ifndef __DCPU_CC_TYPES_STRUCTUNIONTYPE_H
#define __DCPU_CC_TYPES_STRUCTUNIONTYPE_H

#include <string>
#include <stdint.h>

// include needed type classes
#include "AggregateType.h"
#include <map>
#include <string>


namespace dtcc
{
    namespace types
    {

        ///
        /// @class      StructUnionType
        /// @brief      The StructUnionType type class.
        ///
        class StructUnionType : public AggregateType
        {
        private:
            unsigned int size;
            std::map<std::string, unsigned int> m_offsets;
            std::map<std::string, types::Type*> m_types;
            
        public:
            
            const bool isUnion;
            bool complete;
            
            
        public:
            ///
            /// @brief      The constructor of the StructUnionType type class.

            ///
            StructUnionType(bool isUnion) : isUnion(isUnion), complete(false), size(0),
            m_offsets(std::map<std::string, unsigned int>()), m_types(std::map<std::string, types::Type*>()) {}
            
            
            void addMember(std::string name, types::Type* type);
            bool hasMember(std::string name);
            types::Type* getMember(std::string name);
            unsigned int getOffset(std::string name);
            
            ///
            /// @brief          Returns the size of the type in words.
            /// @return         The size of the type.
            ///
            /// This might return 0 if the type is not yet resolved
            /// (i.e. for structs).
            virtual uint16_t getWordSize();
            
            ///
            /// @brief          Returns the size of the type in bytes.
            /// @return         The size of the type.
            ///
            /// This might return 0 if the type is not yet resolved
            /// (i.e. for structs).
            virtual uint16_t getByteSize();
            
            ///
            /// @brief          Returns whether the type is a complete type.
            /// @return         True, if the type is a complete type, false
            ///                 otherwise
            ///
            virtual bool isComplete();
            
            
            ///
            /// @brief          The accept method of the visitor pattern.
            /// @param tv       The TypeVisitor to be accepted.
            /// @return         The boolean value returned by tv.accept(this)
            ///
            virtual bool accept(TypeVisitor& tv);
            
            ///
            /// @brief          Returns a string representation of the type.
            /// @return         A string representation of the type.
            ///
            /// This is used especially for error messages and warnings.
            virtual std::string toString();
            
            ///
            /// @brief      The destructor of the StructUnionType type class.
            ///
            virtual ~StructUnionType();
        };

    } // namespace types
} // namespace dtcc

#endif

///
/// @}
///