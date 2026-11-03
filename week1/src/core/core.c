#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../IPC/ipc.h"
#include "../logger.h"

#include "cpu.h"
#include "memory.h"
#include "stack.h"
#include "queue.h"

#define MAX_INPUT 256
int main(void)
{
    Processor cpu = {0, 0, 1};
    char input[MAX_TEXT];

    printf("\n=================================\n");
    printf("       CORE PROCESS STARTED\n");
    printf("=================================\n");

    /* Initialize Message Queue */
    if (ipc_initialize(IPC_MESSAGE_QUEUE) == -1)
    {
        printf("Core: Failed to initialize IPC.\n");
        return 1;
    }

    printf("Core: Waiting for commands from UI...\n");

    while (cpu.active)
    {
        printf("\nWaiting for UI command...\n");

        if (ipc_receive(IPC_MESSAGE_QUEUE, input, sizeof(input)) == -1)
        {
            printf("Core: Failed to receive command.\n");
            break;
        }

        printf("Received: %s\n", input);
        logger_send_event(MSG_RESULT, input);
        

       if (strcmp(input, "EXIT") == 0 ||
    strcmp(input, "HALT") == 0)
{
    logger_send_event(MSG_RESULT, "Core stopped.");

    logger_send_event(MSG_SHUTDOWN, "LOGGER_SHUTDOWN");

    cpu.active = 0;

    printf("Core stopped.\n");
    break;
}
        else if (strncmp(input, "STORE ", 6) == 0)
        {
            int address;

            if (sscanf(input + 6, "%d", &address) == 1)
            {
                memoryWrite(address, cpu.acc);
                printf("Value stored successfully.\n");
            }
        }
        else if (strncmp(input, "READ ", 5) == 0)
        {
            int address;

            if (sscanf(input + 5, "%d", &address) == 1)
            {
                cpu.acc = memoryRead(address);
                printf("Accumulator = %d\n", cpu.acc);
            }
        }
        else if (strncmp(input, "PUSH ", 5) == 0)
        {
            int value;

            if (sscanf(input + 5, "%d", &value) == 1)
            {
                push(value);
                printf("Value pushed.\n");
            }
        }
        else if (strcmp(input, "POP") == 0)
        {
            printf("Popped value = %d\n", pop());
        }
        else if (strcmp(input, "PEEK") == 0)
        {
            printf("Top value = %d\n", peek());
        }
        else if (strncmp(input, "ENQUEUE ", 8) == 0)
        {
            int value;

            if (sscanf(input + 8, "%d", &value) == 1)
            {
                enqueue(value);
                printf("Value enqueued.\n");
            }
        }
        else if (strcmp(input, "DEQUEUE") == 0)
        {
            printf("Dequeued value = %d\n", dequeue());
        }
        else if (strcmp(input, "QPEEK") == 0)
        {
            printf("Front value = %d\n", queuePeek());
        }
        else
        {
            execute_instruction(&cpu, input);
        }

        cpu.pc++;
    }

    ipc_cleanup(IPC_MESSAGE_QUEUE);

    return 0;
}