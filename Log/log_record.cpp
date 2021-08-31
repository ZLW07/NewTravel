//
// Created by zw on 2021/8/14.
//

#include "Log/log_record.h"

#define CLOG(sFile, LineNumber) \
    { \
        sFile = sFile.substr(sFile.find_last_of('/') + 1); \
        std::cout << sFile << ":" << iLineNumber; \
    }

Log::Log(std::string sFile, int iLineNumber)
{
    CLOG(sFile, iLineNumber);
}

Log::~Log()
{
    Record();
}

void Log::Record()
{
    std::string sMessage = sStream.str();
    std::cout << " " << sMessage << std::endl;
}

Logger::Logger(std::string sFile, int iLineNumber) : Log(sFile, iLineNumber){};