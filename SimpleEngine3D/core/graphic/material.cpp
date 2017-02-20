#include "material.h"
#include "../utilities/string.h"
#include "../math/matrix4d.h"
#include "shader_params/param_matrix4d.h"
#include "shader_params/param_matrix3d.h"
#include "shader_params/param_uint32.h"
#include "shader_params/param_int32.h"
#include "shader_params/param_float.h"
#include "shader_params/param_bool.h"
#include "../system/shader_manager.h"
#include "shader_params/param_texture2d.h"
#include "../system/texture_manager.h"

namespace SE3D
{
	Material::Material(const String& vertShader, const String& fragShader)
	{
		m_Shader = ShaderManager::GetInstance().Get(vertShader, fragShader);
		m_TexturesCounter = 0;
	}

	Material::~Material()
	{
		for (uint32 i = 0; i < m_Params.Size(); i++)
		{
			delete m_Params[i];
		}
	}

	void Material::Bind() const
	{
		m_Shader->Bind();
		for (uint32 i = 0; i < m_Params.Size(); i++)
		{
			m_Params[i]->Bind();
		}
	}

	void Material::Unbind() const
	{
		m_Shader->Unbind();
	}

	bool Material::SetParamBool(uint32 nameID, bool value)
	{
		for (uint32 i = 0; i < m_Params.Size(); i++)
		{
			if (m_Params[i]->GetNameID() == nameID && m_Params[i]->GetParamType() == BOOL)
			{
				static_cast<ParamBool*>(m_Params[i])->SetValue(value);
				return true;
			}
		}
		int32 location;
		if ((location = m_Shader->CheckParam(nameID, BOOL)) >= 0)
		{
			ParamBool* param = new ParamBool(value, nameID, location);
			m_Params.Push(param);
			return true;
		}
		return false;
	}

	bool Material::SetParamFloat(uint32 nameID, float value)
	{
		for (uint32 i = 0; i < m_Params.Size(); i++)
		{
			if (m_Params[i]->GetNameID() == nameID && m_Params[i]->GetParamType() == FLOAT)
			{
				static_cast<ParamFloat*>(m_Params[i])->SetValue(value);
				return true;
			}
		}
		int32 location;
		if ((location = m_Shader->CheckParam(nameID, FLOAT)) >= 0)
		{
			ParamFloat* param = new ParamFloat(value, nameID, location);
			m_Params.Push(param);
			return true;
		}
		return false;
	}

	bool Material::SetParamInt32(uint32 nameID, int32 value)
	{
		for (uint32 i = 0; i < m_Params.Size(); i++)
		{
			if (m_Params[i]->GetNameID() == nameID && m_Params[i]->GetParamType() == INT32)
			{
				static_cast<ParamInt32*>(m_Params[i])->SetValue(value);
				return true;
			}
		}
		int32 location;
		if ((location = m_Shader->CheckParam(nameID, INT32)) >= 0)
		{
			ParamInt32* param = new ParamInt32(value, nameID, location);
			m_Params.Push(param);
			return true;
		}
		return false;
	}

	bool Material::SetParamUInt32(uint32 nameID, uint32 value)
	{
		for (uint32 i = 0; i < m_Params.Size(); i++)
		{
			if (m_Params[i]->GetNameID() == nameID && m_Params[i]->GetParamType() == UINT32)
			{
				static_cast<ParamUInt32*>(m_Params[i])->SetValue(value);
				return true;
			}
		}
		int32 location;
		if ((location = m_Shader->CheckParam(nameID, UINT32)) >= 0)
		{
			ParamUInt32* param = new ParamUInt32(value, nameID, location);
			m_Params.Push(param);
			return true;
		}
		return false;
	}

	bool Material::SetParamMatrix3D(uint32 nameID, const Matrix3D& value)
	{
		for (uint32 i = 0; i < m_Params.Size(); i++)
		{
			if (m_Params[i]->GetNameID() == nameID && m_Params[i]->GetParamType() == MATRIX3D)
			{
				static_cast<ParamMatrix3D*>(m_Params[i])->SetValue(value);
				return true;
			}
		}
		int32 location;
		if ((location = m_Shader->CheckParam(nameID, MATRIX3D)) >= 0)
		{
			ParamMatrix3D* param = new ParamMatrix3D(value, nameID, location);
			m_Params.Push(param);
			return true;
		}
		return false;
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
		if ((location = m_Shader->CheckParam(nameID, MATRIX4D)) >= 0)
		{
			ParamMatrix4D* param = new ParamMatrix4D(value, nameID, location);
			m_Params.Push(param);
			return true;
		}
		return false;
	}

	bool Material::SetTexture2D(uint32 nameID, const String& path)
	{
		for (uint32 i = 0; i < m_Params.Size(); i++)
		{
			if (m_Params[i]->GetNameID() == nameID && m_Params[i]->GetParamType() == TEXTURE2D)
			{
				static_cast<ParamTexture2D*>(m_Params[i])->SetValue(TextureManager::GetInstance().Get(path)->GetTextureID());
				return true;
			}
		}
		int32 location;
		if ((location = m_Shader->CheckParam(nameID, TEXTURE2D)) >= 0)
		{
			ParamTexture2D* param = new ParamTexture2D(TextureManager::GetInstance().Get(path)->GetTextureID(), nameID, location, m_TexturesCounter++);
			m_Params.Push(param);
			return true;
		}
		return false;
	}
}
