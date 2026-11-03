#define _POSIX_C_SOURCE 200809L

#include "pipe.h"
#include "../../logger.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* Create an anonymous pipe */
int pipe_create(int pipefd[2])
{
    if (pipefd == NULL) {
        errno = EINVAL;
        logger_send_event(
            MSG_ERROR,
            "Pipe: invalid file descriptor array"
        );
        return -1;
    }

    if (pipe(pipefd) == -1) {
        char message[MAX_TEXT];

        snprintf(
            message,
            sizeof(message),
            "Pipe: creation failed: %s",
            strerror(errno)
        );

        perror("pipe");
        logger_send_event(MSG_ERROR, message);

        return -1;
    }

    logger_send_event(
        MSG_RESULT,
        "Pipe: anonymous pipe created successfully"
    );

    return 0;
}

/* Write a string into the pipe */
int pipe_write(int write_fd, const char *text)
{
    if (write_fd < 0 || text == NULL) {
        errno = EINVAL;

        logger_send_event(
            MSG_ERROR,
            "Pipe: invalid input to write"
        );

        return -1;
    }

    size_t length = strlen(text);
    size_t total_written = 0;

    while (total_written < length) {
        ssize_t written = write(
            write_fd,
            text + total_written,
            length - total_written
        );

        if (written == -1) {
            if (errno == EINTR)
                continue;

            char message[MAX_TEXT];

            snprintf(
                message,
                sizeof(message),
                "Pipe: write failed: %s",
                strerror(errno)
            );

            perror("pipe write");
            logger_send_event(MSG_ERROR, message);

            return -1;
        }

        total_written += (size_t)written;
    }

    logger_send_event(
        MSG_RESULT,
        "Pipe: data written successfully"
    );

    return 0;
}

/* Read data from the pipe */
int pipe_read(
    int read_fd,
    char *buffer,
    size_t buffer_size
)
{
    if (read_fd < 0 || buffer == NULL || buffer_size < 2) {
        errno = EINVAL;

        logger_send_event(
            MSG_ERROR,
            "Pipe: invalid input to read"
        );

        return -1;
    }

    ssize_t bytes_read;

    do {
        bytes_read = read(
            read_fd,
            buffer,
            buffer_size - 1
        );
    } while (bytes_read == -1 && errno == EINTR);

    if (bytes_read == -1) {
        char message[MAX_TEXT];

        snprintf(
            message,
            sizeof(message),
            "Pipe: read failed: %s",
            strerror(errno)
        );

        perror("pipe read");
        logger_send_event(MSG_ERROR, message);

        return -1;
    }

    buffer[bytes_read] = '\0';

    logger_send_event(
        MSG_RESULT,
        "Pipe: data read successfully"
    );

    return (int)bytes_read;
}

/* Close a pipe descriptor */
int pipe_close(int fd)
{
    if (fd < 0) {
        errno = EINVAL;

        logger_send_event(
            MSG_ERROR,
            "Pipe: invalid file descriptor for close"
        );

        return -1;
    }

    if (close(fd) == -1) {
        char message[MAX_TEXT];

        snprintf(
            message,
            sizeof(message),
            "Pipe: close failed: %s",
            strerror(errno)
        );

        perror("pipe close");
        logger_send_event(MSG_ERROR, message);

        return -1;
    }

    logger_send_event(
        MSG_RESULT,
        "Pipe: file descriptor closed"
    );

    return 0;
}