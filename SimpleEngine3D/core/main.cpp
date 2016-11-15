#include <Windows.h>
#include "platform/windows/win32_window.h"
#include "platform/windows/win32_timer.h"
#include "platform/windows/win32_file.h"

#include "system/window.h"

#include <stdio.h>

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	Window win;

	win.Init("Lukasz Lipski : SimpleEngine3D",1024,720,hInstance);
	Win32_Timer timer;
	//void* buffer = Win32_File::PlatformGetFileAPI().PlatformReadFileSync(__FILE__);
	//delete buffer;

	win.SetCursor(true);
	win.SetFullScreen(false);
	//win.SetWindowSize(800, 600);
	
	timer.PlatformInit();
	while (!win.ShouldWindowClose())
	{
		win.Clear();
		win.ProcessInput();

		if (win.GetMouseButton(0))
			OutputDebugString("!");

		char Buffer[256];
		sprintf_s(Buffer,"TimeElapsed: %f\n",timer.PlatformTimeSEC());
		OutputDebugString(Buffer);

		short x = win.GetMousePositionX();
		short y = win.GetMousePositionY();

		win.SwapBuffers();
		timer.PlatformUpdate();
	}

	win.Terminate();

	return EXIT_SUCCESS;
}