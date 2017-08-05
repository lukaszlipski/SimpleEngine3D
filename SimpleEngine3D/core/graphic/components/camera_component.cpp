#include "camera_component.h"
#include "../system/graphics.h"

namespace SE3D
{
	CameraComponent::CameraComponent(Frustum frustum)
		: m_CameraFrustum(frustum)
	{
		m_Projection = Matrix4D::Perspective(frustum.GetAngle(), frustum.GetRatio(), frustum.GetNearPlane(), frustum.GetFarPlane());
	}

	Matrix4D CameraComponent::GetView() const
	{
		return Matrix4D::TranslateMatrix(m_Owner->GetPosition() * -1 - m_Owner->GetRotation().GetForward()) * m_Owner->GetRotation().Conjugate().ToRotationMatrix();
	}

	void CameraComponent::Init() {}
	void CameraComponent::Input(float DeltaTime) {}
	
	void CameraComponent::Update(float DeltaTime) {
		m_CameraFrustum.UpdateCameraFrustum(m_Owner->GetPosition(), m_Owner->GetRotation().GetForward(), m_Owner->GetRotation().GetRight());
	}

	void CameraComponent::Render(DeferredRenderer *renderer) {}

}
