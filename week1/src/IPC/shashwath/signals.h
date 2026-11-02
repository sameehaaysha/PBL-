#ifndef SIGNALS_H
#define SIGNALS_H

#include <sys/types.h>
#include <signal.h>

/*
 * Register handlers for SIGUSR1 and SIGUSR2.
 * The handler only sets a sig_atomic_t flag; do logging in normal code.
 */
int signals_install_handlers(void);

/* Send a user-defined signal to another process. */
int signals_send(pid_t target_pid, int signal_number);

/* Returns SIGUSR1, SIGUSR2, or 0 if no handled signal is pending.
 * Calling this function clears the pending flag.
 */
int signals_take_pending(void);

#endif
