#define _POSIX_C_SOURCE 200809L
#include "signals.h"
#include "../../logger.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static volatile sig_atomic_t pending_signal = 0;

static void ipc_signal_handler(int signal_number)
{
    /* Only async-signal-safe work here. No printf, malloc, or file I/O. */
    pending_signal = signal_number;
}

int signals_install_handlers(void)
{
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = ipc_signal_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    if (sigaction(SIGUSR1, &action, NULL) == -1) {
        perror("sigaction(SIGUSR1)");
        logger_send_event(MSG_ERROR, "Signals: failed to install SIGUSR1 handler");
        return -1;
    }

    if (sigaction(SIGUSR2, &action, NULL) == -1) {
        perror("sigaction(SIGUSR2)");
        logger_send_event(MSG_ERROR, "Signals: failed to install SIGUSR2 handler");
        return -1;
    }

    logger_send_event(MSG_RESULT, "Signals: SIGUSR1 and SIGUSR2 handlers installed");
    return 0;
}

int signals_send(pid_t target_pid, int signal_number)
{
    if (target_pid <= 0 ||
        (signal_number != SIGUSR1 && signal_number != SIGUSR2)) {
        errno = EINVAL;
        logger_send_event(MSG_ERROR, "Signals: invalid PID or unsupported signal");
        return -1;
    }

    if (kill(target_pid, signal_number) == -1) {
        char text[MAX_TEXT];
        snprintf(text, sizeof(text), "Signals: failed to send signal %d to PID %ld: %s",
                 signal_number, (long)target_pid, strerror(errno));
        perror("kill");
        logger_send_event(MSG_ERROR, text);
        return -1;
    }

    char text[MAX_TEXT];
    snprintf(text, sizeof(text), "Signals: sent signal %d to PID %ld",
             signal_number, (long)target_pid);
    logger_send_event(MSG_RESULT, text);
    return 0;
}

int signals_take_pending(void)
{
    sig_atomic_t signal_number = pending_signal;
    pending_signal = 0;

    if (signal_number == SIGUSR1) {
        logger_send_event(MSG_RESULT, "Signals: SIGUSR1 notification received");
        return SIGUSR1;
    }
    if (signal_number == SIGUSR2) {
        logger_send_event(MSG_RESULT, "Signals: SIGUSR2 notification received");
        return SIGUSR2;
    }
    return 0;
}
