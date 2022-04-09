#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void printVirus(virus* vir, FILE* output)
{
	fprintf(output, "Virus name: %s\n", vir->virusName);
	fprintf(output, "Virus size: %d\n", vir->sigSize);
	fprintf(output, "signature:\n%s", vir->sig);
	PrintHex(vir->sig, vir->sigSize);
	free(vir->sig);
}
