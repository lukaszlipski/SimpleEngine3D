#include "../system/graphics.h"
#include "../system/window.h"
#include "win32_opengl_definitions.h"

extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}

extern "C"
{
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;

PFNGLACTIVETEXTUREPROC glActiveTexture;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
PFNGLBLITFRAMEBUFFERPROC glBlitFramebuffer;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLCREATESHADERPROC glCreateShader;
PFNGLDELETEBUFFERSPROC glDeleteBuffers;
PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;
PFNGLDELETEPROGRAMPROC glDeleteProgram;
PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers;
PFNGLDELETESHADERPROC glDeleteShader;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
PFNGLDRAWBUFFERSPROC glDrawBuffers;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer;
PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;
PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
PFNGLGETPROGRAMIVPROC glGetProgramiv;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLUNIFORM1FPROC glUniform1f;
PFNGLUNIFORM1IPROC glUniform1i;
PFNGLUNIFORM1UIPROC glUniform1ui;
PFNGLUNIFORM2FPROC glUniform2f;
PFNGLUNIFORM3FPROC glUniform3f;
PFNGLUNIFORM4FPROC glUniform4f;
PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv;
PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;

void *GetOpenGLFuncPtr(const char *name)
{
	void *p = reinterpret_cast<void*>(wglGetProcAddress(name));
	if (p == 0 || (p == reinterpret_cast<void*>(0x1)) || (p == reinterpret_cast<void*>(0x2)) || (p == reinterpret_cast<void*>(0x3)) || (p == reinterpret_cast<void*>(-1)))
	{
		HMODULE module = LoadLibraryA("opengl32.dll");
		p = reinterpret_cast<void*>(GetProcAddress(module, name));
	}

	return p;
}

namespace SE3D
{
	Graphics::Graphics()
		: m_MajorVersion(3), m_MinorVersion(3)
	{
	}

	bool Graphics::Startup()
	{
		m_ResolutionX = 1024;
		m_ResolutionY = 720;

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

		
		InitAPI();

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
		SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		Resize(Window::GetInstance().GetSizeX(), Window::GetInstance().GetSizeY());
		SetDepthBuffer(true);

		ReleaseDC(Window::GetInstance().GetWindowHandle(), WindowDC);
		glEnable(GL_CULL_FACE);

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

	void Graphics::InitAPI()
	{
		wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(GetOpenGLFuncPtr("wglCreateContextAttribsARB"));
		wglSwapIntervalEXT = reinterpret_cast<PFNWGLSWAPINTERVALEXTPROC>(GetOpenGLFuncPtr("wglSwapIntervalEXT"));

		glGenerateMipmap = reinterpret_cast<PFNGLGENERATEMIPMAPPROC>(GetOpenGLFuncPtr("glGenerateMipmap"));
		glActiveTexture = reinterpret_cast<PFNGLACTIVETEXTUREPROC>(GetOpenGLFuncPtr("glActiveTexture"));
		glGenFramebuffers = reinterpret_cast<PFNGLGENFRAMEBUFFERSPROC>(GetOpenGLFuncPtr("glGenFramebuffers"));
		glBindFramebuffer = reinterpret_cast<PFNGLBINDFRAMEBUFFERPROC>(GetOpenGLFuncPtr("glBindFramebuffer"));
		glFramebufferTexture2D = reinterpret_cast<PFNGLFRAMEBUFFERTEXTURE2DPROC>(GetOpenGLFuncPtr("glFramebufferTexture2D"));
		glDeleteFramebuffers = reinterpret_cast<PFNGLDELETEFRAMEBUFFERSPROC>(GetOpenGLFuncPtr("glDeleteFramebuffers"));
		glCreateShader = reinterpret_cast<PFNGLCREATESHADERPROC>(GetOpenGLFuncPtr("glCreateShader"));
		glShaderSource = reinterpret_cast<PFNGLSHADERSOURCEPROC>(GetOpenGLFuncPtr("glShaderSource"));
		glCompileShader = reinterpret_cast<PFNGLCOMPILESHADERPROC>(GetOpenGLFuncPtr("glCompileShader"));
		glGetShaderiv = reinterpret_cast<PFNGLGETSHADERIVPROC>(GetOpenGLFuncPtr("glGetShaderiv"));
		glGetShaderInfoLog = reinterpret_cast<PFNGLGETSHADERINFOLOGPROC>(GetOpenGLFuncPtr("glGetShaderInfoLog"));
		glCreateProgram = reinterpret_cast<PFNGLCREATEPROGRAMPROC>(GetOpenGLFuncPtr("glCreateProgram"));
		glAttachShader = reinterpret_cast<PFNGLATTACHSHADERPROC>(GetOpenGLFuncPtr("glAttachShader"));
		glLinkProgram = reinterpret_cast<PFNGLLINKPROGRAMPROC>(GetOpenGLFuncPtr("glLinkProgram"));
		glGetProgramInfoLog = reinterpret_cast<PFNGLGETPROGRAMINFOLOGPROC>(GetOpenGLFuncPtr("glGetProgramInfoLog"));
		glDeleteShader = reinterpret_cast<PFNGLDELETESHADERPROC>(GetOpenGLFuncPtr("glDeleteShader"));
		glDeleteProgram = reinterpret_cast<PFNGLDELETEPROGRAMPROC>(GetOpenGLFuncPtr("glDeleteProgram"));
		glUseProgram = reinterpret_cast<PFNGLUSEPROGRAMPROC>(GetOpenGLFuncPtr("glUseProgram"));
		glGetProgramiv = reinterpret_cast<PFNGLGETPROGRAMIVPROC>(GetOpenGLFuncPtr("glGetProgramiv"));
		glGetActiveUniform = reinterpret_cast<PFNGLGETACTIVEUNIFORMPROC>(GetOpenGLFuncPtr("glGetActiveUniform"));
		glGetUniformLocation = reinterpret_cast<PFNGLGETUNIFORMLOCATIONPROC>(GetOpenGLFuncPtr("glGetUniformLocation"));
		glGenVertexArrays = reinterpret_cast<PFNGLGENVERTEXARRAYSPROC>(GetOpenGLFuncPtr("glGenVertexArrays"));
		glGenBuffers = reinterpret_cast<PFNGLGENBUFFERSPROC>(GetOpenGLFuncPtr("glGenBuffers"));
		glBindVertexArray = reinterpret_cast<PFNGLBINDVERTEXARRAYPROC>(GetOpenGLFuncPtr("glBindVertexArray"));
		glBindBuffer = reinterpret_cast<PFNGLBINDBUFFERPROC>(GetOpenGLFuncPtr("glBindBuffer"));
		glBufferData = reinterpret_cast<PFNGLBUFFERDATAPROC>(GetOpenGLFuncPtr("glBufferData"));
		glEnableVertexAttribArray = reinterpret_cast<PFNGLENABLEVERTEXATTRIBARRAYPROC>(GetOpenGLFuncPtr("glEnableVertexAttribArray"));
		glVertexAttribPointer = reinterpret_cast<PFNGLVERTEXATTRIBPOINTERPROC>(GetOpenGLFuncPtr("glVertexAttribPointer"));
		glDeleteBuffers = reinterpret_cast<PFNGLDELETEBUFFERSPROC>(GetOpenGLFuncPtr("glDeleteBuffers"));
		glDeleteVertexArrays = reinterpret_cast<PFNGLDELETEVERTEXARRAYSPROC>(GetOpenGLFuncPtr("glDeleteVertexArrays"));
		glBlitFramebuffer = reinterpret_cast<PFNGLBLITFRAMEBUFFERPROC>(GetOpenGLFuncPtr("glBlitFramebuffer"));
		glUniformMatrix2fv = reinterpret_cast<PFNGLUNIFORMMATRIX2FVPROC>(GetOpenGLFuncPtr("glUniformMatrix2fv"));
		glUniformMatrix3fv = reinterpret_cast<PFNGLUNIFORMMATRIX3FVPROC>(GetOpenGLFuncPtr("glUniformMatrix3fv"));
		glUniformMatrix4fv = reinterpret_cast<PFNGLUNIFORMMATRIX4FVPROC>(GetOpenGLFuncPtr("glUniformMatrix4fv"));
		glUniform1ui = reinterpret_cast<PFNGLUNIFORM1UIPROC>(GetOpenGLFuncPtr("glUniform1ui"));
		glUniform1i = reinterpret_cast<PFNGLUNIFORM1IPROC>(GetOpenGLFuncPtr("glUniform1i"));
		glUniform1f = reinterpret_cast<PFNGLUNIFORM1FPROC>(GetOpenGLFuncPtr("glUniform1f"));
		glUniform2f = reinterpret_cast<PFNGLUNIFORM2FPROC>(GetOpenGLFuncPtr("glUniform2f"));
		glUniform3f = reinterpret_cast<PFNGLUNIFORM3FPROC>(GetOpenGLFuncPtr("glUniform3f"));
		glUniform4f = reinterpret_cast<PFNGLUNIFORM4FPROC>(GetOpenGLFuncPtr("glUniform4f"));
		glGenRenderbuffers = reinterpret_cast<PFNGLGENRENDERBUFFERSPROC>(GetOpenGLFuncPtr("glGenRenderbuffers"));
		glBindRenderbuffer = reinterpret_cast<PFNGLBINDRENDERBUFFERPROC>(GetOpenGLFuncPtr("glBindRenderbuffer"));
		glRenderbufferStorage = reinterpret_cast<PFNGLRENDERBUFFERSTORAGEPROC>(GetOpenGLFuncPtr("glRenderbufferStorage"));
		glFramebufferRenderbuffer = reinterpret_cast<PFNGLFRAMEBUFFERRENDERBUFFERPROC>(GetOpenGLFuncPtr("glFramebufferRenderbuffer"));
		glDrawBuffers = reinterpret_cast<PFNGLDRAWBUFFERSPROC>(GetOpenGLFuncPtr("glDrawBuffers"));
		glDeleteRenderbuffers = reinterpret_cast<PFNGLDELETERENDERBUFFERSPROC>(GetOpenGLFuncPtr("glDeleteRenderbuffers"));
	}

	void Graphics::SetDepthBuffer(bool db)
	{
		if (db)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);
	}

	void Graphics::SetClearColor(float r, float g, float b, float a) const
	{
		glClearColor(r, g, b, a);
	}

	void Graphics::SetVSync(short vsync) const
	{
		wglSwapIntervalEXT(vsync);
	}

	void Graphics::Resize(int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void Graphics::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Graphics::SetFaceCulling(byte value) const
	{
		if(value == 0)
			glCullFace(GL_FRONT);
		else if(value == 1)
			glCullFace(GL_BACK);
		else if(value == 2)
			glCullFace(GL_FRONT_AND_BACK);
	}

	void Graphics::SetFrontFace(bool value) const
	{
		if (value == false)
			glFrontFace(GL_CCW);
		else if (value == true)
			glFrontFace(GL_CW);
	}
}
