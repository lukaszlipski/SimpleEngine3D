#pragma once
#include "../system/file.h"
#include "types.h"
#include <GL/glew.h>

namespace SE3D
{
	enum ImageFormat
	{
		RGB = GL_RGB,
		RGBA = GL_RGBA
	};

	class Image
	{
	private:
		int32 m_Width;
		int32 m_Height;
		ImageFormat m_Format;
		void* m_Pixels;
		FILE m_File;

	public:
		~Image();
		Image(const char* filePath);

		inline int32 GetWidth() const { return m_Width; }
		inline int32 GetHeight() const { return m_Height; }
		inline void* GetPixels() const { return m_Pixels; }
		inline ImageFormat GetFormat() const { return m_Format; }
		void Delete() const;

	private:
		void LoadBMP();
		void LoadBMP8();
	};
}
