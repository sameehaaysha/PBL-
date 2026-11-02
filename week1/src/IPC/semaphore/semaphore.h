#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "../common.h"
#include <semaphore.h>

#define SEM_NAME "/simulator_semaphore"

sem_t *create_semaphore(void);
sem_t *open_semaphore(void);

void semaphore_wait(sem_t *sem);
void semaphore_signal(sem_t *sem);

void close_semaphore(sem_t *sem);
void remove_semaphore(void);

#endif