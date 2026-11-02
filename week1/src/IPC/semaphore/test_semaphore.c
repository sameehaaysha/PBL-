#include <stdio.h>
#include "semaphore.h"

int main(void)
{
    sem_t *sem = create_semaphore();

    if (sem == NULL)
        return 1;

    printf("\nSemaphore Test\n");
    printf("--------------------\n");

    printf("Waiting for semaphore...\n");

    semaphore_wait(sem);

    printf("Semaphore acquired successfully!\n");

    printf("Critical section is running...\n");

    semaphore_signal(sem);

    printf("Semaphore released successfully!\n");

    close_semaphore(sem);

    remove_semaphore();

    return 0;
}