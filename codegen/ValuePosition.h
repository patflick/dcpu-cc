///
/// @addtogroup LibDCPU-CI-Lang-C/CodeGen
/// @{
///

///
/// @file       ValuePosition.h
/// @brief      Declaration of the ValuePosition class.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_CODEGEN_VALUEPOSITION_H
#define __DCPU_CC_CODEGEN_VALUEPOSITION_H

#include <stdint.h>



namespace dtcc
{
    namespace codegen
    {
        
        enum ValPos {};
        
        ///
        /// @class      ValuePosition
        /// @brief      The ValuePosition class.
        ///
        class ValuePosition
        {
            
        public:

            
        public:
            ///
            /// @brief      The constructor of the ValuePosition class.
            ///
            ValuePosition()  {}
            
            ///
            /// @brief          Returns the size of the value in words.
            /// @return         The size of the value.
            ///
            virtual uint16_t getWordSize() = 0;


            
            ///
            /// @brief      The destructor of the ValuePosition class.
            ///
            virtual ~ValuePosition();
        };

    } // namespace codegen
} // namespace dtcc

#endif

///
/// @}
///