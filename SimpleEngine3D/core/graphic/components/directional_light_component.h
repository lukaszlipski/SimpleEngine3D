#pragma once
#include "base_light.h"
#include "component.h"

namespace SE3D
{
	class DirectionalLightComponent : public BaseLight, public Component
	{
	private:
		Vector3D m_Direction;
		uint32 m_DirectionNameID;

	public:
		DirectionalLightComponent(const Vector3D& direction);

		inline void SetDirection(const Vector3D& direction) { m_Direction = direction; }
		inline Vector3D GetDirection() const { return m_Direction; }

		void Init() override;
		void Input(float DeltaTime) override;
		void Update(float DeltaTime) override;
		void Render(DeferredRenderer* renderer) override;
	};
}
