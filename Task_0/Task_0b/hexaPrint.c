#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    char c;
    FILE* input = fopen(argv[1], "r");
    printf("%s", argv[1]);
    while ((c = fgetc(input)) != EOF)
    {
        printf("%", 2, c);
    }
}
