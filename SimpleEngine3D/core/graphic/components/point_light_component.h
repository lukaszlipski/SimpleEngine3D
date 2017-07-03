#pragma once
#include "base_light.h"
#include "component.h"

namespace SE3D
{
	class PointLightComponent : public BaseLight, public Component
	{
	private:
		Vector3D m_Position;
		float m_Radius;
		uint32 m_RadiusNameID;
		uint32 m_PositionNameID;


	public:
		PointLightComponent(const Vector3D& position = Vector3D(0,0,0), float radius = 5.0f);

		inline void SetPosition(const Vector3D& pos) { m_Position = pos; }
		inline Vector3D GetPosition() const { return m_Position; }

		void Init() override;
		void Input(float DeltaTime) override;
		void Update(float DeltaTime) override;
		void Render(DeferredRenderer* renderer) override;
		void RenderShadowMap(DeferredRenderer* renderer) override;

	private:
		void SetParams();
	};
}
