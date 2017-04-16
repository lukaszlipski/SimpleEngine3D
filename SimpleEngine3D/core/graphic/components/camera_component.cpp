#include "camera_component.h"

namespace SE3D
{
	CameraComponent::CameraComponent(Matrix4D projection)
		: m_Projection(projection)
	{
	}

	Matrix4D CameraComponent::GetView() const
	{
		return Matrix4D::TranslateMatrix(m_Owner->GetPosition() * -1) * m_Owner->GetRotation().Conjugate().ToRotationMatrix(); 
	}

	void CameraComponent::Init() {}
	void CameraComponent::Input(float DeltaTime) {}
	void CameraComponent::Update(float DeltaTime) {}
	void CameraComponent::Render(DeferredRenderer *renderer) {}

}
