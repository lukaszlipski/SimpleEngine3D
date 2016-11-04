#pragma once
#include <Windows.h>
#include "../opengl/win32_opengl.h"

class Win32_Window {

private:
	HWND m_WindowHandle;
	Win32_Opengl m_Win32opengl;
public:
	bool PlatformInit(const char* title, int width, int height, HINSTANCE hInstance);
	void PlatformUpdate();

};


