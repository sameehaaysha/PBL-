#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>

#include "ipc.h"

/* IPC resources */
static int pipe_fd[2] = {-1, -1};
static int fifo_fd = -1;
static int socket_fd = -1;
static int server_fd = -1;

static mqd_t mq_fd = (mqd_t)-1;

static SharedData *shared_data = NULL;
static sem_t *semaphore = NULL;

/* Initialize IPC mechanism */
int ipc_initialize(IPCType type)
{
switch (type)
{
case IPC_PIPE:
return pipe_create(pipe_fd);


    case IPC_FIFO:
        if (fifo_create("/tmp/simulator_fifo", 0666) == -1)
            return -1;

        fifo_fd = fifo_open("/tmp/simulator_fifo", O_RDWR);
        return fifo_fd;

    case IPC_MESSAGE_QUEUE:
{
    struct mq_attr attr;

    memset(&attr, 0, sizeof(attr));

    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(Message);

    /* Remove an old queue before creating a fresh one */
    mq_unlink(UI_TO_CORE);

    mq_fd = mq_open(UI_TO_CORE,
                    O_CREAT | O_RDWR,
                    0666,
                    &attr);

    if (mq_fd == (mqd_t)-1)
    {
        perror("IPC: Message queue creation failed");
        return -1;
    }

    printf("IPC: Message queue initialized successfully.\n");

    return 0;
}

    case IPC_SHARED_MEMORY:
        shared_data = create_shared_memory();

        return shared_data == NULL ? -1 : 0;

    case IPC_SEMAPHORE:
        semaphore = create_semaphore();

        return semaphore == SEM_FAILED ? -1 : 0;

    case IPC_SIGNALS:
        return signals_install_handlers();

    case IPC_SOCKET:
        server_fd = create_server();

        return server_fd == -1 ? -1 : 0;

    default:
        return -1;
}


}

/* Send data through selected IPC mechanism */
int ipc_send(IPCType type, const char *message)
{
if (message == NULL)
return -1;


switch (type)
{
    case IPC_PIPE:
        return pipe_write(pipe_fd[1], message);

    case IPC_FIFO:
        return fifo_write(fifo_fd, message);

    case IPC_MESSAGE_QUEUE:
    {
        Message msg = {0};
        msg.type = MSG_COMMAND;

        snprintf(msg.text, MAX_TEXT, "%s", message);

        return message_queue_send(mq_fd, &msg);
    }

    case IPC_SHARED_MEMORY:
        if (shared_data == NULL)
            return -1;

        semaphore_wait(semaphore);

        snprintf(shared_data->message,
                 MAX_TEXT,
                 "%s",
                 message);

        shared_data->ready = 1;

        semaphore_signal(semaphore);

        return 0;

    case IPC_SEMAPHORE:
        semaphore_signal(semaphore);
        return 0;

    case IPC_SIGNALS:
        return signals_send(getpid(), SIGUSR1);

    case IPC_SOCKET:
        if (socket_fd == -1)
            return -1;

        return send_message(socket_fd, message);

    default:
        return -1;
}


}

/* Receive data through selected IPC mechanism */
int ipc_receive(IPCType type, char *buffer, int buffer_size)
{
if (buffer == NULL || buffer_size <= 0)
return -1;


switch (type)
{
    case IPC_PIPE:
        return pipe_read(pipe_fd[0], buffer, buffer_size);

    case IPC_FIFO:
        return fifo_read(fifo_fd, buffer, buffer_size);

    case IPC_MESSAGE_QUEUE:
    {
        Message msg;

        if (message_queue_receive(mq_fd, &msg) == -1)
            return -1;

        snprintf(buffer, buffer_size, "%s", msg.text);

        return 0;
    }

    case IPC_SHARED_MEMORY:
        if (shared_data == NULL)
            return -1;

        semaphore_wait(semaphore);

        if (shared_data->ready == 0)
        {
            semaphore_signal(semaphore);
            return -1;
        }

        snprintf(buffer, buffer_size, "%s",
                 shared_data->message);

        shared_data->ready = 0;

        semaphore_signal(semaphore);

        return 0;

    case IPC_SEMAPHORE:
        semaphore_wait(semaphore);
        return 0;

    case IPC_SIGNALS:
    {
        int signal_number = signals_take_pending();

        if (signal_number == 0)
            return -1;

        snprintf(buffer, buffer_size, "Signal received: %d",
                 signal_number);

        return 0;
    }

    case IPC_SOCKET:
        if (socket_fd == -1)
            return -1;

        return receive_message(socket_fd, buffer, buffer_size);

    default:
        return -1;
}


}

/* Release IPC resources */
void ipc_cleanup(IPCType type)
{
switch (type)
{
case IPC_PIPE:
if (pipe_fd[0] != -1)
pipe_close(pipe_fd[0]);


        if (pipe_fd[1] != -1)
            pipe_close(pipe_fd[1]);

        pipe_fd[0] = pipe_fd[1] = -1;
        break;

    case IPC_FIFO:
        if (fifo_fd != -1)
        {
            fifo_close(fifo_fd);
            fifo_fd = -1;
        }
        break;

    case IPC_MESSAGE_QUEUE:
        if (mq_fd != (mqd_t)-1)
        {
            message_queue_close(mq_fd);
            mq_fd = (mqd_t)-1;
        }
        break;

    case IPC_SHARED_MEMORY:
        if (shared_data != NULL)
        {
            close_shared_memory(shared_data);
            shared_data = NULL;
        }

        remove_shared_memory();
        break;

    case IPC_SEMAPHORE:
        if (semaphore != NULL && semaphore != SEM_FAILED)
        {
            close_semaphore(semaphore);
            semaphore = NULL;
        }

        remove_semaphore();
        break;

    case IPC_SOCKET:
        if (socket_fd != -1)
        {
            close_socket(socket_fd);
            socket_fd = -1;
        }

        if (server_fd != -1)
        {
            close_socket(server_fd);
            server_fd = -1;
        }
        break;

    default:
        break;
}


}
