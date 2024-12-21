#ifndef CS_H
#define CS_H

#include <WinSock2.h>

int create_client_socket(char** argv);

int client_connection(SOCKET);

int create_server_socket(char** argv);

int client_handler(SOCKET);

#endif