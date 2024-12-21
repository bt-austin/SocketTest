#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Winsock2.h>
#include <WS2tcpip.h>
#include <iphlpapi.h>

#include <cstdio>
#include <cstdlib>

#define DEFAULT_PORT "12862"

// Once accepting a client, send the client to the socket where data can be sent/received
// TODO: change to handle multiple client sockets
int client_handler(SOCKET client_socket) {
#define DEFAULT_BUFLEN 512

	char recvbuf[DEFAULT_BUFLEN];
	int iResult, iSendResult;
	int recvbuflen = DEFAULT_BUFLEN;

	// Receive until the peer shuts down the connection
	do {

		iResult = recv(client_socket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);

			// Echo the buffer back to the sender
			iSendResult = send(client_socket, "You are connected!", iResult, 0);
			if (iSendResult == SOCKET_ERROR) {
				// On failure to send, close socket and cleanup
				printf("send failed: %d\n", WSAGetLastError());
				closesocket(client_socket);
				WSACleanup();
				return 1;
			}
			printf("Bytes sent: %d\n", iSendResult);
		}
		else if (iResult == 0)
			printf("Connection closing...\n");
		else {
			// On failure to receive, close socket and cleanup
			printf("recv failed: %d\n", WSAGetLastError());
			closesocket(client_socket);
			WSACleanup();
			return 1;
		}

	} while (iResult > 0);

	// shutdown the send half of the connection since no more data will be sent
	iResult = shutdown(client_socket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(client_socket);
		WSACleanup();
		return 1;
	}

	// cleanup
	closesocket(client_socket);
	WSACleanup();

	return 0;
}

// Create the server's welcoming socket, and send the connected clients to client handler
// TODO: Change to use multi-threading for multiple clients, currently accepts only one.
int create_server_socket(char** argv)
{
	WSADATA		socket_data = { 0 };
	int			creation_result = 0;

	creation_result = WSAStartup(MAKEWORD(2, 2), &socket_data);
	if (creation_result != 0)
	{
		printf("[Engine Error]: failed to create valid socket!\n");
		return EXIT_FAILURE;
	}

	printf("[Engine]: Socket context created %i\n", creation_result);

	int creation_results = 0;
	struct addrinfo* result = NULL;
	[[maybe_unused]] struct addrinfo* ptr = NULL;
	struct addrinfo hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the local address and port to be used by the server
	creation_results = getaddrinfo(nullptr, DEFAULT_PORT, &hints, &result);
	if (creation_results != 0) {
		printf("getaddrinfo failed: %d\n", creation_results);
		WSACleanup();
		return 1;
	}

	SOCKET ListenSocket = INVALID_SOCKET;

	// Create a SOCKET for the server to listen for client connections

	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	if (ListenSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	creation_results = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (creation_results == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	printf("Listening on port %s\n", DEFAULT_PORT);

	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
		printf("Listen failed with error: %ld\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	// No longer need result info
	freeaddrinfo(result);

	// Temporary Socket for accepting clients
	SOCKET ClientSocket;

	ClientSocket = INVALID_SOCKET;

	// Accept a client socket
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) {
		printf("accept failed: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	// ** NOTICE ** not sure if we want to return at this point 
	// considering we want the listening socket to remain active
	// Curretnly, if the client socket fails or closes, we return 
	// from create_server_socket for testing.

	// Send the client from the welcoming socket to the client handler.
	if (client_handler(ClientSocket) == 1) {
		printf("Failure handling client socket.");
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	else {
		printf("Success closing client socket");
		return 0;
	}

	// ** NOTICE ** if there were multiple clients, we don't want the listening socket to close
}

/*
int main(int argc, char** argv)
{
	WSADATA		socket_data = { 0 };
	int			creation_result = 0;

	creation_result = WSAStartup(MAKEWORD(2, 2), &socket_data);
	if (creation_result != 0)
	{
		printf("[Engine Error]: failed to create valid socket!\n");
		return EXIT_FAILURE;
	}

	printf("[Engine]: Socket context created %i\n", creation_result);

	if (create_server_socket(argv) == 1) {
		printf("Failed to start server or handle client.");
		return EXIT_FAILURE;
	}
	else {
		printf("Shut down successful.");
		return EXIT_SUCCESS;
	}

	// If for some reason the server socket creation was never done, then exit on failure.
	return EXIT_FAILURE;
}
*/