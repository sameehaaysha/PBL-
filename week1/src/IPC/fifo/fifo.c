#define _POSIX_C_SOURCE 200809L

#include "fifo.h"
#include "../../logger.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/* Create a named pipe */
int fifo_create(const char *path, unsigned int permissions)
{
    if (path == NULL || path[0] == '\0') {
        errno = EINVAL;

        logger_send_event(
            MSG_ERROR,
            "FIFO: invalid path"
        );

        return -1;
    }

    if (mkfifo(path, (mode_t)permissions) == -1) {
        if (errno == EEXIST) {
            struct stat info;

            if (stat(path, &info) == 0 &&
                S_ISFIFO(info.st_mode)) {

                logger_send_event(
                    MSG_RESULT,
                    "FIFO: named pipe already exists"
                );

                return 0;
            }
        }

        char message[MAX_TEXT];

        snprintf(
            message,
            sizeof(message),
            "FIFO: creation failed for %s: %s",
            path,
            strerror(errno)
        );

        perror("mkfifo");
        logger_send_event(MSG_ERROR, message);

        return -1;
    }

    logger_send_event(
        MSG_RESULT,
        "FIFO: named pipe created successfully"
    );

    return 0;
}

/* Open a FIFO */
int fifo_open(const char *path, int flags)
{
    if (path == NULL || path[0] == '\0') {
        errno = EINVAL;

        logger_send_event(
            MSG_ERROR,
            "FIFO: invalid path for open"
        );

        return -1;
    }

    int fd;

    do {
        fd = open(path, flags);
    } while (fd == -1 && errno == EINTR);

    if (fd == -1) {
        char message[MAX_TEXT];

        snprintf(
            message,
            sizeof(message),
            "FIFO: open failed for %s: %s",
            path,
            strerror(errno)
        );

        perror("fifo open");
        logger_send_event(MSG_ERROR, message);

        return -1;
    }

    logger_send_event(
        MSG_RESULT,
        "FIFO: named pipe opened successfully"
    );

    return fd;
}

/* Write data to the FIFO */
int fifo_write(int fd, const char *text)
{
    if (fd < 0 || text == NULL) {
        errno = EINVAL;

        logger_send_event(
            MSG_ERROR,
            "FIFO: invalid input to write"
        );

        return -1;
    }

    size_t length = strlen(text);
    size_t total_written = 0;

    while (total_written < length) {
        ssize_t written = write(
            fd,
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
                "FIFO: write failed: %s",
                strerror(errno)
            );

            perror("fifo write");
            logger_send_event(MSG_ERROR, message);

            return -1;
        }

        total_written += (size_t)written;
    }

    logger_send_event(
        MSG_RESULT,
        "FIFO: data written successfully"
    );

    return 0;
}

/* Read data from the FIFO */
int fifo_read(
    int fd,
    char *buffer,
    size_t buffer_size
)
{
    if (fd < 0 || buffer == NULL || buffer_size < 2) {
        errno = EINVAL;

        logger_send_event(
            MSG_ERROR,
            "FIFO: invalid input to read"
        );

        return -1;
    }

    ssize_t bytes_read;

    do {
        bytes_read = read(
            fd,
            buffer,
            buffer_size - 1
        );
    } while (bytes_read == -1 && errno == EINTR);

    if (bytes_read == -1) {
        char message[MAX_TEXT];

        snprintf(
            message,
            sizeof(message),
            "FIFO: read failed: %s",
            strerror(errno)
        );

        perror("fifo read");
        logger_send_event(MSG_ERROR, message);

        return -1;
    }

    buffer[bytes_read] = '\0';

    logger_send_event(
        MSG_RESULT,
        "FIFO: data read successfully"
    );

    return (int)bytes_read;
}

/* Close the FIFO */
int fifo_close(int fd)
{
    if (fd < 0) {
        errno = EINVAL;

        logger_send_event(
            MSG_ERROR,
            "FIFO: invalid file descriptor for close"
        );

        return -1;
    }

    if (close(fd) == -1) {
        char message[MAX_TEXT];

        snprintf(
            message,
            sizeof(message),
            "FIFO: close failed: %s",
            strerror(errno)
        );

        perror("fifo close");
        logger_send_event(MSG_ERROR, message);

        return -1;
    }

    logger_send_event(
        MSG_RESULT,
        "FIFO: file descriptor closed"
    );

    return 0;
}
