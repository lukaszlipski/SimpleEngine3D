#include "win32_window.h"
#include <Windows.h>


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
bool Win32_Window::m_IsRunning = true;

bool Win32_Window::PlatformInit(const char * title, int width, int height, HINSTANCE hInstance)
{
	m_isFullScreen = false;

	WNDCLASSEX WindowClass = {};
	WindowClass.cbSize = sizeof(WNDCLASSEX);
	WindowClass.lpfnWndProc = WindowProc;
	WindowClass.hInstance = hInstance;
	WindowClass.lpszClassName = "randomClassName";
	WindowClass.hCursor = LoadCursor(0, IDC_ARROW);

	if (!RegisterClassExA(&WindowClass))
		return false;

	m_WindowHandle = CreateWindowExA(0, WindowClass.lpszClassName, title, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, hInstance, 0);
	
	if (!m_WindowHandle)
		return false;

	GetWindowPlacement(m_WindowHandle, &m_WindowPreviousPosition);

	// TODO: function for choosing version number & choosing opengl
	m_Win32opengl.PlatformSetOpenGlVersion(3, 3);
	m_Win32opengl.PlatformInit(m_WindowHandle);

	return true;
}

void Win32_Window::PlatformProcessInput(Win32_Input& input)
{
	MSG Message;
	while (PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
	{
		if (Message.message == WM_QUIT)
			m_IsRunning = false;
		
		input.ProcessInput(Message);


		TranslateMessage(&Message);
		DispatchMessageA(&Message);

	}
}

void Win32_Window::PlatformClear()
{
	m_Win32opengl.PlatformClear();
}

void Win32_Window::PlatformTerminate()
{
	PostQuitMessage(0);
	DestroyWindow(m_WindowHandle);
}

void Win32_Window::PlatformSetFullscreen(bool fullscreen)
{
	DWORD dwStyle = GetWindowLong(m_WindowHandle, GWL_STYLE);
	m_isFullScreen = fullscreen;
	if(fullscreen)
	{
		MONITORINFO mi = { sizeof(mi) };
		if (GetWindowPlacement(m_WindowHandle, &m_WindowPreviousPosition) && GetMonitorInfo(MonitorFromWindow(m_WindowHandle, MONITOR_DEFAULTTOPRIMARY), &mi))
		{
			SetWindowLong(m_WindowHandle, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
			SetWindowPos(m_WindowHandle, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left,	mi.rcMonitor.bottom - mi.rcMonitor.top,	SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
		}
	}
	else 
	{
		SetWindowLong(m_WindowHandle, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME);
		SetWindowPlacement(m_WindowHandle, &m_WindowPreviousPosition);
		SetWindowPos(m_WindowHandle, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER |	SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
	}
}

void Win32_Window::PlatformSetWindowSize(int width, int height)
{
	bool wasFS = false;
	if (m_isFullScreen)
	{
		PlatformSetFullscreen(false);
		wasFS = true;
	}

	SetWindowPos(m_WindowHandle, NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
	GetWindowPlacement(m_WindowHandle, &m_WindowPreviousPosition);
	m_Win32opengl.PlatformResize(width, height);

	if (wasFS)
		PlatformSetFullscreen(true);
}

void Win32_Window::PlatformSwapBuffers()
{
	m_Win32opengl.PlatformUpdate();
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	switch (uMsg)
	{
	//case WM_SIZE:
	//{
	//	RECT ClientRect;
	//	GetClientRect(hwnd, &ClientRect);
	//	int Height = ClientRect.bottom - ClientRect.top;
	//	int Width = ClientRect.right - ClientRect.left;

	//	// TODO: Add DirectX
	//	Win32_Opengl::PlatformResize(Width, Height);
	//	
	//	break;
	//}
	case WM_DESTROY:
	{
		//PostQuitMessage(0);
		Win32_Window::m_IsRunning = false;
		break;
	}
	case WM_CLOSE:
	{
		//DestroyWindow(hwnd);
		Win32_Window::m_IsRunning = false;
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