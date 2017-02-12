#pragma once
#include "shader_parameter.h"
#include "../../math/vector4d.h"

namespace SE3D
{
	class ParamVector4D : public ShaderParameter
	{
	private:
		Vector4D m_Value;
	public:
		ParamVector4D(Vector4D value, uint32 nameID, int32 location)
			: ShaderParameter(nameID, VECTOR4D, location), m_Value(value)
		{
		}

		void Bind() override
		{
			glUniform4f(m_Location, m_Value.x, m_Value.y, m_Value.z, m_Value.w);
		}

		inline void SetValue(Vector4D value) { m_Value = value; }
	};
}
