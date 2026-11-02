#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include "../common.h"

#include <sys/types.h>

#define SHM_NAME "/simulator_shared_memory"

typedef struct
{
    int ready;
    int value;
    char message[MAX_TEXT];
} SharedData;

SharedData *create_shared_memory(void);
SharedData *open_shared_memory(void);
void close_shared_memory(SharedData *data);
void remove_shared_memory(void);

#endif