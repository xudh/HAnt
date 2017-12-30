#ifndef PTHREAD___H
#define PTHREAD___H

#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>
#include <pthread.h>

enum ThreadPrior
{
	eHighPrior,
	eMiddlePrior,
	eLowPrior
};

pid_t GetTid(void);

// 创建线程并设置一些属性，指定栈大小能节省内存
int CreateThread(pthread_t *pTid, void *(*start_routine)(void *), void *arg, size_t stackSize, _Bool selfDetach, enum ThreadPrior prior);

int TerminateThread(pthread_t tid);

#endif

