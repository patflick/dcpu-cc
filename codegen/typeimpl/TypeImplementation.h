///
/// @addtogroup LibDCPU-CI-Lang-C/CodeGen
/// @{
///

///
/// @file       TypeImplementation.h
/// @brief      Declaration of the TypeImplementation class.
/// @author     Patrick Flick
///

#ifndef __DCPU_CC_CODEGEN_TYPEIMPL_TYPEIMPLEMENTATION_H
#define __DCPU_CC_CODEGEN_TYPEIMPL_TYPEIMPLEMENTATION_H


namespace dtcc
{
    namespace codegen
    {

        /// @brief      Defines the interface for base type implementations.
        class TypeImplementation
        {
        private:

            TypeImplementation() { };
            
        public:
            
            virtual std::deque<std::string> printConstant(double value) = 0;
            virtual std::deque<std::string> printConstant(long value) = 0;
            
            
            /// implements addition: B = B + A
            virtual std::string add(ValuePosition* posB, ValuePosition* posA) = 0;
        };


    } // namespace codegen
} // namespace dtcc

#endif
