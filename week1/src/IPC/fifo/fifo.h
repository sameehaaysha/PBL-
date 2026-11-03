#ifndef IPC_FIFO_H
#define IPC_FIFO_H

#include <stddef.h>

/* Create a named pipe */
int fifo_create(const char *path, unsigned int permissions);

/* Open the FIFO */
int fifo_open(const char *path, int flags);

/* Write data to the FIFO */
int fifo_write(int fd, const char *text);

/* Read data from the FIFO */
int fifo_read(int fd, char *buffer, size_t buffer_size);

/* Close the FIFO */
int fifo_close(int fd);

#endif