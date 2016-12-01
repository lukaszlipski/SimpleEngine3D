#include "win32_input.h"

namespace SE3D {

	bool Win32_Input::getKey(const char key)
	{
		if (key < 1024 && key >= 0)
			return m_Keyboard[key];
		return false;
	}

	bool Win32_Input::getMouseButton(byte mouse)
	{
		if(mouse < 4 && mouse >=0)
			return m_Mouse[mouse];
		return false;
	}

	int16 Win32_Input::getMousePositionX()
	{
		return m_MousePositionX;
	}

	int16 Win32_Input::getMousePositionY()
	{
		return m_MousePositionY;
	}

	void Win32_Input::ProcessInput(MSG Message)
	{

		switch (Message.message)
		{
		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
		case WM_KEYDOWN:
		case WM_KEYUP:
		{
			UINT32 key = (UINT32)Message.wParam;
			bool wasDown = (Message.lParam & (1 << 30)) != 0;
			bool isDown = (Message.lParam & (1 << 31)) == 0;

			if (isDown != wasDown)
			{
				m_Keyboard[key] = isDown;
			}
			break;
		}
		case WM_LBUTTONDOWN:
		{
			m_Mouse[0] = true;
			break;
		}
		case WM_MBUTTONDOWN:
		{
			m_Mouse[2] = true;
			break;
		}
		case WM_RBUTTONDOWN:
		{
			m_Mouse[1] = true;
			break;
		}
		case WM_LBUTTONUP:
		{
			m_Mouse[0] = false;
			break;
		}
		case WM_MBUTTONUP:
		{
			m_Mouse[2] = false;
			break;
		}
		case WM_RBUTTONUP:
		{
			m_Mouse[1] = false;
			break;
		}
		case WM_MOUSEMOVE:
		{
			m_MousePositionX = static_cast<int16>(Message.lParam);
			m_MousePositionY = static_cast<int16>(Message.lParam >> 16);
			break;
		}

		}


	}
}