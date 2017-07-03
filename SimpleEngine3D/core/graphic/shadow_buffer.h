#pragma 
#include "..\utilities\types.h"
#include "texture2d.h"

namespace SE3D
{
	class ShadowBuffer
	{
	private:
		uint32 m_ShadowBuffer;
		Texture2D m_DepthMap;
		int32 m_Width;
		int32 m_Height;

	public:
		ShadowBuffer(int32 width, int32 height);
		~ShadowBuffer();

		void Bind() const;
		void Unbind() const;
		void Clear() const;

		inline Texture2D& GetTexture() { return m_DepthMap; }
		inline int32 GetWidth() const { return m_Width; }
		inline int32 GetHeight() const { return m_Height; }
	};
}