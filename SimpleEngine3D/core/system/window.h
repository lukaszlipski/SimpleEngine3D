#pragma once
#include "../platform/windows/win32_window.h"
#include "../platform/windows/win32_input.h"

class Window {

private:

	Win32_Window m_Window;
	Win32_Input m_Input;

	int m_Width;
	int m_Height;
	short m_VSync;
	bool m_Cursor;
	bool m_FullScreen;

public:
	// Window
	void Init(const char * title, int width, int height, HINSTANCE hInstance);
	void SetCursor(bool cursor);
	void SetFullScreen(bool fs);
	void SetWindowSize(int width, int height);
	void ProcessInput();
	void PlatformSetVSync(short vsync);
	inline bool ShouldWindowClose() { return m_Window.PlatformShouldWindowClose(); }
	inline void Clear() { m_Window.PlatformClear(); }
	inline void SwapBuffers() { m_Window.PlatformSwapBuffers(); }
	inline void Terminate() { m_Window.PlatformTerminate(); }

	// Input
	inline bool GetKey(const char key)	{ return m_Input.getKey(key); }
	/**
	Left mouse button - 0
	Right mouse button - 1
	Middle mouse button - 2
	*/
	inline bool GetMouseButton(const byte mouse) {	return m_Input.getMouseButton(mouse); }
	inline short GetMousePositionX() {	return m_Input.getMousePositionX();	}
	inline short GetMousePositionY() { return m_Input.getMousePositionY(); }

};