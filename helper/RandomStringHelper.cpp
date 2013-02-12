///
/// @addtogroup LibDCPU-CI-Lang-C/Helper
/// @{
///

///
/// @file       RandomStringHelper.cpp
/// @brief      Definition of the RandomStringHelper helper class.
/// @author     Patrick Flick
///


#include "RandomStringHelper.h"
#include <algorithm>
#include <iterator>
#include <cstdlib>


using namespace dcpucc::helper;

RandomStringHelper::RandomStringHelper()
{

}

RandomStringHelper::~RandomStringHelper()
{

}

// Generates a random string.
std::string RandomStringHelper::randString(std::string::size_type sz)
{
    std::string s;
    s.reserve(sz);
    std::generate_n(std::back_inserter(s), sz, RandomStringHelper::randChar);
    return s;
}

// Generates a random character.
char RandomStringHelper::randChar()
{
    static const char alphanum[] =
    "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";
    
    return alphanum[rand() % (sizeof(alphanum) - 1)];
}

std::string RandomStringHelper::getUniqueString(std::string::size_type length)
{
    // initialize singleton
    if (RandomStringHelper::instance == NULL)
    {
        RandomStringHelper::instance = new RandomStringHelper();
    }
    RandomStringHelper* rs = RandomStringHelper::instance;
    
    // find a string that is unique, i.e. hasn't been generated before
    std::string result = RandomStringHelper::randString(length);
    while (rs->m_usedStrings.find(result) != rs->m_usedStrings.end())
    {
        result = RandomStringHelper::randString(length);
    }
    
    return result;
}

std::string RandomStringHelper::getUniqueLabel(std::string prefix)
{
    return prefix + std::string("_") + RandomStringHelper::getUniqueString(__DCPU_CC_RANDOM_LABEL_LENGTH);
}

RandomStringHelper* RandomStringHelper::instance = NULL;


///
/// @}
///