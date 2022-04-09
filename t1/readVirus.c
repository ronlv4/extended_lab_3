#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


void readVirus (virus* vir, FILE* input)
{
	unsigned short  N = fgetc(input) | fgetc(input) << 8;
	vir->sigSize = N;
	vir->sig = malloc(N);
	fread(vir->sig, 1, N, input);
	fread(vir->virusName, 1, 16, input);
}

