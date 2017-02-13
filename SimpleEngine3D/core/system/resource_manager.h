#pragma once
#include "../containers/dynamic_array.h"
#include "../graphic/shader.h"
#include "../utilities/string.h"

namespace SE3D
{
	struct SHADER_RES
	{
		Shader* m_Shader;
		uint32 m_VertNameID;
		uint32 m_FragNameID;
	};

	class ResourceManager
	{
	private:
		DynamicArray<SHADER_RES> m_Shaders;

		ResourceManager()
		{
		}

	public:
		static ResourceManager& GetInstance()
		{
			static ResourceManager* instance = new ResourceManager();
			return *instance;
		}

		~ResourceManager();

		void Startup()
		{
		}

		void Shutdown()
		{
		}

		Shader* AddShader(const String& vertexShaderFile, const String& fragmentShaderFile);
		Shader* GetShader(const String& vertexShaderFile, const String& fragmentShaderFile);
	};
}
