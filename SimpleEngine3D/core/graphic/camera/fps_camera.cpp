#include "fps_camera.h"
#include "../../system/window.h"
#include "../../system/input.h"
#include "../../math/math.h"
#include "../../system/global_timer.h"

namespace SE3D
{
	FPSCamera::FPSCamera(const Matrix4D& projection, const Vector3D& position, const Vector3D& front, const Vector3D& up)
		: Camera(projection, position, front, up), m_Yaw(90), m_Pitch(0), m_MouseSensitivity(0.4f), m_Speed(2), m_FirstMouseUsage(true)
	{
		Window::GetInstance().SetCursor(false);
	}

	void FPSCamera::Update()
	{
		int32 centerX = static_cast<int32>(Window::GetInstance().GetSizeX() / 2.0f);
		int32 centerY = static_cast<int32>(Window::GetInstance().GetSizeY() / 2.0f);
		int32 x;
		int32 y;
		if (!m_FirstMouseUsage)
		{
			x = Input::GetInstance().GetMousePositionX();
			y = Input::GetInstance().GetMousePositionY();
		}
		else
		{
			x = centerX;
			y = centerY;
			m_FirstMouseUsage = false;
		}
		Input::GetInstance().SetMousePosition(centerX, centerY);
		x = (x - centerX);
		y = (centerY - y);

		if (x * x != 1)
			m_Yaw += x * this->m_MouseSensitivity;
		if (y * y != 1)
			m_Pitch += y * this->m_MouseSensitivity;

		m_Front.x = static_cast<float>(cos(ToRadians(m_Yaw)) * cos(ToRadians(m_Pitch)));
		m_Front.y = static_cast<float>(sin(ToRadians(m_Pitch)));
		m_Front.z = static_cast<float>(sin(ToRadians(m_Yaw)) * cos(ToRadians(m_Pitch)));
		m_Front = m_Front.Normalize();
		m_Right = m_Front.Cross(m_WorldUp).Normalize();
		m_Up = m_Right.Cross(m_Front).Normalize();

		Vector3D direction = {};
		if (Input::GetInstance().GetKey('W'))
			direction += m_Front;
		if (Input::GetInstance().GetKey('S'))
			direction -= m_Front;
		if (Input::GetInstance().GetKey('A'))
			direction -= m_Right;
		if (Input::GetInstance().GetKey('D'))
			direction += m_Right;

		if (direction != Vector3D(0, 0, 0))
			m_Position += direction.Normalize() * m_Speed * GlobalTimer::GetInstance().DeltaTime();
	}
}
