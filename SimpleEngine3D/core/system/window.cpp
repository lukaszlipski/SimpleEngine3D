#include "window.h"

namespace SE3D {

	void Window::SetVSync(int16 vsync)
	{
		m_VSync = vsync;
		m_GraphicsAPI.PlatformSetVSync(vsync);
	}

}