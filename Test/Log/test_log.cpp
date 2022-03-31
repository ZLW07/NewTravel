//
// Created by wei-shao on 8/16/21.
//

#include "Log/log.h"

int main()
{
    int a = 10;
    int b = 30;
    ZLOG << " the message is " << (a + b);
    ZLOG << " the message is " << (a + b);
}
