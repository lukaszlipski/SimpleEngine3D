#pragma once
#include "shader.h"
#include "shader_params/shader_parameter.h"

namespace SE3D
{
	struct Matrix4D;

	class Material
	{
	private:
		Shader m_Shader;
		DynamicArray<ShaderParameter*> m_Params;
		// TODO: Add textures
	public:
		Material(const Shader& shader);

		void Bind() const;
		void Unbind() const;

		bool SetParamMatrix4D(uint32 nameID, const Matrix4D& value);
	};
}
