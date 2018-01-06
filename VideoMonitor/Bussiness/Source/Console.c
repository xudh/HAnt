#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void *ConsoleThr(void *arg)
{
	char buf[512] = "", cmd[512] = "";
	const size_t bufLen = sizeof(buf);
	const size_t readLen = bufLen - 1;
	char *pStr = NULL, *pSaveStr = NULL;
	const char *pSplit = " \t\n";
	while (true)
	{
		printf("->");
		memset(buf, 0, bufLen);
		pStr = fgets(buf, readLen, stdin); 	
		if (pStr == NULL)
		{
			printf("%s:%d pStr == NULL\n", __func__, __LINE__);
			continue;
		}

		pStr = strtok_r(pStr, pSplit, &pSaveStr);
		if (strcmp(pStr, "q") == 0)
		{
			exit(0);
		}
		else if (strcmp(pStr, "system") == 0)
		{
			pStr = strtok_r(NULL, pSplit, &pSaveStr);
			if (pStr != NULL)
			{
				memset(cmd, 0, sizeof(cmd));
				strcpy(cmd, pStr);
				while ((pStr = strtok_r(NULL, pSplit, &pSaveStr)) != NULL)
				{
					strcat(cmd, pStr);
				}
				system(cmd);
			}
		}
		else
		{
			printf("%s:%d unsupport cmd\n", __func__, __LINE__);
			continue;
		}
	}

	return NULL;
}

