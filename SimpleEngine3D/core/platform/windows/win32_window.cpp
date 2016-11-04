#include "win32_window.h"
#include <Windows.h>


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


bool Win32_Window::PlatformInit(const char * title, int width, int height, HINSTANCE hInstance)
{

	WNDCLASSEX WindowClass = {};
	WindowClass.cbSize = sizeof(WNDCLASSEX);
	WindowClass.lpfnWndProc = WindowProc;
	WindowClass.hInstance = hInstance;
	WindowClass.lpszClassName = "randomClassName";

	if (!RegisterClassExA(&WindowClass))
		return false;

	m_WindowHandle = CreateWindowExA(0, WindowClass.lpszClassName, title, WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, hInstance, 0);
	
	if (!m_WindowHandle)
		return false;

	m_Win32opengl.PlatformInit(m_WindowHandle);

	return true;
}

void Win32_Window::PlatformUpdate()
{
	MSG Message;
	while (PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
	{
		//if (Message.message == WM_QUIT)
			

		TranslateMessage(&Message);
		DispatchMessageA(&Message);

	}

	m_Win32opengl.PlatformUpdate();
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	switch (uMsg)
	{
	case WM_SIZE:
	{
		RECT ClientRect;
		GetClientRect(hwnd, &ClientRect);
		int Height = ClientRect.bottom - ClientRect.top;
		int Width = ClientRect.right - ClientRect.left;

		//glViewport(0, 0, Width, Height);


		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	case WM_CLOSE:
	{
		DestroyWindow(hwnd);
		break;
	}
	case WM_ACTIVATEAPP:
	{
		break;
	}
	default:
	{
		result = DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	}
	return result;
}