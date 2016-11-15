#pragma once
#include <Windows.h>

class Win32_Input {

private:
	bool m_Keyboard[1024];
	bool m_Mouse[3];
	short m_MousePositionX;
	short m_MousePositionY;


public:
	void ProcessInput(MSG Message);
	bool getKey(const char key);
	bool getMouseButton(byte mouse);

	short getMousePositionX();
	short getMousePositionY();

};