#include <stdio.h>
#include <string.h>
#include "IPC/pipe/pipe.h"

int main(void)
{
    int pipefd[2];
    char buffer[100];

    if (pipe_create(pipefd) == -1)
    {
        perror("Pipe creation failed");
        return 1;
    }

    printf("Pipe created successfully!\n");

    if (pipe_write(pipefd[1], "Hello from Pipe!") == -1)
    {
        perror("Pipe write failed");
        return 1;
    }

    if (pipe_read(pipefd[0], buffer, sizeof(buffer)) == -1)
    {
        perror("Pipe read failed");
        return 1;
    }

    printf("Received message: %s\n", buffer);

    pipe_close(pipefd[0]);
    pipe_close(pipefd[1]);

    printf("Pipe test completed successfully!\n");

    return 0;
}
