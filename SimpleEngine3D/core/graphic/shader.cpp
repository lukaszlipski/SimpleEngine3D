#include "shader.h"
#include "../system/file.h"
#include "../utilities/string.h"
#include <winerror.h>

namespace SE3D
{
	Shader::Shader(const char* filePathVS, const char* filePathFS)
	{
		FILE vsFile = File::GetInstance().ReadTextSync(filePathVS);
		FILE fsFile = File::GetInstance().ReadTextSync(filePathFS);

		const GLchar* vsSource = static_cast<GLchar*>(vsFile.Content);
		const GLchar* fsSource = static_cast<GLchar*>(fsFile.Content);

		GLuint vShader, fShader;
		GLint success;
		GLchar infoLog[512];

		vShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vShader, 1, &vsSource, 0);
		glCompileShader(vShader);
		glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vShader, 512, 0, infoLog);
			// TODO: Add to log
			m_Program = -1;
			File::GetInstance().Delete(vsFile);
			File::GetInstance().Delete(fsFile);
			return;
		}

		fShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fShader, 1, &fsSource, 0);
		glCompileShader(fShader);
		if (!success)
		{
			glGetShaderInfoLog(fShader, 512, 0, infoLog);
			// TODO: Add to log
			m_Program = -1;
			File::GetInstance().Delete(vsFile);
			File::GetInstance().Delete(fsFile);
			return;
		}


		m_Program = glCreateProgram();
		glAttachShader(m_Program, vShader);
		glAttachShader(m_Program, fShader);
		glLinkProgram(m_Program);
		if (!success)
		{
			glGetProgramInfoLog(m_Program, 512, 0, infoLog);
			// TODO: Add to log
			m_Program = -1;
			File::GetInstance().Delete(vsFile);
			File::GetInstance().Delete(fsFile);
			return;
		}

		EnableAllAttributes();
		GetAllUniforms();

		glDeleteShader(vShader);
		glDeleteShader(fShader);
		File::GetInstance().Delete(vsFile);
		File::GetInstance().Delete(fsFile);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_Program);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_Program);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	bool Shader::CheckParam(uint32 paramID, ParamType type) const
	{
		bool result = false;
		for(uint32 i=0;i<m_Uniforms.Size();i++)
		{
			if (m_Uniforms[i].m_ParamID == paramID && m_Uniforms[i].m_Type == type)
				result = true;
		}
		return result;
	}

	void Shader::EnableAllAttributes() const
	{
		GLint count;
		glGetProgramiv(m_Program, GL_ACTIVE_ATTRIBUTES, &count);
		for (int32 i = 0; i < count; i++)
		{
			glEnableVertexAttribArray(0);
		}
	}

	void Shader::GetAllUniforms()
	{
		GLint count;
		GLchar name[256];
		GLenum type;
		glGetProgramiv(m_Program, GL_ACTIVE_UNIFORMS, &count);
		for(int32 i=0;i<count;i++)
		{
			glGetActiveUniform(m_Program, i, 256, nullptr, nullptr, &type, name);
			String strName(name);
			m_Uniforms.Push(ShaderParam{strName.GetStringID(),ParamType(type)});
		}
	}
}
