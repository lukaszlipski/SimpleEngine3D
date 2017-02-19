#pragma once
#include "shader_parameter.h"

namespace SE3D
{
	class ParamInt32 : public ShaderParameter
	{
	private:
		int32 m_Value;
	public:
		ParamInt32(int32 value, uint32 nameID, int32 location)
			: ShaderParameter(nameID, INT32, location), m_Value(value)
		{
		}

		void Bind() override
		{
			glUniform1i(m_Location, m_Value);
		}

		inline void SetValue(int32 value) { m_Value = value; }
	};
}
