#pragma once
#include "component.h"

namespace SE3D
{
	class MovementComponent : public Component
	{
	private:
		bool m_FirstMouseUsage;
		float m_Sensitivity;
		float m_Speed;
		Vector3D m_Up;

	public:
		MovementComponent(float speed=2.0f, float sensitivity=5.0f);

		void Init() override;
		void Input(float DeltaTime) override;
		void Update(float DeltaTime) override;
		void Render(DeferredRenderer *renderer) override;

	};
}
