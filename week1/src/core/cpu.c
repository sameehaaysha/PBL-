#include <stdio.h>
#include <string.h>
#include "cpu.h"

void execute_instruction(Processor *cpu, char instruction[])
{
    int value;

    if (sscanf(instruction, "LOAD %d", &value) == 1)
    {
        cpu->acc = value;
        printf("Accumulator loaded with %d\n", value);
    }
    else if (sscanf(instruction, "ADD %d", &value) == 1)
    {
        cpu->acc += value;
        printf("Addition result: %d\n", cpu->acc);
    }
    else if (sscanf(instruction, "SUB %d", &value) == 1)
    {
        cpu->acc -= value;
        printf("Subtraction result: %d\n", cpu->acc);
    }
    else if (sscanf(instruction, "MUL %d", &value) == 1)
    {
        cpu->acc *= value;
        printf("Multiplication result: %d\n", cpu->acc);
    }
    else if (sscanf(instruction, "DIV %d", &value) == 1)
    {
        if (value != 0)
        {
            cpu->acc /= value;
            printf("Division result: %d\n", cpu->acc);
        }
        else
        {
            printf("Error: Division by zero!\n");
        }
    }
    else
    {
        printf("Invalid instruction!\n");
    }
}