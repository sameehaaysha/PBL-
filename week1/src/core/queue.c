#include <stdio.h>
#include "queue.h"

#define QUEUE_SIZE 100

static int queue[QUEUE_SIZE];
static int front = 0;
static int rear = -1;
static int count = 0;

void enqueue(int value)
{
    if (count == QUEUE_SIZE)
    {
        printf("Queue is full!\n");
        return;
    }

    rear = (rear + 1) % QUEUE_SIZE;
    queue[rear] = value;
    count++;
}

int dequeue(void)
{
    if (count == 0)
    {
        printf("Queue is empty!\n");
        return -1;
    }

    int value = queue[front];
    front = (front + 1) % QUEUE_SIZE;
    count--;

    return value;
}

int queuePeek(void)
{
    if (count == 0)
    {
        printf("Queue is empty!\n");
        return -1;
    }

    return queue[front];
}