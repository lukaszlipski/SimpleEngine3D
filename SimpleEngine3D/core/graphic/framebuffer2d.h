#pragma once
#include "../utilities/types.h"
#include "texture2d.h"
#include "../math/vector4d.h"

namespace SE3D
{
	class Framebuffer2D
	{
	private:
		uint32 m_FramebufferID;
		uint32 m_RenderbufferID;
		uint32 m_Width;
		uint32 m_Height;
		Texture2D m_Texture;
		Vector4D m_ClearColor;

	public:
		Framebuffer2D(uint32 width, uint32 height , TextureSettings texSettings = TextureSettings());
		~Framebuffer2D();

		void Bind() const;
		void Unbind() const;
		void Clear() const;
		inline uint32 GetID() const { return m_FramebufferID; }
		inline void SetClearColor(Vector4D color) { m_ClearColor = color; }
		inline Texture2D& GetTexture() { return m_Texture; }
		inline uint32 GetWidth() const { return m_Width; }
		inline uint32 GetHeight() const { return m_Height; }

	};
}
