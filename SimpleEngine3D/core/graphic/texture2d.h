#pragma once
#include "../utilities/string.h"

namespace SE3D
{
	class Texture2D
	{
	private:
		uint32 m_TextureID;
		bool m_IsValid;
		uint32 m_Height;
		uint32 m_Width;

	public:
		Texture2D(const String& path, bool srgb = false);
		Texture2D(int width, int height);
		~Texture2D();

		void Bind(uint32 index = 0) const;
		void Unbind() const;

		inline bool IsValid() const { return m_IsValid; }
		inline uint32 GetTextureID() const { return m_TextureID; }
		inline uint32 GetWidth() const { return m_Width; }
		inline uint32 GetHeight() const { return m_Height; }
	};
}
