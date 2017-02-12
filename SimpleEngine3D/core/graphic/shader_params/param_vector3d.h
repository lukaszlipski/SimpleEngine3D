#pragma once
#include "shader_parameter.h"
#include "../../math/vector3d.h"

namespace SE3D
{
	class ParamVector3D : public ShaderParameter
	{
	private:
		Vector3D m_Value;
	public:
		ParamVector3D(Vector3D value, uint32 nameID, int32 location)
			: ShaderParameter(nameID, VECTOR3D, location), m_Value(value)
		{
		}

		void Bind() override
		{
			glUniform3f(m_Location, m_Value.x, m_Value.y, m_Value.z);
		}

		inline void SetValue(Vector3D value) { m_Value = value; }
	};
}
