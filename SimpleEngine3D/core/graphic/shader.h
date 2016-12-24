#pragma once
#include <GL/glew.h>

namespace SE3D {

	class Shader {

	private:
		GLuint m_Program;
	public:
		Shader(const char* filePathVS, const char* filePathFS);
		~Shader();
		void Bind();
		void Unbind();
	};
}