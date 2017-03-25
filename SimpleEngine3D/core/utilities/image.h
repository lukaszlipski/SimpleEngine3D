#pragma once
#include "../system/file.h"
#include "types.h"
#include <GL/glew.h>

namespace SE3D
{
	enum class ImageFormat : int32
	{
		RGB = GL_RGB,
		RGBA = GL_RGBA
	};

	enum class ColorSpaceFormat : int32
	{
		RGB = GL_RGB,
		RGBA = GL_RGBA,
		sRGB = GL_SRGB,
		sRGBA = GL_SRGB_ALPHA
	};

	class Image
	{
	private:
		int32 m_Width;
		int32 m_Height;
		ImageFormat m_Format;
		ColorSpaceFormat m_ColorSpaceFormat;
		void* m_Pixels;
		FILE m_File;
		int32 m_Bytes;

	public:
		~Image();
		Image(const char* filePath, bool srgb = false);

		inline int32 GetWidth() const { return m_Width; }
		inline int32 GetHeight() const { return m_Height; }
		inline void* GetPixels() const { return m_Pixels; }
		inline ImageFormat GetFormat() const { return m_Format; }
		inline ColorSpaceFormat GetColorSpaceFormat() const { return m_ColorSpaceFormat; }
		void Delete() const;

	private:
		void LoadBMP();
		void FlipX() const;
	};
}
