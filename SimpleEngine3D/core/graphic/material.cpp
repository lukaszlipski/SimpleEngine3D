#include "material.h"
#include "../utilities/string.h"
#include "../math/matrix4d.h"
#include "shader_params/param_matrix4d.h"

namespace SE3D
{
	Material::Material(const Shader& shader)
		: m_Shader(shader)
	{
	}

	void Material::Bind() const
	{
		m_Shader.Bind();
		for (uint32 i = 0; i < m_Params.Size(); i++)
		{
			m_Params[i]->Bind();
		}
	}

	void Material::Unbind() const
	{
		m_Shader.Unbind();
	}

	bool Material::SetParamMatrix4D(uint32 nameID, const Matrix4D& value)
	{
		for (uint32 i = 0; i < m_Params.Size(); i++)
		{
			if (m_Params[i]->GetNameID() == nameID && m_Params[i]->GetParamType() == MATRIX4D)
			{
				static_cast<ParamMatrix4D*>(m_Params[i])->SetValue(value);
				return true;
			}
		}
		int32 location;
		if ((location = m_Shader.CheckParam(nameID, MATRIX4D)) >= 0)
		{
			ParamMatrix4D* param = new ParamMatrix4D(value);
			param->SetLocation(location);
			m_Params.Push(param);
			return true;
		}
		return false;
	}
}
