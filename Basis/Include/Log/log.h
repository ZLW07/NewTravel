//
// Created by zw on 2021/8/14.
//

#ifndef CSW_TEST_LOG_H
#define CSW_TEST_LOG_H
#include "log_record.h"

#ifndef ZLOG
#define ZLOG Logger(__FILE__,__LINE__)
#endif

#ifndef ZLOG_ERR
#define ZLOG_ERR ZLOG << "[ERROR] "
#endif

#ifndef ZLOG_WARN
#define ZLOG_WARN ZLOG << "[WARNING] "
#endif

#ifndef ZLOG_INFO
#define ZLOG_INFO ZLOG << "[IFNO] "
#endif

#endif // CSW_TEST_LOG_H
