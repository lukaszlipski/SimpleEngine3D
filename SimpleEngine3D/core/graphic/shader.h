#pragma once
#include <GL/glew.h>

namespace SE3D {

	class Shader {

	private:
		GLuint m_Program;
	public:
		Shader(const char* filePathVS, const char* filePathFS);
		void Bind();
		void Unbind();
	};
}