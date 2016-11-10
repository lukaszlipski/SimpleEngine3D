#pragma once
#include <Windows.h>
#include <Gl/glew.h>
#include <GL/wglew.h>



class Win32_Opengl {

private:
	HGLRC m_OpenGLRC;
	HWND m_Hwnd;
	GLubyte m_MajorVersion;
	GLubyte m_MinorVersion;
public:
	bool PlatformInit(HWND hwnd);
	void PlatformUpdate();
	void PlatformSetOpenGlVersion(GLubyte major, GLubyte minor);

	inline void PlatformSetVSync(short vsync)
	{
		wglSwapIntervalEXT(vsync);
	}

	inline void PlatformResize(int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	inline void PlatformClear()
	{
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	~Win32_Opengl();
};