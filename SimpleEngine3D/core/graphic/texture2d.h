#pragma once
#include "../utilities/string.h"
#include "../utilities/image.h"

namespace SE3D
{
	enum class ImageType
	{
		FLOAT = GL_FLOAT,
		UBYTE = GL_UNSIGNED_BYTE
	};
	enum class ImageFilter
	{
		LINEAR = GL_LINEAR,
		NEAREST = GL_NEAREST
	};

	class Texture2D
	{
	private:
		uint32 m_TextureID;
		bool m_IsValid;
		uint32 m_Height;
		uint32 m_Width;

	public:
		Texture2D(const String& path, bool srgb = false);
		Texture2D(int width, int height, ImageFormat format = ImageFormat::RGB, ImageType it=ImageType::UBYTE, ImageFilter imgF = ImageFilter::LINEAR);
		~Texture2D();

		void Bind(uint32 index = 0) const;
		void Unbind() const;

		inline bool IsValid() const { return m_IsValid; }
		inline uint32 GetTextureID() const { return m_TextureID; }
		inline uint32 GetWidth() const { return m_Width; }
		inline uint32 GetHeight() const { return m_Height; }
	};
}
