#include <Windows.h>
#include "platform/windows/win32_window.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	Win32_Window win;
	win.PlatformInit("test",800,600,hInstance);
	while (true)
		win.PlatformUpdate();

	return EXIT_SUCCESS;
}