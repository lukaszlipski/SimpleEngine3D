#pragma once
#include "shader_parameter.h"
#include "../../math/matrix4d.h"

namespace SE3D
{
	class ParamMatrix4D : public ShaderParameter
	{
	private:
		Matrix4D m_Value;
	public:
		ParamMatrix4D(Matrix4D value);
		void Bind() override;
		void SetValue(Matrix4D value);
	};
}
