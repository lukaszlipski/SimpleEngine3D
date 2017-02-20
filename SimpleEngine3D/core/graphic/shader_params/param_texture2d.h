#pragma once
#include "shader_parameter.h"

namespace SE3D
{
	class ParamTexture2D : public ShaderParameter
	{
	private:
		uint32 m_Value;
		uint32 m_TextureNumber;

	public:
		ParamTexture2D(uint32 value, uint32 nameID, int32 location, uint32 texNumber)
			: ShaderParameter(nameID, TEXTURE2D, location), m_Value(value), m_TextureNumber(texNumber)
		{
		}

		void Bind() override
		{
			glActiveTexture(GL_TEXTURE0 + m_TextureNumber);
			glBindTexture(GL_TEXTURE_2D, m_Value);
			glUniform1i(m_Location, m_TextureNumber);
		}

		inline void SetValue(uint32 value) { m_Value = value; }
		inline void SetTextureNumber(uint32 texNumber) { m_TextureNumber = texNumber; }
	};
}
