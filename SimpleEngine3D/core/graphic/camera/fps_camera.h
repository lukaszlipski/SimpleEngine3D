#pragma once
#include "camera.h"

namespace SE3D
{
	class FPSCamera : public Camera
	{
	private:
		float m_Yaw;
		float m_Pitch;
		float m_MouseSensitivity;
		float m_Speed;
		bool m_FirstMouseUsage;

	public:
		FPSCamera(const Matrix4D& projection, const Vector3D& position = Vector3D(0, 0, 0), const Vector3D& front = Vector3D(0, 0, 1), const Vector3D& worldIp = Vector3D(0, 1, 0));
		
		void Update() override;

		void ChangeMouseSensitivity(float sensitivity) { m_MouseSensitivity = sensitivity; }
		float GetMouseSensitivity() const { return m_MouseSensitivity; }

	};
}