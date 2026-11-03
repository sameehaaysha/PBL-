#ifndef IPC_PIPE_H
#define IPC_PIPE_H

#include <stddef.h>

/* Create an anonymous pipe */
int pipe_create(int pipefd[2]);

/* Write a string into the pipe */
int pipe_write(int write_fd, const char *text);

/* Read data from the pipe */
int pipe_read(int read_fd, char *buffer, size_t buffer_size);

/* Close a pipe descriptor */
int pipe_close(int fd);

#endif