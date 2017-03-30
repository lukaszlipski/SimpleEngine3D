#pragma once
#include "base_light.h"
#include "component.h"

namespace SE3D
{
	class PointLightComponent : public BaseLight, public Component
	{
	private:
		Vector3D m_Position;
		float m_Constant;
		float m_Linear;
		float m_Quadratic;
		uint32 m_ConstantID;
		uint32 m_LinearID;
		uint32 m_QuadraticID;
		uint32 m_PositionNameID;


	public:
		PointLightComponent(const Vector3D& position);

		void Init() override;
		void Input(float DeltaTime) override;
		void Update(float DeltaTime) override;
		void Render(DeferredRenderer* renderer) override;

	private:
		void SetParams();
	};
}
