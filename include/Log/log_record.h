//
// Created by zw on 2021/8/14.
//

#ifndef CSW_TEST_LOG_RECORD_H
#define CSW_TEST_LOG_RECORD_H

#include <iostream>
#include <sstream>
class Log
{
public:
    Log(std::string sFile,int iLineNumber);

    template <class T> Log &operator<<(T val)
    {
        sStream << val;
        return *this;
    }
    ~Log();
    void Record();

public:
protected:
    std::stringstream sStream;
    std::string m_sLogData;
};

class Logger : public Log
{
public:
    Logger(std::string sFile,int iLineNumber);
};

#endif // CSW_TEST_LOG_RECORD_H
