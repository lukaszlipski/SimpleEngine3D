#pragma once
#include "../utilities/string.h"
#include "../utilities/image.h"

namespace SE3D
{
	enum class TextureFilter : int32
	{
		LINEAR = GL_LINEAR,
		NEAREST = GL_NEAREST
	};

	struct TextureSettings
	{
		ImageFormat m_Format = ImageFormat::RGB;;
		InternalFormat m_InternalFormat = InternalFormat::RGB;
		ImageType m_ImageType = ImageType::UBYTE;
		TextureFilter m_TextureFilter = TextureFilter::LINEAR;
		TextureSettings(ImageFormat format = ImageFormat::RGB, InternalFormat internalFormat = InternalFormat::RGB, ImageType imgType = ImageType::UBYTE, TextureFilter texFilter = TextureFilter::LINEAR)
			: m_Format(format), m_InternalFormat(internalFormat), m_ImageType(imgType) ,m_TextureFilter(texFilter)
		{}
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
		Texture2D(int width, int height, TextureSettings texSettings = TextureSettings());
		~Texture2D();

		void Bind(uint32 index = 0) const;
		void Unbind() const;

		inline bool IsValid() const { return m_IsValid; }
		inline uint32 GetTextureID() const { return m_TextureID; }
		inline uint32 GetWidth() const { return m_Width; }
		inline uint32 GetHeight() const { return m_Height; }
	};
}
