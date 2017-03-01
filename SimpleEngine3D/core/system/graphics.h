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

		Graphics();

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
		void SetDepthBuffer(bool db);
		void SetClearColor(float r, float g, float b, float a) const;
		void SetVSync(short vsync) const;
		void Resize(int width, int height);
		void Clear() const;
	};
}
