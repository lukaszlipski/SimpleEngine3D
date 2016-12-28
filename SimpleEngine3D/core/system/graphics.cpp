#include "graphics.h"

namespace SE3D
{
	void Graphics::SetOpenGLVersion(GLubyte major, GLubyte minor)
	{
		m_MajorVersion = major;
		m_MinorVersion = minor;
	}
}
