//
// Created by wei on 2022/4/19.
//

#ifndef NEWTRAVEL_TEST_MUTEX_H
#define NEWTRAVEL_TEST_MUTEX_H

#include "Log/log.h"
#include "Mutex/base_mutex.h"
#include "gtest/gtest.h"
#include <thread>

class TestUT : public ::testing::Test
{
public:
        TestUT(){};
       ~TestUT() {}
};

int f(int x, int y)
{
    return x - y;
}

TEST_F(TestUT, Test1)
{
    auto i = 0;
    auto ret = f(++i, ++i);
    ZLOG << ret;
}

#endif // NEWTRAVEL_TEST_MUTEX_H
