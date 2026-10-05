#include <stdio.h>

#define MAX_ITEMS 100

int stackData[MAX_ITEMS];
int stackTop = -1;

void push(int number)
{
    if (stackTop >= MAX_ITEMS - 1)
    {
        printf("Error: Stack is full\n");
        return;
    }

    stackTop++;
    stackData[stackTop] = number;

    printf("Pushed %d\n", number);
}

int pop()
{
    if (stackTop < 0)
    {
        printf("Error: Stack is empty\n");
        return -1;
    }

    int number = stackData[stackTop];
    stackTop--;

    return number;
}

int peek()
{
    if (stackTop < 0)
    {
        printf("Stack is empty\n");
        return -1;
    }

    return stackData[stackTop];
}