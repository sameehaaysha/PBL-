#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mqueue.h>
#include <fcntl.h>
#include "common.h"

void log_message(Message *msg)
{
    FILE *file;
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char time_str[30];

    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", t);

    if (msg->type == MSG_ERROR)
        file = fopen("logs/error.log", "a");
    else
        file = fopen("logs/execution.log", "a");

    if (file == NULL)
    {
        perror("Log file");
        return;
    }

    fprintf(file, "[%s] %s\n", time_str, msg->text);
    fclose(file);
}

int main()
{
    struct mq_attr attr = {0};
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(Message);

    mqd_t queue = mq_open(CORE_TO_LOG, O_RDONLY | O_CREAT, 0666, &attr);

    if (queue == (mqd_t)-1)
    {
        perror("mq_open");
        return 1;
    }

    printf("Logger started. Waiting for messages...\n");

    while (1)
    {
        Message msg;

        if (mq_receive(queue, (char *)&msg, sizeof(msg), NULL) == -1)
        {
            perror("mq_receive");
            break;
        }

        log_message(&msg);

        printf("Logged: %s\n", msg.text);

        if (msg.type == MSG_SHUTDOWN)
            break;
    }

    mq_close(queue);
    mq_unlink(CORE_TO_LOG);

    printf("Logger stopped.\n");

    return 0;
}