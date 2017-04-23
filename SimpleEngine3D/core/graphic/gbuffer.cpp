#include "gbuffer.h"
#include "../system/graphics.h"

namespace SE3D
{
	GBuffer::GBuffer()
		:	m_Width(Graphics::GetInstance().GetResolutionX()), m_Height(Graphics::GetInstance().GetResolutionY()), 
			m_Position(Texture2D(m_Width, m_Height, TextureSettings{ ImageFormat::RGB,InternalFormat::RGB32F, ImageType::FLOAT, TextureFilter::NEAREST })), 
			m_Normal(Texture2D(m_Width, m_Height, TextureSettings{ ImageFormat::RGB, InternalFormat::RGB32F, ImageType::FLOAT, TextureFilter::NEAREST })), 
			m_Albedo(Texture2D(m_Width, m_Height, TextureSettings{ ImageFormat::RGB, InternalFormat::RGB, ImageType::UBYTE, TextureFilter::NEAREST })),
			m_MetallicRoughnessAO(Texture2D(m_Width, m_Height, TextureSettings{ ImageFormat::RGB, InternalFormat::RGB, ImageType::UBYTE, TextureFilter::NEAREST }))
	{
		
		glGenFramebuffers(1, &m_GBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, m_GBuffer);

		glGenRenderbuffers(1, &m_DepthStencil);
		glBindRenderbuffer(GL_RENDERBUFFER, m_DepthStencil);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_DepthStencil);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Position.GetTextureID(), 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_Normal.GetTextureID(), 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, m_Albedo.GetTextureID(), 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, m_MetallicRoughnessAO.GetTextureID(), 0);
		uint32 attachments[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
		glDrawBuffers(4, attachments);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}

	GBuffer::~GBuffer()
	{
		glDeleteRenderbuffers(1, &m_DepthStencil);
		glDeleteFramebuffers(1, &m_GBuffer);
	}

	void GBuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_GBuffer);
	}

	void GBuffer::Unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void GBuffer::Clear()
	{
		glClearColor(m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, m_ClearColor.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}
