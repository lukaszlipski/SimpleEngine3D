#include "window.h"

namespace SE3D {

	void Window::SetVSync(short vsync)
	{
		m_VSync = vsync;
		m_GraphicsAPI.PlatformSetVSync(vsync);
	}

}