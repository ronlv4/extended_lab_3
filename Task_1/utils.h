#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct virus {
	unsigned short sigSize;
	unsigned char* sig;
	char virusName[16];
} virus;

void PrintHex(unsigned char* buffer, int length)
{
	int i;
	for (i = 0; i < length; i++)
	{
		printf("%02X ", buffer[i]&0xff);
    	}
     	printf("\n");
}

#endif
