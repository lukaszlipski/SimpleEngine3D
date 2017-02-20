#pragma once
#include "shader.h"
#include "shader_params/shader_parameter.h"
#include "../utilities/string.h"

namespace SE3D
{
	struct Matrix3D;
	struct Matrix4D;

	class Material
	{
	private:
		Shader* m_Shader;
		DynamicArray<ShaderParameter*> m_Params;
		uint32 m_TexturesCounter;

	public:
		Material(const String& vertShader, const String& fragShader);
		~Material();

		void Bind() const;
		void Unbind() const;

		bool SetParamBool(uint32 nameID, bool value);
		bool SetParamFloat(uint32 nameID, float value);
		bool SetParamInt32(uint32 nameID, int32 value);
		bool SetParamUInt32(uint32 nameID, uint32 value);
		bool SetParamMatrix3D(uint32 nameID, const Matrix3D& value);
		bool SetParamMatrix4D(uint32 nameID, const Matrix4D& value);
		bool SetTexture2D(uint32 nameID, const String& path);
	};
}
