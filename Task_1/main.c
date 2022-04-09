#include <stdio.h>
#include <stdlib.h>
#include "readVirus.c"
#include "printVirus.c"

/*
void readVirus(virus* vir, FILE* input);
void printVirus(virus* vir, FILE* output);
*/

int main(int argc, char**argv)
{
	FILE* input = fopen("signatures", "r");
	FILE* output = stdout;
	virus* vir = malloc(sizeof(*vir));
	int c;
	readVirus(vir, input);
	printVirus(vir, output);
	readVirus(vir, input);
	printVirus(vir, output);
	readVirus(vir, input);
	printVirus(vir, output);
	readVirus(vir, input);
	printVirus(vir, output);
	readVirus(vir, input);
	printVirus(vir, output);
	readVirus(vir, input);
	printVirus(vir, output);
	readVirus(vir, input);
	printVirus(vir, output);
	readVirus(vir, input);
	printVirus(vir, output);
	free(vir);



}
