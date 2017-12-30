#include <stdio.h>
#include <stdint.h>
#include "Common.h"

void PrintByte(const void *pBuf, size_t count)
{
	printf("%s: pBuf = %p, count = %zu\n", __func__, pBuf, count);
	uint8_t *pI = (uint8_t *)pBuf;
	for (size_t i = 0; i < count; ++i)
	{
		printf("%02x ", *pI);
		if (i % 16 == 15 || i + 1 == count)
			printf("\n");
		++pI;
	}
}

