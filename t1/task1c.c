#include <stdio.h>
#include <stdlib.h>

typedef struct virus {
    unsigned short sigSize;
    unsigned char* sig;
    char virusName[16];
} virus;

typedef struct link link;
 
struct link {
    link *nextVirus;
    virus *vir;
};

struct fun_desc
{
	char *name;
	char (*fun)(char);
};

void printHex(unsigned char* buffer, int length)
{
	int i;
	for (i = 0; i < length; i++)
	{
		printf("%02X ", buffer[i]&0xff);
    	}
     	printf("\n");
}

void readVirus (virus* vir, FILE* input)
{
	unsigned short  N = fgetc(input) | fgetc(input) << 8;
	vir->sigSize = N;
	vir->sig = malloc(N);
	fread(vir->sig, 1, N, input);
	fread(vir->virusName, 1, 16, input);
}

void printVirus(virus* vir, FILE* output)
{
	fprintf(output, "Virus name: %s\n", vir->virusName);
	fprintf(output, "Virus size: %d\n", vir->sigSize);
	fprintf(output, "signature:\n%s", vir->sig);
	printHex(vir->sig, vir->sigSize);
	free(vir->sig);
}



void list_print(link *virus_list, FILE* output)
{
    while (virus_list != NULL && virus_list->vir != NULL)
    {
        printVirus(virus_list->vir, output);
        virus_list = virus_list->nextVirus;
    }
    

}

link* list_append(link* virus_list, link* to_add)
{
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

void load_signatures(char* signatures, FILE* input)
{
    printf("please enter a signatures file name: \n");
    scanf(signatures);
	input = fopen(signatures, "r");
}

void print_signatures()
{
    
}

void validate_input(int input, char* menu[], int length)
{
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

void print_menu(char* menu[], size_t length)
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

}


int main(int argc, char **argv)
{
	int user_input;
    char* signatures;
    char* buffer = malloc(1 << 10);
	FILE* input = stdin;
	FILE* output = stdout;
	link* virus_list = malloc(sizeof(link));
    char* menu[] = {"Load signatures", "Print signatures", "Detect viruses", "Quit"};
    int length = sizeof(menu) / sizeof(menu[0]);
    do
	{
		print_menu(menu, length);
        user_input = fgetc(stdin) - '0';
        fflush(stdin);
		validate_input(user_input, menu, length);
        switch (user_input)
        {
        case 0:
//            load_signatures(signatures, user_input);
            break;
        
        case 1:
            print_signatures(signatures);
        
        case 2:
            break;

        default:
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