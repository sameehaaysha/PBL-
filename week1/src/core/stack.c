#include <stdio.h>
#include "stack.h"

#define STACK_SIZE 100

int stack[STACK_SIZE];
int top = -1;

void push(int value)
{
    if (top == STACK_SIZE - 1)
    {
        printf("Stack Overflow!\n");
        return;
    }

    top++;
    stack[top] = value;

    printf("%d pushed into stack.\n", value);
}

int pop(void)
{
    if (top == -1)
    {
        printf("Stack Underflow!\n");
        return -1;
    }

    int value = stack[top];
    top--;

    return value;
}

int peek(void)
{
    if (top == -1)
    {
        printf("Stack is empty!\n");
        return -1;
    }

    return stack[top];
}