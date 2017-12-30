#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include "Uart.h"

int OpenUart(const char *pDev)
{
	int fd = open(pDev, O_RDWR|O_NOCTTY);
	if (fd < 0)
	{
		printf("%s:%d errno = %d, means: %s.\n", __func__, __LINE__, errno, strerror(errno));
		return -1;
	}

	return fd;
}

int SetBaudrate(int fd, unsigned int baud, _Bool bFlowCtrl)
{
	struct termios opt;
	if (tcgetattr(fd, &opt) != 0)
	{
		printf("%s:%d errno = %d, means: %s.\n", __func__, __LINE__, errno, strerror(errno));
		return -1;
	}

	opt.c_cflag |= (CLOCAL | CREAD);
	opt.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	opt.c_iflag &= ~(IXON | IXOFF | IXANY | ICRNL);
	opt.c_oflag &= ~OPOST;
	if (bFlowCtrl)
		opt.c_cflag |= CRTSCTS;
	else
		opt.c_cflag &= ~CRTSCTS;
	cfsetispeed(&opt, baud);
	cfsetospeed(&opt, baud);
	tcflush(fd, TCIOFLUSH);
	if (tcsetattr(fd, TCSANOW, &opt) != 0)
	{
		printf("%s:%d errno = %d, means: %s.\n", __func__, __LINE__, errno, strerror(errno));
		return -1;
	}

	return 0;
}

int SetCheck(int fd, unsigned int dataBit, unsigned int stopBit, char type)
{
	struct termios opt;
	if (tcgetattr(fd, &opt) != 0)
	{
		printf("%s:%d errno = %d, means: %s.\n", __func__, __LINE__, errno, strerror(errno));
		return -1;
	}

	opt.c_cflag &= ~CSIZE;
	if (dataBit == 7)
		opt.c_cflag |= CS7;
	else if (dataBit == 8)
		opt.c_cflag |= CS8;
	else
	{
		printf("%s:%d dataBit = %u unsupport\n", __func__, __LINE__, dataBit);
		return -1;
	}

	if (stopBit == 1)
		opt.c_cflag &= ~CSTOPB;
	else if (stopBit == 2)
		opt.c_cflag |= CSTOPB;
	{
		printf("%s:%d stopBit = %u unsupport\n", __func__, __LINE__, stopBit);
		return -1;
	}

	switch (type)
	{
		case 'n':	// 无校验
		case 'N':
			opt.c_cflag &= ~PARENB;
			opt.c_iflag &= ~INPCK;
			break;
		case 'o':	// odd奇校验
		case 'O':
			opt.c_cflag |= (PARODD | PARENB);
			opt.c_iflag |= INPCK;
			break;
		case 'e':	// even偶校验
		case 'E':
			opt.c_cflag |= PARENB;
			opt.c_cflag &= ~PARODD;
			opt.c_iflag |= INPCK;
			break;
		case 'S':
		case 's':
			opt.c_cflag &= ~PARENB;
			opt.c_cflag &= ~CSTOPB;
			break;
		default:
			printf("%s:%d type = %c\n", __func__, __LINE__, type);
			return -1;
	}

	tcflush(fd, TCIOFLUSH);
	if (tcsetattr(fd, TCSANOW, &opt) != 0)
	{
		printf("%s:%d errno = %d, means: %s.\n", __func__, __LINE__, errno, strerror(errno));
		return -1;
	}

	return 0;
}

int SetTimeOut(int fd, int vtime, int vmin)
{
	struct termios opt;
	if (tcgetattr(fd, &opt) != 0)
	{
		printf("%s:%d errno = %d, means: %s.\n", __func__, __LINE__, errno, strerror(errno));
		return -1;
	}

	opt.c_cc[VTIME] = vtime;
	opt.c_cc[VMIN] = vmin;
	tcflush(fd, TCIOFLUSH);
	if (tcsetattr(fd, TCSANOW, &opt) != 0)
	{
		printf("%s:%d errno = %d, means: %s.\n", __func__, __LINE__, errno, strerror(errno));
		return -1;
	}

	return 0;
}

