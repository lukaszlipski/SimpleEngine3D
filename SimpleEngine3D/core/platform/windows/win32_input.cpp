#include <Windows.h>
#include "../system/input.h"
#include "../system/window.h"

namespace SE3D
{
	void Input::Update()
	{
		MSG Message;
		while (PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
		{
			if (Message.message == WM_QUIT)
				Window::GetInstance().CloseWindow();

			switch (Message.message)
			{
			case WM_SYSKEYDOWN:
			case WM_SYSKEYUP:
			case WM_KEYDOWN:
			case WM_KEYUP:
				{
					UINT32 key = static_cast<UINT32>(Message.wParam);
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
				/*case WM_MOUSEMOVE:
					{
						
						break;
					}*/
			}

			TranslateMessage(&Message);
			DispatchMessageA(&Message);
		}

		POINT coursorCoords;
		GetCursorPos(&coursorCoords);
		ScreenToClient(Window::GetInstance().GetWindowHandle(), &coursorCoords);
		m_MousePositionX = coursorCoords.x;
		m_MousePositionY = coursorCoords.y;
	}

	void Input::SetMousePosition(const Vector2D& position) const
	{
		POINT coursorCoords = {static_cast<LONG>(position.x), static_cast<LONG>(position.y)};
		ClientToScreen(Window::GetInstance().GetWindowHandle(), &coursorCoords);
		SetCursorPos(coursorCoords.x, coursorCoords.y);
	}

	void Input::SetMousePosition(uint32 x, uint32 y) const
	{
		POINT coursorCoords = {static_cast<LONG>(x), static_cast<LONG>(y)};
		ClientToScreen(Window::GetInstance().GetWindowHandle(), &coursorCoords);
		SetCursorPos(coursorCoords.x, coursorCoords.y);
	}
}
