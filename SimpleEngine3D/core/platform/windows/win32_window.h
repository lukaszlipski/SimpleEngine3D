#pragma once
#include <Windows.h>
#include "../opengl/win32_opengl.h"

class Win32_Window {

private:
	HWND m_WindowHandle;
	Win32_Opengl m_Win32opengl;
	static bool m_IsRunning;
	WINDOWPLACEMENT m_WindowPreviousPosition = { sizeof(m_WindowPreviousPosition) };

public:
	bool PlatformInit(const char* title, int width, int height, HINSTANCE hInstance);
	void PlatformUpdate();
	void PlatformClear();
	void PlatformTerminate();
	void PlatformSetFullscreen(bool fullscreen);


	inline void PlatformSetCursor(bool cursor)
	{
		//(cursor) ? SetCursor(LoadCursor(0,IDC_ARROW)) : SetCursor(NULL);
		(cursor) ? ShowCursor(true) : ShowCursor(false);
	}

	inline bool PlatformShouldWindowClose() const
	{
		return !m_IsRunning;
	}

	friend LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


};


