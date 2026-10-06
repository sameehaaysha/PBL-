#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <mqueue.h>
#include <fcntl.h>
#include "common.h"

int main()
{
    pid_t ui_pid, core_pid, logger_pid;

    mq_unlink(UI_TO_CORE);
    mq_unlink(CORE_TO_UI);
    mq_unlink(CORE_TO_LOG);

    struct mq_attr attr = {0};
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(Message);

    mqd_t q1 = mq_open(UI_TO_CORE, O_CREAT | O_RDWR, 0666, &attr);
    mqd_t q2 = mq_open(CORE_TO_UI, O_CREAT | O_RDWR, 0666, &attr);
    mqd_t q3 = mq_open(CORE_TO_LOG, O_CREAT | O_RDWR, 0666, &attr);

    if (q1 == (mqd_t)-1 ||
        q2 == (mqd_t)-1 ||
        q3 == (mqd_t)-1)
    {
        perror("Message queue creation failed");
        return 1;
    }

    printf("Message queues created successfully.\n");

    ui_pid = fork();

    if (ui_pid == 0)
    {
        execl("./ui", "./ui", NULL);
        perror("Failed to start UI");
        exit(1);
    }

    core_pid = fork();

    if (core_pid == 0)
    {
        execl("./core", "./core", NULL);
        perror("Failed to start Core");
        exit(1);
    }

    logger_pid = fork();

    if (logger_pid == 0)
    {
        execl("./logger", "./logger", NULL);
        perror("Failed to start Logger");
        exit(1);
    }

    printf("UI started. PID = %d\n", ui_pid);
    printf("Core started. PID = %d\n", core_pid);
    printf("Logger started. PID = %d\n", logger_pid);

    waitpid(ui_pid, NULL, 0);
    waitpid(core_pid, NULL, 0);
    waitpid(logger_pid, NULL, 0);

    mq_close(q1);
    mq_close(q2);
    mq_close(q3);

    mq_unlink(UI_TO_CORE);
    mq_unlink(CORE_TO_UI);
    mq_unlink(CORE_TO_LOG);

    printf("\nAll processes stopped.\n");

    return 0;
}
