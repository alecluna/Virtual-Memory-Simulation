#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pageRequestArray[30];
int pageNumber;
int frameNumber;
int numberofRequests;
int frameIndex = 0;
int pageFault = 0;
int pageFaultIndex = 0;

//search function for existing page requests
int search(int pageRequest, int frames[])
{
    for (int i = 0; i <= frameNumber; i++)
    {
        if (frames[i] == pageRequest)
            return i;
    }
    return -1;
}

int NextPageUse(int cur, int frames[], int f)
{
    for (; cur < numberofRequests; cur++)
    {
        if (pageRequestArray[cur] == frames[f])
        {
            return cur;
        }
    }
    return 9999;
}

int main(int argc, char *argv[])
{

    if (argc < 2 || argc > 4)
    {
        printf("Invalid argument count\n");
        printf("Enter in the format: ./a.out input1.txt [FIFO | LRU | OPT]\n");
        exit(EXIT_FAILURE);
    }

    FILE *input_file;
    int counter = 0;

    input_file = fopen(argv[1], "r");

    if (input_file == NULL)
    {
        printf("Error opening the input file \n");
        exit(EXIT_FAILURE);
    }
    //grab first three values
    //&pageNumber, &frameNumber, &numberofAccessRequests
    if (fscanf(input_file, "%d %d %d", &pageNumber, &frameNumber, &numberofRequests) == 3)
    {

        while (fscanf(input_file, "%d", &pageRequestArray[counter]) != EOF)
        {
            counter++;
        }
        fclose(input_file);
    }
    else
    {
        printf("Error, text file must start with 3 integers\n");
    }
    int frames[frameNumber];

    for (int i = 0; i <= frameNumber; i++)
    {
        frames[i] = -1;
    }

    if (strcmp(argv[2], "FIFO") == 0)
    {
        int i;
        for (i = 0; i < numberofRequests; i++)
        {
            //build page requests to be looked at
            int tobeLoaded = pageRequestArray[i];

            //if search does not find the value in question
            if ((pageFaultIndex = search(tobeLoaded, frames)) == -1)
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

                frameIndex++; //update frame index
                if (frameIndex == frameNumber)
                {
                    frameIndex = 0;
                }
            }
            else // if the page is already loaded
            {
                printf("Page %d already loaded in Frame %d\n", tobeLoaded, pageFaultIndex);
            }
        }
        printf("%d Page Faults\n", pageFault);
    }

    else if (strcmp(argv[2], "LRU") == 0)
    {
        int frameTime[frameNumber];
        int i;
        for (i = 0; i < numberofRequests; i++)
        {
            int tobeLoaded = pageRequestArray[i];

            if ((pageFaultIndex = search(tobeLoaded, frames)) == -1)
            {
                pageFault++; //increment page fault
                //load empty frames if none exist yet
                if (frames[frameIndex] == -1)
                {
                    printf("Page %d loaded in empty Frame %d\n", tobeLoaded, frameIndex);
                    frames[frameIndex] = tobeLoaded; //set new page in frame
                    frameTime[frameIndex] = i;       //set time of frame load
                    frameIndex++;                    //update frame index
                    if (frameIndex == frameNumber)
                        frameIndex = 0;

                    continue;
                }

                int mostRecent = 0;
                int toUseTime = 9999;
                int j;
                for (j = 0; j < frameNumber; j++)
                {
                    if (frameTime[j] < toUseTime)
                    {
                        mostRecent = j;
                        toUseTime = frameTime[j];
                    }
                }

                printf("Page %d unloaded from Frame %d", frames[mostRecent], mostRecent);
                frames[mostRecent] = tobeLoaded; //set new page in frame
                frameTime[mostRecent] = i;       //set time of frame load
                printf(", Page %d loaded into Frame %d\n", tobeLoaded, mostRecent);
            }
            else
            {                                  //page already loaded
                frameTime[pageFaultIndex] = i; //set time of frame access
                printf("Page %d already loaded in Frame %d\n", tobeLoaded, pageFaultIndex);
            }
        }
        printf("%d Page Faults\n", pageFault);
    }
    else if (strcmp(argv[2], "OPT") == 0)
    {
        int i;
        for (i = 0; i < numberofRequests; i++)
        {
            int tobeLoaded = pageRequestArray[i];

            //search function call
            if ((pageFaultIndex = search(tobeLoaded, frames)) == -1)
            {

                pageFault++;

                //load into empty frames
                if (frames[frameIndex] == -1)
                {
                    printf("Page %d loaded in empty Frame %d\n", tobeLoaded, frameIndex);
                    frames[frameIndex] = tobeLoaded; //set new page in frame
                    frameIndex++;                    //update frame index
                    if (frameIndex == frameNumber)
                    {
                        frameIndex = 0;
                    }
                    continue;
                }

                int tobeUsed = 0;
                int touseTime = 0;
                int f = 0;
                int t = 0;
                for (f = 0; f < frameNumber; f++)
                {
                    if ((t = NextPageUse(i, frames, f)) > touseTime)
                    {
                        tobeUsed = f;
                        touseTime = t;
                    }
                }

                printf("Page %d unloaded from Frame %d", frames[tobeUsed], tobeUsed);
                frames[tobeUsed] = tobeLoaded; //set new page in frame
                printf(", Page %d loaded into Frame %d\n", tobeLoaded, tobeUsed);
            }
            else
            { //page already loaded
                printf("Page %d already loaded in Frame %d\n", tobeLoaded, pageFaultIndex);
            }
        }
        printf("%d Page Faults\n", pageFault);
    }
    else
    {
        printf("error");
    }
}
