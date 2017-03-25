#include "texture_manager.h"

namespace SE3D
{
	TextureManager::~TextureManager()
	{
		for (uint32 i = 0; i < m_Textures.Size(); i++)
		{
			delete m_Textures[i].m_Texture;
		}
	}

	Texture2D* TextureManager::Add(const String& textureFile, bool srgb)
	{
		Texture2D* texture = new Texture2D(RES_TEXTURE_PATH + textureFile,srgb);
		if (!texture->IsValid())
		{
			delete texture;
			return nullptr;
		}
		TEXTURE_RES texRes = {texture, String(textureFile).GetStringID()};
		m_Textures.Push(texRes);
		return m_Textures[m_Textures.Size() - 1].m_Texture;
	}

	Texture2D* TextureManager::Get(const String& textureFile, bool srgb)
	{
		uint32 texID = String(textureFile).GetStringID();
		for (uint32 i = 0; i < m_Textures.Size(); i++)
		{
			if (m_Textures[i].m_TexturePathID == texID)
				return m_Textures[i].m_Texture;
		}
		return Add(textureFile, srgb);
	}
}
