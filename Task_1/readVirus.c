#include <stdio.h>
#include <stdlib.h>

typedef struct virus {
	unsigned short sigSize;
	unsigned char* sig;
	char virtusName[16];
} virus;

void readVirus (virus* vir, FILE* input)
{
	int N = (fgetc(input) | fgetc(input) << 8;
	fread(vir.sig, 1, N, input);
	fread(vir.virusName, 1, 16, input);
	printf("%d\n", vir.sigSize);
	printf("%s\n", vir.sig);
	printf("%s\n", vir.virusName);
}

