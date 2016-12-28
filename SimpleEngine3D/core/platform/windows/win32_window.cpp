#include "../system/window.h"
#include "../system/graphics.h"

namespace SE3D
{
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	bool Window::m_IsRunning = true;

	bool Window::Startup(const char* title, int width, int height, HINSTANCE hInstance)
	{
		m_FullScreen = false;
		m_VSync = 1;
		m_Width = width;
		m_Height = height;
		WNDCLASSEX WindowClass = {};
		WindowClass.cbSize = sizeof(WNDCLASSEX);
		WindowClass.lpfnWndProc = WindowProc;
		WindowClass.hInstance = hInstance;
		WindowClass.lpszClassName = "randomClassName";
		WindowClass.hCursor = LoadCursor(0, IDC_ARROW);

		if (!RegisterClassExA(&WindowClass))
			return false;

		m_WindowHandle = CreateWindowExA(0, WindowClass.lpszClassName, title, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, hInstance, 0);

		if (!m_WindowHandle)
			return false;

		GetWindowPlacement(m_WindowHandle, &m_WindowPreviousPosition);

		return true;
	}

	void Window::Shutdown() const
	{
		PostQuitMessage(0);
		DestroyWindow(m_WindowHandle);
	}

	void Window::SetFullScreen(bool fullscreen)
	{
		DWORD dwStyle = GetWindowLong(m_WindowHandle, GWL_STYLE);
		m_FullScreen = fullscreen;
		if (fullscreen)
		{
			MONITORINFO mi = {sizeof(mi)};
			if (GetWindowPlacement(m_WindowHandle, &m_WindowPreviousPosition) && GetMonitorInfo(MonitorFromWindow(m_WindowHandle, MONITOR_DEFAULTTOPRIMARY), &mi))
			{
				SetWindowLong(m_WindowHandle, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(m_WindowHandle, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
			}
			Graphics::GetInstance().Resize(mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top);
		}
		else
		{
			SetWindowLong(m_WindowHandle, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX);
			SetWindowPlacement(m_WindowHandle, &m_WindowPreviousPosition);
			SetWindowPos(m_WindowHandle, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
			Graphics::GetInstance().Resize(m_Width, m_Height);
		}
	}

	void Window::SetWindowSize(int width, int height)
	{
		bool wasFS = false;
		if (m_FullScreen)
		{
			SetFullScreen(false);
			wasFS = true;
		}

		SetWindowPos(m_WindowHandle, NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
		GetWindowPlacement(m_WindowHandle, &m_WindowPreviousPosition);
		Graphics::GetInstance().Resize(width, height);

		if (wasFS)
			SetFullScreen(true);
	}

	void Window::SetCursor(bool cursor)
	{
		m_Cursor = cursor;
		(cursor) ? ShowCursor(true) : ShowCursor(false);
	}

	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT result = 0;

		switch (uMsg)
		{
		case WM_DESTROY:
			{
				//PostQuitMessage(0);
				Window::m_IsRunning = false;
				break;
			}
		case WM_CLOSE:
			{
				//DestroyWindow(hwnd);
				Window::m_IsRunning = false;
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
}
