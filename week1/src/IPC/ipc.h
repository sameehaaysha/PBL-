#ifndef IPC_H
#define IPC_H

#include "common.h"

#include "pipe/pipe.h"
#include "fifo/fifo.h"
#include "shashwath/message_queue.h"
#include "shared_memory/shared_memory.h"
#include "semaphore/semaphore.h"
#include "shashwath/signals.h"
#include "socket/socket.h"

typedef enum
{
IPC_PIPE = 1,
IPC_FIFO,
IPC_MESSAGE_QUEUE,
IPC_SHARED_MEMORY,
IPC_SEMAPHORE,
IPC_SIGNALS,
IPC_SOCKET
} IPCType;

int ipc_initialize(IPCType type);
int ipc_send(IPCType type, const char *message);
int ipc_receive(IPCType type, char *buffer, int buffer_size);
void ipc_cleanup(IPCType type);

#endif
