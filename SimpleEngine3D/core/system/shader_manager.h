#pragma once
#include "../containers/dynamic_array.h"
#include "../graphic/shader.h"
#include "../utilities/string.h"

#define RES_SHADER_PATH "resources/shaders/"

namespace SE3D
{
	struct SHADER_RES
	{
		Shader* m_Shader;
		uint32 m_VertNameID;
		uint32 m_FragNameID;
	};

	class ShaderManager
	{
	private:
		DynamicArray<SHADER_RES> m_Shaders;

		ShaderManager()
		{
		}

	public:
		static ShaderManager& GetInstance()
		{
			static ShaderManager* instance = new ShaderManager();
			return *instance;
		}

		~ShaderManager();

		void Startup()
		{
		}

		void Shutdown()
		{
		}

		Shader* Add(const String& vertexShaderFile, const String& fragmentShaderFile);
		Shader* Get(const String& vertexShaderFile, const String& fragmentShaderFile);
	};
}
