#include "../system/graphics.h"
#include "../system/window.h"

namespace SE3D
{
	bool Graphics::Startup()
	{
		PIXELFORMATDESCRIPTOR DesiredPixelFormat = {};
		DesiredPixelFormat.nSize = sizeof(DesiredPixelFormat);
		DesiredPixelFormat.nVersion = 1;
		DesiredPixelFormat.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		DesiredPixelFormat.iPixelType = PFD_TYPE_RGBA;
		DesiredPixelFormat.cColorBits = 32;
		DesiredPixelFormat.cStencilBits = 8;
		DesiredPixelFormat.cDepthBits = 24;
		DesiredPixelFormat.cAlphaBits = 8;
		DesiredPixelFormat.iLayerType = PFD_MAIN_PLANE;


		HDC WindowDC = GetDC(Window::GetInstance().GetWindowHandle());

		int SuggestedPixelFormatIndex = ChoosePixelFormat(WindowDC, &DesiredPixelFormat);
		PIXELFORMATDESCRIPTOR SuggestedPixelFormat = {};
		DescribePixelFormat(WindowDC, SuggestedPixelFormatIndex, sizeof(SuggestedPixelFormat), &SuggestedPixelFormat);
		SetPixelFormat(WindowDC, SuggestedPixelFormatIndex, &SuggestedPixelFormat);

		m_OpenGLRC = wglCreateContext(WindowDC);
		if (!wglMakeCurrent(WindowDC, m_OpenGLRC))
			return false;

		if (glewInit() != GLEW_OK)
			return false;


		int attrib[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, m_MajorVersion,
			WGL_CONTEXT_MINOR_VERSION_ARB, m_MinorVersion,
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB
#ifdef _DEBUG
			| WGL_CONTEXT_DEBUG_BIT_ARB
#endif // _DEBUG
			,WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
		};

		HGLRC newOpenGLC = wglCreateContextAttribsARB(WindowDC, 0, attrib);
		if (newOpenGLC)
		{
			wglDeleteContext(m_OpenGLRC);
			m_OpenGLRC = newOpenGLC;
			wglMakeCurrent(WindowDC, newOpenGLC);
		}
		else
			return false;

		SetVSync(1);
		glViewport(0, 0, Window::GetInstance().GetSizeX(), Window::GetInstance().GetSizeY());
		glEnable(GL_DEPTH_TEST);

		ReleaseDC(Window::GetInstance().GetWindowHandle(), WindowDC);

		return true;
	}

	void Graphics::Update()
	{
		HDC WindowDC = GetDC(Window::GetInstance().GetWindowHandle());
		SwapBuffers(WindowDC);
		ReleaseDC(Window::GetInstance().GetWindowHandle(), WindowDC);
	}

	void Graphics::Shutdown() const
	{
		HDC WindowDC = GetDC(Window::GetInstance().GetWindowHandle());
		wglMakeCurrent(WindowDC, 0);
		wglDeleteContext(m_OpenGLRC);
		ReleaseDC(Window::GetInstance().GetWindowHandle(), WindowDC);
	}

	void Graphics::SetDepthBuffer(bool db)
	{
		if (db)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);
	}
}
