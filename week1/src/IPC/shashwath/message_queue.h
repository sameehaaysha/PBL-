#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include <mqueue.h>
#include <stddef.h>
#include "../common.h"

/* Open an existing named queue for sending or receiving. */
mqd_t message_queue_open(const char *name, int flags);

/* Send/receive exactly one shared Message structure. */
int message_queue_send(mqd_t queue, const Message *message);
int message_queue_receive(mqd_t queue, Message *message);

/* Close a queue descriptor. */
void message_queue_close(mqd_t queue);

#endif
