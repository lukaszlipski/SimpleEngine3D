#pragma once
#include <Windows.h>
#include <Gl/glew.h>
#include <GL/wglew.h>

namespace SE3D
{
	class Graphics
	{
	private:
		HGLRC m_OpenGLRC;
		GLubyte m_MajorVersion;
		GLubyte m_MinorVersion;

		Graphics()
		{
			m_MajorVersion = 3;
			m_MinorVersion = 3;
		}

	public:
		static Graphics& GetInstance()
		{
			static Graphics* instance = new Graphics();
			return *instance;
		}

		bool Startup();
		void Shutdown() const;
		void Update();
		void SetOpenGLVersion(GLubyte major, GLubyte minor);

		inline void SetVSync(short vsync)
		{
			wglSwapIntervalEXT(vsync);
		}

		inline void Resize(int width, int height) { glViewport(0, 0, width, height); }

		inline void Clear()
		{
			glClearColor(0.4f, 0.7f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
		}
	};
}
