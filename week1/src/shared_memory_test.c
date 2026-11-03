#include <stdio.h>
#include <string.h>
#include "IPC/shared_memory/shared_memory.h"

int main(void)
{
    SharedData *data = create_shared_memory();

    if (data == NULL)
        return 1;

    strcpy(data->message, "Hello from Shared Memory!");
    data->value = 100;
    data->ready = 1;

    printf("Data written successfully!\n");

    SharedData *reader = open_shared_memory();

    if (reader == NULL)
        return 1;

    printf("Received message: %s\n", reader->message);
    printf("Received value: %d\n", reader->value);

    close_shared_memory(reader);
    close_shared_memory(data);
    remove_shared_memory();

    printf("Shared Memory test completed successfully!\n");

    return 0;
}
