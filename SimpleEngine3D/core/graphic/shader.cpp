#include "shader.h"
#include "../system/file.h"

namespace SE3D {

	Shader::Shader(const char * filePathVS, const char * filePathFS)
	{

		FILE vsFile = File::GetInstance().ReadTextSync(filePathVS);
		FILE fsFile = File::GetInstance().ReadTextSync(filePathFS);

		const GLchar* vsSource = (GLchar*)vsFile.Content;
		const GLchar* fsSource = (GLchar*)fsFile.Content;

		GLuint vShader, fShader;
		GLint success;
		GLchar infoLog[512];

		vShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vShader, 1, &vsSource, 0);
		glCompileShader(vShader);
		glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vShader, 512, NULL, infoLog);
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
			glGetShaderInfoLog(fShader, 512, NULL, infoLog);
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
			glGetProgramInfoLog(m_Program, 512, NULL, infoLog);
			// TODO: Add to log
			m_Program = -1;
			File::GetInstance().Delete(vsFile);
			File::GetInstance().Delete(fsFile);
			return;
		}


		glDeleteShader(vShader);
		glDeleteShader(fShader);
		File::GetInstance().Delete(vsFile);
		File::GetInstance().Delete(fsFile);

	}

	void Shader::Bind()
	{
		glUseProgram(m_Program);
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
	}

}