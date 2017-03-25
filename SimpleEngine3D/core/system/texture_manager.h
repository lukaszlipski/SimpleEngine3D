#pragma once
#include "../containers/dynamic_array.h"
#include "../graphic/texture2d.h"

#define RES_TEXTURE_PATH "resources/textures/"

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

		Texture2D* Add(const String& textureFile, bool srgb = false);
		Texture2D* Get(const String& textureFile, bool srgb = false);
	};
}
