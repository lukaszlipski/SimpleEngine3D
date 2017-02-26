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
#include "shader_params/param_vector2d.h"
#include "shader_params/param_vector3d.h"
#include "shader_params/param_vector4d.h"

namespace SE3D
{
	Material::Material(const String& vertShader, const String& fragShader)
	{
		m_Shader = ShaderManager::GetInstance().Get(vertShader, fragShader);
		m_TexturesCounter = 0;
	}

	Material::Material()
	{
		m_Shader = ShaderManager::GetInstance().Get(DEFAULT_VS_SHADER, DEFAULT_FS_SHADER);
		m_TexturesCounter = 0;
	}

	Material::Material(const Material& material)
	{
		*this = material;
	}

	Material::~Material()
	{
		m_Params.Clear(true);
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

	bool Material::SetParamVector2D(uint32 nameID, const Vector2D& value)
	{
		for (uint32 i = 0; i < m_Params.Size(); i++)
		{
			if (m_Params[i]->GetNameID() == nameID && m_Params[i]->GetParamType() == VECTOR2D)
			{
				static_cast<ParamVector2D*>(m_Params[i])->SetValue(value);
				return true;
			}
		}
		int32 location;
		if ((location = m_Shader->CheckParam(nameID, VECTOR2D)) >= 0)
		{
			ParamVector2D* param = new ParamVector2D(value, nameID, location);
			m_Params.Push(param);
			return true;
		}
		return false;
	}

	bool Material::SetParamVector3D(uint32 nameID, const Vector3D& value)
	{
		for (uint32 i = 0; i < m_Params.Size(); i++)
		{
			if (m_Params[i]->GetNameID() == nameID && m_Params[i]->GetParamType() == VECTOR3D)
			{
				static_cast<ParamVector3D*>(m_Params[i])->SetValue(value);
				return true;
			}
		}
		int32 location;
		if ((location = m_Shader->CheckParam(nameID, VECTOR3D)) >= 0)
		{
			ParamVector3D* param = new ParamVector3D(value, nameID, location);
			m_Params.Push(param);
			return true;
		}
		return false;
	}

	bool Material::SetParamVector4D(uint32 nameID, const Vector4D& value)
	{
		for (uint32 i = 0; i < m_Params.Size(); i++)
		{
			if (m_Params[i]->GetNameID() == nameID && m_Params[i]->GetParamType() == VECTOR4D)
			{
				static_cast<ParamVector4D*>(m_Params[i])->SetValue(value);
				return true;
			}
		}
		int32 location;
		if ((location = m_Shader->CheckParam(nameID, VECTOR4D)) >= 0)
		{
			ParamVector4D* param = new ParamVector4D(value, nameID, location);
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

	Material& Material::operator=(const Material& right)
	{
		m_Shader = right.m_Shader;
		m_TexturesCounter = right.m_TexturesCounter;
		for(uint32 i=0;i<right.m_Params.Size();i++)
		{
			ShaderParameter* param = right.m_Params[i];
			if (param->GetParamType() == FLOAT)
				m_Params.Push(new ParamFloat( static_cast<ParamFloat*>(param)->GetValue() , param->GetNameID(), param->GetLocation()));
			else if (param->GetParamType() == VECTOR2D)
				m_Params.Push(new ParamVector2D(static_cast<ParamVector2D*>(param)->GetValue(), param->GetNameID(), param->GetLocation()));
			else if (param->GetParamType() == VECTOR3D)
				m_Params.Push(new ParamVector3D(static_cast<ParamVector3D*>(param)->GetValue(), param->GetNameID(), param->GetLocation()));
			else if (param->GetParamType() == VECTOR4D)
				m_Params.Push(new ParamVector4D(static_cast<ParamVector4D*>(param)->GetValue(), param->GetNameID(), param->GetLocation()));
			else if (param->GetParamType() == INT32)
				m_Params.Push(new ParamInt32(static_cast<ParamInt32*>(param)->GetValue(), param->GetNameID(), param->GetLocation()));
			else if (param->GetParamType() == UINT32)
				m_Params.Push(new ParamUInt32(static_cast<ParamUInt32*>(param)->GetValue(), param->GetNameID(), param->GetLocation()));
			else if (param->GetParamType() == BOOL)
				m_Params.Push(new ParamBool(static_cast<ParamBool*>(param)->GetValue(), param->GetNameID(), param->GetLocation()));
			else if (param->GetParamType() == MATRIX4D)
				m_Params.Push(new ParamMatrix4D(static_cast<ParamMatrix4D*>(param)->GetValue(), param->GetNameID(), param->GetLocation()));
			else if (param->GetParamType() == MATRIX3D)
				m_Params.Push(new ParamMatrix3D(static_cast<ParamMatrix3D*>(param)->GetValue(), param->GetNameID(), param->GetLocation()));
			else if (param->GetParamType() == TEXTURE2D)
				m_Params.Push(new ParamTexture2D(static_cast<ParamTexture2D*>(param)->GetValue(), param->GetNameID(), param->GetLocation(), static_cast<ParamTexture2D*>(param)->GetTextureNumber()));
		}
		return *this;
	}
}
