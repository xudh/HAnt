#ifndef UART___H
#define UART___H

#include <stdbool.h>

int OpenUart(const char *pDev);
int SetBaudrate(int fd, unsigned int baud, _Bool bFlowCtrl);
int SetCheck(int fd, unsigned int dataBit, unsigned int stopBit, char type);
int SetTimeOut(int fd, int vtime, int vmin);	// vtime等待的最大时间，单位是十分之一秒；vmin表示要读到的最小个数

#endif

