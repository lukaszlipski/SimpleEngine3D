#include "resource_manager.h"

namespace SE3D
{
	Shader* ResourceManager::AddShader(const String& vertexShaderFile, const String& fragmentShaderFile)
	{
		Shader* shader = new Shader(vertexShaderFile.CString(), fragmentShaderFile.CString());
		if (!shader->IsValid())
		{
			delete shader;
			return nullptr;
		}
		SHADER_RES shaderRes = {shader, String(vertexShaderFile).GetStringID(), String(fragmentShaderFile).GetStringID()};
		m_Shaders.Push(shaderRes);
		return m_Shaders[m_Shaders.Size() - 1].m_Shader;
	}

	Shader* ResourceManager::GetShader(const String& vertexShaderFile, const String& fragmentShaderFile)
	{
		uint32 vertID = String(vertexShaderFile).GetStringID();
		uint32 fragID = String(fragmentShaderFile).GetStringID();
		for (uint32 i = 0; i < m_Shaders.Size(); i++)
		{
			if (m_Shaders[i].m_VertNameID == vertID && m_Shaders[i].m_FragNameID == fragID)
				return m_Shaders[i].m_Shader;
		}
		return AddShader(vertexShaderFile, fragmentShaderFile);
	}
}
