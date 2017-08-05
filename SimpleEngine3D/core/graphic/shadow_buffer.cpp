#include "shadow_buffer.h"
#include "../system/graphics.h"

namespace SE3D
{

	ShadowBuffer::ShadowBuffer(int32 width, int32 height)
		: m_Width(width), m_Height(height), m_DepthMap(width, height, TextureSettings(ImageFormat::DEPTH_COMPONENT, InternalFormat::DEPTH_COMPONENT, ImageType::FLOAT, TextureFilter::NEAREST, TextureWrap::CLAMP_TO_BORDER, Vector4D(1.0f,1.0f,1.0f,1.0f)))
	{
		glGenFramebuffers(1, &m_ShadowBuffer);		

		glBindFramebuffer(GL_FRAMEBUFFER, m_ShadowBuffer);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthMap.GetTextureID(), 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	ShadowBuffer::~ShadowBuffer()
	{
		glDeleteFramebuffers(1, &m_ShadowBuffer);
	}

	void ShadowBuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_ShadowBuffer);
	}

	void ShadowBuffer::Unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void ShadowBuffer::Clear() const
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}

}