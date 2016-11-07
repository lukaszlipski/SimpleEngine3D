#include "win32_opengl.h"
//#include <gl/GL.h>
#include <Gl/glew.h>
#include <GL/wglew.h>

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


Win32_Opengl::~Win32_Opengl()
{
	HDC WindowDC = GetDC(m_Hwnd);
	wglMakeCurrent(WindowDC, NULL);
	ReleaseDC(m_Hwnd, WindowDC);
}
