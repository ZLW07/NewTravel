//
// Created by zw on 2021/9/1.
//

#include "Log/log.h"
#include "Mutex/base_mutex.h"
#include <thread>

BaseMutex oBaseMutex;

void PrintBlock(int iNumber, char cByte)
{

    for (int i = 0; i < iNumber; i++)
    {
        oBaseMutex.Lock();
        ZLOG << cByte;
        oBaseMutex.UnLock();
    }

}

int main()
{
    std::thread th1(PrintBlock, 50, '!');
    std::thread th2(PrintBlock, 50, '$');

    th1.join();
    th2.join();
    return 0;
};
