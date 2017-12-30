#ifndef READ_WRITE___H
#define READ_WRITE___H

#include <stddef.h>
#include <unistd.h>

ssize_t ReadAntiInter(int fd, void *pBuf, size_t count);			// 抗中断的读
ssize_t WriteAntiInter(int fd, const void *pBuf, size_t count);	// 抗中断的写

#endif

