#pragma once
#include "../containers/dynamic_array.h"
#include "../graphic/texture2d.h"

namespace SE3D
{
	struct TEXTURE_RES
	{
		Texture2D* m_Texture;
		uint32 m_TexturePathID;
	};

	class TextureManager
	{
	private:
		DynamicArray<TEXTURE_RES> m_Textures;

		TextureManager()
		{
		}

	public:
		static TextureManager& GetInstance()
		{
			static TextureManager* instance = new TextureManager();
			return *instance;
		}

		~TextureManager();

		void Startup()
		{
		}

		void Shutdown()
		{
		}

		Texture2D* Add(const String& textureFile);
		Texture2D* Get(const String& textureFile);
	};
}