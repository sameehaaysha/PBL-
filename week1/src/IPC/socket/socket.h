#ifndef SOCKET_H
#define SOCKET_H
#include "../common.h"

#define SOCKET_PATH "/tmp/core_simulator.sock"

int create_server(void);
int connect_to_server(void);

int send_message(int socket_fd, const char *message);
int receive_message(int socket_fd, char *buffer, int size);

void close_socket(int socket_fd);

#endif