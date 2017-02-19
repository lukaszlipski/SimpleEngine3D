#include "texture2d.h"
#include <GL/glew.h>
#include "../utilities/image.h"

namespace SE3D
{
	Texture2D::Texture2D(const String& path)
	{
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
		m_IsValid = true;
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_TextureID);
	}
}
