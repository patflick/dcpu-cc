///
/// @addtogroup LibDCPU-CI-Lang-C/CodeGen
/// @{
///

///
/// @file       TypeSizes.h
/// @brief      Declaration of the TypeSizes class.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_CODEGEN_TYPEIMPL_TYPESIZES_H
#define __DCPU_CC_CODEGEN_TYPEIMPL_TYPESIZES_H


namespace dtcc
{
    namespace codegen
    {
        typedef uint16_t typesize_t;

        /// @brief      Defines the sizes for all basic types.
        class TypeSizes
        {
        private:

            TypeSizes() { };
            
        public:
            
            /// the size of a char in words
            static const typesize_t size_SignedChar = 1;
            
            /// the size of an unsigned char in words
            static const typesize_t size_UnsignedChar = 1;
            
            /// the size of a short in words
            static const typesize_t size_SignedShort = 1;
            
            /// the size of an unsigned short in words
            static const typesize_t size_UnsignedShort = 1;
            
            /// the size of a int in words
            static const typesize_t size_SignedInt = 1;
            
            /// the size of an unsigned int in words
            static const typesize_t size_UnsignedInt = 1;
            
            /// the size of a long int in words
            static const typesize_t size_SignedLong = 1;
            
            /// the size of an unsigned long int in words
            static const typesize_t size_UnsignedLong = 1;
            
            /// the size of a float in words
            static const typesize_t size_Float = 1;
            
            /// the size of a double in words
            static const typesize_t size_Double = 1;
            
            /// the size of a long double in words
            static const typesize_t size_LongDouble = 1;
            
        };


    } // namespace codegen
} // namespace dtcc

#endif
