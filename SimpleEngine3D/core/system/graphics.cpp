#include "graphics.h"

namespace SE3D
{
	void Graphics::SetOpenGLVersion(GLubyte major, GLubyte minor)
	{
		m_MajorVersion = major;
		m_MinorVersion = minor;
	}

	void Graphics::SetResolution(int32 X, int32 Y)
	{
		m_ResolutionX = X;
		m_ResolutionY = Y;
	}
}
