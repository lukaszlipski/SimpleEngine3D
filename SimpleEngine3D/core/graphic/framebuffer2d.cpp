#include "framebuffer2d.h"
#include <GL/glew.h>

namespace SE3D
{

	Framebuffer2D::Framebuffer2D(uint32 width, uint32 height, TextureSettings texSettings)
		: m_Width(width), m_Height(height), m_Texture(Texture2D(width,height,texSettings)), m_ClearColor(Vector4D(0.0f,0.0f,0.0f,1.0f))
	{
		glGenFramebuffers(1, &m_FramebufferID);
		glGenRenderbuffers(1, &m_RenderbufferID);

		glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture.GetTextureID(), 0);

		glBindRenderbuffer(GL_RENDERBUFFER, m_RenderbufferID);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderbufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}

	Framebuffer2D::~Framebuffer2D()
	{
		glDeleteRenderbuffers(1, &m_RenderbufferID);
		glDeleteFramebuffers(1, &m_FramebufferID);
	}

	void Framebuffer2D::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);
	}

	void Framebuffer2D::Unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Framebuffer2D::Clear() const
	{
		glClearColor(m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, m_ClearColor.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}
