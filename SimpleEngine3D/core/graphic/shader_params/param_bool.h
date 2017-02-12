#pragma once
#include "shader_parameter.h"

namespace SE3D
{
	class ParamBool : public ShaderParameter
	{
	private:
		bool m_Value;
	public:
		ParamBool(bool value, uint32 nameID, int32 location)
			: ShaderParameter(nameID, BOOL, location), m_Value(value)
		{
		}

		void Bind() override
		{
			glUniform1i(m_Location, m_Value);
		}

		inline void SetValue(bool value) { m_Value = value; }
	};
}
