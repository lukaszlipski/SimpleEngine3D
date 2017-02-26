#pragma once
#include "shader_parameter.h"
#include "../../math/matrix3d.h"

namespace SE3D
{
	class ParamMatrix3D : public ShaderParameter
	{
	private:
		Matrix3D m_Value;
	public:
		ParamMatrix3D(Matrix3D value, uint32 nameID, int32 location)
			: ShaderParameter(nameID, MATRIX3D, location), m_Value(value)
		{
		}

		void Bind() override
		{
			glUniformMatrix3fv(m_Location, 1, GL_TRUE, (GLfloat*)m_Value.GetPtr());
		}

		void SetValue(Matrix3D value) { m_Value = value; }
		inline Matrix3D GetValue() const { return m_Value; }
	};
}
