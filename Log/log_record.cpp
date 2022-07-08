//
// Created by zw on 2021/8/14.
//

#include "Log/log_record.h"
#include <sys/time.h>

#define CLOG(sFile, LineNumber,sData) \
    { \
        sFile = sFile.substr(sFile.find_last_of('/') + 1); \
        sData = GetLogTime();         \
        sData = sData + " " + sFile + ":" + std::to_string(iLineNumber) + " "; \
    }

static std::string GetLogTime()
{
    timeval tv{};
    gettimeofday(&tv, 0);
    time_t nowtime = tv.tv_sec;
    struct tm *nowtm;
    nowtm = localtime(&nowtime);
    char tmbuf[128];
    strftime(tmbuf, sizeof(tmbuf), "%Y-%m-%d %H:%M:%S", nowtm);
    long iMillisecond = tv.tv_usec / 1000;
    long iMicroseconds = tv.tv_usec % 1000;
    std::string sTime = tmbuf;
    sTime = sTime + ":" + std::to_string(iMillisecond) +":" + std::to_string(iMicroseconds);
    return sTime;
}

Log::Log(std::string sFile, int iLineNumber)
{
    CLOG(sFile, iLineNumber,m_sLogData);
}

Log::~Log()
{
    Record();
}

void Log::Record()
{
    m_sLogData.append(sStream.str());
    std::cout << m_sLogData << std::endl;
}

Logger::Logger(std::string sFile, int iLineNumber) : Log(sFile, iLineNumber){};