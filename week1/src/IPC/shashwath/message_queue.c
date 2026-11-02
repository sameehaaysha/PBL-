#include "message_queue.h"
#include "../../logger.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

mqd_t message_queue_open(const char *name, int flags)
{
    if (name == NULL) {
        errno = EINVAL;
        perror("message_queue_open: invalid queue name");
        logger_send_event(MSG_ERROR, "Message Queue: invalid queue name");
        return (mqd_t)-1;
    }

    mqd_t queue = mq_open(name, flags);
    if (queue == (mqd_t)-1) {
        char text[MAX_TEXT];
        snprintf(text, sizeof(text), "Message Queue: mq_open failed for %s: %s",
                 name, strerror(errno));
        perror("mq_open");
        logger_send_event(MSG_ERROR, text);
    } else {
        char text[MAX_TEXT];
        snprintf(text, sizeof(text), "Message Queue: opened %s", name);
        logger_send_event(MSG_RESULT, text);
    }
    return queue;
}

int message_queue_send(mqd_t queue, const Message *message)
{
    if (queue == (mqd_t)-1 || message == NULL) {
        errno = EINVAL;
        logger_send_event(MSG_ERROR, "Message Queue: send called with invalid input");
        return -1;
    }

    if (mq_send(queue, (const char *)message, sizeof(*message), 0) == -1) {
        char text[MAX_TEXT];
        snprintf(text, sizeof(text), "Message Queue: send failed: %s", strerror(errno));
        perror("mq_send");
        logger_send_event(MSG_ERROR, text);
        return -1;
    }

    logger_send_event(MSG_RESULT, "Message Queue: message sent successfully");
    return 0;
}

int message_queue_receive(mqd_t queue, Message *message)
{
    if (queue == (mqd_t)-1 || message == NULL) {
        errno = EINVAL;
        logger_send_event(MSG_ERROR, "Message Queue: receive called with invalid input");
        return -1;
    }

    unsigned int priority = 0;
    ssize_t received = mq_receive(queue, (char *)message, sizeof(*message), &priority);
    if (received == -1) {
        char text[MAX_TEXT];
        snprintf(text, sizeof(text), "Message Queue: receive failed: %s", strerror(errno));
        perror("mq_receive");
        logger_send_event(MSG_ERROR, text);
        return -1;
    }

    if ((size_t)received != sizeof(*message)) {
        logger_send_event(MSG_ERROR, "Message Queue: received message has unexpected size");
        errno = EMSGSIZE;
        return -1;
    }

    message->text[MAX_TEXT - 1] = '\0';
    logger_send_event(MSG_RESULT, "Message Queue: message received successfully");
    return 0;
}

void message_queue_close(mqd_t queue)
{
    if (queue != (mqd_t)-1 && mq_close(queue) == -1) {
        perror("mq_close");
        logger_send_event(MSG_ERROR, "Message Queue: failed to close queue");
    } else {
        logger_send_event(MSG_RESULT, "Message Queue: queue descriptor closed");
    }
}
