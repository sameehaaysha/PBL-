#include <stdio.h>
#include "../common.h"
#include "shared_memory.h"

int main()
{
    SharedData *data = create_shared_memory();

    if (data == NULL)
        return 1;

    data->value = 100;

    snprintf(data->message, MAX_TEXT,
             "Hello from Shared Memory");

    data->ready = 1;

    printf("\nShared Memory Test\n");
    printf("------------------\n");
    printf("Value: %d\n", data->value);
    printf("Message: %s\n", data->message);

    close_shared_memory(data);
    remove_shared_memory();

    return 0;
}

