#pragma once
#include <GL/glew.h>
#include "../utilities/types.h"

namespace SE3D
{
	class Shader
	{
	private:
		GLuint m_Program;
	public:
		Shader(const char* filePathVS, const char* filePathFS);
		~Shader();
		void Bind() const;
		void Unbind();
		uint32 GetProgram() const { return m_Program; }
	};
}
