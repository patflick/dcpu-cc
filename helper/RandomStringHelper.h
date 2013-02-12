///
/// @addtogroup LibDCPU-CI-Lang-C/ValueTypes
/// @{
///

///
/// @file       RandomStringHelper.h
/// @brief      Declaration of the RandomStringHelper helper class.
/// @author     Patrick Flick
///
    

#ifndef __DCPU_CC_HELPER_RANDOMSTRINGHELPER_H
#define __DCPU_CC_HELPER_RANDOMSTRINGHELPER_H

#define __DCPU_CC_RANDOM_LABEL_LENGTH 8

#include <string>
#include <set>

namespace dcpucc
{
    namespace helper
    {

        class RandomStringHelper
        {
        private:
            /// No public construction
            RandomStringHelper();
            
            /// returns a random character
            static char randChar();
            
            /// returns a random string of given length
            static std::string randString(std::string::size_type sz);
            
            /// a singleton self reference:
            static RandomStringHelper* instance;
            
            /// contains all already generated strings
            std::set<std::string> m_usedStrings;
        public:
            
            /// returns a random string, that has not been returned before
            /// (i.e. that is unique).
            static std::string getUniqueString(std::string::size_type length);
            
            /// returns a random label with the given prefix, that has not been
            /// returned before (i.e. that is unique).
            static std::string getUniqueLabel(std::string prefix);
            
            virtual ~RandomStringHelper();
        };
    }
}

#endif // __DCPU_CC_HELPER_RANDOMSTRINGHELPER_H
