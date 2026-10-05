#include <stdio.h>
#include <string.h>

typedef struct {
    int acc;
    int pc;
    int active;
} Processor;

/* CPU */
void execute_instruction(Processor *cpu, char instruction[]);

/* Memory */
void writeMemory(int location, int data);
int readMemory(int location);

/* Stack */
void push(int number);
int pop(void);
int peek(void);

/* Queue */
void enqueue(int value);
int dequeue(void);
int queue_peek(void);

int main()
{
    Processor cpu = {0, 0, 1};

    char instruction[100];
    char command[20];

    int value;
    int address;
    int result;

    while (cpu.active)
    {
        printf("\nEnter instruction: ");
        fgets(instruction, sizeof(instruction), stdin);

        instruction[strcspn(instruction, "\n")] = '\0';

        sscanf(instruction, "%s", command);

        if (strcmp(command, "STORE") == 0)
        {
            sscanf(instruction, "%s %d %d", command, &address, &value);
            writeMemory(address, value);
        }
        else if (strcmp(command, "READ") == 0)
        {
            sscanf(instruction, "%s %d", command, &address);

            result = readMemory(address);

            if (result != -1)
                printf("Memory[%d] = %d\n", address, result);
        }
        else if (strcmp(command, "PUSH") == 0)
        {
            sscanf(instruction, "%s %d", command, &value);
            push(value);
        }
        else if (strcmp(command, "POP") == 0)
        {
            result = pop();

            if (result != -1)
                printf("Popped %d\n", result);
        }
        else if (strcmp(command, "PEEK") == 0)
        {
            result = peek();

            if (result != -1)
                printf("Top = %d\n", result);
        }
        else if (strcmp(command, "ENQUEUE") == 0)
        {
            sscanf(instruction, "%s %d", command, &value);
            enqueue(value);
        }
        else if (strcmp(command, "DEQUEUE") == 0)
        {
            result = dequeue();

            if (result != -1)
                printf("Dequeued %d\n", result);
        }
        else if (strcmp(command, "QPEEK") == 0)
        {
            result = queue_peek();

            if (result != -1)
                printf("Front = %d\n", result);
        }
        else
        {
            execute_instruction(&cpu, instruction);
        }
    }

    printf("\nFinal ACC = %d\n", cpu.acc);
    printf("Final PC = %d\n", cpu.pc);

    return 0;
}