#include "win32_input.h"


void Win32_Input::setKey(const char key, bool isPressed)
{
	if (key < 1024 && key >= 0)
		m_Keyboard[key] = isPressed;
}

bool Win32_Input::getKey(const char key)
{
	if (key < 1024 && key >= 0)
		return m_Keyboard[key];
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
			setKey(key,isDown);
		}
	}
	}


}