#include <stdio.h>

#define QUEUE_LIMIT 100

int queueData[QUEUE_LIMIT];
int frontIndex = 0;
int rearIndex = -1;
int itemCount = 0;

void enqueue(int value)
{
    if (itemCount == QUEUE_LIMIT)
    {
        printf("Error: Queue is full\n");
        return;
    }

    rearIndex = (rearIndex + 1) % QUEUE_LIMIT;
    queueData[rearIndex] = value;
    itemCount++;

    printf("Enqueued %d\n", value);
}

int dequeue()
{
    int value;

    if (itemCount == 0)
    {
        printf("Error: Queue is empty\n");
        return -1;
    }

    value = queueData[frontIndex];
    frontIndex = (frontIndex + 1) % QUEUE_LIMIT;
    itemCount--;

    return value;
}

int queue_peek()
{
    if (itemCount == 0)
    {
        printf("Queue is empty\n");
        return -1;
    }

    return queueData[frontIndex];
}