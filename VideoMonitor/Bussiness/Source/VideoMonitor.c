#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "PThread.h"

int main(void)
{
	int iRet = 0;
	pthread_t tid = 0;
	extern void *ConsoleThr(void *arg);
	iRet = CreateThread(&tid, ConsoleThr, NULL, 32*1024, true, eMiddlePrior);
	while (true)
		sleep(5);

	return 0;
}

