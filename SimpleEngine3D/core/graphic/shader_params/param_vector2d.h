#pragma once
#include "shader_parameter.h"
#include "../../math/vector2d.h"

namespace SE3D
{
	class ParamVector2D : public ShaderParameter
	{
	private:
		Vector2D m_Value;
	public:
		ParamVector2D(Vector2D value, uint32 nameID, int32 location)
			: ShaderParameter(nameID, VECTOR2D, location), m_Value(value)
		{
		}

		void Bind() override
		{
			glUniform2f(m_Location, m_Value.x, m_Value.y);
		}

		inline void SetValue(Vector2D value) { m_Value = value; }
		inline Vector2D GetValue() const { return m_Value; }
	};
}
