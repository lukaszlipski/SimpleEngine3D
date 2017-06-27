#pragma once
#include "../../math/matrix4d.h"
#include "component.h"
#include "../math/frustum.h"

namespace SE3D
{
	class CameraComponent : public Component
	{
	private:
		Matrix4D m_Projection;
		Frustum m_CameraFrustum;

	public:
		CameraComponent(Frustum frustum);
		Matrix4D GetView() const;
		inline Matrix4D GetProjection() const { return m_Projection; }
		Vector3D GetPosition() const { return m_Owner->GetPosition(); }
		inline Frustum GetFrustum() const { return m_CameraFrustum; }

		void Init() override;
		void Input(float DeltaTime) override;
		void Update(float DeltaTime) override;
		void Render(DeferredRenderer *renderer) override;

	};
}
