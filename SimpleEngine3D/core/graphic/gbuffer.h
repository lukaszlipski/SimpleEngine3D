#pragma once
#include "../utilities/types.h"
#include "texture2d.h"
#include "../math/vector4d.h"

namespace SE3D
{
	class GBuffer
	{
	private:
		int32 m_Width;
		int32 m_Height;
		uint32 m_GBuffer;
		uint32 m_DepthStencil;
		Texture2D m_Position;
		Texture2D m_Normal;
		Texture2D m_Albedo;
		Texture2D m_MetallicRoughnessAO;
		Vector4D m_ClearColor;

	public:
		GBuffer();
		~GBuffer();
		void Bind() const;
		void Unbind() const;
		void Clear();

		inline void SetClearColor(Vector4D color) { m_ClearColor = color; }
		inline Texture2D& GetPositionBuffer() { return m_Position; }
		inline Texture2D& GetNormalBuffer() { return m_Normal; }
		inline Texture2D& GetAlbedoBuffer() { return m_Albedo; }
		inline Texture2D& GetMetallicRoughnessAOBuffer() { return m_MetallicRoughnessAO; }
		inline int32 GetWidth() const { return m_Width; }
		inline int32 GetHeight() const { return m_Height; }

	};
}
