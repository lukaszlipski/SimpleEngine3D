//if Windows
#include <Windows.h>

#include "system/window.h"
#include "system/timer.h"
#include "system/file.h"

// debug
#include <stdio.h>

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	Window win;

	win.Init("Lukasz Lipski : SimpleEngine3D",1024,720,hInstance);
	Timer timer;
	//void* buffer = File::GetInstance().ReadSync(__FILE__);
	//delete buffer;

	win.SetCursor(true);
	win.SetFullScreen(false);
	//win.SetWindowSize(800, 600);
	
	timer.Init();
	while (!win.ShouldWindowClose())
	{
		win.Clear();
		win.ProcessInput();

		if (win.GetMouseButton(0))
			OutputDebugString("!");

		char Buffer[256];
		sprintf_s(Buffer,"TimeElapsed: %f\n",timer.TimeSEC());
		OutputDebugString(Buffer);

		short x = win.GetMousePositionX();
		short y = win.GetMousePositionY();

		win.SwapBuffers();
		timer.Update();
	}

	win.Terminate();

	return EXIT_SUCCESS;
}