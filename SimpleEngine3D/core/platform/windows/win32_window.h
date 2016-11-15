#pragma once
#include <Windows.h>
#include "../opengl/win32_opengl.h"
#include "win32_input.h"

class Win32_Window {

private:
	HWND m_WindowHandle;
	Win32_Opengl m_Win32opengl;
	static bool m_IsRunning;
	bool m_isFullScreen;
	WINDOWPLACEMENT m_WindowPreviousPosition = { sizeof(m_WindowPreviousPosition) };

public:
	bool PlatformInit(const char* title, int width, int height, HINSTANCE hInstance);
	void PlatformProcessInput(Win32_Input& input);
	void PlatformClear();
	void PlatformTerminate();
	void PlatformSetFullscreen(bool fullscreen);
	void PlatformSetWindowSize(int width, int height);
	void PlatformSwapBuffers();
	inline void PlatformSetCursor(bool cursor) { (cursor) ? ShowCursor(true) : ShowCursor(false); }
	inline bool PlatformShouldWindowClose() const {	return !m_IsRunning; }
	inline void PlatformSetVSync(short vsync) {	m_Win32opengl.PlatformSetVSync(vsync); }

	friend LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


};


