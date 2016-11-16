#pragma once
//if Windows
#include "../platform/windows/win32_input.h"
#include "../platform/opengl/win32_opengl.h"

class Window {

private:

	//if Windows
	Win32_Input m_Input;
	Win32_Opengl m_GraphicsAPI;
	WINDOWPLACEMENT m_WindowPreviousPosition = { sizeof(m_WindowPreviousPosition) };
	HWND m_WindowHandle;

	int m_Width;
	int m_Height;
	short m_VSync;
	bool m_Cursor;
	bool m_FullScreen;
	static bool m_IsRunning;

public:
	// Window
	bool Init(const char * title, int width, int height, HINSTANCE hInstance);
	void SetCursor(bool cursor);
	void SetFullScreen(bool fs);
	void SetWindowSize(int width, int height);
	void ProcessInput();
	void Terminate();
	inline bool ShouldWindowClose() { return !m_IsRunning; }
private:
	friend LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
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


	// Graphics
	void SetVSync(short vsync);
	inline void Clear() { m_GraphicsAPI.PlatformClear(); }
	inline void SwapBuffers() { m_GraphicsAPI.PlatformUpdate(); }

};