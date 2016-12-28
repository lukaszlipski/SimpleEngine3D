#include <Windows.h>
#include "../system/input.h"
#include "../system/window.h"

namespace SE3D {

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

			TranslateMessage(&Message);
			DispatchMessageA(&Message);
		}
	}

}