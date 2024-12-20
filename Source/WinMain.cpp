#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Winsock2.h>
#include <WS2tcpip.h>
#include <iphlpapi.h>

#include <cstdio>
#include <cstdlib>

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
	return EXIT_SUCCESS;
}