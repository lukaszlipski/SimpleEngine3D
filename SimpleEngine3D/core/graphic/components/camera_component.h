#pragma once
#include "../../math/matrix4d.h"
#include "component.h"

namespace SE3D
{
	class CameraComponent : public Component
	{
	private:
		Matrix4D m_Projection;

	public:
		CameraComponent(Matrix4D projection);
		Matrix4D GetView() const;
		inline Matrix4D GetProjection() const { return m_Projection; }
		Vector3D GetPosition() const { return m_Owner->GetPosition(); }

		void Init() override;
		void Input(float DeltaTime) override;
		void Update(float DeltaTime) override;
		void Render(DeferredRenderer *renderer) override;

	};
}
