//
// Created by zw on 2021/10/21.
//

#ifndef NEWTRAVEL_TEST_LOG_H
#define NEWTRAVEL_TEST_LOG_H

#include "gtest/gtest.h"
#include "Log/log.h"

class LogTest: public ::testing::Test
    {
    public:
        LogTest(){}
        ~LogTest(){}
    private:
    };

TEST_F(LogTest, ddd)
{
    ZLOG << " Hello gtest";
}

#endif // NEWTRAVEL_TEST_LOG_H
