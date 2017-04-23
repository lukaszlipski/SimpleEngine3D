#pragma once
#include "shader.h"
#include "shader_params/shader_parameter.h"
#include "../utilities/string.h"
#include "texture2d.h"

#define DEFAULT_VS_SHADER "default.vs"
#define DEFAULT_FS_SHADER "default.fs"

#define DEFAULT_ALBEDO_NAME "u_albedo"
#define DEFAULT_NORMAL_NAME "u_normal"
#define DEFAULT_METALLIC_NAME "u_metallic"
#define DEFAULT_ROUGHNESS_NAME "u_roughness"
#define DEFAULT_AMBIENT_OCCLUSION_NAME "u_ambientOcclusion"
#define DEFAULT_HEIGHT_NAME "u_height"

namespace SE3D
{
	class Mesh;
	struct Vector4D;
	struct Vector3D;
	struct Vector2D;
	struct Matrix3D;
	struct Matrix4D;

	class Material
	{
	private:
		Shader* m_Shader;
		uint32 m_TexturesCounter;
		DynamicArray<ShaderParameter*> m_Params;
		uint32 m_AlbedoNameID;
		uint32 m_NormalNameID;
		uint32 m_MetallicNameID;
		uint32 m_RoughnessNameID;
		uint32 m_AmbientOcclusionNameID;
		uint32 m_HeightNameID;

	public:
		Material();
		Material(const Material& material);
		Material(const String& vertShader, const String& fragShader);
		~Material();

		void Bind() const;
		void Unbind() const;

		bool SetParamBool(uint32 nameID, bool value);
		bool SetParamFloat(uint32 nameID, float value);
		bool SetParamInt32(uint32 nameID, int32 value);
		bool SetParamUInt32(uint32 nameID, uint32 value);
		bool SetParamVector2D(uint32 nameID, const Vector2D& value);
		bool SetParamVector3D(uint32 nameID, const Vector3D& value);
		bool SetParamVector4D(uint32 nameID, const Vector4D& value);
		bool SetParamMatrix3D(uint32 nameID, const Matrix3D& value);
		bool SetParamMatrix4D(uint32 nameID, const Matrix4D& value);
		bool SetParamTexture2D(uint32 nameID, const String& path, bool srgb = false);
		bool SetParamTexture2D(uint32 nameID, const Texture2D& texture);

		Material& operator=(const Material& right);

	private:
		void SetDefaultParams();

	};
}