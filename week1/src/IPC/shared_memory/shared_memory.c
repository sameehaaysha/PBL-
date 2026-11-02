#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "shared_memory.h"

SharedData *create_shared_memory(void)
{
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);

    if (fd == -1)
    {
        perror("Shared memory creation failed");
        return NULL;
    }

    if (ftruncate(fd, sizeof(SharedData)) == -1)
    {
        perror("Shared memory size failed");
        close(fd);
        return NULL;
    }

    SharedData *data = mmap(
        NULL,
        sizeof(SharedData),
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        fd,
        0
    );

    close(fd);

    if (data == MAP_FAILED)
    {
        perror("Shared memory mapping failed");
        return NULL;
    }

    data->ready = 0;
    data->value = 0;
    data->message[0] = '\0';

    printf("Shared memory created successfully.\n");

    return data;
}

SharedData *open_shared_memory(void)
{
    int fd = shm_open(SHM_NAME, O_RDWR, 0666);

    if (fd == -1)
    {
        perror("Unable to open shared memory");
        return NULL;
    }

    SharedData *data = mmap(
        NULL,
        sizeof(SharedData),
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        fd,
        0
    );

    close(fd);

    if (data == MAP_FAILED)
    {
        perror("Shared memory mapping failed");
        return NULL;
    }

    return data;
}

void close_shared_memory(SharedData *data)
{
    if (data != NULL)
    {
        munmap(data, sizeof(SharedData));
    }
}

void remove_shared_memory(void)
{
    shm_unlink(SHM_NAME);
    printf("Shared memory removed.\n");
}