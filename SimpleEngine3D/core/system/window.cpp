#include "window.h"


void Window::Init(const char * title, int width, int height, HINSTANCE hInstance)
{
	m_Width = width;
	m_Height = height;
	m_Cursor = true;
	m_FullScreen = false;
	m_Window.PlatformInit(title, width, height, hInstance);
}

void Window::SetCursor(bool cursor)
{
	m_Cursor = cursor;
	m_Window.PlatformSetCursor(cursor);
}

void Window::SetFullScreen(bool fs)
{
	m_FullScreen = fs;
	m_Window.PlatformSetFullscreen(fs);
}

void Window::SetWindowSize(int width, int height)
{
	m_Width = width;
	m_Height = height;
	m_Window.PlatformSetWindowSize(width, height);
}

void Window::ProcessInput()
{
	m_Window.PlatformProcessInput(m_Input);
}

void Window::PlatformSetVSync(short vsync)
{
	m_VSync = vsync;
	m_Window.PlatformSetVSync(vsync);
}
