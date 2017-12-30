#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <errno.h>
#include "ReadWrite.h"

ssize_t ReadAntiInter(int fd, void *pBuf, size_t count)
{
	size_t readLen = 0;
	ssize_t ret = 0;
	while (readLen < count)
	{
		ret = read(fd, (char *)pBuf + readLen, count - readLen);
		if (ret == 0 || ret == count - readLen)
		{
			readLen += ret;
			break;
		}
		else if (errno == EINTR)
		{
			if (ret > 0)
				readLen += ret;
			else if (ret != -1)
			{
				printf("%s:%d ret = %zd\n", __func__, __LINE__, ret);
				readLen = ret;
				break;
			}
			printf("%s:%d ret = %zd interrupted continue.\n", __func__, __LINE__, ret);
		}
		else
		{
			printf("%s:%d errno = %d, means %s\n", __func__, __LINE__, errno, strerror(errno));
			readLen = ret;
			break;
		}
	}

	return readLen;
}

ssize_t WriteAntiInter(int fd, const void *pBuf, size_t count)
{
	size_t writeLen = 0;
	ssize_t ret = 0;
	while (writeLen < count)
	{
		ret = write(fd, (const char *)pBuf + writeLen, count - writeLen);
		if (ret == 0 || ret == count - writeLen)
		{
			writeLen += ret;
			break;
		}
		else if (errno == EINTR)
		{
			if (ret > 0)
				writeLen += ret;
			else if (ret != -1)
			{
				printf("%s:%d ret = %zd\n", __func__, __LINE__, ret);
				writeLen = ret;
				break;
			}
			printf("%s:%d ret = %zd interrupted continue.\n", __func__, __LINE__, ret);
		}
		else
		{
			printf("%s:%d errno = %d, means %s\n", __func__, __LINE__, errno, strerror(errno));
			writeLen = ret;
			break;
		}
	}

	return writeLen;
}

