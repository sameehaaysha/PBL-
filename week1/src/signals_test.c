#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "IPC/shashwath/signals.h"

int main(void)
{
    if (signals_install_handlers() == -1)
    {
        printf("Handler installation failed!\n");
        return 1;
    }

    printf("Signal handlers installed successfully!\n");

    if (signals_send(getpid(), SIGUSR1) == -1)
        return 1;

    if (signals_take_pending() == SIGUSR1)
        printf("SIGUSR1 received successfully!\n");
    else
        printf("SIGUSR1 test failed!\n");

    if (signals_send(getpid(), SIGUSR2) == -1)
        return 1;

    if (signals_take_pending() == SIGUSR2)
        printf("SIGUSR2 received successfully!\n");
    else
        printf("SIGUSR2 test failed!\n");

    printf("Signals test completed!\n");

    return 0;
}
