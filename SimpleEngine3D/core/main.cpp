#include <Windows.h>
#include "platform/windows/win32_window.h"
#include "platform/windows/win32_timer.h"
#include "platform/windows/win32_file.h"

#include <stdio.h>

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	Win32_Window win;

	win.PlatformInit("Lukasz Lipski : SimpleEngine3D",1024,720,hInstance);
	Win32_Time timer;
	//void* buffer = Win32_File::PlatformGetFileAPI().PlatformReadFileSync(__FILE__);
	//delete buffer;

	win.PlatformSetCursor(true);
	win.PlatformSetFullscreen(false);
	//win.PlatformSetWindowSize(800, 600);
	
	timer.PlatformInit();
	while (!win.PlatformShouldWindowClose())
	{
		win.PlatformClear();
		win.PlatformProcessInput();

		if (win.PlatformGetMouseButton(0))
			OutputDebugString("!");

		char Buffer[256];
		sprintf_s(Buffer,"TimeElapsed: %f\n",timer.PlatformTimeSEC());
		OutputDebugString(Buffer);

		short x = win.PlatformGetMousePositionX();
		short y = win.PlatformGetMousePositionY();

		win.PlatformSwapBuffers();
		timer.PlatformUpdate();
	}

	win.PlatformTerminate();

	return EXIT_SUCCESS;
}