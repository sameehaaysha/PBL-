#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "socket.h"

// Create socket server
int create_server(void)
{
    int server_fd;
    struct sockaddr_un address;

    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);

    if (server_fd < 0)
    {
        perror("Socket creation failed");
        return -1;
    }

    memset(&address, 0, sizeof(address));

    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, SOCKET_PATH);

    unlink(SOCKET_PATH);

    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        perror("Bind failed");
        close(server_fd);
        return -1;
    }

    if (listen(server_fd, 5) < 0)
    {
        perror("Listen failed");
        close(server_fd);
        unlink(SOCKET_PATH);
        return -1;
    }

    printf("Socket server waiting for connection...\n");

    return server_fd;
}

// Connect client to server
int connect_to_server(void)
{
    int client_fd;
    struct sockaddr_un address;

    client_fd = socket(AF_UNIX, SOCK_STREAM, 0);

    if (client_fd < 0)
    {
        perror("Socket creation failed");
        return -1;
    }

    memset(&address, 0, sizeof(address));

    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, SOCKET_PATH);

    if (connect(client_fd, (struct sockaddr *)&address,
                sizeof(address)) < 0)
    {
        perror("Connection failed");
        close(client_fd);
        return -1;
    }

    printf("Connected to socket server!\n");

    return client_fd;
}

// Send message
int send_message(int socket_fd, const char *message)
{
    int result = send(socket_fd, message, strlen(message) + 1, 0);

    if (result < 0)
    {
        perror("Send failed");
        return -1;
    }

    return 0;
}

// Receive message
int receive_message(int socket_fd, char *buffer, int size)
{
    int result = recv(socket_fd, buffer, size - 1, 0);

    if (result <= 0)
    {
        return -1;
    }

    buffer[result] = '\0';

    return result;
}

// Close socket
void close_socket(int socket_fd)
{
    close(socket_fd);
}