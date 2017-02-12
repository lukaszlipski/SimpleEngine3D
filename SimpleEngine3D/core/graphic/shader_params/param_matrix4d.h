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
		ParamMatrix4D(Matrix4D value, uint32 nameID, int32 location)
			: ShaderParameter(nameID, MATRIX4D, location), m_Value(value)
		{
		}

		void Bind() override
		{
			glUniformMatrix4fv(m_Location, 1, GL_TRUE, (GLfloat*)m_Value.GetPtr());
		}

		void SetValue(Matrix4D value) { m_Value = value; }
	};
}
