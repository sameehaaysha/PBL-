#include <stdio.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h>
#include "common.h"

int main()
{
    struct mq_attr attr = {0};
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(Message);

    mqd_t to_core = mq_open(UI_TO_CORE, O_WRONLY);

    if (to_core == (mqd_t)-1)
    {
        perror("UI: mq_open");
        return 1;
    }

    printf("UI started.\n");
    printf("Enter commands for Core.\n");
    printf("Type EXIT to stop.\n");

    while (1)
    {
        Message msg;

        printf("\nCommand: ");
        fgets(msg.text, MAX_TEXT, stdin);

        msg.text[strcspn(msg.text, "\n")] = '\0';

        if (strcmp(msg.text, "EXIT") == 0)
        {
            msg.type = MSG_SHUTDOWN;
            mq_send(to_core, (char *)&msg, sizeof(msg), 0);
            break;
        }

        msg.type = MSG_COMMAND;

        mq_send(to_core, (char *)&msg, sizeof(msg), 0);
    }

    mq_close(to_core);

    printf("UI stopped.\n");

    return 0;
}