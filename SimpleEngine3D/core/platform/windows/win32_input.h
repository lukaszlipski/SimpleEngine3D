#pragma once
#include <Windows.h>

class Win32_Input {

private:
	bool m_Keyboard[1024];
	bool m_Mouse[32];
	int m_MousePositionX;
	int m_MousePositionY;


public:
	void ProcessInput(MSG Message);

	void setKey(const char key, bool isPressed);
	bool getKey(const char key);

	void setMouseButton();
	bool getMouseButton();

	void setMousePositionX();
	int getMousePositionX();

	void setMousePositionY();
	int getMousePositionY();

};