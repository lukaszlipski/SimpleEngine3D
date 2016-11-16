#include "window.h"

void Window::SetVSync(short vsync) 
{ 
	m_VSync = vsync;
	m_GraphicsAPI.PlatformSetVSync(vsync); 
}