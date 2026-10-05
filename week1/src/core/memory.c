#include <stdio.h>

#define MEMORY_CAPACITY 100

int memoryData[MEMORY_CAPACITY];

void writeMemory(int location, int data)
{
    if (location < 0 || location >= MEMORY_CAPACITY)
    {
        printf("Error: Invalid memory address\n");
        return;
    }

    memoryData[location] = data;
    printf("Memory[%d] = %d\n", location, data);
}

int readMemory(int location)
{
    if (location < 0 || location >= MEMORY_CAPACITY)
    {
        printf("Error: Invalid memory address\n");
        return -1;
    }

    return memoryData[location];
}