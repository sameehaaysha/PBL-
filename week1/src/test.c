#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "IPC/fifo/fifo.h"

int main(void)
{
    const char *path = "/tmp/my_fifo_test";
    char buffer[100];

    if (fifo_create(path, 0666) == -1)
    {
        perror("FIFO creation failed");
        return 1;
    }

    printf("FIFO created successfully!\n");

    int fd = fifo_open(path, O_RDWR);

    if (fd == -1)
    {
        perror("FIFO open failed");
        return 1;
    }

    printf("FIFO opened successfully!\n");

    if (fifo_write(fd, "Hello from FIFO!") == -1)
    {
        perror("FIFO write failed");
        return 1;
    }

    if (fifo_read(fd, buffer, sizeof(buffer)) == -1)
    {
        perror("FIFO read failed");
        return 1;
    }

    printf("Received message: %s\n", buffer);

    fifo_close(fd);
    unlink(path);

    printf("FIFO test completed successfully!\n");

    return 0;
}
