#include "input.h"

namespace SE3D
{
	bool Input::GetKey(const char key)
	{
		if (key < SE3D_KEYBOARD_KEYS && key >= 0)
			return m_Keyboard[key];
		return false;
	}

	bool Input::GetMouseButton(byte mouse)
	{
		if (mouse < SE3D_MOUSE_BUTTONS && mouse >= 0)
			return m_Mouse[mouse];
		return false;
	}

	int16 Input::GetMousePositionX() const
	{
		return m_MousePositionX;
	}

	int16 Input::GetMousePositionY() const
	{
		return m_MousePositionY;
	}

	bool Input::Startup()
	{
		for (uint16 i = 0; i < SE3D_KEYBOARD_KEYS; i++)
		{
			m_Keyboard[i] = false;
		}
		for (uint16 i = 0; i < SE3D_MOUSE_BUTTONS; i++)
		{
			m_Mouse[i] = false;
		}
		m_MousePositionX = 0;
		m_MousePositionY = 0;
		return true;
	}

	void Input::Shutown()
	{
	}
}
