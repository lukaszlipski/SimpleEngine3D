#pragma once
#include "../system/graphics.h"
#include "../utilities/types.h"
#include "../containers/dynamic_array.h"

namespace SE3D
{
	class String;

	enum ParamType
	{
		FLOAT = GL_FLOAT,
		VECTOR2D = GL_FLOAT_VEC2,
		VECTOR3D = GL_FLOAT_VEC3,
		VECTOR4D = GL_FLOAT_VEC4,
		INT32 = GL_INT,
		UINT32 = GL_UNSIGNED_INT,
		BOOL = GL_BOOL,
		MATRIX4D = GL_FLOAT_MAT4,
		MATRIX3D = GL_FLOAT_MAT3,
		//Matrix2D = GL_FLOAT_MAT2,
		TEXTURE2D = GL_SAMPLER_2D
	};

	struct ShaderParam
	{
		uint32 m_ParamID;
		ParamType m_Type;
		int32 m_Location;
	};

	class Shader
	{
	private:
		GLuint m_Program;
		bool m_IsValid;
		DynamicArray<ShaderParam> m_Uniforms;
	public:
		Shader(const String& filePathVS, const String& filePathFS);
		~Shader();
		void Bind() const;
		void Unbind() const;

		uint32 GetProgram() const { return m_Program; }
		int32 CheckParam(uint32 paramID, ParamType type) const;

		inline uint32 GetNumberOfParams() const { return m_Uniforms.Size(); }
		inline uint32 GetParamID(uint32 index) const { return m_Uniforms[index].m_ParamID; }
		inline ParamType GetParamType(uint32 index) const { return m_Uniforms[index].m_Type; }
		inline bool IsValid() const { return m_IsValid; }
	private:
		void GetAllUniforms();
	};
}
