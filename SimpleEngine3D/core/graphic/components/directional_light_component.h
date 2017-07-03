#pragma once
#include "base_light.h"
#include "component.h"
#include "..\shadow_buffer.h"

#define SE3D_SHADOW_MAP_1 4096

namespace SE3D
{
	class DirectionalLightComponent : public BaseLight, public Component
	{
	private:
		Vector3D m_Direction;
		uint32 m_DirectionNameID;
		ShadowBuffer m_ShadowBuffer;
		Material m_ShadowMaterial;
		Matrix4D m_Projection;
		Matrix4D m_View;
		uint32 m_ProjectionNameID;
		uint32 m_ViewNameID;
		uint32 m_ModelNameID;
		uint32 m_ShadowMapNameID;
		float m_Size;

	public:
		DirectionalLightComponent(const Vector3D& direction = Vector3D(0,-1,0), float size = 10);

		inline void SetDirection(const Vector3D& direction) { m_Direction = direction; }
		inline Vector3D GetDirection() const { return m_Direction; }

		void Init() override;
		void Input(float DeltaTime) override;
		void Update(float DeltaTime) override;
		void Render(DeferredRenderer* renderer) override;
		void RenderShadowMap(DeferredRenderer* renderer) override;

	};
}
