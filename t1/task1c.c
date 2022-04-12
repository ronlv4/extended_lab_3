#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct virus
{
	unsigned short sigSize;
	unsigned char *sig;
	char virusName[16];
} virus;

typedef struct link link;

struct link
{
	link *nextVirus;
	virus *vir;
};

struct fun_desc
{
	char *name;
	char (*fun)(char);
};

char *map(char *array, int array_length, char (*f)(char))
{
	char *mapped_array = (char *)(malloc(array_length * sizeof(char)));
	int i;
	for (i = 0; i < array_length; i++)
	{
		mapped_array[i] = f(array[i]);
	}
	return mapped_array;
}

void printHex(unsigned char *buffer, int length)
{
	int i;
	for (i = 0; i < length; i++)
	{
		printf("%02X ", ((int)buffer[i]) & 0xff);
	}
	printf("\n");
}

void readVirus(virus *vir, FILE *input)
{
	unsigned short N = fgetc(input) | fgetc(input) << 8;
	vir->sigSize = N;
	vir->sig = malloc(N);
	fread(vir->sig, 1, N, input);
	fread(vir->virusName, 1, 16, input);
}

void printVirus(virus *vir, FILE *output)
{
	fprintf(output, "Virus name: %s\n", vir->virusName);
	fprintf(output, "Virus size: %d\n", vir->sigSize);
	fprintf(output, "signature:\n");
	printHex(vir->sig, vir->sigSize);
}

void list_print(link *virus_list, FILE *output)
{
	link *current_link = virus_list;
	while (current_link != NULL && current_link->vir != NULL)
	{
		printVirus(current_link->vir, output);
		current_link = current_link->nextVirus;
		printf("\n");
	}
}

link *list_append(link *virus_list, link *to_add)
{
	if (to_add == NULL)
	{
		return virus_list;
	}
	// to_add->nextVirus = malloc(sizeof(link));
	to_add->nextVirus = virus_list;
	return to_add;
}

void list_free(link *virus_list)
{
	while (virus_list != NULL && virus_list->vir != NULL)
	{
		free(virus_list->vir);
		virus_list = virus_list->nextVirus;
	}
}

link *load_signatures()
{
	printf("please enter a signatures file name: \n");
	FILE *sig_file;
	char *file_name = malloc(100);
	link *virus_list = NULL;
	// scanf("\n%s", file_name);
	// while ((ch = getchar()) != '\n' && ch != EOF);
	file_name = "signatures";
	sig_file = fopen(file_name, "r");
	while (!feof(sig_file))
	{
		virus *vir = (virus *)malloc(sizeof(virus));
		readVirus(vir, sig_file);
		link *to_add = (link *)malloc(sizeof(link));
		to_add->nextVirus = NULL;
		to_add->vir = vir;
		virus_list = list_append(virus_list, to_add);
	}
	return virus_list->nextVirus;
}

void print_signatures(link *virus_list)
{
	printf("printing signatures:\n");
	list_print(virus_list, stdout);
}

void validate_input(int input, char *menu[], int length)
{
	printf("validating input: %d\n", input);
	if (input >= 0 && input <= length - 1)
	{
		printf("Within bounds\n");
	}
	else
	{
		printf("Not within bounds\n");
		exit(1);
	}
}

void print_menu(char *menu[], size_t length)
{
	int i;
	for (i = 0; i < length; i++)
	{
		printf("%d) %s\n", i, menu[i]);
	}
	printf("Option: ");
}

void detect_virus(char *buffer, unsigned int size, link *virus_list)
{
	char ch;
	char *file_path = malloc(100);
	printf("Please enter a file path: \n");
	scanf("\n%s", file_path);
	while ((ch = getchar()) != '\n' && ch != EOF)
		;
	FILE *f = fopen(file_path, "r");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	fread(buffer, fsize, 1, f);
	fclose(f);
	buffer[fsize] = 0;

	for (size_t i = 0; i < fsize; i++)
	{
		printf("%X ",buffer[i]);
	}
	

	link *list_iter = virus_list;
	while (list_iter != NULL)
	{
		printf("comparing with virus %s\n", list_iter->vir->virusName);
		if (memcmp(buffer, list_iter->vir->sig, size) == 0)
		{
			printVirus(list_iter->vir,stdout);
		}
		list_iter = list_iter->nextVirus;
	}
	
}

int main(int argc, char **argv)
{
	char* string = "Hello 01 02 03 04 05";
	FILE *fp = fopen("testVirus", "w");
	fwrite(string, 1, 20, fp);
	exit(0);
	int user_input;
	char *buffer = malloc(1 << 10);
	link *virus_list = NULL;
	char *menu[] = {"Load signatures", "Print signatures", "Detect viruses", "Quit"};
	int length = sizeof(menu) / sizeof(menu[0]);
	do
	{
		print_menu(menu, length);
		user_input = fgetc(stdin) - '0';
		char ch;
		while ((ch = getchar()) != '\n' && ch != EOF)
			;
		validate_input(user_input, menu, length);
		switch (user_input)
		{
		case 0:
			virus_list = load_signatures();
			break;

		case 1:
			print_signatures(virus_list);
			break;

		case 2:
			detect_virus(buffer, 5, virus_list);
			break;

		default:
			list_free(virus_list);
			exit(0);
		}
	} while (1);
}
/*
Load signatures requests a signature file name parameter from the user after the user runs it by entering "1".

After the signatures are loaded, Print signatures can be used to print them to the screen. If no file was loaded nothing is printed. You should read the user's input using fgets and sscanf.

Test yourself by:

Read the signatures of the viruses into buffers in memory.
Creates a linked list that contains all the viruses where each node represents a single virus.
Prints the content. Here's an example output: lab3_out.
*/