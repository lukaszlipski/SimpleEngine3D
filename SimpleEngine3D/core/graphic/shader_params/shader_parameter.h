#pragma once
#include "../utilities/types.h"
#include "../shader.h"

namespace SE3D
{
	class ShaderParameter
	{
	protected:
		uint32 m_NameID;
		int32 m_Location;
		ParamType m_Type;
	public:
		virtual ~ShaderParameter() = default;
		virtual void Bind() = 0;
		virtual void SetLocation(int32 location) { m_Location = location; }
		virtual uint32 GetNameID() const { return m_NameID; }
		virtual ParamType GetParamType() const { return m_Type; }
	};
}
