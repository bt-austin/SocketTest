#ifndef CS_H
#define CS_H

//
// Avoid including headers within a header!
//
#ifndef _WINSOCK2API_
	typedef unsigned long long int SOCKET;
#endif // !_WINSOCK2API_

#define DEFAULT_PORT		"12862"
#define DEFAULT_BUFLEN		512


//
// CLIENT.CPP
//

int create_client_socket(char** argv);
int client_connection(SOCKET ConnectSocket);

//
// SERVER.CPP
//

int create_server_socket(char** argv);
int client_handler(SOCKET client_socket);

#endif