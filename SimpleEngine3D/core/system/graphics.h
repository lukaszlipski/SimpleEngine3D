#pragma once
#include <Windows.h>
#include "../utilities/types.h"
#include "../platform/opengl/win32_opengl_definitions.h"

namespace SE3D
{

	class Graphics
	{
	private:
		HGLRC m_OpenGLRC;
		uint8 m_MajorVersion;
		uint8 m_MinorVersion;
		int32 m_ResolutionX;
		int32 m_ResolutionY;

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
		void InitAPI();

		void SetOpenGLVersion(byte major, byte minor);
		void SetDepthBuffer(bool db);
		void SetClearColor(float r, float g, float b, float a) const;
		void SetVSync(short vsync) const;
		void Resize(int width, int height);
		void Clear() const;
		void SetFaceCulling(byte value=0) const;
		void SetFrontFace(bool value=0) const;

		void SetResolution(int32 X, int32 Y);
		inline int32 GetResolutionX() const { return m_ResolutionX; }
		inline int32 GetResolutionY() const { return m_ResolutionY; }

	};
}
