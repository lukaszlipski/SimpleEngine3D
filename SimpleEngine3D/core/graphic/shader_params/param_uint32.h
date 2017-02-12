#pragma once
#include "shader_parameter.h"

namespace SE3D
{
	class ParamUInt32 : public ShaderParameter
	{
	private:
		uint32 m_Value;
	public:
		ParamUInt32(uint32 value, uint32 nameID, int32 location)
			: ShaderParameter(nameID, UINT32, location), m_Value(value)
		{
		}

		void Bind() override
		{
			glUniform1ui(m_Location, m_Value);
		}

		inline void SetValue(uint32 value) { m_Value = value; }
	};
}
