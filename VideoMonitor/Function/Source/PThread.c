#include <stdio.h>
#include <string.h>
#include <errno.h>
#define _GNU_SOURCE     // -std=c99时要放首行，-std=gnu99时可放这
#include <unistd.h>
#include <sys/syscall.h>
#include <syslog.h>
#include "PThread.h"

pid_t GetTid(void)
{
	return syscall(__NR_gettid);
}

int CreateThread(pthread_t *pTid, void *(*start_routine)(void *), void *arg, size_t stackSize, _Bool selfDetach, enum ThreadPrior prior)
{
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
	struct sched_param sch;
	pthread_attr_getschedparam(&attr, &sch);
	sch.sched_priority = ((prior == eHighPrior) ? 30 : ((prior == eMiddlePrior) ? 50 : 70));
	pthread_attr_setschedparam(&attr, &sch);
	if (stackSize != 0)
		pthread_attr_setstacksize(&attr, stackSize);
	if (selfDetach)
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if (pthread_create(pTid, &attr, start_routine, arg) != 0)
	{
		printf("%s:%d errno = %d, means: %s.\n", __func__, __LINE__, errno, strerror(errno));
		return -1;
	}
	if (*pTid == 0)
	{
		printf("%s:%d errno = %d, means: %s.\n", __func__, __LINE__, errno, strerror(errno));
		syslog(LOG_WARNING, "%s:%d errno = %d, means: %s.\n", __func__, __LINE__, errno, strerror(errno));
		return -1;
	}

	return 0;
}

int TerminateThread(pthread_t tid)
{
	if (tid == 0)
	{
		printf("%s:%d tid == 0\n", __func__, __LINE__);
		return -1;
	}
	pthread_cancel(tid);	// 被结束的线程属性要是self dettach，否则资源不会回收
	void *tmp = NULL;
	return pthread_join(tid, &tmp);		// 若线程还没开始跑，这里会卡死
}

