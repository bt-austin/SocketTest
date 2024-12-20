#include <Windows.h>

int WINAPI wWinMain
(
	[[maybe_unused]] _In_		HINSTANCE	hInstance, 
	[[maybe_unused]] _In_opt_	HINSTANCE	hPrevInstance, 
	[[maybe_unused]] _In_		PWSTR		pCmdLine, 
	[[maybe_unused]] _In_		int			nCmdShow
)
{
	MessageBox(nullptr, L"Hello, Sailor!", L"SocketTest", MB_ICONINFORMATION | MB_OKCANCEL);
	return 0;
}