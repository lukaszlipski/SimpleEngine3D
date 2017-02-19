#pragma once
#include "shader_parameter.h"

namespace SE3D
{
	class ParamTexture2D : public ShaderParameter
	{
	private:
		uint32 m_Value;
	public:
		ParamTexture2D(uint32 value, uint32 nameID, int32 location)
			: ShaderParameter(nameID, TEXTURE2D, location), m_Value(value)
		{
		}

		void Bind() override
		{
			glBindTexture(GL_TEXTURE_2D, m_Value);
		}

		inline void SetValue(uint32 value) { m_Value = value; }
	};
}
