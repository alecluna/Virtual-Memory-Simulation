#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

void createQueue(Queue *q, int memSize)
{
    q->sizeOfQueue = 0;
    q->memSize = memSize;
    q->head = q->tail = NULL;
}

int enqueue(Queue *q, const void *data)
{
    node *newNode = (node *)malloc(sizeof(node));

    if (newNode == NULL)
    {
        return -1;
    }

    newNode->data = malloc(q->memSize);

    if (newNode->data == NULL)
    {
        free(newNode);
        return -1;
    }

    newNode->next = NULL;

    memcpy(newNode->data, data, q->memSize);

    if (q->sizeOfQueue == 0)
    {
        q->head = q->tail = newNode;
    }
    else
    {
        q->tail->next = newNode;
        q->tail = newNode;
    }

    q->sizeOfQueue++;
    return 0;
}

void dequeue(Queue *q, void *data)
{
    if (q->sizeOfQueue > 0)
    {
        node *temp = q->head;
        memcpy(data, temp->data, q->memSize);

        if (q->sizeOfQueue > 1)
        {
            q->head = q->head->next;
        }
        else
        {
            q->head = NULL;
            q->tail = NULL;
        }

        q->sizeOfQueue--;
        free(temp->data);
        free(temp);
    }
}

void queuePeek(Queue *q, void *data)
{
    if (q->sizeOfQueue > 0)
    {
        node *temp = q->head;
        memcpy(data, temp->data, q->memSize);
    }
}

void clearQueue(Queue *q)
{
    node *temp;

    while (q->sizeOfQueue > 0)
    {
        temp = q->head;
        q->head = temp->next;
        free(temp->data);
        free(temp);
        q->sizeOfQueue--;
    }

    q->head = q->tail = NULL;
}

int getQueueSize(Queue *q)
{
    return q->sizeOfQueue;
}

int main(int argc, char *argv[])
{
    //input validation
    if (argc > 4)
    {
        printf("Incorrect number of arguments\n");
        return 1;
    }

    int pageNumber = 0;
    int frameNumber = 0;
    int frameNumberCounter = 1;
    int numberofAccessRequests = 0;
    int accessRequest = 0;
    char str[256];
    int val;
    Queue q;

    FILE *input_file;
    input_file = fopen(argv[1], "r");

    //file validation
    if (input_file == NULL)
    {
        printf("Error on opening the input file \n");
        exit(EXIT_FAILURE);
    }

    //read input file
    fgets(str, sizeof str, input_file);

    if (sscanf(str, "%d %d %d\n", &pageNumber, &frameNumber, &numberofAccessRequests) == 3)
    {
        printf("%d %d %d\n", pageNumber, frameNumber, numberofAccessRequests);
    }
    else
    {
        printf("error reading file, text file needs to start with 3 integers");
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[2], "FIFO") == 0)
    {
        //         1- Start traversing the pages.
        //  i) If set holds less pages than capacity.
        //    a) Insert page into the set one by one until
        //       the size  of set reaches capacity or all
        //       page requests are processed.
        //    b) Simultaneously maintain the pages in the
        //       queue to perform FIFO.
        //    c) Increment page fault

        createQueue(&q, sizeof(int));
        printf("Queue is succesfully created");
        //build queue
        // while (fgets(str, sizeof str, input_file))
        // {

        //checking if it is a single line in the text file, if its not, skip
        // if (sscanf(str, "%d %d %d\n", &pageNumber, &frameNumber, &numberofAccessRequests) == 1)
        // {
        //     printf("\n# of access requests: %d\n", numberofAccessRequests);

        //     sscanf(str, "%d", &accessRequest);
        //     enQueue(q, accessRequest);
        //     printf("\n%d was just enqueued.", accessRequest);
        //     frameNumberCounter++;

        //     printf("while loop exited after 4");
        //     struct QueueNode *n = deQueue(q);
        //     if (n != NULL)
        //         printf("Dequeued item from list is: %d", n->data);
        //     printf("\n");
        //}
        //}
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