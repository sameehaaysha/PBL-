#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "semaphore.h"

sem_t *create_semaphore(void)
{
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);

    if (sem == SEM_FAILED)
    {
        perror("Semaphore creation failed");
        return NULL;
    }

    printf("Semaphore created successfully.\n");
    return sem;
}

sem_t *open_semaphore(void)
{
    sem_t *sem = sem_open(SEM_NAME, 0);

    if (sem == SEM_FAILED)
    {
        perror("Semaphore opening failed");
        return NULL;
    }

    return sem;
}

void semaphore_wait(sem_t *sem)
{
    if (sem != NULL)
    {
        if (sem_wait(sem) == -1)
            perror("Semaphore wait failed");
    }
}

void semaphore_signal(sem_t *sem)
{
    if (sem != NULL)
    {
        if (sem_post(sem) == -1)
            perror("Semaphore signal failed");
    }
}

void close_semaphore(sem_t *sem)
{
    if (sem != NULL)
        sem_close(sem);
}

void remove_semaphore(void)
{
    sem_unlink(SEM_NAME);
    printf("Semaphore removed.\n");
}