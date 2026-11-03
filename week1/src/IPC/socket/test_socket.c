#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include "../common.h"

#include "socket.h"

int main(int argc, char *argv[])
{
    char buffer[256];

    // SERVER
    if (argc > 1 && strcmp(argv[1], "server") == 0)
    {
        int server_fd = create_server();

        if (server_fd < 0)
            return 1;

        int client_fd = accept(server_fd, NULL, NULL);

        if (client_fd < 0)
        {
            perror("Accept failed");
            close_socket(server_fd);
            unlink(SOCKET_PATH);
            return 1;
        }

        printf("Client connected!\n");

        if (receive_message(client_fd, buffer, sizeof(buffer)) > 0)
        {
            printf("Message received: %s\n", buffer);
        }

        send_message(client_fd, "Hello from Core Server!");

        close_socket(client_fd);
        close_socket(server_fd);
        unlink(SOCKET_PATH);
    }

    // CLIENT
    else if (argc > 1 && strcmp(argv[1], "client") == 0)
    {
        sleep(1);

        int client_fd = connect_to_server();

        if (client_fd < 0)
            return 1;

        send_message(client_fd, "Hello from UI Client!");

        if (receive_message(client_fd, buffer, sizeof(buffer)) > 0)
        {
            printf("Server response: %s\n", buffer);
        }

        close_socket(client_fd);
    }

    else
    {
        printf("Usage:\n");
        printf("./test_socket server\n");
        printf("./test_socket client\n");
    }

    return 0;
}