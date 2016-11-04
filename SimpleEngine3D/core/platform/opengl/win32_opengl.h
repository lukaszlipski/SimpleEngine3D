#pragma once
#include <Windows.h>

class Win32_Opengl {

private:
	HGLRC m_OpenGLRC;
	HWND m_Hwnd;
public:
	bool PlatformInit(HWND hwnd);
	void PlatformUpdate();
	~Win32_Opengl();
};