#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pageRequestArray[20];
int pageNumber;
int frameNumber;
int numberofRequests;

int main(int argc, char *argv[])
{

    if (argc < 2 || argc > 4)
    {
        printf("Invalid argument count\n");
        return 0;
    }

    FILE *input_file;
    int counter = 0;

    input_file = fopen(argv[1], "r");

    if (input_file == NULL)
    {
        printf("Error on opening the input file \n");
        exit(EXIT_FAILURE);
    }
    //grab first three values
    //&pageNumber, &frameNumber, &numberofAccessRequests
    fscanf(input_file, "%d %d %d", &pageNumber, &frameNumber, &numberofRequests);

    while (fscanf(input_file, "%d", &pageRequestArray[counter]) != EOF)
    {
        printf("Page requests from text file: %d\n", pageRequestArray[counter]);
        counter++;
    }
    fclose(input_file);

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