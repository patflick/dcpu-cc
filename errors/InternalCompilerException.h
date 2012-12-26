///
/// @addtogroup LibDCPU-CI-Lang-C/Errors
/// @{
///

///
/// @file       InternalCompilerException.h
/// @brief      Declaration of the InternalCompilerException class.
/// @author     Patrick Flick
///

#ifndef __DCPU_LIBDCC_INTERNALCOMPILEREXCEPTION_H
#define __DCPU_LIBDCC_INTERNALCOMPILEREXCEPTION_H

#include <string>
#include <sstream>

namespace dtcc
{
    namespace errors
    {
        /// @class InternalCompilerException
        /// @brief A std::exception that is used to throw internal compiler errors.
        /// This exception is used for errors that are programming or design errors,
        /// that occur while compiling code. I.e. if a NULL pointer is encountered
        /// where there should not be a NULL pointer, etc. This is NOT an
        /// error that is thrown if the compiled code is faulty.
        class InternalCompilerException : public std::exception
        {
        private:
            /// The message of the internal exception.
            std::string m_Message;

        public:
            
            /// @brief Constructs a new InternalCompilerException.
            /// @param message The message for the new internal compiler exception.
            InternalCompilerException(std::string message) : m_Message(message) { };
            
            /// @brief The destructor.
            virtual ~InternalCompilerException() throw() { };
            
            virtual const char* what() const throw()
            {
                return this->m_Message.c_str();
            }
            inline std::string getMessage()
            {
                return this->m_Message.c_str();
            }
        };

    } // namespace errors
} // namespace dtcc

#endif