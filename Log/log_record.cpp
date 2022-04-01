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
    struct timeval time;
    gettimeofday(&time, NULL);
    time_t nowTime = time.tv_sec;
    tm *LocalTime = localtime(&nowTime);
    char cTimeBuff[128];
    strftime(cTimeBuff, sizeof(cTimeBuff), "%Y/%m/%d %H:%M:%S", LocalTime);
    long iMillisecond = time.tv_usec % 1000000;
    std::string sTime = cTimeBuff;
    sTime = sTime + "." + std::to_string(iMillisecond);
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