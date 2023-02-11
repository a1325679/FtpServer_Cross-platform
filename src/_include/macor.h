#ifndef _MACOR_H
#define _MACOR_H
#include "log.h"
//LOG宏定义
#define STDERR 0
#define EMERG 1
#define ALERT 2
#define CRIT 3
#define ERROR 4
#define WARN 5
#define NOTICE 6
#define INFO 7
#define DEBUG 8

#define myprintf(...) printf(__VA_ARGS__)

#define log(level,str,...) MyLog::GetInstance()->Log(level,str,__VA_ARGS__) 


#endif
