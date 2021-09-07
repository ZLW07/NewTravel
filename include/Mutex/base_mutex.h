//
// Created by zw on 2021/9/1.
//

#ifndef NEWTRAVEL_BASE_MUTEX_H
#define NEWTRAVEL_BASE_MUTEX_H

#include <mutex>

class BaseMutex
    {
    public:
        BaseMutex(){};
        ~BaseMutex(){};
        void Lock();
        void UnLock();
    private:
        std::mutex m_oMutex;
    };

#endif // NEWTRAVEL_BASE_MUTEX_H
