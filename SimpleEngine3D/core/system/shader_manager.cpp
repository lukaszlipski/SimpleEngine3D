#include "shader_manager.h"

namespace SE3D
{
	ShaderManager::~ShaderManager()
	{
		for (uint32 i = 0; i < m_Shaders.Size(); i++)
		{
			delete m_Shaders[i].m_Shader;
		}
	}

	Shader* ShaderManager::Add(const String& vertexShaderFile, const String& fragmentShaderFile)
	{
		Shader* shader = new Shader(RES_SHADER_PATH + vertexShaderFile, RES_SHADER_PATH + fragmentShaderFile);
		if (!shader->IsValid())
		{
			delete shader;
			return nullptr;
		}
		SHADER_RES shaderRes = {shader, String(vertexShaderFile).GetStringID(), String(fragmentShaderFile).GetStringID()};
		m_Shaders.Push(shaderRes);
		return m_Shaders[m_Shaders.Size() - 1].m_Shader;
	}

	Shader* ShaderManager::Get(const String& vertexShaderFile, const String& fragmentShaderFile)
	{
		uint32 vertID = String(vertexShaderFile).GetStringID();
		uint32 fragID = String(fragmentShaderFile).GetStringID();
		for (uint32 i = 0; i < m_Shaders.Size(); i++)
		{
			if (m_Shaders[i].m_VertNameID == vertID && m_Shaders[i].m_FragNameID == fragID)
				return m_Shaders[i].m_Shader;
		}
		return Add(vertexShaderFile, fragmentShaderFile);
	}
}
