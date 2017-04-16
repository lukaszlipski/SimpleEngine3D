#include "movement_component.h"
#include "../../system/window.h"
#include "../../system/input.h"
#include "../../math/math.h"

namespace SE3D
{
	MovementComponent::MovementComponent(float speed, float sensitivity)
		: m_FirstMouseUsage(false), m_Sensitivity(sensitivity), m_Speed(speed), m_Up(Vector3D(0.0f,1.0f,0.0f))
	{
	}

	void MovementComponent::Init()
	{
		Window::GetInstance().SetCursor(false);
	}

	void MovementComponent::Input(float DeltaTime)
	{
		int32 centerX = static_cast<int32>(Window::GetInstance().GetSizeX() / 2.0f);
		int32 centerY = static_cast<int32>(Window::GetInstance().GetSizeY() / 2.0f);
		int32 x;
		int32 y;
		if (m_FirstMouseUsage)
		{
			x = Input::GetInstance().GetMousePositionX();
			y = Input::GetInstance().GetMousePositionY();
		}
		else
		{
			x = centerX;
			y = centerY;
			m_FirstMouseUsage = true;
		}
		Input::GetInstance().SetMousePosition(centerX, centerY);
		x = centerX - x;
		y = centerY - y;

		Quaternion ownerRot = m_Owner->GetRotation();

		Vector3D direction = {};
		if (Input::GetInstance().GetKey('W'))
			direction += ownerRot.GetForward();
		if (Input::GetInstance().GetKey('S'))
			direction -= ownerRot.GetForward();
		if (Input::GetInstance().GetKey('A'))
			direction -= ownerRot.GetRight();
		if (Input::GetInstance().GetKey('D'))
			direction += ownerRot.GetRight();
		
		if (direction != Vector3D(0, 0, 0))
			m_Owner->SetPosition(m_Owner->GetPosition() + direction.Normalize() * m_Speed * DeltaTime);

		Quaternion rotX;
		Quaternion rotY;
		if (abs(x) > 1)
		{
			rotX = Quaternion(m_Up, x * m_Sensitivity * DeltaTime);
		}
		if(abs(y) > 1)
		{
			rotY = Quaternion(ownerRot.GetForward().Cross(m_Up), y * m_Sensitivity * DeltaTime);
		}
		m_Owner->SetRotation(rotX * rotY * m_Owner->GetRotation() );
		
	}

	void MovementComponent::Update(float DeltaTime) {}
	void MovementComponent::Render(DeferredRenderer *renderer) {}
}
