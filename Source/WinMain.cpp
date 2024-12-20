#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Winsock2.h>
#include <WS2tcpip.h>
#include <iphlpapi.h>

#include <cstdlib>

int WINAPI wWinMain
(
	[[maybe_unused]] _In_		HINSTANCE	hInstance,
	[[maybe_unused]] _In_opt_	HINSTANCE	hPrevInstance,
	[[maybe_unused]] _In_		PWSTR		pCmdLine,
	[[maybe_unused]] _In_		int			nCmdShow
)
{
	WSADATA		socket_data		= { 0 };
	int			creation_result	= 0;

	creation_result = WSAStartup(MAKEWORD(2,2), &socket_data);
	if (creation_result != 0)
	{
		MessageBox(nullptr, L"WSAStartup: Failed to create socket!", L"SocketTest - Engine Error", MB_ICONERROR | MB_OK);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}