#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <fcntl.h>
#include <unistd.h>
#include "IPC/common.h"

static int ensure_log_directory(void)
{
    if (mkdir("logs", 0755) == 0 || errno == EEXIST)
        return 0;
    perror("mkdir logs");
    return -1;
}

static void log_message(const Message *message)
{
    time_t now = time(NULL);
    struct tm local_time;
    char timestamp[32] = "unknown-time";

    if (now != (time_t)-1 && localtime_r(&now, &local_time) != NULL) {
        if (strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S",
                     &local_time) == 0) {
            snprintf(timestamp, sizeof(timestamp), "unknown-time");
        }
    }

    const char *path = (message->type == MSG_ERROR)
                       ? "logs/error.log" : "logs/execution.log";
    FILE *file = fopen(path, "a");
    if (file == NULL) {
        perror("logger: fopen");
        return;
    }

    const char *level = message->type == MSG_ERROR ? "ERROR" :
                        message->type == MSG_SHUTDOWN ? "SHUTDOWN" : "INFO";
    fprintf(file, "[%s] [%s] %s\n", timestamp, level, message->text);
    fflush(file);
    fclose(file);

    printf("[%s] [%s] %s\n", timestamp, level, message->text);
}

int main(void)
{
    if (ensure_log_directory() == -1)
        return EXIT_FAILURE;

    struct mq_attr attr;
    memset(&attr, 0, sizeof(attr));
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(Message);

    /*
     * ipc.c is expected to create CORE_TO_LOG before launching logger.
     * O_CREAT is retained so logger can also be launched standalone.
     */
    mqd_t queue = mq_open(CORE_TO_LOG, O_RDONLY | O_CREAT, 0666, &attr);
    if (queue == (mqd_t)-1) {
        perror("logger: mq_open");
        return EXIT_FAILURE;
    }

    puts("Logger started. Waiting for events...");
    for (;;) {
        Message message;
        memset(&message, 0, sizeof(message));

        ssize_t bytes = mq_receive(queue, (char *)&message, sizeof(message), NULL);
        if (bytes == -1) {
            if (errno == EINTR)
                continue;
            perror("logger: mq_receive");
            mq_close(queue);
            return EXIT_FAILURE;
        }

        if ((size_t)bytes != sizeof(message)) {
            fputs("Logger: discarded malformed message\n", stderr);
            continue;
        }
        message.text[MAX_TEXT - 1] = '\0';
        log_message(&message);

        /* Only this explicit marker should stop the logger. */
        if (message.type == MSG_SHUTDOWN &&
            strcmp(message.text, "LOGGER_SHUTDOWN") == 0) {
            break;
        }
    }

    mq_close(queue);
    puts("Logger stopped.");
    return EXIT_SUCCESS;
}
