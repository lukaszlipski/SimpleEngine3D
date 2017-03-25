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
		Framebuffer2D(uint32 width, uint32 height);
		~Framebuffer2D();

		void Bind() const;
		void Unbind() const;
		void Clear() const;
		inline void SetClearColor(Vector4D color) { m_ClearColor = color; }
		inline Texture2D& GetTexture() { return m_Texture; }

	};
}
