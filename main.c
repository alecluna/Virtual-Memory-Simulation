#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define FILE_IN "input.1.txt"

int main(int argc, char *argv[])
{
    if (argc > 4) //error validate more than 4 args
    {
        printf("Incorrect number of arguments\n");
        return 1;
    }

    FILE *input_file;
    input_file = fopen(argv[1], "r");

    if (strcmp(argv[2], "FIFO") == 0)
    {
        printf("FIFO");
    }
    else if (strcmp(argv[2], "LRU") == 0)
    {
        printf("LRU");
    }
    else if (strcmp(argv[2], "OPT") == 0)
    {
        printf("OPT");
    }
    else
    {
        printf("error");
    }
}