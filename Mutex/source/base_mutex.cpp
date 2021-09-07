//
// Created by zw on 2021/9/1.
//

#include "Mutex/base_mutex.h"

void BaseMutex::Lock()
{
    m_oMutex.lock();
}

void BaseMutex::UnLock()
{
    m_oMutex.unlock();
}
