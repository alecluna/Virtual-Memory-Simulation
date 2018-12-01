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

        int i;
        int frameIndex = 0;
        int pageFault = 0;
        int pageFaultCount = 0;

        for (i = 0; i < numberofRequests; i++)
        {
            //build page requests to be looked at
            int tobeLoaded = pageRequestArray[i];

            if ((pageFaultCount = isPageLoaded(tobeLoaded, frames)) == -1)
            {

                pageFault++;

                //checking for empty frames
                if (frames[frameIndex] == -1)
                {
                    printf("Page %d loaded in empty Frame %d\n", tobeLoaded, frameIndex);
                    frames[frameIndex] = tobeLoaded; //set new page in frame
                    frameIndex++;
                    if (frameIndex == frameNumber)
                    {
                        frameIndex = 0;
                    }
                    continue;
                }

                //else add pages to unloaded frames
                printf("Page %d unloaded from Frame %d", frames[frameIndex], frameIndex);
                frames[frameIndex] = tobeLoaded; //set new page in frame
                printf(", Page %d loaded into Frame %d\n", tobeLoaded, frameIndex);

                ++frameIndex; //update frame index
                if (frameIndex == frameNumber)
                {
                    frameIndex = 0;
                }
            }
            else
            { //page already loaded
                printf("Page %d already loaded in Frame %d\n", tobeLoaded, pageFaultCount);
            }
        }
        printf("%d Page Faults\n", pageFault);
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