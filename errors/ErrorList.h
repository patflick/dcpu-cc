///
/// @addtogroup LibDCPU-CI-Lang-C/Errors
/// @{
///

///
/// @file       ErrorList.h
/// @brief      Declaration of the ErrorList class.
/// @author     Patrick Flick
///

#ifndef __DCPU_LIBDCC_ERRORLIST_H
#define __DCPU_LIBDCC_ERRORLIST_H

#include <string>
#include <vector>
#include <iostream>
#include <list>

namespace dcpucc
{
    namespace errors
    {
        class Error
        {
        public:
            int col;
            int line;
            std::string file;
            std::string errmsg;
            int warnErr;
            
            Error(int line, int col, std::string file, std::string errmsg, int warnErr) :
                col(col),
                line(line),
                file(file),
                errmsg(errmsg),
                warnErr(warnErr) {}
        };

        class ErrorList
        {
        private:
            std::vector<Error> m_list;
            bool m_hasWarnings;
            bool m_hasErrors;
            
            std::string errToStr(Error err);
        public:
            static const int ERROR_LIST_WARNING = 0;
            static const int ERROR_LIST_ERROR = 1;
            static const int ERROR_LIST_FATAL_ERROR = 2;

            ErrorList() : m_list(std::vector<Error>()), m_hasWarnings(false), m_hasErrors(false) {}
            
            void addWarning(int line, int col, std::string file, std::string errmsg);
            void addWarning(int line, int col, std::string file, int errid);
            void addWarning(int line, int col, std::string file, int errid, std::string errdata);
            void addError(int line, int col, std::string file, std::string errmsg);
            void addError(int line, int col, std::string file, int errid);
            void addError(int line, int col, std::string file, int errid, std::string errdata);
            void addFatalError(int line, int col, std::string file, std::string errmsg);
            void addFatalError(int line, int col, std::string file, int errid);
            void addFatalError(int line, int col, std::string file, int errid, std::string errdata);
            
            bool hasWarnings();
            bool hasErrors();
            
            std::list<std::string> getWarnings();
            std::list<std::string> getErrors();
            std::list<std::string> getWarningsAndErrors();
            
            void printall();
        };
    }
}

#endif

///
/// @}
///
