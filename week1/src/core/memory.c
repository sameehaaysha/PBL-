#include <stdio.h>
#include "memory.h"

#define MEMORY_SIZE 100

static int memoryData[MEMORY_SIZE] = {0};

void memoryWrite(int address, int value)
{
    if (address >= 0 && address < MEMORY_SIZE)
    {
        memoryData[address] = value;
    }
    else
    {
        printf("Invalid memory address!\n");
    }
}

int memoryRead(int address)
{
    if (address >= 0 && address < MEMORY_SIZE)
    {
        return memoryData[address];
    }

    printf("Invalid memory address!\n");
    return -1;
}