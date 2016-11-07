#include <Windows.h>
#include "platform/windows/win32_window.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	Win32_Window win;
	win.PlatformInit("Lukasz Lipski : SimpleEngine3D",1024,720,hInstance);

	win.PlatformSetCursor(true);
	win.PlatformSetFullscreen(false);
	//win.PlatformSetWindowSize(800, 600);
	
	while (!win.PlatformShouldWindowClose())
	{
		win.PlatformClear();


		win.PlatformUpdate();
	}

	win.PlatformTerminate();

	return EXIT_SUCCESS;
}