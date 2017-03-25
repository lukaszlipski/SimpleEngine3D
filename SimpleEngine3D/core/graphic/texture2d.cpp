#include "texture2d.h"
#include <GL/glew.h>
#include "../utilities/image.h"

namespace SE3D
{
	Texture2D::Texture2D(const String& path)
	{
		m_IsValid = true;
		Image img(path.CString());
		if (img.GetPixels() == nullptr)
			m_IsValid = false;
		m_Width = img.GetWidth();
		m_Height = img.GetHeight();
		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, img.GetFormat(), img.GetWidth(), img.GetHeight(), 0, img.GetFormat(), GL_UNSIGNED_BYTE, img.GetPixels());
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture2D::Texture2D(int width, int height)
	{
		m_IsValid = true;
		if (width > 0)
			m_Width = width;
		else
			m_IsValid = false;
		if (height > 0)
			m_Height = height;
		else
			m_IsValid = false;

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_TextureID);
	}

	void Texture2D::Bind(uint32 index) const
	{
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}

	void Texture2D::Unbind() const 
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
