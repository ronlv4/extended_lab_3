#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    char c;
    FILE* input = fopen(argv[1], "r");
    while ((c = fgetc(input)) != EOF)
    {
        printf("%02X ", c&0xff);
    }
    printf("\n");
}
