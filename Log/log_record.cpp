//
// Created by zw on 2021/8/14.
//

#include "Log/log_record.h"

#define CLOG(LineNumber) \
    { \
        std::cout << iLineNumber << ":]  "; \
    }

Log::Log(int iLineNumber)
{
    CLOG(iLineNumber);
}

Log::~Log()
{
    Record();
}
void Log::Record()
{
    std::string sMessage = sStream.str();
    std::cout << sMessage << std::endl;
}

Logger::Logger(int iLineNumber):Log(iLineNumber){};