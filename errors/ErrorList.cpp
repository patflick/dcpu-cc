/**

    File:           ErrorList.cpp

    Project:        DCPU-16 Tools
    Component:      LibDCPU-ci-lang

    Authors:        Patrick Flick

    Description:    Defines the ErrorList class.

**/

#include "ErrorList.h"

#include <errors/derr.defs.h>

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdio>

using namespace dcpucc::errors;

extern std::vector<std::string> yylines;

void ErrorList::addWarning(int line, int col, std::string file, std::string errmsg)
{
    Error err(line, col, file, errmsg, ErrorList::ERROR_LIST_WARNING);
    this->m_list.push_back(err);
    this->m_hasWarnings = true;
}

void ErrorList::addWarning(int line, int col, std::string file, int errid)
{
    std::string errormsg(derrstr[errid]);
    this->addWarning(line, col, file, errormsg);
}

void ErrorList::addWarning(int line, int col, std::string file, int errid, std::string errdata)
{
    std::string errormsg(derrstr[errid]);
    char buffer[256];
    sprintf(buffer, errormsg.c_str(), errdata.c_str());
    errormsg = std::string(buffer);
    this->addWarning(line, col, file, errormsg);
}

void ErrorList::addError(int line, int col, std::string file, std::string errmsg)
{
    Error err(line, col, file, errmsg, ErrorList::ERROR_LIST_ERROR);
    this->m_list.push_back(err);
    this->m_hasErrors = true;
}

void ErrorList::addError(int line, int col, std::string file, int errid)
{
    std::string errormsg(derrstr[errid]);
    this->addError(line, col, file, errormsg);
}

void ErrorList::addError(int line, int col, std::string file, int errid, std::string errdata)
{
    std::string errormsg(derrstr[errid]);
    char buffer[256];
    sprintf(buffer, errormsg.c_str(), errdata.c_str());
    errormsg = std::string(buffer);
    this->addError(line, col, file, errormsg);
}

void ErrorList::addFatalError(int line, int col, std::string file, std::string errmsg)
{
    Error err(line, col, file, errmsg, ErrorList::ERROR_LIST_FATAL_ERROR);
    this->m_list.push_back(err);
    this->m_hasErrors = true;
}

void ErrorList::addFatalError(int line, int col, std::string file, int errid)
{
    std::string errormsg(derrstr[errid]);
    this->addFatalError(line, col, file, errormsg);
}

void ErrorList::addFatalError(int line, int col, std::string file, int errid, std::string errdata)
{
    std::string errormsg(derrstr[errid]);
    char buffer[256];
    sprintf(buffer, errormsg.c_str(), errdata.c_str());
    errormsg = std::string(buffer);
    this->addFatalError(line, col, file, errormsg);
    
    // TODO 
    // FIXME stop execution right away via dhalt
}

std::string ErrorList::errToStr(Error err)
{
    std::string errwar;
    switch (err.warnErr)
    {
        case ErrorList::ERROR_LIST_WARNING:
            errwar = "warning";
            break;
        case ErrorList::ERROR_LIST_ERROR:
            errwar = "error";
            break;
        case ErrorList::ERROR_LIST_FATAL_ERROR:
            errwar = "error";
            break;
    }
    
    std::stringstream ss;
    ss  << err.file << ":" << err.line << ":" << err.col << ": " << errwar << ": " << err.errmsg;
    ss << yylines[err.line-1] << std::endl;
    ss << std::setw(err.col) << "^" << std::endl;
    return ss.str();
}

void ErrorList::printall()
{
    std::cerr << " printing all errors: " << this->m_list.size() << std::endl;
    
    std::vector<Error>::iterator it;
    for (it = this->m_list.begin(); it != this->m_list.end(); it++)
    {
        std::cerr << errToStr(*it);
    }
}

bool ErrorList::hasWarnings()
{
    return this->m_hasWarnings;
}

bool ErrorList::hasErrors()
{
    return this->m_hasErrors;
}

std::list<std::string> ErrorList::getWarnings()
{
    std::vector<Error>::iterator it;
    std::list<std::string> result;
    for (it = this->m_list.begin(); it != this->m_list.end(); it++)
    {
        if (it->warnErr == ErrorList::ERROR_LIST_WARNING)
            result.push_back(errToStr(*it));
    }
    return result;
}

std::list<std::string> ErrorList::getErrors()
{
    std::vector<Error>::iterator it;
    std::list<std::string> result;
    for (it = this->m_list.begin(); it != this->m_list.end(); it++)
    {
        if (it->warnErr != ErrorList::ERROR_LIST_WARNING)
            result.push_back(errToStr(*it));
    }
    return result;
}

std::list<std::string> ErrorList::getWarningsAndErrors()
{
    std::vector<Error>::iterator it;
    std::list<std::string> result;
    for (it = this->m_list.begin(); it != this->m_list.end(); it++)
    {
        result.push_back(errToStr(*it));
    }
    return result;
}


