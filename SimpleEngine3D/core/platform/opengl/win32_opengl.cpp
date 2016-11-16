#include "win32_opengl.h"
//#include <gl/GL.h>

namespace SE3D {

	bool Win32_Opengl::PlatformInit(HWND hwnd)
	{
		m_Hwnd = hwnd;

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


		HDC WindowDC = GetDC(hwnd);

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

		PlatformSetVSync(1);
		glViewport(0, 0, 800, 600);

		ReleaseDC(hwnd, WindowDC);

		return true;
	}

	void Win32_Opengl::PlatformUpdate()
	{
		HDC WindowDC = GetDC(m_Hwnd);
		SwapBuffers(WindowDC);
		ReleaseDC(m_Hwnd, WindowDC);
	}

	void Win32_Opengl::PlatformSetOpenGlVersion(GLubyte major, GLubyte minor)
	{
		m_MajorVersion = major;
		m_MinorVersion = minor;
	}

	Win32_Opengl::~Win32_Opengl()
	{
		HDC WindowDC = GetDC(m_Hwnd);
		wglMakeCurrent(WindowDC, NULL);
		wglDeleteContext(m_OpenGLRC);
		ReleaseDC(m_Hwnd, WindowDC);
	}

}