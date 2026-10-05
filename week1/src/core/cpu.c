#include <stdio.h>
#include <string.h>

typedef struct {
    int acc;
    int pc;
    int active;
} Processor;

void execute_instruction(Processor *cpu, char instruction[])
{
    char command[10];
    int number = 0;

    sscanf(instruction, "%s %d", command, &number);

    if (strcmp(command, "LOAD") == 0)
    {
        cpu->acc = number;
        printf("ACC = %d\n", cpu->acc);
    }
    else if (strcmp(command, "ADD") == 0)
    {
        cpu->acc = cpu->acc + number;
        printf("ACC = %d\n", cpu->acc);
    }
    else if (strcmp(command, "SUB") == 0)
    {
        cpu->acc = cpu->acc - number;
        printf("ACC = %d\n", cpu->acc);
    }
    else if (strcmp(command, "MUL") == 0)
    {
        cpu->acc = cpu->acc * number;
        printf("ACC = %d\n", cpu->acc);
    }
    else if (strcmp(command, "DIV") == 0)
    {
        if (number == 0)
        {
            printf("Error: Cannot divide by zero\n");
        }
        else
        {
            cpu->acc = cpu->acc / number;
            printf("ACC = %d\n", cpu->acc);
        }
    }
    else if (strcmp(command, "HALT") == 0)
    {
        cpu->active = 0;
        printf("CPU stopped\n");
    }
    else
    {
        printf("Invalid instruction\n");
    }

    cpu->pc++;
}
