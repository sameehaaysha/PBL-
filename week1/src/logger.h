#ifndef LOGGER_CLIENT_H
#define LOGGER_CLIENT_H

#include "IPC/common.h"
#include <mqueue.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/*
 * Lightweight client helper for any IPC module.
 * The logger process must already have created/opened CORE_TO_LOG.
 * This helper deliberately does not print or write files itself.
 */
static inline int logger_send_event(int type, const char *description)
{
    mqd_t queue = mq_open(CORE_TO_LOG, O_WRONLY);
    if (queue == (mqd_t)-1) {
        /* Do not recursively call the logger when its queue is unavailable. */
        return -1;
    }

    Message message;
    memset(&message, 0, sizeof(message));
    message.type = type;
    if (description != NULL) {
        snprintf(message.text, sizeof(message.text), "%s", description);
    } else {
        snprintf(message.text, sizeof(message.text), "%s", "(no description)");
    }

    int result = mq_send(queue, (const char *)&message, sizeof(message), 0);
    int saved_errno = errno;
    mq_close(queue);
    errno = saved_errno;
    return result;
}

#endif
