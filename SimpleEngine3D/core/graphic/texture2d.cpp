#include "texture2d.h"
#include <GL/glew.h>
#include "../utilities/image.h"

namespace SE3D
{
	Texture2D::Texture2D(const String& path, bool srgb)
	{
		m_IsValid = true;
		Image img(path.CString(),srgb);
		if (img.GetPixels() == nullptr)
			m_IsValid = false;
		m_Width = img.GetWidth();
		m_Height = img.GetHeight();
		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, static_cast<int32>(img.GetInternalFormat()), img.GetWidth(), img.GetHeight(), 0, static_cast<int32>(img.GetFormat()), GL_UNSIGNED_BYTE, img.GetPixels());
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture2D::Texture2D(int width, int height, TextureSettings texSettings)
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
		glTexImage2D(GL_TEXTURE_2D, 0, static_cast<int32>(texSettings.m_InternalFormat) ,m_Width, m_Height, 0, static_cast<int32>(texSettings.m_Format), static_cast<int32>(texSettings.m_ImageType), 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<int32>(texSettings.m_TextureFilter));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<int32>(texSettings.m_TextureFilter));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<int32>(texSettings.m_TextureWrap));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<int32>(texSettings.m_TextureWrap));
		//float borderCol[] = { texSettings.m_BorderColor.x,texSettings.m_BorderColor.y,texSettings.m_BorderColor.z,texSettings.m_BorderColor.w };
		float borderCol[] = { 1,1,1,1 };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderCol);
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
