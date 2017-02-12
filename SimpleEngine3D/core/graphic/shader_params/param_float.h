#pragma once
#include "shader_parameter.h"

namespace SE3D
{
	class ParamFloat : public ShaderParameter
	{
	private:
		float m_Value;
	public:
		ParamFloat(float value, uint32 nameID, int32 location)
			: ShaderParameter(nameID, FLOAT, location), m_Value(value)
		{
		}

		void Bind() override
		{
			glUniform1f(m_Location, m_Value);
		}

		inline void SetValue(float value) { m_Value = value; }
	};
}
