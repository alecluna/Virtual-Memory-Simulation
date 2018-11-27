#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define FILE_IN "input.1.txt"

// A linked list (LL) node to store a queue entry
struct QueueNode
{
    int key;
    struct QueueNode *next;
};

// The queue, front stores the front node of LL and rear stores ths
// last node of LL
struct Queue
{
    struct QueueNode *front, *rear;
};

// A utility function to create a new linked list node.
struct QueueNode *newNode(int k)
{
    struct QueueNode *temp = (struct QueueNode *)malloc(sizeof(struct QueueNode));
    temp->key = k;
    temp->next = NULL;
    return temp;
}

// A utility function to create an empty queue
struct Queue *createQueue()
{
    struct Queue *q = (struct Queue *)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

// The function to add a key k to q
void enQueue(struct Queue *q, int k)
{
    // Create a new LL node
    struct QueueNode *temp = newNode(k);

    // If queue is empty, then new node is front and rear both
    if (q->rear == NULL)
    {
        q->front = q->rear = temp;
        return;
    }

    // Add the new node at the end of queue and change rear
    q->rear->next = temp;
    q->rear = temp;
}

// Function to remove a key from given queue q
struct QueueNode *deQueue(struct Queue *q)
{
    // If queue is empty, return NULL.
    if (q->front == NULL)
        return NULL;

    // Store previous front and move front one node ahead
    struct QueueNode *temp = q->front;
    q->front = q->front->next;

    // If front becomes NULL, then change rear also as NULL
    if (q->front == NULL)
        q->rear = NULL;
    return temp;
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
    int accessRequest = 0;
    char str[256];

    FILE *input_file;
    input_file = fopen(argv[1], "r");

    //file validation
    if (input_file == NULL)
    {
        printf("Error on opening the input file \n");
        exit(EXIT_FAILURE);
    }

    //read input file
    if (fgets(str, sizeof str, input_file))
    {
        sscanf(str, "%d %d %d", &pageNumber, &frameNumber, &accessRequest);

        if (strcmp(argv[2], "FIFO") == 0)
        {
            struct Queue *q = createQueue();
            printf("Queue is succesfully created");
            enQueue(q, 20);
            struct QueueNode *n = deQueue(q);
            printf("item removed at front of list: %d", n->key);
            // The first integer is the number of pages,
            // the second integer is the number of frames, and the
            // third integer is the number of page access requests.
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
    else
    {
        printf("error reading file, text file needs to start with 3 integers");
    }
}